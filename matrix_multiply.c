#include "matrix_multiply.h"

static int **matrix_multiply(int **X, int** Y, int x_rows, int x_cols, int y_rows, int y_cols){
    if (x_cols != y_rows){
        printf("Error: columns of matrix X mismatches with that of columns of Y\n");
        return NULL;
    }
    
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

int **sparse_matrix_wrapper(bool arg_sparse, int ** X, int** Y, int x_rows, int x_cols, int y_rows, int y_cols) {
    int **result = NULL;

    if (arg_sparse) {
        // sparseMatrix converted_x = generate_sparse_matrix(X, x_rows, x_cols);
        // sparseMatrix converted_y = generate_sparse_matrix(Y, y_rows, y_cols);
        // result = sparse_matrix_multiply(&converted_x, &converted_y);
    } else {
        result = matrix_multiply(X, Y, x_rows, x_cols, y_rows, y_cols);
    }

    return result;
}
