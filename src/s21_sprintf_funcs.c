#include "s21_sprintf_funcs.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "s21_string.h"

/*%% template
* DELETE 1, 0 FROM PRINT CHAR MAKE MACRO!
WCHAR_T
MANY FUNCS CODE DUP PROBLEM CAN BE SOLVED WITH CAST TO HIGHER TYPE AND BACKCAST
IN FUNCTION
*/

void print_char(char symb, char* dst, int width, int right_padding,
                char pading_symbol) {
  char source[2];
  source[0] = symb;
  source[1] = 0;
  if (width > 1 && !right_padding) {
    add_padding(width - 1, pading_symbol, dst);
  }
  s21_strcat(dst, source);
  if (width > 1 && right_padding) {
    add_padding(width - 1, pading_symbol, dst);
  }
}

void add_padding(int num, char pading_symbol, char* dst) {
  for (int i = 0; i < num; i++) {
    print_char(pading_symbol, dst, 1, 0, pading_symbol);
  }
}

void print_string(char* string, char* dst, int precision, int width,
                  int right_padding, char pading_symbol) {
  s21_size_t str_len;
  if (precision == -1) {
    str_len = s21_strlen(string);
  } else {
    str_len = precision;
  }
  if ((int)str_len < width && !right_padding) {
    add_padding(width - str_len, pading_symbol, dst);
  }
  if (precision == -1) {
    s21_strcat(dst, string);
  } else {
    s21_strncat(dst, string, precision);
  }
  if ((int)str_len < width && right_padding) {
    add_padding(width - str_len, pading_symbol, dst);
  }
}

// precision 0 number 0, widdth >0?
// minus sign width and prec check!!
void print_int(void* number, int precision, int width, int right_padding,
               char pading_symbol, int plus_sgn, int minus_sgn,
               int space_symbol, char* dst, int type) {
  s21_size_t array_len = number_length(number, type);
  char* array = s21_NULL;
  int printing_len = precision > (int)array_len ? precision : (int)array_len;
  if (precision != 0 || (precision == 0 && !is_zero(number, type))) {
    array = malloc(sizeof(char) * array_len);
  } else { printing_len = 0; }
  int number_sgn = get_int_sign(number, type);
  printing_len += (plus_sgn || space_symbol || (minus_sgn && number_sgn == -1));
  if (width > printing_len && !right_padding) {
    add_padding(width - (printing_len), pading_symbol, dst);
  }
  if (array != s21_NULL) {
    int_to_chars(number, array_len, array, type);
    print_sign(plus_sgn, minus_sgn, space_symbol, number_sgn, dst);
    if (precision > 0 && precision > (int)array_len) {
      int difference = precision - (int)array_len;
      for (; difference > 0; difference--) {
        print_char('0', dst, 1, 0, pading_symbol);
      }
    }
    for (int i = 0; i < (int)array_len; i++) {
      print_char(array[i], dst, 1, 0, pading_symbol);
    }
    free(array);
  }
  if (width > printing_len && right_padding) {
    add_padding(width - (printing_len), ' ', dst);
  }
}

void print_octal(long unsigned int number, int precision, int width,
                 int right_padding, char pading_symbol, int prefix, char* dst) {
  int num_width = precision > width ? precision : width;
  char* tmp = malloc(sizeof(char) * (40 + num_width));
  if (tmp != s21_NULL) {
    tmp[0] = 0;
    if (prefix && number != 0) {
      print_char('0', tmp, 0, 0, pading_symbol);
    }
    if (number != 0) {
      for (long unsigned int num = number; num > 0; num = num / 8) {
        int digit = num % 8;
        print_char(digit + '0', tmp, 0, 0, pading_symbol);
      }
    } else {
      print_char('0', tmp, 0, 0, pading_symbol);
    }
    int printed_len = s21_strlen(tmp);
    if (precision > 0 && precision > printed_len) {
      int difference = precision - printed_len;
      for (; difference > 0; difference--) {
        print_char('0', tmp, 1, 0, pading_symbol);
      }
      printed_len = s21_strlen(tmp);
    }
    if (width > printed_len && !right_padding) {
      add_padding(width - (printed_len), pading_symbol, dst);
    }
    if (precision != 0 || number != 0) {
      reverse_string(tmp + prefix);
      print_string(tmp, dst, -1, 0, 0, pading_symbol);
    }
    if (width > printed_len && right_padding) {
      add_padding(width - (printed_len), pading_symbol, dst);
    }
    free(tmp);
  }
}

void reverse_string(char* str) {
  int left = 0;
  int right = s21_strlen(str) - 1;
  while (left < right) {
    char tmp = str[left];
    str[left] = str[right];
    str[right] = tmp;
    left++;
    right--;
  }
}

void print_hexadecimal(long unsigned int number, int precision, int width,
                       int right_padding, char pading_symbol, int prefix,
                       int in_upper_case, int pointer, char* dst) {
  int num_width = precision > width ? precision : width;
  char* tmp = malloc(sizeof(char) * (40 + num_width));
  if (tmp != s21_NULL) {
    tmp[0] = 0;
    if (prefix && number != 0) {
      print_char('0', tmp, 0, 0, pading_symbol);
      if (in_upper_case) {
        print_char('X', tmp, 0, 0, pading_symbol);
      } else {
        print_char('x', tmp, 0, 0, pading_symbol);
      }
    }
    if (number != 0) {
      for (long unsigned int num = number; num > 0; num = num / 16) {
        int digit = num % 16;
        print_char(hex_char_from_num(digit, in_upper_case), tmp, 0, 0,
                   pading_symbol);
      }
    } else if (!pointer) {
      print_char('0', tmp, 0, 0, pading_symbol);
    }
    int printed_len = s21_strlen(tmp);
    if (pointer && number == 0) {
      print_string("(nil)", tmp, -1, 0, 0, pading_symbol);
      printed_len = s21_strlen("(nil)");
    }
    if (precision > 0 && precision > printed_len) {
      int difference = precision - printed_len;
      for (; difference > 0; difference--) {
        print_char('0', tmp, 1, 0, pading_symbol);
      }
      printed_len = s21_strlen(tmp);
    }
    if (width > printed_len && !right_padding) {
      if (pading_symbol == '0') {
        add_padding(width - (printed_len), pading_symbol, tmp);
      } else {
        add_padding(width - (printed_len), pading_symbol, dst);
      }
    }
    if (precision != 0 || number != 0 || pointer) {
      if (number != 0) {
        reverse_string(tmp + prefix * 2);
      }
      print_string(tmp, dst, -1, 0, 0, pading_symbol);
    }
    if (width > printed_len && right_padding) {
      add_padding(width - (printed_len), ' ', dst);
    }
    free(tmp);
  }
}

char hex_char_from_num(int num, int capital) {
  char result = 0;
  if (num < 10) {
    result = '0' + num;
  } else {
    if (!capital) {
      result = 'a' + (num - 10);
    } else {
      result = 'A' + (num - 10);
    }
  }
  return result;
}

void int_to_chars(void* input, int number_length, char* array, int type) {
  int i = number_length - 1;
  if (type == TYPE_INT || type == TYPE_SHORT_INT || type == TYPE_LONG_INT) {
    long int number = *(long int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + abs(digit);
      number /= 10;
    } while (number != 0);
  } else if (type == TYPE_UNSIGNED_INT || type == TYPE_SHORT_UNSIGNED_INT ||
             type == TYPE_LONG_UNSIGNED_INT) {
    unsigned long int number = *(unsigned long int*)input;
    do {
      int digit = number % 10;
      array[i--] = '0' + digit;
      number /= 10;
    } while (number != 0);
  }
}

s21_size_t number_length(void* input, int type) {
  s21_size_t result = 0;
  if (type == TYPE_INT || type == TYPE_LONG_INT || type == TYPE_SHORT_INT) {
    long int number = *(long int*)input;
    if (number == 0) {
      result = 1;
    }
    for (; number != 0; number /= 10, result++) {
    }
  } else if (type == TYPE_UNSIGNED_INT || type == TYPE_LONG_UNSIGNED_INT ||
             type == TYPE_SHORT_UNSIGNED_INT) {
    unsigned long int number = *(unsigned long int*)input;
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
  if (type == TYPE_INT || type == TYPE_LONG_INT || type == TYPE_SHORT_INT) {
    int zero = 0;
    if (*(long int*)number < zero) {
      result = -1;
    }
  }
  return result;
}

void print_sign(int plus_sgn, int minus_sgn, int space_symbol, int sgn,
                char* dst) {
  if ((sgn == -1 && minus_sgn)) {
    print_char('-', dst, 1, 0, ' ');
  } else if (plus_sgn) {
    print_char('+', dst, 1, 0, ' ');
  } else if (space_symbol) {
    print_char(' ', dst, 1, 0, ' ');
  }
}

int is_zero(void* number, int type) {
  int result = 0;
  if (type == TYPE_INT || type == TYPE_SHORT_INT || type == TYPE_LONG_INT) {
    long int zero = 0;
    if (*(long int*)number == zero) {
      result = 1;
    }
  }
  if (type == TYPE_UNSIGNED_INT || type == TYPE_SHORT_UNSIGNED_INT ||
      type == TYPE_LONG_UNSIGNED_INT) {
    unsigned long int zero = 0;
    if (*(unsigned long int*)number == zero) {
      result = 1;
    }
  }
  return result;
}

// prec+w+printing len check INF SGN
void print_double(long double num, int precision, int width, int right_padding,
                  char pading_symbol, int plus_sgn, int space_symbol,
                  int point_forced, char* dst) {
  if (!check_special_float_nums(num,width,right_padding, pading_symbol, plus_sgn, space_symbol, dst)) {
    int number_sgn = 0;
    int whole_len;
    if (num < 0) {
      number_sgn = -1;
      num = -num;
    }
    long double whole_part;
    long double fract_part = modfl(num, &whole_part);
    if (whole_part > 0) {
      whole_len = log10l(whole_part) + 1;
    } else {
      whole_len = 1;
    }
    char* tmp = malloc(sizeof(char) * (precision + 3 + whole_len));
    int printed_len = precision + whole_len + (precision > 0 || point_forced)+
                    (plus_sgn || space_symbol || number_sgn == -1);
    if (width > printed_len && !right_padding) {
      add_padding(width - printed_len, pading_symbol, dst);
    }
    if (tmp != s21_NULL) {
      tmp[0] = 0;
      print_sign(plus_sgn, 1, space_symbol, number_sgn, tmp);
      if (whole_len > 1 || whole_part != 0) {
        print_whole_float(precision == 0?roundl(num):whole_part, tmp);
      } else {
        print_char('0', tmp, 1, 0, pading_symbol);
      }
      if (precision > 0 || point_forced) {
        print_char('.', tmp, 1, 0, pading_symbol);
      }
      int next_digigt = fmodl(fract_part * powl(10, precision + 1), 10);
      if (next_digigt >= 5) {
        fract_part = fract_part + 0.5 * powl(10, -precision);
      //} else {
      //fract_part = fract_part + 0.1 * powl(10, -precision); // tmp fix for rounding issues -764231539. with .11 prec
      }
      print_fractional_float(fract_part, precision, 0, tmp);
      print_string(tmp, dst, -1, 0, 0, pading_symbol);
      free(tmp);
    }
    if (width > printed_len && right_padding) {
      add_padding(width - printed_len, pading_symbol, dst);
    }
  }
}

int check_special_float_nums(long double num, int width,
                           int right_padding, char pading_symbol,int plus_sgn, int space_symbol, char* dst) {
  int result = 0;
  int printed_len = 3  + (plus_sgn || space_symbol || signbit(num) != 0);
  if (isnan(num) || isinf(num)){
  if (width > printed_len && !right_padding) {
      add_padding(width - printed_len, pading_symbol, dst);
    }
  }
  if (isnan(num)) {
    if (signbit(num) == 0) {
      if(plus_sgn) {
      print_char('+', dst, 0, 0, ' ');
      } else if(space_symbol) {
      print_char(' ', dst, 0, 0, ' ');
      }
    } else {
      print_char('-', dst, 0, 0, ' ');
    }
    print_string("nan", dst, -1, 0, 0, ' ');
    result = 1;
  } else if (isinf(num)) {
    if (signbit(num) == 0) {
      if(plus_sgn) {
      print_char('+', dst, 0, 0, ' ');
      } else if(space_symbol) {
      print_char(' ', dst, 0, 0, ' ');
      }
    } else {
      print_char('-', dst, 0, 0, ' ');
    }
    print_string("inf", dst, -1, 0, 0, ' ');
    result = 1;
  }
  if(result){
  if (width > printed_len && right_padding) {
      add_padding(width - printed_len, pading_symbol, dst);
    }
  }
  return result;
}

void print_fractional_float(long double fractional, int precision, int plus_sgn,
                            char* dst) {
  int i = 0;
  for (; i < precision; i++) {
    fractional = fractional * 10;
    long double whole;
    fractional = modfl(fractional, &whole);
    long int digit = (long int)(whole);
    print_int(&digit, 1, 0, 0, ' ', plus_sgn, 0, 0, dst, TYPE_INT);
  }
}

void print_whole_float(long double num, char* dst) {
  long int digit;
  for (int i = log10l(num); i >= 0; i--) {
    long double weight = powl(10.0, i);
    if (weight > 0 && !isinf(weight)) {
      digit = floorl(num / weight);
      num -= (digit * weight);
      print_int(&digit, 1, 0, 0, ' ', 0, 0, 0, dst, TYPE_INT);
    }
  }
}

void print_double_scientific(long double num, int precision, int width,
                             int right_padding, char pading_symbol,
                             int plus_sgn, int space_symbol, int capital,
                             int point_forced, char* dst) {
if (!check_special_float_nums(num,width,right_padding, pading_symbol, plus_sgn, space_symbol, dst)) {
  int number_sgn = 0;
  char* start_of_num = &dst[s21_strlen(dst)];
  if (num < 0) {
    number_sgn = -1;
    num = -num;
  }
  long int power = get_power(num);
  int power_len = (int)number_length(&power, TYPE_LONG_INT);
  if (power_len < 2) {power_len = 2;}
  int num_len = 3 + power_len  + (precision > 0 || point_forced) + precision + (plus_sgn || space_symbol || number_sgn == -1);
  if (width > num_len && !right_padding) {
    add_padding(width - num_len, pading_symbol, dst);
  }
  print_sign(plus_sgn, 1, space_symbol, number_sgn, dst);
  print_double(num * powl(10, -power), precision, 0, 0, pading_symbol, 0, 0,
               point_forced, dst);
  if(!right_padding && (plus_sgn || space_symbol || number_sgn == -1)){correct_padding(start_of_num);}
  if (capital) {
    print_char('E', dst, 0, 0, pading_symbol);
  } else {
    print_char('e', dst, 0, 0, pading_symbol);
  }
  print_int(&power, 2, 0, 0, pading_symbol, 1, 1, 0, dst, TYPE_INT);
  if (width > num_len && right_padding) {
    add_padding(width - num_len, pading_symbol, dst);
  }
}
}

long int get_power(long double num){
long int result;
  if (num == 0.f) { result = 0; }
        else {
            result = log10l(num);
            if (result <= 0) {
            result--;
        }  
        }
   return result;
}
// vezde LONG DOUBLE!!! PEW PEW
/*void print_double_shortest(long double num, int precision, int width,
                           int right_padding, char pading_symbol, int plus_sgn,
                           int space_symbol, int capital, int point_forced,
                           char* dst) {
  // int number_sgn = 0;
  int whole_len;
  int real_precision = precision;
  int num_of_preceding_zeros = 0;
  long double original_num = num;
  if (num < 0) {
    // number_sgn = -1;
    num = -num;
  }
  long double whole_part;
  modfl(num, &whole_part);
  if (whole_part >= 1.0) {
    whole_len = log10l(whole_part) + 1;
    real_precision = precision - whole_len;
    if (real_precision < 0) {
      real_precision = 0;
    }
  } else {
    whole_len = 1;
    for (; num < 1.0; num = num * 10, num_of_preceding_zeros++) {
    }
    num_of_preceding_zeros--;
    real_precision += num_of_preceding_zeros;
  }
  int num_len_normal = whole_len + 1 + real_precision;
  if (real_precision == 0) {
    num_len_normal--;
  }
  int num_len_scientific = (precision) + 5;

  if (num_len_scientific > num_len_normal) {
    print_double(original_num, real_precision, width, right_padding,
                 pading_symbol, plus_sgn, space_symbol, point_forced, dst);
  } else {
    print_double_scientific(original_num, precision - 1, width, right_padding,
                            pading_symbol, plus_sgn, space_symbol, capital,
                            point_forced, dst);
  }
}
*/


//PROBLEM WITH ZERO NUMBER
void print_double_shortest(long double num, int precision, int width,
                           int right_padding, char pading_symbol, int plus_sgn,
                           int space_symbol, int capital, int point_forced,
                           char* dst) {
    if (!check_special_float_nums(num,width,right_padding, pading_symbol, plus_sgn, space_symbol, dst)) {
    	char* start_of_num = &dst[s21_strlen(dst)];
        long double original_num = num;
        if (num < 0) {
            num = -num;
        }
        long int power = get_power(num);
        char* tmp = malloc(sizeof(char) * (width + 300)) ;
        tmp[0] = 0;
        if (precision == 0) { precision = 1; }
        if (power < precision && power >= -4) {
            print_double(original_num, precision - 1 - power, 0, right_padding,
                pading_symbol, plus_sgn, space_symbol, point_forced, tmp);
            if (!point_forced && precision - 1 - power > 0) { delete_zeros(tmp); }
            //if (num == 0.f) {delete_zeros(tmp, point_forced);}
        }
        else {
            print_double(original_num * powl(10, -power), precision - 1, 0, 0, pading_symbol, plus_sgn, space_symbol,
                point_forced, tmp);
            if (!point_forced) { delete_zeros(tmp); }

            if (capital) {
                print_char('E', tmp, 0, 0, pading_symbol);
            }
            else {
                print_char('e', tmp, 0, 0, pading_symbol);
            }
            print_int(&power, 2, 0, 0, pading_symbol, 1, 1, 0, tmp, TYPE_INT);
        }
        int num_len = (int)s21_strlen(tmp);
        int padding_added = 0;
        if (width > num_len && !right_padding) {
        padding_added = 1;
    add_padding(width - num_len, pading_symbol, dst);
  }
        print_string(tmp, dst, -1, 0, right_padding, pading_symbol);
        if(!right_padding && (plus_sgn || space_symbol || original_num <0 ) && padding_added){correct_padding(start_of_num);}
        if (width > num_len && right_padding) {
    add_padding(width - num_len, ' ', dst);
  }
  free(tmp);
    }
}

void delete_zeros(char* str) {
    int i = s21_strlen(str);
   
    while (str[--i] == '0') {
        str[i] = 0;
        //i--;
    }
    if (str[i] == '.') {
    	str[i] = 0;
    }
}


void correct_padding(char* str){
char* search_result = s21_strpbrk(str, " +-");
char tmp = *str;
*str = *search_result;
*search_result = tmp;
}

