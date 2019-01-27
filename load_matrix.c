#include <unistd.h>
#include "matrix_multiply.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>


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
            printf("Test first file %s\n", optarg);
            break;
        case ARG_SECOND_FILE:
            arg_second_file = optarg;
            printf("Test second file %s\n", optarg);
            break;
        }
    }
    return 1;
}

int main (int argc, char **argv){

    int r = parse_argv(argc, argv);
    if (r <= 0)
        return r;

    if (arg_first_file == NULL || arg_second_file == NULL) {
        printf("Error: You need to specify two input matrix file to perform multiplication!\n");
        return 0;
    }
}

