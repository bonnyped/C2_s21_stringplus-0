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
long double a = -777;
char res[400];
char resorig[400];
s21_sprintf(res, "%- 2.0Le|", a);
 sprintf(resorig, "%- 2.0Le|", a);
  printf("%s\n",res);
  printf("%s\n",resorig);
}
