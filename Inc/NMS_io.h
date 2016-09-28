/*NMS_io.h*/

#ifndef _INCLUDE_NMS_IO_
#define _INCLUDE_NMS_IO_

#include <stdio.h>

#define ESC 0x1B
#define ARROW 0xe0
#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define LEFT_ARROW 0x4b
#define RIGHT_ARROW 0x4d
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

void disp_str(char str[],int x,int y,int color);//座標、文字色を指定して文字列を出力
void disp_num(int num,int x,int y,int color);//座標、文字色を指定して数字を出力
int input_num();//数字の入力

#endif










