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
  char str1[300];
  char str2[300];
  char *str3 = "Third test: %010e|\nForth test: %010.e|\nFifth test: %0.0e!|";
  double num =
      -5921563224775977777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777776.;
 
  int w = sprintf(str1, str3, num, num, num);
int ww =                    s21_sprintf(str2, str3, num, num, num);

  printf("%s\n",str1);
  printf("|%d|\n", w);
  printf("%s\n",str2);
  printf("|%d|\n", ww);
  

}
