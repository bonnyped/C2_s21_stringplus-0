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
  const char *s21_str1 = (const char *)str1;
  const char *s21_str2 = (const char *)str2;
  int stop = 0;
  int status = 0;
  while (stop == 0) {
    if ((*s21_str1 == '\0' || *s21_str2 == '\0') || (*s21_str1 - *s21_str2 != 0)) {
      stop = 1;
      if (*s21_str1 - *s21_str2 != 0) {
      status = *s21_str1 - *s21_str2;
      }
    } else {
      s21_str1++;
      s21_str2++;
    }
  }
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
  while (*s21_str1 != '\0' && stop == 0) {
    while (*s21_str2 != '\0' && stop == 0) {
      if (*s21_str1 == *s21_str2) {
        stop = 1;
        status = s21_str1;
      }
      s21_str2++;
    }
    if (stop == 0) {
      s21_str2 = (char *)str2;
    }
    s21_str1++;
  }
  return status;
}

char* s21_strrchr(const char *str, int ch){
    char *pointer = s21_NULL;
    if(str && ch >= 0 && ch <= 255 ){
        int i = 0;
        while(str[i] != '\0'){
            if(str[i] == ch){
                pointer = (char*)str + i;
            }
            i++;
        }
    }
    return pointer;
}

s21_size_t s21_strspn(const char *str, const char *accept){
    s21_size_t result = 0;
    for(s21_size_t i = 0; i < s21_strlen(str); i++){
        s21_size_t match = 0;
        for(s21_size_t j = 0; j < s21_strlen(accept); j++){
        if(str[i] == accept[j]){
            result++;
            match++;
            j = s21_strlen(accept);
        } else if (j == (s21_strlen(accept) - 1) && match == 0){
            i = s21_strlen(str);
        }
    }
}
    return result;
}

char *s21_strstr(const char* str1, const char *str2){
    char *pointer = s21_NULL;
    char *tmp = s21_NULL;
    s21_size_t length_str1 = s21_strlen(str1);
    s21_size_t length_str2 = s21_strlen(str2);
    s21_size_t capacity = 0;
    for(s21_size_t i = 0; i < length_str1; i++){
        for(s21_size_t j = 0; j < length_str2; j++){
            if(!tmp) { 
                if(str1[i + j] == str2[j]){
                tmp = (char*)(str1 + i + j);
                capacity++;
                if(j == length_str2 - 1){
                    i = length_str1;
                    }
                } else {
                    j = length_str2;
                } 
            }
            if((tmp && j != 0 && length_str2 > 1) || (tmp && length_str2 == 1)){
            if(str1[i + j] == str2[j]){
                capacity++;
            }
            if(j != length_str2 - 1 && str1[i + j] != str2[j]){
                tmp = s21_NULL;
                i = i + j;
                j = length_str2;
            }
            if((capacity == length_str2 - 1 && length_str2 > 1) || (tmp && length_str2 == 1)){
                pointer = tmp;
            }
            }
        }
    }
    return pointer;
}

char *s21_strtok(char* str1, const char* str2){
    char *pointer = str1;
    static char *static_pointer;
    s21_size_t length_str1;
    s21_size_t length_str2 = s21_strlen(str2);
    if(pointer) {
        length_str1 = s21_strlen(pointer);
     } else {
        if(static_pointer){
        pointer = static_pointer;
        length_str1 = s21_strlen(pointer);
        }
     }
     if(pointer){
    for(s21_size_t i = 0; i < length_str1; i++){
        for(s21_size_t j = 0; j < length_str2; j++){
            if(pointer[i] == str2[j] && i != 0){
                pointer[i] = '\0';
                static_pointer = &pointer[i + 1];
                i = length_str1;
                j = length_str2;
            } else if(pointer[i] == str2[j] && i == 0){
                pointer = &pointer[i + 1];
                i--;
                if(*pointer == '\0'){
                    pointer = s21_NULL;
                    i = length_str1;
                    j =length_str2;
                }
            }
        }
        if(i == length_str1 - 1){
            static_pointer = s21_NULL;
        } 
    }
     }
    return pointer;
}

void *s21_to_upper(const char *str) {
  char *src = s21_NULL;
  if (str) {
    s21_size_t capacity = s21_strlen(str);
    src = calloc(capacity + 1, sizeof(char));

    if (src) {
      for (s21_size_t i = 0; i < capacity; i++) {
        if (str[i] >= 97 && str[i] <= 122) {
          src[i] = str[i] - 32;
          } else {
            src[i] = str[i];
          }
          if (i == capacity - 1) {
              src[i + 1] = '\0';
          }
      }
    }
  }

  return src;
}

void *s21_to_lower(const char *str){
    char *src = s21_NULL;
    if(str){
        s21_size_t capacity = s21_strlen(str);
        src = calloc(capacity + 1, sizeof(char));
        if(src){
        for(s21_size_t i = 0; i < capacity; i++){
            if(str[i] >= 65 && str[i] <= 90){
                src[i] = str[i] + 32;
            } else {
                src[i] = str[i];
            }
            if(i == capacity - 1){
                src[i + 1] = '\0';
            }
        }
    }
    }
    return src;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index){
    char *srcstr = s21_NULL;
    if(src && str){
        s21_size_t length_src, length_str;
        s21_size_t count = 0;
        s21_size_t start_index_for_strsrc = 0;
        length_src = s21_strlen(src);
        length_str = s21_strlen(str);
        if(start_index <= length_src){
        srcstr = calloc(length_src + length_str + 1, sizeof(char));
        if(length_str > 0){
        if(srcstr){
            for(s21_size_t i = 0; i < length_src + length_str; i++){
                if(i == start_index){
                    for(s21_size_t j = 0; j < length_str; j++){
                        srcstr[start_index + j] = str[j];
                        count++;
                    }
                    start_index_for_strsrc = start_index + count;
                } else {
                count > 0 ? (srcstr[start_index_for_strsrc] = src[i - 1]) : (srcstr[start_index_for_strsrc] = src[i]);
                start_index_for_strsrc++;
                if(i == length_str +length_src - 1){
                    srcstr[start_index_for_strsrc + i + 1] = '\0';
                }
            }
            }
        }
        } else if(length_str == 0){
            srcstr = (char*)src;
        }
    }
    }
    return srcstr;
}

void *s21_trim(const char *src, const char *trim_chars){
    char *str = s21_NULL;
    if(src && trim_chars){
        s21_size_t length_src = s21_strlen(src);
        s21_size_t length_trim_chars = s21_strlen(trim_chars);
        if(length_trim_chars > 0){
        s21_size_t start_index_trimed_buffer = 0;
        char *trimed_buffer = calloc(length_src + 1, sizeof(char));
        for(s21_size_t i = 0; i < length_src; i++){
            for(s21_size_t j = 0; j < length_trim_chars; j++){
                if(src[i] == trim_chars[j]){
                    j = length_trim_chars;
                    trimed_buffer[start_index_trimed_buffer] = trim_chars[j];
                }
                if(j == length_trim_chars - 1 && src[i] != trim_chars[j]){
                    trimed_buffer[start_index_trimed_buffer] = src[i];
                    start_index_trimed_buffer++;
                }
            }
            if(i == length_src - 1){
                start_index_trimed_buffer = 0;
            }
            }
        str = trimed_buffer;
    } else {
        str = (char*)src;
    }
        }
    return str;
}
