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
double a = 1344527.434;
double c = 0.00000389849885794308485;
char res[300];
char resorig[300];
s21_sprintf(res, "%+16g |%+*G|\n", a, 20, c); 
sprintf(resorig, "%+16g |%+*G|\n", a, 20, c);
  printf("%s\n",res);
  printf("%s\n",resorig);
  

}
