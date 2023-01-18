#include "s21_string.h"
#include <stdio.h>
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
  char* src_copy = calloc (n, sizeof(char));

  s21_memcpy(src_copy, src, n);
  s21_memcpy(dest, src_copy, n);
  free(src_copy);

  return dest;
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

int s21_strcmp(const char *str1, const char *str2) {
  char *s21_str1 = (char *)str1;
  char *s21_str2 = (char *)str2;
  int stop = 0;
  int status = 0;
  do {
    if (*s21_str1 - *s21_str2 != 0) {
      stop = 1;
      status = *s21_str1 - *s21_str2;
    }
  } while (stop == 0 && *s21_str1++ != '\0' && *s21_str2++ != '\0');
  return status;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  char *s21_str1 = (char *)str1;
  char *s21_str2 = (char *)str2;
  unsigned i = 0;
  int stop = 0;
  int status = 0;
  while (stop == 0 && i++ < n) {
    if (*s21_str1 - *s21_str2 != 0) {
      stop = 1;
      status = *s21_str1 - *s21_str2;
    }
    if (*s21_str1 != '\0' && *s21_str2 != '\0') {
      s21_str1++;
      s21_str2++;
    }
  }
  return status;
}

char *s21_strcpy(char *dest, const char *src) {
  char *s21_dest = NULL;
  char *s21_src = NULL;
  if ((dest != NULL) && (src != NULL)) {
    s21_dest = (char *)dest;
    s21_src = (char *)src;
    while (((*s21_dest++ = *s21_src++)) != '\0')
      ;
  }
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *s21_dest = NULL;
  char *s21_src = NULL;
  unsigned i = 0;
  if ((dest != NULL) && (src != NULL)) {
    s21_dest = (char *)dest;
    s21_src = (char *)src;
    while (i < n) {
      *s21_dest++ = *s21_src++;
      i++;
    }
    while (*s21_src++ != '\0') {
      *s21_dest++ = '\0';
    };
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  char *s21_str1 = (char *)str1;
  char *s21_str2 = (char *)str2;
  size_t status = 0;
  int stop = 0;
  while (*s21_str1 != '\0' && stop == 0) {
    while (*s21_str2 != '\0' && stop == 0) {
      if (*s21_str1 == *s21_str2) {
        stop = 1;
      }
      s21_str2++;
    }
    if (stop == 0) {
      status += 1;
      s21_str2 = (char *)str2;
    }
    s21_str1++;
  }
  return status;
}

char *s21_strerror(int errnum) {
  char *str_error = NULL;
  if (errnum < 0 || errnum > ARRAY_SIZE) {
    char buffer_error[4500];
    sprintf(buffer_error, "%s%d", UNKNOWN_ERROR, errnum); // s21_sprintf
    str_error = buffer_error;
  } else {
    char *array_error[] = s21_error;
    str_error = (char *)array_error[errnum];
  }
  return str_error;
}

s21_size_t s21_strlen(const char *str) {
  char *s21_str = (char *)str;
  size_t count = 0;
  while (*s21_str != '\0') {
    count++;
    s21_str++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *s21_str1 = (char *)str1;
  char *s21_str2 = (char *)str2;
  char *status = NULL;
  int stop = 0;
  while (*s21_str2 != '\0' && stop == 0) {
    while (*s21_str1 != '\0' && stop == 0) {
      if (*s21_str1 == *s21_str2) {
        stop = 1;
        status = s21_str1;
      }
      s21_str1++;
    }
    if (stop == 0) {
      s21_str2 = (char *)str2;
    }
    s21_str2++;
  }
  return status;
}

char *s21_strrchr(const char *str, int c) { return strrchr(str, c); }

s21_size_t s21_strspn(const char *str1, const char *str2) {
  return strspn(str1, str2);
}

char *s21_strstr(const char *haystack, const char *needle) {
  return strstr(haystack, needle);
}

char *s21_strtok(char *str, const char *delim) { return strtok(str, delim); }
