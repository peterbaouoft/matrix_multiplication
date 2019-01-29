#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int** sparse_matrix_wrapper(bool arg_sparse, int** X, int** Y, int x_rows, int x_cols, int y_rows, int y_cols);

struct sparseMatrix {
    int *column_vals;
    int *row_vals;
    int *value_arrs;
    int NNZ; // Number of non zeroes
};
