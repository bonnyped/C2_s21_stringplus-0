#ifndef _S21_SPRINTF_PARSER_H_
#define _S21_SPRINTF_PARSER_H_
#include "s21_sprintf_funcs.h"
#include <stdarg.h>

#define FLAG_STATE 0
#define WIDTH_STATE 1
#define PRECISION_STATE 2
#define LENGTH_STATE 3

int s21_sprintf(char* dst, const char* format_string, ...);
int get_format_type(char* format_string);
pattern init_pattern(int data_type);
void execute_pattern(int data_type, va_list* args, char* dst, pattern executable_pattern);
void execute_int_pattern(int data_type, va_list* args, char* dst, pattern executable_pattern);
void execute_unsigned_int_pattern(int data_type, va_list* args, char* dst, pattern executable_pattern);
pattern read_pattern(char** format_string, pattern result);
int flag_set(char symbol, pattern* pattern_to_set);
int num_param_set(char** str, int* param);
int length_set(char symbol, pattern* pattern_to_set);

#endif

