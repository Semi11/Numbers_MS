/*NMS_init.h*/

#ifndef _INCLUDE_NMS_INIT_
#define _INCLUDE_NMS_INIT_

#include"NMS_game.h"

#define INIT_STA STA_CLOSE
#define _GETPOS(x,y,w) ((y)*(w)+(x))

void init_ran_num();//seed値を設定
void init_disp();//画面の初期化
void init_board(Square_t *board);//ボードの初期化
void count_around_mines(Square_t *board,int pos);//マスの周りの地雷をカウントする
int get_ran_num(int min,int max);//乱数を取得する

#endif


















