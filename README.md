# matrix_multiplication
Matrix multiplication written in C

This program contains two parts: the frontend CLI(command line interface) and the matrix multiplication algorithm.

# Run the program:
Currently, you need to manually build the program via `gcc load_matrix.c -o ${your_file_name}`, and there are
4 arguments being supported currently. They are 1: help 2: sparse (supporting sparse matrices)
3: matrix_x (input file for first_matrix) and 4: matrix_y (input file for second matrix)

A similar description will be displayed when you specify the help option. To specify the arguments, an example to do
so is like the following:

```
gcc load_matrix.c -o test
./test --help
```

