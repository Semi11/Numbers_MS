/*NMS_title.c*/

#include"NMS_io.h"

int title(void){
  int select;

  while(1){
    _CLRDISP();
    disp_str("Please slect ",0,0,YELLOW);
    disp_str("1: Game Start",0,3,GREEN);
    disp_str("2: END",0,4,BLUE);
    disp_str("Select(1~2)->",0,6,WHITE);
    
    select = input_num();

    switch(select){
    case 1: break;
    case 2: return 1;
    default: continue;
    }

    break;
  }
  
  
  _CLRDISP();
  return 0;
}



















