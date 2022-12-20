#include <string.h>
#include "s21_string.h"

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

void* s21_memset(void* str, int c, s21_size_t n) {
  return memset(str, c, n);
}

char* s21_strcat(char* dest, const char* src) {
  return strcat(dest, src);
}

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  return strncat(dest, src, n);
}

char* s21_strchr(const char* str, int c) {
  return strchr(str, c);
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
