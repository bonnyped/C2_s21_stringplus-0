#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_sprintf_funcs.h"
#include "s21_string.h"

/* TODO:
Specifiers:, n
Flags: #, 0 ĞÅØÅÒÊÀ Ó %g - îñòàâëÿåò íóëè áåç ğåøåòêè åñëè âñå íóëè òî íå
ïèøåì... (ÍÓ ÒÎ×ÍÅÅ ÑÊÎËÜÊÎ ÍÅ ÍÀÄÎ)éééééééé Width description: * Precision
description: .* Length description: L add all to parser!!!
*/
int main() {
  int i2 = -43;
  long int li1 = -3245235;

  short int si1 = -1234;
  unsigned int ui1 = 24;
  unsigned int ui2 = 0;
  unsigned long int uli1 = 3235;
  short unsigned int sui1 = -1212;
  float f4 = 23.5;
  float f3 = -235454.2352526;

  wchar_t warr[20];
  warr[0] = 234;
  warr[1] = 235;
  warr[2] = 56;
  warr[3] = 3667;
  warr[4] = 0;
  char resw[500];
  char resiw[500];
  sprintf(resiw, "%ls", warr);
  s21_sprintf(resw, "%ls", warr);
  printf("%ls", (wchar_t*)resw);
  printf("\n");
  printf("%ls", (wchar_t*)resiw);

  printf("\n");

  char testarr1[200];
  char testarr2[200];
  char format222[] =
      "%#X %*.*X %5.8X %#-+10.1o %#.0f %#.0E %.5G %035c %hu %u %lu %d %ld "
      "%hd\n";
  sprintf(testarr1, format222, ui1, 5, 2, ui2, uli1, ui1, f3, f4, f4, 'q', sui1,
          ui1, uli1, i2, li1, si1);
  s21_sprintf(testarr2, format222, ui1, 5, 2, ui2, uli1, ui1, f3, f4, f4, 'q',
              sui1, ui1, uli1, i2, li1, si1);
  // char format222[] = "test_ %%p\n";
  // sprintf(testarr1, format222,  &A[1]);
  // s21_sprintf(testarr2, format222, 15,5, &A[1]);
  printf("%s", testarr1);
  printf("%s", testarr2);
  /* char dst0[111];
   dst0[0] = 0;
   char dst00[111];
   dst00[0] = 0;

   char dst000[111];
   dst000[0] = 0;
   printf("%15.20p\n", &si1);

   print_hexadecimal(&si1, 1, 15, 0, 0, 0, 1, dst000);
   print_char(' ', dst000, 0, 0);
   printf("%s\n", dst000);

   printf("%#x %#x %#lX\n", ui1, ui2, uli1);
   print_hexadecimal(ui1, 1, 1, 0, 1, 0, 0, dst00);
   print_char(' ', dst00, 0, 0);
   print_hexadecimal(ui2, 1, 1, 0, 1, 0, 0, dst00);
   print_char(' ', dst00, 0, 0);
   print_hexadecimal(uli1, 1, 1, 0, 1, 1, 0, dst00);
   printf("%s\n", dst00);

   printf("%#o %#o %#lo\n", ui1, ui2, uli1);
   print_octal(ui1, 1, 1, 0, 1, dst0);
   print_char(' ', dst0, 0, 0);
   print_octal(ui2, 1, 1, 0, 1, dst0);
   print_char(' ', dst0, 0, 0);
   print_octal(uli1, 1, 1, 0, 1, dst0);
   printf("%s\n", dst0);

   char dst1[59];
   dst1[0] = 0;
   char dst2[59];
   dst2[0] = 0;

   char arrres[450];
   char arrresiddeal[450];
   char str[] = "this is the test!";
   char format[] =
       "%%+|%-+ +15.3ld||%+ -8.5hd|%d |%+ d| |%+++10.3d||%10.5u|, |%u| |%8lu| "
       "|%-3.1d| %.0u |%5.2c| |%-5c| |% +s|| %-8.10s| |%-3.2f| |%15.6f| "
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
   long int LI1 = -234;
   short int SI1 = 24;
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
   }*/
}
