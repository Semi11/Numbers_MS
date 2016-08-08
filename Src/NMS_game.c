/*NMS_game.c*/

#include "NMS_game.h"
#include "NMS_init.h"
#include "disp.h"

void game_main(){
  Board_t board;

  select_level(&board);
  init_board(&board);
  disp_board(board);
  _PRESSENTER();
}

void disp_board(const Board_t board){
  int i;
  const int wall=2;

  _CLRDISP();

  for(i=board.width * board.height-1;i >= 0 ;i--){
    int x,y;
    x=i%(board.width+1)+wall;
    y=i/(board.width+1)+wall;
    switch(board.chip[i].status){
    case STA_CLOSE:
      disp_str("#",x,y,WHITE);break;
    case STA_OPEN:
      switch(board.chip[i].data){
      case NONE: disp_str(".",x,y,WHITE);break;
      case 1: disp_str("1",x,y,WHITE);break;
      case 2: disp_str("2",x,y,CYAN);break;
      case 3: disp_str("3",x,y,BLUE);break;
      case 4: disp_str("4",x,y,GREEN);break;
      case 5: disp_str("5",x,y,YELLOW);break;
      case 6: disp_str("6",x,y,MAGENTA);break;
      case 7: disp_str("7",x,y,CYAN);break;
      case 8: disp_str("8",x,y,BLUE);break;
      case MINE: disp_str("*",x,y,RED);break;
      default: disp_str("E",x,y,RED);break;//エラー
      }
      break;
    case STA_FLG:
      disp_str("!",x,y,RED);break;
    }
  }
}


















