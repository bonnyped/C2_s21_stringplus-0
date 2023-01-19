#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_sprintf_funcs.h"
#include "s21_string.h"

/* TODO:
Specifiers:, n
Flags: #, 0 РЕШЕТКА У %g - оставляет нули без решетки если все нули то не
пишем... (НУ ТОЧНЕЕ СКОЛЬКО НЕ НАДО)йййййййй Width description: * Precision
description: .* Length description: L add all to parser!!!
*/
int main() {
  char res[200] = "\0";
  char resorig[200] = "\0";
  char format[100] = "%i%d%i%23.3f";
  unsigned int a = INT_MAX;
  int b = 1234567;
  int c = 'f';
  float d = 34.45647;
  sprintf(res, format, a, b, c, d);
  s21_sprintf(resorig, format, a, b, c, d);
  printf("%s\n",res);
  printf("%s\n",resorig);
}
