#include "s21_sprintf_parser.h"

#include "s21_string.h"

int get_format_type(const char* format_string) {
  int result = NOT_VALID_RESULT;
  char correct_formats[] = "ducsfi";
  char* result_of_search = s21_strpbrk(format_string, correct_formats);
  if (result_of_search != NULL) {
    for (int i = 0; i < BASE_TYPES; i++) {
      if (*result_of_search == correct_formats[i]) {
        result = i;
      }
    }
  }
  if (*result_of_search == 'i') {
    result = TYPE_INT;
  }
  return result;
}

pattern init_pattern(int data_type) {
  pattern result;
  result.precision = 1;
  result.length = 'n';
  result.width = 0;
  result.pattern_flags.minus_sgn = 0;
  result.pattern_flags.plus_sgn = 0;
  result.pattern_flags.space_char = 0;
  result.pattern_is_ok = 1;
  result.type = data_type;
  switch (data_type) {
    case TYPE_STRING:
      result.precision = 0;
      result.width = -1;
      break;
    case TYPE_CHAR:
      result.width = -1;
      break;
    case TYPE_INT:
      result.width = -1;
      break;
    case TYPE_FLOAT:
      result.precision = 6;
      break;
    case TYPE_UNSIGNED_INT:
      result.pattern_flags.minus_sgn = 0;
      break;
  }
  return result;
}

void execute_pattern(int data_type, va_list* args, char* dst,
                     pattern executable_pattern) {
  char* str_arg;
  char char_arg;
  wchar_t wchar_arg;
  double double_arg;

  switch (data_type) {
    case TYPE_STRING:
      str_arg = va_arg(*args, char*);
      print_string(str_arg, dst, executable_pattern.precision,
                   executable_pattern.width,
                   executable_pattern.pattern_flags.minus_sgn);
      break;
    case TYPE_CHAR:
      if (executable_pattern.length == 'n') {
        char_arg = va_arg(*args, int);
        print_char(char_arg, dst, executable_pattern.width,
                   executable_pattern.pattern_flags.minus_sgn);
      } else if (executable_pattern.length == 'l') {
        wchar_arg = va_arg(*args, wchar_t);
        print_long_char(wchar_arg, dst);
      }
      break;
    case TYPE_INT:
      execute_int_pattern(data_type, args, dst, executable_pattern);
      break;
    case TYPE_FLOAT:
      double_arg = va_arg(*args, double);
      print_double(double_arg, executable_pattern.precision,
                   executable_pattern.width,
                   executable_pattern.pattern_flags.minus_sgn,
                   executable_pattern.pattern_flags.plus_sgn,
                   executable_pattern.pattern_flags.space_char, dst);
      break;
    case TYPE_UNSIGNED_INT:
      execute_unsigned_int_pattern(data_type, args, dst, executable_pattern);
      break;
  }
}

void execute_unsigned_int_pattern(int data_type, va_list* args, char* dst,
                                  pattern executable_pattern) {
  unsigned int uint_arg;
  unsigned long int long_uint_arg;
  unsigned short int short_uint_arg;
  if (executable_pattern.length == 'n') {
    uint_arg = va_arg(*args, unsigned int);
    print_int(&uint_arg, executable_pattern.precision, executable_pattern.width,
              executable_pattern.pattern_flags.minus_sgn, 0, 0, 0, dst,
              data_type);
  } else if (executable_pattern.length == 'l') {
    long_uint_arg = va_arg(*args, unsigned long int);
    print_int(&long_uint_arg, executable_pattern.precision,
              executable_pattern.width,
              executable_pattern.pattern_flags.minus_sgn, 0, 0, 0, dst,
              TYPE_LONG_UNSIGNED_INT);
  } else if (executable_pattern.length == 'h') {
    short_uint_arg = va_arg(*args, int);
    print_int(&short_uint_arg, executable_pattern.precision,
              executable_pattern.width,
              executable_pattern.pattern_flags.minus_sgn, 0, 0, 0, dst,
              TYPE_SHORT_UNSIGNED_INT);
  }
}

void execute_int_pattern(int data_type, va_list* args, char* dst,
                         pattern executable_pattern) {
  if (executable_pattern.length == 'n') {
    int int_arg = va_arg(*args, int);
    print_int(&int_arg, executable_pattern.precision, executable_pattern.width,
              executable_pattern.pattern_flags.minus_sgn,
              executable_pattern.pattern_flags.plus_sgn, 1,
              executable_pattern.pattern_flags.space_char, dst, data_type);
  } else if (executable_pattern.length == 'l') {
    long int long_int_arg = va_arg(*args, long int);
    print_int(&long_int_arg, executable_pattern.precision,
              executable_pattern.width,
              executable_pattern.pattern_flags.minus_sgn,
              executable_pattern.pattern_flags.plus_sgn, 1,
              executable_pattern.pattern_flags.space_char, dst, TYPE_LONG_INT);
  } else if (executable_pattern.length == 'h') {
    short int short_int_arg = va_arg(*args, int);
    print_int(&short_int_arg, executable_pattern.precision,
              executable_pattern.width,
              executable_pattern.pattern_flags.minus_sgn,
              executable_pattern.pattern_flags.plus_sgn, 1,
              executable_pattern.pattern_flags.space_char, dst, TYPE_SHORT_INT);
  }
}

pattern read_pattern(const char** format_string, pattern result) {
  int state = FLAG_STATE;
  const char* curr_ptr = *format_string;
  char correct_formats[] = "ducsfi";
  char* result_of_search = s21_strpbrk(curr_ptr, correct_formats);
  while (curr_ptr != result_of_search && result.pattern_is_ok) {
    int set_result = 0;
    if (state == FLAG_STATE) {
      set_result = flag_set(*curr_ptr, &result);
      if (!set_result) {
        state++;
      }
    }
    if (state <= WIDTH_STATE && !set_result) {
      set_result = num_param_set(&curr_ptr, &(result.width));
      state = PRECISION_STATE;
    }
    if (state <= PRECISION_STATE && !set_result) {
      if (*curr_ptr == '.' && result_of_search - curr_ptr > 1) {
        curr_ptr++;
        set_result = num_param_set(&curr_ptr, &(result.precision));
      }
      state = LENGTH_STATE;
    }
    if (state == LENGTH_STATE) {
      if (!set_result) {
        set_result = length_set(*curr_ptr, &result);
        state++;
      }
    }
    if (set_result) {
      curr_ptr++;
    } else {
      result.pattern_is_ok = 0;
    }
  }
  *format_string = curr_ptr;
  return result;
}

int flag_set(char symbol, pattern* pattern_to_set) {
  int result = 0;
  if (symbol == '+') {
    pattern_to_set->pattern_flags.plus_sgn = 1;
    result = 1;
  }
  if (symbol == '-') {
    pattern_to_set->pattern_flags.minus_sgn = 1;
    result = 1;
  }
  if (symbol == ' ') {
    pattern_to_set->pattern_flags.space_char = 1;
    result = 1;
  }
  return result;
}

int num_param_set(const char** str, int* param) {
  const char* curr_ptr = *str;
  int width = 0;
  int result = 0;
  while (*curr_ptr >= '0' && *curr_ptr <= '9') {
    width = width * 10 + *curr_ptr - '0';
    curr_ptr++;
  }
  if (curr_ptr != *str) {
    result = 1;
    *param = width;
    *str = curr_ptr - 1;
  }
  return result;
}

int length_set(char symbol, pattern* pattern_to_set) {
  int result = 0;
  if (symbol == 'l') {
    pattern_to_set->length = 'l';
    result = 1;
  }
  if (symbol == 'h') {
    pattern_to_set->length = 'h';
    result = 1;
  }
  return result;
}
