all: matmul

matmul: load_matrix.o matrix_multiply.o
		gcc load_matrix.o matrix_multiply.o -o matmul

load_matrix.o: 	load_matrix.c
				gcc -c load_matrix.c

matrix_multiply.o: 	matrix_multiply.c
					gcc -c matrix_multiply.c
clean:
		rm -rf *o matmul
