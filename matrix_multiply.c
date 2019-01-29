#include "matrix_multiply.h"

static int **matrix_multiply(int **X, int** Y, int x_rows, int x_cols, int y_rows, int y_cols){

    // Zero initialize all values using calloc
    int **result = (int **)malloc(x_rows * sizeof(int*));
    for (int row = 0; row < x_rows; row++)
       result[row] = (int *)calloc(y_cols, sizeof(int));

    // Case when both square matrix multiply
    if (x_rows == x_cols && x_rows == y_rows && y_rows == y_cols)
        // TODO: Use strassen's algorithm or Coppersmith–Winograd algorithm
        // Or other existing mechanisms for multiplying square matrices
        result = NULL;
    else {
        for (int row = 0; row < x_rows; row++)
            for (int col = 0; col < y_cols; col++)
                for (int shared_dim = 0; shared_dim < x_cols; shared_dim++)
                    result[row][col] += X[row][shared_dim] * Y[shared_dim][col];

    }

    return result;
}

static struct sparseMatrix generate_sparse_matrix(int **matrix, int rows, int cols){
    struct sparseMatrix result;
    int *column_vals = NULL, *row_vals = NULL, *value_arrs = NULL, NNZ = 0;

    // Assume matrix is already initialized
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            if (matrix[row][col] != 0)
                NNZ++;

    // Allocate corresponding arrays
    column_vals = (int *)calloc(NNZ, sizeof(int));
    row_vals = (int *)calloc(NNZ, sizeof(int));
    value_arrs = (int *)calloc(NNZ, sizeof(int));

    // Construct the generated sparse matrix
    int k = 0;
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            if (matrix[row][col] != 0){
                column_vals[k] = col;
                row_vals[k] = row;
                value_arrs[k] = matrix[row][col];
                k++;
            }

    result.column_vals = column_vals;
    result.row_vals = row_vals;
    result.value_arrs = value_arrs;
    result.NNZ = NNZ;

    return result;
}

void printSparseMatrix(struct sparseMatrix result){
    printf("row     col     value\n");

    for (int i = 0; i < result.NNZ; i++)
        printf("%d      %d      %d\n", result.row_vals[i], result.column_vals[i], result.value_arrs[i]);
}

int **sparse_matrix_wrapper(bool arg_sparse, int ** X, int** Y, int x_rows, int x_cols, int y_rows, int y_cols) {
    int **result = NULL;

    if (x_cols != y_rows){
        printf("Error: columns of matrix X mismatches with that of columns of Y\n");
        return NULL;
    }

    if (arg_sparse) {
        struct sparseMatrix converted_x = generate_sparse_matrix(X, x_rows, x_cols);
        struct sparseMatrix converted_y = generate_sparse_matrix(Y, y_rows, y_cols);

        printf("=======================Generated Sparse Matrix Representation for X============\n");
        printSparseMatrix(converted_x);
        printf("=======================Generated Sparse Matrix Representation for Y============\n");
        printSparseMatrix(converted_y);
        // result = sparse_matrix_multiply(&converted_x, &converted_y);
    } else {
        result = matrix_multiply(X, Y, x_rows, x_cols, y_rows, y_cols);
    }

    return result;
}
