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
    _CLRDISP();
    disp_str("難易度を選んでください",0,0,WHITE);
    disp_str("0:Easy",0,2,GREEN);
    disp_str("1:Normal",0,3,YELLOW);
    disp_str("2:Hard",0,4,RED);
    disp_str("Select(0~2)->",0,6,WHITE);
    if(input_num(&level))continue;
   
    flg=0;

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
      continue;
      break;
    }
    board->size = board->width * board->height;
  }
  _CLRDISP();
}

void init_board(Board_t *board){
  int i;

  /* 動的メモリ確保 */
  board->squares=(Square_t *)malloc(sizeof(Square_t) * board->size);
  if(board->squares==NULL){
    _CLRDISP();
    disp_str("error:ボードのメモリ確保に失敗",0,0,RED);
    exit(1);
  }  

  /* ボードの状態を全て初期状態にし、個数分だけ地雷を設置 */
  for(i=0;i<board->size;i++){
    board->squares[i].status=INIT_STA;
    if(i < board->bom_num)board->squares[i].data=MINE;
    else board->squares[i].data=NONE;
  }
    
  /* 地雷を全てシャッフルする */
  for(i=0;i<board->size;i++){
    int j = get_ran_num(0,board->size-1);
    int buf = board->squares[i].data;
    board->squares[i].data = board->squares[j].data;
    board->squares[j].data = buf;
  }

  /* 周りにある地雷の数をカウント */
  for(i=0;i<board->size;i++){
    if(board->squares[i].data == NONE){
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
    if(board->squares[_GETPOS(x,y-1,width)].data == MINE){
      board->squares[pos].data++;//上
    }
    if(x-1 >= 0){
      if(board->squares[_GETPOS(x-1,y-1,width)].data == MINE)board->squares[pos].data++;//左上
    }
    if(x+1 < width){
      if(board->squares[_GETPOS(x+1,y-1,width)].data == MINE)board->squares[pos].data++;//右上
    }
  }

  /* 下３つ */
  if(y+1 < height){
    if(board->squares[_GETPOS(x,y+1,width)].data == MINE){
      board->squares[pos].data++;//下
    }
    if(x-1 >= 0){
      if(board->squares[_GETPOS(x-1,y+1,width)].data == MINE)board->squares[pos].data++;//左下
    }
    if(x+1 < width){
      if(board->squares[_GETPOS(x+1,y+1,width)].data == MINE)board->squares[pos].data++;//右下
    }
  }

  /* 横２つ */
  if(x-1 >=0){
    if(board->squares[_GETPOS(x-1,y,width)].data == MINE)board->squares[pos].data++;//左
  }
  if(x+1 < width){
    if(board->squares[_GETPOS(x+1,y,width)].data == MINE)board->squares[pos].data++;//右
  }

}

int get_ran_num(int min,int max){
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}










