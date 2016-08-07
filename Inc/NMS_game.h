/*NMS_game.h*/

#ifndef _INCLUDE_NMS_GAME_
#define _INCLUDE_NMS_GAME_

#define WIDTH_MAX 80
#define HEIGHT_MAX 30
#define EASY 0
#define NORMAL 1
#define HARD 2
#define EASY_WIDTH 10
#define EASY_HEIGHT 10
#define NORMAL_WIDTH 16
#define NORMAL_HEIGHT 16
#define HARD_WIDTH 25
#define HARD_HEIGHT 25
#define EASY_BOM_NUM 10
#define NORMAL_BOM_NUM 40
#define HARD_BOM_NUM 99 

typedef struct{
  int status;
  int data;
}Chip_t;

typedef struct{
  Chip_t *chip;
  int width;
  int height;
  int bom;
}Board_t;

void game_main();//ゲームのメインループ

#endif
















