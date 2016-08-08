/*NMS_io.c*/

#include<stdio.h>
#include<stdlib.h>
#include"NMS_io.h"

void disp_str(char str[],int x,int y,int color){
  printf("%c[%dm",ESC,color);
  printf("%c[%d;%dH %s",ESC,y,x,str);
  printf("%c[39m",ESC);//文字色を元に戻す
}

void input_num(int *num){
  char buf[100];
  
  fgets(buf,sizeof(buf),stdin);
      
  *num=atoi(buf);
  fflush(stdin);
}









