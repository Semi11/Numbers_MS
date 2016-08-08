/*NMS_init.c*/

#include<stdlib.h>
#include<time.h>
#include"NMS_io.h"
#include"NMS_init.h"
#include"NMS_game.h"

void init_ran_num(){
  srand((unsigned int)time(NULL));
}

void init_disp(){
  system("resize -s 35 100");//ターミナルのサイズを縦35横100に設定
  _CLRDISP();
}

void select_level(Board_t *board){
  int level,flg=1;
  while(flg){
    flg=0;
    disp_str("難易度を選んでください",0,0,WHITE);
    disp_str("0:Easy",0,2,GREEN);
    disp_str("1:Normal",0,3,YELLOW);
    disp_str("2:Hard",0,4,RED);
    disp_str("Select(0~2)->",0,6,WHITE);
    input_num(&level);

    switch(level){
    case EASY:
      board->width = EASY_WIDTH;
      board->height = EASY_HEIGHT;
      board->bom_num = EASY_MINE_NUM;
      break;
    case NORMAL:
      board->width = NORMAL_WIDTH;
      board->height = NORMAL_HEIGHT;
      board->bom_num = NORMAL_MINE_NUM;
      break;
    case HARD:
      board->width = HARD_WIDTH;
      board->height = HARD_HEIGHT;
      board->bom_num = HARD_MINE_NUM;
      break;
    default:
      flg=1;
      break;
    }
    _CLRDISP();
  }
}

void init_board(Board_t *board){
  int i,board_size=board->width * board->height;

  /* 動的メモリ確保 */
  board->chip=(Chip_t *)malloc(sizeof(Chip_t) * board_size);
  if(board->chip==NULL){
    _CLRDISP();
    disp_str("error:ボードのメモリ確保に失敗",0,0,RED);
    exit(1);
  }  

  /* ボードの状態を全て初期状態にし、個数分だけ地雷を設置 */
  for(i=0;i<board_size;i++){
    board->chip[i].status=INIT_STA;
    if(i < board->bom_num)board->chip[i].data=MINE;
    else board->chip[i].data=NONE;
  }
    
  /* 地雷を全てシャッフルする */
  for(i=0;i<board_size;i++){
    int j = get_ran_num(0,board_size-1);
    int buf = board->chip[i].data;
    board->chip[i].data = board->chip[j].data;
    board->chip[j].data = buf;
  }

  /* 周りにある地雷の数をカウント */
  for(i=0;i<board_size;i++){
    if(board->chip[i].data == NONE){
      count_around_mines(board,i);
    }
  }

}

void count_around_mines(Board_t *board,int pos){
  const int width = board->width;
  const int height = board->height;
  int x = pos % board->width;
  int y = pos / board->width; 

  /* 上３つ */
  if(y-1 >= 0){
    if(board->chip[_GETPOS(x,y-1,width)].data == MINE){
      board->chip[pos].data++;//上
    }
    if(x-1 >= 0){
      if(board->chip[_GETPOS(x-1,y-1,width)].data == MINE)board->chip[pos].data++;//左上
    }
    if(x+1 < width){
      if(board->chip[_GETPOS(x+1,y-1,width)].data == MINE)board->chip[pos].data++;//右上
    }
  }

  /* 下３つ */
  if(y+1 < height){
    if(board->chip[_GETPOS(x,y+1,width)].data == MINE){
      board->chip[pos].data++;//下
    }
    if(x-1 >= 0){
      if(board->chip[_GETPOS(x-1,y+1,width)].data == MINE)board->chip[pos].data++;//左下
    }
    if(x+1 < width){
      if(board->chip[_GETPOS(x+1,y+1,width)].data == MINE)board->chip[pos].data++;//右下
    }
  }

  /* 横２つ */
  if(x-1 >=0){
    if(board->chip[_GETPOS(x-1,y,width)].data == MINE)board->chip[pos].data++;//左
  }
  if(x+1 < width){
    if(board->chip[_GETPOS(x+1,y,width)].data == MINE)board->chip[pos].data++;//右
  }

}

int get_ran_num(int min,int max){
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}










