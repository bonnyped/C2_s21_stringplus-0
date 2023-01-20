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
double a = 777.0;
char res[300];
char resorig[300];
s21_sprintf(res, "%E", a);
 sprintf(resorig, "%E", a);
  printf("%s\n",res);
  printf("%s\n",resorig);
  
  
double b = 777.0;

s21_sprintf(res, "%e", b);
sprintf(resorig, "%e", b);
  printf("%s\n",res);
  printf("%s\n",resorig);
}
