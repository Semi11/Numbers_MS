/*NMS_game.c*/

#include "NMS_game.h"
#include "NMS_init.h"
#include "NMS_io.h"

void game_main(){
  Board_t board;
  int game_flg=1;

  select_level(&board);
  init_board(&board);
  
  while(game_flg){
    disp_board(board);
    select_square(&board);
    game_flg = should_continue_game(board);
  }

}

void disp_board(const Board_t board){
  int i,x,y;
  
  _CLRDISP();

  for(i=board.size-1;i >= 0 ;i--){
    int data=board.squares[i].data;
    x = i%board.width*2+BOARD_POS_X;
    y = i/board.width+BOARD_POS_Y;

    switch(board.squares[i].status){
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
      case MINE: disp_str("*",x,y,RED);break;
      case WALL: disp_wall(x,y,board.width,board.height);break;
      default: disp_str("E",x,y,RED);break;//エラー
      }
      break;
    case STA_FLG:
      disp_str("!",x,y,RED);break;
    }
  }
  
  for(x=board.width-WALL_SIZE-1;x>=0;x--){
    if(x>=10)disp_num(x/10,x*2+BOARD_POS_X+WALL_SIZE,BOARD_POS_Y-2,WHITE);
    disp_num(x%10,x*2+BOARD_POS_X+WALL_SIZE,BOARD_POS_Y-1,WHITE);
  }

  for(y=board.height-WALL_SIZE-1;y>=0;y--){
    disp_num(y,BOARD_POS_X-2,y+BOARD_POS_Y+1,WHITE);
  }

}

void disp_wall(int x,int y,int width,int height){
  if((x==BOARD_POS_X &&(y==BOARD_POS_Y || y==BOARD_POS_Y+height-1)))disp_str("+-",x,y,WHITE);
  else if((y==BOARD_POS_Y && x==BOARD_POS_X+width*2-2)||(y==BOARD_POS_Y+height-1 && x==BOARD_POS_X+width*2-2))disp_str("+",x,y,WHITE);
  else if(x==BOARD_POS_X || x==BOARD_POS_X+width*2-2)disp_str("|",x,y,WHITE);
  else if(y==BOARD_POS_Y || y==BOARD_POS_Y+height-1)disp_str("--",x,y,WHITE);
}
      
void select_square(Board_t *board){
  int sq_num,action;
  const int disp_x = board->width*2 +5;
  const int disp_y = 5;

  disp_str("マスを選んでください->",disp_x,disp_y,WHITE);

  if(input_num(&sq_num))return;
  if(sq_num<0 || sq_num>=(board->size))return;
  
  disp_str("行動を選んでください",disp_x,disp_y+1,WHITE);
  disp_str("0:開く",disp_x,disp_y+2,GREEN);
  disp_str("1:旗を立てる/おろす",disp_x,disp_y+3,BLUE);
  disp_str("2:キャンセル",disp_x,disp_y+4,YELLOW);
  disp_str("Select(0~2)->",disp_x,disp_y+5,WHITE);

  if(input_num(&action))return;
  
  switch(action){
  case SLC_OPEN:
    open_square(board,sq_num);
    break;
  case SLC_FLG:
    if(board->squares[sq_num].status == STA_CLOSE){
      board->squares[sq_num].status = STA_FLG;
    }else if(board->squares[sq_num].status == STA_FLG){
      board->squares[sq_num].status=STA_CLOSE;
    }
    break;
  default:return;
  }

}

void open_square(Board_t *board,int pos){
  if(board->squares[pos].status != STA_CLOSE)return;
  
  if(board->squares[pos].data==NONE)
    open_none(board,pos);
  else 
    board->squares[pos].status = STA_OPEN;
}

void open_none(Board_t *board,int pos){
  const int width = board->width;
  const int height = board->height;
  int x = pos % board->width;
  int y = pos / board->width; 

  board->squares[pos].status = STA_OPEN;

  open_square(board,_GETPOS(x-1,y-1,width));//左上
  open_square(board,_GETPOS(x,y-1,width));//上
  open_square(board,_GETPOS(x+1,y-1,width));//右上  
  open_square(board,_GETPOS(x+1,y,width));//右
  open_square(board,_GETPOS(x+1,y+1,width));//右下
  open_square(board,_GETPOS(x,y+1,width));//下
  open_square(board,_GETPOS(x-1,y+1,width));//左下
  open_square(board,_GETPOS(x-1,y,width));//左

}

int should_continue_game(const Board_t board){
  int i,mine_cnt=0;

  for(i=0;i<board.size;i++){
    if(board.squares[i].data==MINE){
      if(board.squares[i].status==STA_OPEN){
	process_game_over();
	return 0;
      }else if(board.squares[i].status==STA_FLG){
	mine_cnt++;
      }
    }else if(board.squares[i].status==STA_FLG){
      mine_cnt--;
    }
  }
  
  if(mine_cnt==board.mine_num){
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
















