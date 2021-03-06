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
#define MINE_NUM 9
#define TREASURE_NUM 1
#define BOARD_POS_X 4
#define BOARD_POS_Y 5
#define NONE 0
#define TREASURE 100
#define MINE 101
#define WALL 102
#define SLC_OPEN 0
#define SLC_FLG 1
#define STA_CLOSE 0
#define STA_OPEN 1
#define STA_FLG 2
#define STA_WALL 3


void game_main();//ゲームのメインループ
void disp_board(const int squares_dat[], const int squares_sta[]);//ボードの表示
void disp_wall(int x,int y,int width,int height);//壁の表示
void select_square(int squares_dat[], int squares_sta[]);//マスの選択
void open_square(int squares_dat[], int squares_sta[],int pos);//マスを開く
void open_none(int squares_dat[], int squares_sta[],int pos);//周りに地雷のないマスを開く
int should_continue_game(const int squares_dat[], const int squares_sta[]);//ゲームの続行判定
void process_game_cleaed();//ゲームクリア時の処理
void process_game_over();//ゲームオーバー時の処理

#endif
















