/*NMS_game.c*/

#include "NMS_game.h"
#include "NMS_init.h"
#include "NMS_io.h"

void game_main(){
  int squares_dat[SIZE];//全マスのデータ
  int squares_sta[SIZE];//全マスの状態

  init_board(squares_dat, squares_sta);
  
  while(1){
    disp_board(squares_dat, squares_sta);
    
    if(should_continue_game(squares_dat, squares_sta)){
      select_square(squares_dat, squares_sta);
    }else{
      break;
    }
  }
  
}

void disp_board(const int squares_dat[], const int squares_sta[]){
  int i,x,y;
  
  _CLRDISP();

  for(i=SIZE-1;i >= 0 ;i--){
    int data=squares_dat[i];
    x = i % WIDTH * 2 + BOARD_POS_X;
    y = i / WIDTH + BOARD_POS_Y;

    switch(squares_sta[i]){
    case STA_CLOSE:
      disp_str("#",x,y,WHITE);break;
    case STA_OPEN:
      switch(data){
      case NONE: disp_str(".",x,y,WHITE);break;
      case 1: disp_str("1",x,y,CYAN);break;
      case 2: disp_str("2",x,y,BLUE);break;
      case 3: disp_str("3",x,y,GREEN);break;
      case 4: disp_str("4",x,y,YELLOW);break;
      case 5: disp_str("5",x,y,MAGENTA);break;
      case 6: disp_str("6",x,y,CYAN);break;
      case 7: disp_str("7",x,y,BLUE);break;
      case 8: disp_str("8",x,y,GREEN);break;
      case TREASURE: disp_str("$",x,y,YELLOW);break;
      case MINE: disp_str("*",x,y,RED);break;
      case WALL: disp_wall(x,y,WIDTH,HEIGHT);break;
      default: disp_str("E",x,y,RED);break;//エラー
      }
      break;
    case STA_FLG:
      disp_str("!",x,y,RED);break;
    }
  }
  
  for(x=WIDTH-WALL_SIZE-1;x>=0;x--){
    if(x>=10)disp_num(x/10,x*2+BOARD_POS_X+WALL_SIZE,BOARD_POS_Y-2,WHITE);
    disp_num(x%10,x*2+BOARD_POS_X+WALL_SIZE,BOARD_POS_Y-1,WHITE);
  }

  for(y=HEIGHT-WALL_SIZE-1;y>=0;y--){
    disp_num(y,BOARD_POS_X-2,y+BOARD_POS_Y+1,WHITE);
  }

}

void disp_wall(int x,int y,int width,int height){
  if((x==BOARD_POS_X &&(y==BOARD_POS_Y || y==BOARD_POS_Y+height-1)))disp_str("+-",x,y,WHITE);
  else if((y==BOARD_POS_Y && x==BOARD_POS_X+width*2-2)||(y==BOARD_POS_Y+height-1 && x==BOARD_POS_X+width*2-2))disp_str("+",x,y,WHITE);
  else if(x==BOARD_POS_X || x==BOARD_POS_X+width*2-2)disp_str("|",x,y,WHITE);
  else if(y==BOARD_POS_Y || y==BOARD_POS_Y+height-1)disp_str("--",x,y,WHITE);
}
      
void select_square(int squares_dat[], int squares_sta[]){
  int sq_num,action,i;
  const int disp_x = 0;
  const int disp_y = HEIGHT + WALL_SIZE + BOARD_POS_Y;

  disp_str("マスを選んでください->",disp_x,disp_y,WHITE);

  sq_num = input_num();

  if(sq_num == -1)return;
  if(sq_num<0 || sq_num>=(SIZE))return;
  sq_num = sq_num + WIDTH+1 +(sq_num/(WIDTH-WALL_SIZE) * WALL_SIZE);//選択番号を見た目どおりにする
  
  disp_str("行動を選んでください",disp_x,disp_y+1,WHITE);
  disp_str("0:開く",disp_x,disp_y+2,GREEN);
  disp_str("1:旗を立てる/おろす",disp_x,disp_y+3,BLUE);
  disp_str("2:キャンセル",disp_x,disp_y+4,YELLOW);
  disp_str("Select(0~2)->",disp_x,disp_y+5,WHITE);

  action = input_num();

  if(action == -1)return;
  
  switch(action){
  case SLC_OPEN:

    for(i=sq_num + 1;i<SIZE;i++){
      if(squares_dat[i] == TREASURE){
	disp_str("答えはもっと大きいです",disp_x,disp_y+7,WHITE);
	_PRESSENTER()
	  break;
      }
    }
    
    for(i=sq_num - 1;i>=0;i--){
      if(squares_dat[i] == TREASURE){
	disp_str("答えはもっと小さいです",disp_x,disp_y+7,WHITE);
	_PRESSENTER()
	  break;
      }
    }
  
    open_square(squares_dat, squares_sta,sq_num);
    
    break;
  case SLC_FLG:
    if(squares_sta[sq_num] == STA_CLOSE){
      squares_sta[sq_num] = STA_FLG;
    }else if(squares_sta[sq_num] == STA_FLG){
      squares_sta[sq_num]=STA_CLOSE;
    }
    break;
  default:return;
  }

}

void open_square(int squares_dat[], int squares_sta[], int pos){

  if(squares_sta[pos] != STA_CLOSE)return;
  
  if(squares_dat[pos]==NONE)
    open_none(squares_dat, squares_sta, pos);
  else 
    squares_sta[pos] = STA_OPEN;
}

void open_none(int squares_dat[], int squares_sta[], int pos){
  const int width = WIDTH;
  const int height = HEIGHT;
  int x = pos % WIDTH;
  int y = pos / WIDTH; 

  squares_sta[pos] = STA_OPEN;

  open_square(squares_dat, squares_sta, _GETPOS(x-1,y-1,width));//左上
  open_square(squares_dat, squares_sta, _GETPOS(x,y-1,width));//上
  open_square(squares_dat, squares_sta, _GETPOS(x+1,y-1,width));//右上
  open_square(squares_dat, squares_sta, _GETPOS(x+1,y,width));//右
  open_square(squares_dat, squares_sta, _GETPOS(x+1,y+1,width));//右下
  open_square(squares_dat, squares_sta, _GETPOS(x,y+1,width));//下
  open_square(squares_dat, squares_sta, _GETPOS(x-1,y+1,width));//左下
  open_square(squares_dat, squares_sta, _GETPOS(x-1,y,width));//左

}

int should_continue_game(const int squares_dat[], const int squares_sta[]){
  int i,mine_cnt=0,get_treasure_flg=0;

  for(i=0;i<SIZE;i++){
    switch(squares_sta[i]){
    case STA_OPEN:
      if(squares_dat[i]==MINE){
	process_game_over();
	return 0;    
      }else if(squares_dat[i]==TREASURE){
	get_treasure_flg=1;
      }
      break;
    case STA_CLOSE:
      mine_cnt--;
      break;
    case STA_FLG:
      if(squares_dat[i]==MINE){
	mine_cnt++;
      }else{
	mine_cnt--;
      }
      break;
    }
  }
  
  if(mine_cnt==MINE_NUM && get_treasure_flg){
    process_game_cleaed();
    return 0;
  }

  return 1;
}

void process_game_cleaed(){
  disp_str("Game clear",30,15,YELLOW);
  _PRESSENTER();
}

void process_game_over(){
  disp_str("Game over",30,15,RED);
  _PRESSENTER();
}
















