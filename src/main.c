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
double y = 0.0;
char res[300];
char resorig[300];
s21_sprintf(res, "%#+G %g\n", y, y);
 sprintf(resorig, "%#+G %g\n", y, y);


  printf("%s\n",res);
  printf("%s\n",resorig);
  

}
