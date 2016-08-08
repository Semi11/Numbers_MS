/*NMS_io.c*/

#include<stdio.h>
#include<stdlib.h>
#include"NMS_io.h"

void disp_str(char str[],int x,int y,int color){
  printf("%c[%dm",ESC,color);
  printf("%c[%d;%dH %s",ESC,y,x,str);
  printf("%c[39m",ESC);//文字色を元に戻す
}

void disp_num(int num,int x,int y,int color){ 
  printf("%c[%dm",ESC,color);
  printf("%c[%d;%dH %d",ESC,y,x,num);
  printf("%c[39m",ESC);//文字色を元に戻す
}

int input_num(int *num){
  char buf[100];
  int i=0;  

  fgets(buf,sizeof(buf),stdin);

  while(buf[i]!='\n'){
    if(buf[i] < '0' || buf[i] > '9')return 1;
    i++;
  }

  *num=atoi(buf);

  return 0;
}









