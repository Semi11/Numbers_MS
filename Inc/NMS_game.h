/*NMS_game.h*/

#ifndef _INCLUDE_NMS_GAME_
#define _INCLUDE_NMS_GAME_

#define WIDTH_MAX 80
#define HEIGHT_MAX 30
#define EASY 0
#define NORMAL 1
#define HARD 2
#define WALL_SIZE 2
#define EASY_WIDTH 10+WALL_SIZE
#define EASY_HEIGHT 10+WALL_SIZE
#define NORMAL_WIDTH 16+WALL_SIZE
#define NORMAL_HEIGHT 16+WALL_SIZE
#define HARD_WIDTH 25+WALL_SIZE
#define HARD_HEIGHT 25+WALL_SIZE
#define EASY_MINE_NUM 10
#define NORMAL_MINE_NUM 40
#define HARD_MINE_NUM 99 
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

typedef struct{
  Square_t *squares;
  int width;
  int height;
  int size;
  int mine_num;
}Board_t;

void game_main();//ゲームのメインループ
void disp_board(const Board_t board);//ボードの表示
void disp_wall(int x,int y,int width,int height);//壁の表示
void select_square(Board_t *board);//マスの選択
void open_square(Board_t *board,int pos);//マスを開く
void open_none(Board_t *board,int pos);//周りに地雷のないマスを開く
int should_continue_game(const Board_t board);//ゲームの続行判定
void process_game_cleaed();//ゲームクリア時の処理
void process_game_over();//ゲームオーバー時の処理

#endif
















