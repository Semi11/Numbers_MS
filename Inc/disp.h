/*NMS_disp.h*/

#ifndef _INCLUDE_NMS_DISP_
#define _INCLUDE_NMS_DISP_

#include <stdio.h>

#define ESC 0x1B
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37
#define _CLRDISP()  printf("%c[2J",ESC);//画面をクリア
#define _PRESSENTER() while(getchar()!='\n');//Enterキー入力待機

void disp_str(char str[],int x,int y,int color);//座標、文字色を指定して出力

#endif










