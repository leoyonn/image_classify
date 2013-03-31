#include "svm.h"
#include <stdio.h>

#define CLASS_NUM 20
void predict(FILE * input, struct svm_model * model, int ** label);
static char* readline(FILE *input);
void exit_input_error(int line_num);