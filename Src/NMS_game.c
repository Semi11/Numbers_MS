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
  }

}

void disp_board(const Board_t board){
  int i,x,y;
  const int wall=2;
  const int board_pos_x=2;
  const int board_pos_y=4;

  _CLRDISP();

  for(i=board.width * board.height-1;i >= 0 ;i--){
    int data=board.squares[i].data;
    x = i%board.width*2+board_pos_x+wall;
    y = i/board.width+board_pos_y+wall;

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
      default: disp_str("E",x,y,RED);break;//エラー
      }
      break;
    case STA_FLG:
      disp_str("!",x,y,RED);break;
    }
  }

  
  for(x=board.width-1;x>=0;x--){
    if(x>=10)disp_num(x/10,x*2+board_pos_x+wall,board_pos_y-1,WHITE);
    disp_num(x%10,x*2+board_pos_x+wall,board_pos_y,WHITE);
    disp_str("--",x*2+board_pos_x+wall,board_pos_y+1,WHITE);
  }
  for(y=board.height-1;y>=0;y--){
    disp_str("|",board_pos_x+1,y+board_pos_y+wall,WHITE);
    disp_num(y,board_pos_x-1,y+board_pos_y+wall,WHITE);
  }
  disp_str("+",board_pos_x+1,board_pos_y+1,WHITE);

}
      
void select_square(Board_t *board){
  int sq_num,action;
  const int disp_x = board->width*2 +5;
  const int disp_y = 5;

  disp_str("マスを選んでください->",disp_x,disp_y,WHITE);

  if(input_num(&sq_num))return;
  if(sq_num<0 || sq_num>=(board->width*board->height))return;

  disp_str("行動を選んでください",disp_x,disp_y+1,WHITE);
  disp_str("0:開く",disp_x,disp_y+2,GREEN);
  disp_str("1:旗を立てる",disp_x,disp_y+3,BLUE);
  disp_str("2:キャンセル",disp_x,disp_y+4,YELLOW);
  disp_str("Select(0~2)->",disp_x,disp_y+5,WHITE);

  if(input_num(&action))return;
  switch(action){
  case SLC_OPEN:
    board->squares[sq_num].status=STA_OPEN;
    break;
  case SLC_FLG:
    board->squares[sq_num].status=STA_FLG;
    break;
  default:return;
  }

}

void open_none(Board_t *board,int sq_num){

}

















