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
  char str1[100];
  char str2[100];
  char *str3 = "%5.11e!";
  double num = -764231539.;
  sprintf(str1, str3, num);
                   s21_sprintf(str2, str3, num);

  printf("%s\n",str1);
  printf("%s\n",str2);
  
  
 char res[200];
  char resorig[200];
  char format[100] = "~hello: %.6Lf!\nHELLO: %.Lf\nhi: %+ 0Lf!!~";
  long double a = 000000000000000.00000000000;
  sprintf(res, format, a, a, a);
  
                   s21_sprintf(resorig, format, a, a, a);
  printf("%s@\n",resorig);
   printf("%s@\n",res);
}
