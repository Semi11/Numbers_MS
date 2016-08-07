/*NMS_init.c*/

#include"disp.h"
#include"NMS_game.h"

void init_disp(){
  system("resize -s 35 100");//ターミナルのサイズを縦35横100に設定
  _CLRDISP();
}

void select_level(Board_t *board){
  int level;
  disp_str("難易度を選んでください",0,0,WHITE);
  disp_str("0:Easy",0,2,GREEN);
  disp_str("1:Normal",0,3,YELLOW);
  disp_str("2:Hard",0,4,RED);
  disp_str("Select(0~2)->",0,6,WHITE);
  scanf("%d",&level);

  switch(level){
  case EASY:
    board->width=EASY_WIDTH;
    board->height=EASY_HEIGHT;
    board->bom=EASY_BOM_NUM;
    break;
  case NORMAL:
    board->width=NORMAL_WIDTH;
    board->height=NORMAL_HEIGHT;
    board->bom=NORMAL_BOM_NUM;
    break;
  case HARD:
    board->width=HARD_WIDTH;
    board->height=HARD_HEIGHT;
    board->bom=HARD_BOM_NUM;
    break;
  }
}











