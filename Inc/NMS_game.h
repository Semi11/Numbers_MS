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
#define EASY_MINE_NUM 10
#define NORMAL_MINE_NUM 40
#define HARD_MINE_NUM 99 
#define NONE 0
#define MINE -1
#define SLC_OPEN 0
#define SLC_FLG 1

enum {
  STA_CLOSE,
  STA_OPEN,
  STA_FLG,
};

typedef struct{
  int status;
  int data;
}Square_t;

typedef struct{
  Square_t *squares;
  int width;
  int height;
  int size;
  int bom_num;
}Board_t;

void game_main();//ゲームのメインループ
void disp_board(const Board_t board);//ボードの表示
void select_square(Board_t *board);//マスの選択
void open_square(Board_t *board,int pos);//マスを開く
void open_none(Board_t *board,int pos);//周りに地雷のないマスを開く

#endif
















