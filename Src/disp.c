/*NMS_disp.c*/

#include<stdio.h>
#include"disp.h"

void disp_str(char str[],int x,int y,int color){
  printf("%c[%dm",ESC,color);
  printf("%c[%d;%dH %s",ESC,y,x,str);
  printf("%c[39m",ESC);//文字色を元に戻す
}











