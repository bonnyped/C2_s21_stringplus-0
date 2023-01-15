#include <string.h>

#include "s21_string.h"
#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>

int main() {
  int i1 = 0;
  int i2 = 43;
  int i3 = INT_MAX;
  int i4 = -324;
  long int li1 = 3245235;
  short int si1 = -1234;
  unsigned int ui1 = 24;
  unsigned int ui2 = 0;
  unsigned long int uli1 = 3235;
  float f1 = 345125.235623;
  float f2 = 0.000403634;
  float f3 = -235.22343442;
  char arrres[450];
  char arrresiddeal[450];
  char arrres2[450];
  char arrresiddeal2[450];
  char str[] = "this is the test!";
  char format[] =
      "%%+|%-+ +15.3ld||%+ -8.5hd|%d |%+ d| |%+++10.3d||%10.5u|, |%u| |%8lu| "
      "|%-3.1d| %.0u |%5.2c| |%-5c| |% +s|| %-8.10s| |%-3.2f| |%15.5f| "
      "|%15.5f|";
  s21_sprintf(arrres, format, li1, si1, i2, i3, i1, ui1, ui2, uli1, i1, ui2,
              'q', 'w', str, str, f1, f2, f3);
  sprintf(arrresiddeal, format, li1, si1, i2, i3, i1, ui1, ui2, uli1, i1, ui2,
          'q', 'w', str, str, f1, f2, f3);
  printf("%s\n", arrres);
  printf("%s\n", arrresiddeal);

  if (strcmp(arrres, arrresiddeal) == 0) {
    printf("\n\nNAIS!\n\n");
  }
  int I1 = INT_MAX;
  int I2 = INT_MIN;
  int I3 = 0;
  long int LI1 = -234;
  short int SI1 = 24;
  unsigned long int ULI1 = 234535;
  unsigned short int USI1 = 1234;
  char format2[] =
      "%%|%i||%3d||%.12d||% -15.3d||%lu||%3lu||%.12lu||% "
      "-15.3lu||%hu||%3hu||%.12hu||% -15.3hu|";
  s21_sprintf(arrres, format2, I1, I2, I1, I2, LI1, LI1, LI1, LI1, SI1, SI1,
              SI1, SI1);
  sprintf(arrresiddeal, format2, I1, I2, I1, I2, LI1, LI1, LI1, LI1, SI1, SI1,
          SI1, SI1);
  printf("%s\n", arrres);
  printf("%s\n", arrresiddeal);

  if (strcmp(arrres, arrresiddeal) == 0) {
    printf("\n\nNAIS!\n\n");
  }
}
