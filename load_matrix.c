#include <unistd.h>
#include "matrix_multiply.h"
#include <assert.h>
#include <getopt.h>
#include <errno.h>

static bool arg_sparse = false;
static const char *arg_first_file = NULL;
static const char *arg_second_file = NULL;

static int help(){
    // TODO: add help messages
    printf ("Test help!\n");
    return 0;
}

static int parse_argv(int argc, char *argv[]){
    enum {
        ARG_FIRST_FILE,
        ARG_SECOND_FILE,
    };

    static const struct option options[] = {
        { "help",       no_argument,        NULL,   'h'},
        { "sparse",     no_argument,        NULL,   's'},
        { "matrix_x",   required_argument,  NULL,   ARG_FIRST_FILE},
        { "matrix_y",   required_argument,  NULL,   ARG_SECOND_FILE},
        {}
    };

    int c;

    while ((c = getopt_long(argc, argv, "h::s::", options, NULL)) >= 0){
        switch (c){
        case 'h':
            return help();
        case 's':
            arg_sparse = true;
            printf("Test sparse\n");
            break;
        case ARG_FIRST_FILE:
            arg_first_file = optarg;
            break;
        case ARG_SECOND_FILE:
            arg_second_file = optarg;
            break;
        }
    }
    return 1;
}

static int load_file_into_matrix(const char *matrix_file_path,
                                 int      ***out_matrix,
                                 int        *out_rows,
                                 int        *out_cols){
    FILE *f = NULL;
    char *line = NULL;
    ssize_t read;
    size_t n_allocated = 0;
    int **matrix = NULL, rows = 0, cols = 0;

    int r;

    f = fopen(matrix_file_path, "r");
    if (!f){
        printf("Error, failed to open the file %s\n", matrix_file_path);
        return errno == ENOENT ? 0 : -errno;
    }

    // Process first line to get row and cols of the matrix
    read = getline(&line, &n_allocated, f);
    if (read < 0){
        printf("Error, failed to read the first line from file %s\n", matrix_file_path);
        return -1;
    }

    r = sscanf(line, "%d %d", &rows, &cols);
    if (r != 2) {
        printf("Error, row and column supposed to be specified in the first line of the file %s\n", matrix_file_path);
        return -1;
    }

    // Initialize the array via malloc
    matrix = (int **)malloc(rows * sizeof(int *));
    for (int row = 0; row < rows; row ++)
        matrix[row] = (int *) malloc(cols * sizeof(int));

    // Collect the remaining matrix information and put into the array
    for (int row = 0; row < rows; row++){
        read = getline(&line, &n_allocated, f);
        if (read < 0) {
            printf("Error, failed to read line number %d from file %s\n", row + 1, matrix_file_path);
            return -1;
        }

        // Use sscanf to read one number at a time, and use the offset to move to the next number
        for (int col = 0; col < cols; col++){
            int offset = 0;
            sscanf(line, "%d%n", &matrix[row][col], &offset);

            if (offset == 0) {
                printf("Error, cell value invalid in line %d from file %s \n", row + 1, matrix_file_path);
                return - 1;
            }
            line += offset;
        }
    }

    // Transfer the ownership
    *out_matrix = matrix;
    matrix = NULL;
    *out_rows = rows;
    *out_cols = cols;

    return 1;
}


static void printMatrix(int **matrix,
                        int         rows,
                        int         cols){

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            printf("%d ", matrix[row][col]);
        printf("\n");
    }
}

int main (int argc, char **argv){

    int r = parse_argv(argc, argv);
    if (r <= 0)
        return r;

    if (arg_first_file == NULL || arg_second_file == NULL) {
        printf("Error: You need to specify two input matrix file to perform multiplication!\n");
        return 0;
    }

    int **matrix_x, x_rows, x_cols;
    int **matrix_y, y_rows, y_cols;

    r = load_file_into_matrix(arg_first_file, &matrix_x, &x_rows, &x_cols);
    if (r <= 0)
        return r;
    printf("Matrix x with %d rows and %d cols is loaded\n", x_rows, x_cols);
    printMatrix(matrix_x, x_rows, x_cols);

    r = load_file_into_matrix(arg_second_file, &matrix_y, &y_rows, &y_cols);
    if (r <= 0)
        return r;
    printf("============================================\n");
    printf("Matrix y with %d rows and %d cols is loaded\n", y_rows, y_cols);
    printMatrix(matrix_y, y_rows, y_cols);

    printf("============================================\n\n");

    int **result = sparse_matrix_wrapper(arg_sparse, matrix_x, matrix_y, x_rows, x_cols, y_rows, y_cols);
    printf("Thre resulting matrix is:\n");
    printMatrix(result, x_rows, y_cols);

    return 0;

    // TODO: free all of the values....
}

