# matrix_multiplication
Matrix multiplication written in C

This program contains two parts: the frontend CLI(command line interface) and the matrix multiplication algorithm.

# Run the program:
To generate the binary of this program, you simply run make command and there are 4 arguments being supported currently. They are 1: help 2: sparse (supporting sparse matrices) 3: matrix_x (input file for first_matrix) and 4: matrix_y (input file for second matrix)

A similar description will be displayed when you specify the help option. To specify the arguments, an example to do so is like the following:

```
make
./test --help
```

# Run one test to see correctness:
```
make
./matmul --matrix_x test/test_matrix.txt --matrix_y test/test_matrix_two.txt
```

Another test that is currently supported by this program is to display the
matrices in sparse form (coordinate wise):

```
make
./matmul -s --matrix_x test/test_sparse_matrix_x.txt --matrix_y test/test_sparse_matrix_y.txt
```

Note: therotically, any file format should work as long as it follows the matrix input format.
An example format of matrix can be seen in the test file:
E.g:

```
2 2
1 2
3 4
```

is a 2 x 2 matrix with ((1, 2) (3 , 4)) as values
