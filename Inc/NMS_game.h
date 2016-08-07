/*NMS_game.h*/

#ifndef _INCLUDE_NMS_GAME_
#define _INCLUDE_NMS_GAME_

#define WIDTH_MAX 80
#define HEIGHT_MAX 30
#define EASY 0
#define NORMAL 1
#define HARD 2

typedef struct{
  int status;
  int data;
}Board_t;

void game_main();//ゲームのメインループ

#endif
















