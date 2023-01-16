#include "s21_sprintf_funcs.h"

#include <math.h>
#include <stdlib.h>

#include "s21_string.h"

/*%% template
* DELETE 1, 0 FROM PRINT CHAR MAKE MACRO!
WCHAR_T

*/

void print_char(char symb, char* dst, int width, int right_padding) {
  char source[2];
  source[0] = symb;
  source[1] = 0;
  if (width > 1 && !right_padding) {
    add_padding(width - 1, dst);
  }
  s21_strcat(dst, source);
  if (width > 1 && right_padding) {
    add_padding(width - 1, dst);
  }
}
// NOT RDY YET
void print_long_char(wchar_t symb, char* input_dst) {
  wchar_t* dst = (wchar_t*)input_dst;
  wchar_t source[2];
  source[0] = symb;
  source[1] = 0;
  while (*dst != 0) {
    dst++;
  }
  s21_memcpy(dst, source, sizeof(wchar_t) * 2);
}

void add_padding(int num, char* dst) {
  for (int i = 0; i < num; i++) {
    print_char(' ', dst, 1, 0);
  }
}

void print_string(char* string, char* dst, int precision, int width,
                  int right_padding) {
  s21_size_t str_len;
  if (precision == 0) {
    str_len = s21_strlen(string);
  } else {
    str_len = precision;
  }
  if ((int)str_len < width && !right_padding) {
    add_padding(width - str_len, dst);
  }
  if (precision == 0) {
    s21_strcat(dst, string);
  } else {
    s21_strncat(dst, string, precision);
  }
  if ((int)str_len < width && right_padding) {
    add_padding(width - str_len, dst);
  }
}

// precision 0 number 0, widdth >0?
// minus sign width and prec check!!
void print_int(void* number, int precision, int width, int right_padding,
               int plus_sgn, int minus_sgn, int space_symbol, char* dst,
               int type) {
  s21_size_t array_len = number_length(number, type);
  char* array = s21_NULL;
  if (precision != 0 || (precision == 0 && !is_zero(number, type))) {
    array = malloc(sizeof(char) * array_len);
  }
  int number_sgn = get_int_sign(number, type);
  int printing_len = precision > (int)array_len ? precision : (int)array_len;
  printing_len += (plus_sgn || space_symbol || (minus_sgn && number_sgn == -1));
  if (width > printing_len && !right_padding) {
    add_padding(width - (printing_len), dst);
  }
  if (array != NULL) {
    int_to_chars(number, array_len, array, type);

    print_sign(plus_sgn, minus_sgn, space_symbol, number_sgn, dst);
    if (precision > 0 && precision > (int)array_len) {
      int difference = precision - (int)array_len;
      for (; difference > 0; difference--) {
        print_char('0', dst, 1, 0);
      }
    }
    for (int i = 0; i < (int)array_len; i++) {
      print_char(array[i], dst, 1, 0);
    }
    free(array);
  }
  if (width > printing_len && right_padding) {
    add_padding(width - (printing_len), dst);
  }
}

void int_to_chars(void* input, int number_length, char* array, int type) {
  int i = number_length - 1;
  if (type == TYPE_INT) {
    int number = *(int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + abs(digit);
      number /= 10;
    } while (number != 0);
  } else if (type == TYPE_LONG_INT) {
    long int number = *(long int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + abs(digit);
      number /= 10;
    } while (number != 0);
  } else if (type == TYPE_SHORT_INT) {
    short int number = *(short int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + abs(digit);
      number /= 10;
    } while (number != 0);
  } else if (type == TYPE_UNSIGNED_INT) {
    unsigned int number = *(unsigned int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + digit;
      number /= 10;
    } while (number != 0);
  } else if (type == TYPE_LONG_UNSIGNED_INT) {
    unsigned long int number = *(unsigned long int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + digit;
      number /= 10;
    } while (number != 0);
  } else if (type == TYPE_SHORT_UNSIGNED_INT) {
    unsigned short int number = *(unsigned short int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + digit;
      number /= 10;
    } while (number != 0);
  }
}

s21_size_t number_length(void* input, int type) {
  s21_size_t result = 0;
  if (type == TYPE_INT) {
    int number = *(int*)input;
    if (number == 0) {
      result = 1;
    }
    for (; number != 0; number /= 10, result++) {
    }
  } else if (type == TYPE_LONG_INT) {
    long int number = *(long int*)input;
    if (number == 0) {
      result = 1;
    }
    for (; number != 0; number /= 10, result++) {
    }
  } else if (type == TYPE_SHORT_INT) {
    short int number = *(short int*)input;
    if (number == 0) {
      result = 1;
    }
    for (; number != 0; number /= 10, result++) {
    }
  } else if (type == TYPE_UNSIGNED_INT) {
    unsigned int number = *(unsigned int*)input;
    if (number == 0) {
      result = 1;
    }
    for (; number != 0; number /= 10, result++) {
    }
  } else if (type == TYPE_LONG_UNSIGNED_INT) {
    unsigned long int number = *(unsigned long int*)input;
    if (number == 0) {
      result = 1;
    }
    for (; number != 0; number /= 10, result++) {
    }
  } else if (type == TYPE_SHORT_UNSIGNED_INT) {
    unsigned short int number = *(unsigned short int*)input;
    if (number == 0) {
      result = 1;
    }
    for (; number != 0; number /= 10, result++) {
    }
  }
  return result;
}

int get_int_sign(void* number, int type) {
  int result = 1;
  if (type == TYPE_INT) {
    int zero = 0;
    if (*(int*)number < zero) {
      result = -1;
    }
  }
  if (type == TYPE_LONG_INT) {
    long int zero = 0;
    if (*(long int*)number < zero) {
      result = -1;
    }
  }
  if (type == TYPE_SHORT_INT) {
    short int zero = 0;
    if (*(short int*)number < zero) {
      result = -1;
    }
  }
  return result;
}

void print_sign(int plus_sgn, int minus_sgn, int space_symbol, int sgn,
                char* dst) {
  if ((sgn == -1 && minus_sgn)) {
    print_char('-', dst, 1, 0);
  } else if (plus_sgn) {
    print_char('+', dst, 1, 0);
  } else if (space_symbol) {
    print_char(' ', dst, 1, 0);
  }
}

int is_zero(void* number, int type) {
  int result = 0;
  if (type == TYPE_INT) {
    int zero = 0;
    if (*(int*)number == zero) {
      result = 1;
    }
  }
  if (type == TYPE_UNSIGNED_INT) {
    unsigned int zero = 0;
    if (*(unsigned int*)number == zero) {
      result = 1;
    }
  }
  if (type == TYPE_LONG_INT) {
    long int zero = 0;
    if (*(long int*)number == zero) {
      result = 1;
    }
  }
  if (type == TYPE_SHORT_INT) {
    short int zero = 0;
    if (*(short int*)number == zero) {
      result = 1;
    }
  }
  if (type == TYPE_SHORT_UNSIGNED_INT) {
    unsigned short int zero = 0;
    if (*(unsigned short int*)number == zero) {
      result = 1;
    }
  }
  if (type == TYPE_LONG_UNSIGNED_INT) {
    unsigned long int zero = 0;
    if (*(unsigned long int*)number == zero) {
      result = 1;
    }
  }
  return result;
}

// prec+w+printing len check INF SGN
void print_double(double num, int precision, int width, int right_padding,
                  int plus_sgn, int space_symbol, char* dst) {
  if (!check_special_float_nums(num, dst)) {
    int number_sgn = 0;
    int whole_len;
    if (num < 0) {
      number_sgn = -1;
      num = -num;
    }
    double tmpval;
    double fract_part = modf(num, &tmpval);
    double whole_part = tmpval;
    if (whole_part > 0) {
      whole_len = log10f(whole_part) + 1;
    } else {
      whole_len = 1;
    }
    char* tmp = malloc(sizeof(char) * (precision + 3 + whole_len));
    if (width > precision + whole_len + 1 +
                    (plus_sgn || space_symbol || number_sgn == -1) &&
        !right_padding) {
      add_padding(width - (whole_len + 1 + precision +
                           (plus_sgn || space_symbol || number_sgn == -1)),
                  dst);
    }
    if (tmp != NULL) {
      tmp[0] = 0;
      print_sign(plus_sgn, 1, space_symbol, number_sgn, tmp);
      if (whole_len > 1 || whole_part != 0) {
        if (precision > 0) {
          print_whole_float(whole_part, tmp);
        } else {
          int i_num = (int)(num + 0.5);
          print_int(&i_num, 0, 0, 0, 0, 0, 0, dst, TYPE_INT);
        }
      } else {
        print_char('0', tmp, 1, 0);
      }
      if (precision > 0) {
        print_char('.', tmp, 1, 0);
      }
      if ((int)(fract_part * pow(10, precision + 1)) % 10 >= 5) {
        fract_part = fract_part + 0.5 * pow(10, -precision);
      }
      print_fractional_float(fract_part, precision, 0, tmp);
      print_string(tmp, dst, 0, 0, 0);
      free(tmp);
    }
    if (width > precision + whole_len + 1 +
                    (plus_sgn || space_symbol || number_sgn == -1) &&
        right_padding) {
      add_padding(width - (whole_len + 1 + precision +
                           (plus_sgn || space_symbol || number_sgn == -1)),
                  dst);
    }
  }
}

int check_special_float_nums(double num, char* dst) {
  int result = 0;
  if (isnan(num)) {
    if (signbit(num) == 0) {
      print_char('+', dst, 0, 0);
    } else {
      print_char('-', dst, 0, 0);
    }
    print_string("nan", dst, 0, 0, 0);
    result = 1;
  } else if (isinf(num)) {
    if (signbit(num) == 0) {
      print_char('+', dst, 0, 0);
    } else {
      print_char('-', dst, 0, 0);
    }
    print_string("inf", dst, 0, 0, 0);
    result = 1;
  }
  return result;
}

void print_fractional_float(float fractional, int precision, int plus_sgn,
                            char* dst) {
  for (int i = 0; i < precision; i++) {
    fractional = fractional * 10;
    int digit = (int)(fractional);
    print_int(&digit, 1, 0, 0, plus_sgn, 0, 0, dst, TYPE_INT);
    fractional = fractional - (int)fractional;
  }
}

void print_whole_float(double num, char* dst) {
  int digit;
  for (int i = log10f(num); i >= 0; i--) {
    double weight = pow(10.0, i);
    if (weight > 0 && !isinf(weight)) {
      digit = floor(num / weight);
      num -= (digit * weight);
      print_int(&digit, 1, 0, 0, 0, 0, 0, dst, TYPE_INT);
    }
  }
}
