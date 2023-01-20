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
  char res[200];
  char resorig[200];
  char format[150] = "%#Lf, %.Lf %0Lf %0.*Lf %+35Lf";
  long double a = 234897562983476.29552345234523452345;
  int b = 1;
  sprintf(res, format, a, a, a, b, a, a);
  s21_sprintf(resorig, format, a, a, a, b, a, a);
  printf("%s\n",res);
  printf("%s\n",resorig);
}
