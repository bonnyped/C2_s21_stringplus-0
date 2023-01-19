#include "s21_string.h"
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

#include "s21_sprintf_parser.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  return memchr(str, c, n);
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  return memcmp(str1, str2, n);
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  return memcpy(dest, src, n);
}

void* s21_memmove(void* dest, const void* src, s21_size_t n) {
  return memmove(dest, src, n);
}

void* s21_memset(void* str, int c, s21_size_t n) { return memset(str, c, n); }

char* s21_strcat(char* dest, const char* src) { return strcat(dest, src); }

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  return strncat(dest, src, n);
}

char* s21_strchr(const char* str, int c) { return strchr(str, c); }

int s21_strcmp(const char* str1, const char* str2) {
  return strcmp(str1, str2);
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  return strncmp(str1, str2, n);
}

char* s21_strcpy(char* dest, const char* src) { return strcpy(dest, src); }

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  return strncpy(dest, src, n);
}

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  return strcspn(str1, str2);
}

char* s21_strerror(int errnum) { return strerror(errnum); }

s21_size_t s21_strlen(const char* str) { return strlen(str); }

char* s21_strpbrk(const char* str1, const char* str2) {
  return strpbrk(str1, str2);
}

char* s21_strrchr(const char* str, int c) { return strrchr(str, c); }

s21_size_t s21_strspn(const char* str1, const char* str2) {
  return strspn(str1, str2);
}

char* s21_strstr(const char* haystack, const char* needle) {
  return strstr(haystack, needle);
}

char* s21_strtok(char* str, const char* delim) { return strtok(str, delim); }

int s21_sprintf(char* dst, const char* format_string, ...) {
  int result = 0;
  *dst = 0;
  *(dst + 1) = 0;
  va_list args;
  va_start(args, format_string);
  while (*format_string) {
    if (*format_string != '%') {
      print_char(*format_string, dst, 1, 0, ' ');
      format_string++;
    } else if (*(format_string + 1) == '%') {
      print_char('%', dst, 1, 0, ' ');
      format_string = format_string + 2;
    } else {
      int data_type = get_format_type(format_string);
      if (data_type != NOT_VALID_RESULT) {
        format_string++;
        pattern executable_pattern = init_pattern(data_type);
        executable_pattern = read_pattern(&format_string, executable_pattern);
        if (executable_pattern.width == READ_REQUIRED) {
          executable_pattern.width = va_arg(args, int);
        }
        if (executable_pattern.precision == READ_REQUIRED) {
          executable_pattern.precision = va_arg(args, int);
        }
        if (executable_pattern.pattern_is_ok) {
          execute_pattern(data_type, &args, dst, executable_pattern);
        }
        format_string++;
      }
    }
  }
  va_end(args);
  result = s21_strlen(dst);
  return result;
}
