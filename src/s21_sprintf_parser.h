#ifndef _S21_SPRINTF_PARSER_H_
#define _S21_SPRINTF_PARSER_H_
#include <stdarg.h>

#include "s21_sprintf_funcs.h"

#define FLAG_STATE 0
#define WIDTH_STATE 1
#define PRECISION_STATE 2
#define LENGTH_STATE 3

int get_format_type(const char* format_string);
pattern init_pattern(int data_type);
void execute_pattern(int data_type, va_list* args, char* dst,
                     pattern executable_pattern);
void execute_int_pattern(int data_type, va_list* args, char* dst,
                         pattern executable_pattern);
void execute_unsigned_int_pattern(int data_type, va_list* args, char* dst,
                                  pattern executable_pattern);
pattern read_pattern(const char** format_string, pattern result);
int flag_set(char symbol, pattern* pattern_to_set);
int num_param_set(const char** str, int* param);
int length_set(char symbol, pattern* pattern_to_set);

#endif
