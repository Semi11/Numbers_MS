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
  system("resize -s 30 50");//ターミナルのサイズを縦35横100に設定
  _CLRDISP();
}

void init_board(int squares_dat[], int squares_sta[]){
  int i,x,y,cnt=0;

  /* マスの状態を全て初期状態にし、個数分だけ地雷を設置 */
  for(y=0;y<HEIGHT;y++){
    for(x=0;x<WIDTH;x++){
      int pos=_GETPOS(x,y,WIDTH);

      if(y==0 || x==0 || y==HEIGHT -1 || x==WIDTH -1){
	squares_sta[pos]=STA_OPEN;
      	squares_dat[pos]=WALL;
      }else{
	 squares_sta[pos]=INIT_STA;
	 if(cnt < MINE_NUM){
	   squares_dat[pos]=MINE;
	   cnt++;
	 }else{ 
	   squares_dat[pos]=NONE;
	 }
      }

    }
  }
    
  /* 地雷を全てシャッフルする */
  for(y=1;y<=HEIGHT-WALL_SIZE;y++){
    for(x=1;x<=WIDTH-WALL_SIZE;x++){
      int _x = get_ran_num(1,WIDTH-WALL_SIZE);
      int _y = get_ran_num(1,HEIGHT-WALL_SIZE);
      int buf = squares_dat[_GETPOS(x,y,WIDTH)];
      squares_dat[_GETPOS(x,y,WIDTH)] = squares_dat[_GETPOS(_x,_y,WIDTH)];
      squares_dat[_GETPOS(_x,_y,WIDTH)] = buf;
    }
  }

  /* 周りにある地雷の数をカウント */
  for(i=0;i<SIZE;i++){
    if(squares_dat[i] == NONE){
      count_around_mines(squares_dat,i);
    }
  }

}

void count_around_mines(int squares_dat[],int pos){
  const int width = WIDTH;
  const int height = HEIGHT;
  int x = pos % WIDTH;
  int y = pos / WIDTH; 

  if(squares_dat[_GETPOS(x-1,y-1,width)] == MINE)squares_dat[pos]++;//左上
  if(squares_dat[_GETPOS(x,y-1,width)]   == MINE)squares_dat[pos]++;//上
  if(squares_dat[_GETPOS(x+1,y-1,width)] == MINE)squares_dat[pos]++;//右上
  if(squares_dat[_GETPOS(x-1,y,width)]   == MINE)squares_dat[pos]++;//左
  if(squares_dat[_GETPOS(x+1,y,width)]   == MINE)squares_dat[pos]++;//右
  if(squares_dat[_GETPOS(x-1,y+1,width)] == MINE)squares_dat[pos]++;//左下
  if(squares_dat[_GETPOS(x,y+1,width)]   == MINE)squares_dat[pos]++;//下
  if(squares_dat[_GETPOS(x+1,y+1,width)] == MINE)squares_dat[pos]++;//右下

}

int get_ran_num(int min,int max){
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}










