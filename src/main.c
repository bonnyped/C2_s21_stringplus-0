#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_sprintf_funcs.h"
#include "s21_string.h"

/* TODO:
Specifiers:, n
Flags: #, 0 ������� � %g - ��������� ���� ��� ������� ���� ��� ���� �� ��
�����... (�� ������ ������� �� ����)�������� Width description: * Precision
description: .* Length description: L add all to parser!!!
*/
int main() {
char res[200];
  char resorig[200];
  char format[100] = "%10f %15f %20.f";
  float a = -1000./0.;
  float b = 0.0 / 0.0;
  float c = 100./0.;
  sprintf(res, format, a, b, c);
   s21_sprintf(resorig, format, a, b, c);


  printf("%s\n",res);
  printf("%s\n",resorig);
  

}
