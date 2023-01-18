#include "s21_string.h"

#include <string.h>

void* s21_memchr(const void* str, int c, s21_size_t n) {
  const char* str_copy = str;
  void* res = (void*)str;
  s21_size_t i = 0;
  int exit = 0;

  while (i < n && !exit) {
    if (str_copy[i] == c) {
      exit = 1;
      res = (void*)(str_copy + i);
    }
    i++;
  }

  return exit ? res : NULL;
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  int res = 0;
  const char* first = str1;
  const char* second = str2;
  s21_size_t i = 0;
  int exit = 0;

  while (i < n && !exit) {
    if (first[i] != second[i]) {
      if (first[i] < second[i]) {
        res = -1;
        exit = 1;
      }
      else {
        res = 1;
        exit = 1;
      }
    }
    i++;
  }

  return res;
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  char* dest_copy = dest;
  const char* src_copy = src;

  for (s21_size_t i = 0; i < n; i++) {
    dest_copy[i] = src_copy[i];
  }

  return dest;
}

void* s21_memmove(void* dest, const void* src, s21_size_t n) {
  return memmove(dest, src, n);
}

void* s21_memset(void* str, int c, s21_size_t n) {
  char* str_copy = str;
  s21_size_t i = 0;

  while (i < n) {
    str_copy[i] = c;
    i++;
  }

  return str_copy;
}

char* s21_strcat(char* dest, const char* src) {
  s21_size_t len = 0;
  s21_size_t i = 0;

  len = s21_strlen(dest);
  for (; src[i] != '\0'; i++) {
    dest[len + i] = src[i];
  }

  dest[len + i] = '\0';

  return dest;
}

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  s21_size_t len = 0;
  s21_size_t i = 0;
  
  len = s21_strlen(dest);
  for (; (i < n) && (src[i] != '\0'); i++) {
    dest[len + i] = src[i];
  }

  dest[len + i] = '\0';

  return dest;
}

char* s21_strchr(const char* str, int c) {
  char* res = NULL;
  s21_size_t i = 0;
  int exit = 0;

  while (str[i] != '\0' && !exit) {
    if (str[i] == c) {
      exit = 1;
      res = (char*)(str + i);
    }
    i++;
  }

  return exit ? res : NULL;
}

int s21_strcmp(const char* str1, const char* str2) {
  return strcmp(str1, str2);
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  return strncmp(str1, str2, n);
}

char* s21_strcpy(char* dest, const char* src) {
  return strcpy(dest, src);
}

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  return strncpy(dest, src, n);
}

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  return strcspn(str1, str2);
}

char* s21_strerror(int errnum) {
  return strerror(errnum);
}

s21_size_t s21_strlen(const char* str) {
  return strlen(str);
}

char* s21_strpbrk(const char* str1, const char* str2) {
  return strpbrk(str1, str2);
}

char* s21_strrchr(const char* str, int c) {
  return strrchr(str, c);
}

s21_size_t s21_strspn(const char* str1, const char* str2) {
  return strspn(str1, str2);
}

char* s21_strstr(const char* haystack, const char* needle) {
  return strstr(haystack, needle);
}

char* s21_strtok(char* str, const char* delim) {
  return strtok(str, delim);
}
