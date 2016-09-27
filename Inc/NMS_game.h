/*NMS_game.h*/

#ifndef _INCLUDE_NMS_GAME_
#define _INCLUDE_NMS_GAME_

#define WIDTH_MAX 80
#define HEIGHT_MAX 30
#define EASY 0
#define NORMAL 1
#define HARD 2
#define WALL_SIZE 2
#define WIDTH ((10) + (WALL_SIZE))
#define HEIGHT ((10) + (WALL_SIZE))
#define SIZE (WIDTH) * (HEIGHT)
#define MINE_NUM 10
#define BOARD_POS_X 4
#define BOARD_POS_Y 5
#define NONE 0
#define MINE 100
#define WALL 101
#define SLC_OPEN 0
#define SLC_FLG 1

enum {
  STA_CLOSE,
  STA_OPEN,
  STA_FLG,
  STA_WALL,
};

typedef struct{
  int status;
  int data;
}Square_t;

void game_main();//ゲームのメインループ
void disp_board(const Square_t square[]);//ボードの表示
void disp_wall(int x,int y,int width,int height);//壁の表示
void select_square(Square_t square[]);//マスの選択
void open_square(Square_t square[],int pos);//マスを開く
void open_none(Square_t square[],int pos);//周りに地雷のないマスを開く
int should_continue_game(const Square_t square[]);//ゲームの続行判定
void process_game_cleaed();//ゲームクリア時の処理
void process_game_over();//ゲームオーバー時の処理

#endif
















