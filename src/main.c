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
  //char format[100] = "this is kek %n";
  int a= 0;
  int b = 0;
  sprintf(res, "this is kek %n", &a);
   s21_sprintf(resorig, "this is kek %5n", &b);


  printf("%s\n",res);
  printf("%s\n",resorig);
  printf("%d\n", a);
printf("%d\n", b);
}
