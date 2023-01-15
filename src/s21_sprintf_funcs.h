#ifndef _S21_SPRINTF_FUNCS_H_
#define _S21_SPRINTF_FUNCS_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>

#include "s21_string.h"

#define NOT_VALID_RESULT -1
#define BASE_TYPES 5
#define TYPE_INT 0
#define TYPE_UNSIGNED_INT 1
#define TYPE_CHAR 2
#define TYPE_STRING 3
#define TYPE_FLOAT 4

#define TYPE_LONG_INT 5
#define TYPE_SHORT_INT 6
#define TYPE_LONG_UNSIGNED_INT 7
#define TYPE_SHORT_UNSIGNED_INT 8
#define TYPE_WCHAR 9

typedef struct flags {
  int plus_sgn;
  int minus_sgn;
  int space_char;
} flags;

typedef struct pattern {
  int type;
  flags pattern_flags;
  int precision;
  int width;
  char length;
  int pattern_is_ok;
} pattern;

void print_char(char symb, char* dst, int width, int right_padding);
void print_long_char(wchar_t symb, char* input_dst, int width,
                     int right_padding);
void print_string(char* string, char* dst, int precision, int width,
                  int left_padding);
void add_padding(int num, char* dst);
void print_int(void* number, int precision, int width, int right_padding,
               int plus_sgn, int minus_sgn, int space_symbol, char* dst,
               int type);
void int_to_chars(void* input, int number_length, char* array, int type);
s21_size_t number_length(void* input, int type);
int get_int_sign(void* number, int type);
int is_zero(void* number, int type);
void print_sign(int plus_sgn, int minus_sgn, int space_symbol, int sgn,
                char* dst);
void print_double(double num, int precision, int width, int right_padding,
                  int plus_sgn, int space_symbol, char* dst);
void print_whole_float(double num, char* dst);
void print_fractional_float(float fractional, int precision, int plus_sgn,
                            char* dst);
#endif
