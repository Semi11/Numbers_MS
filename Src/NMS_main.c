#include<stdio.h>
#include"NMS_init.h"
#include"NMS_title.h"
#include"NMS_game.h"

int main(void){
  init_ran_num();
  init_disp();
  
  while(1){
    if(title())break;
    game_main();
  }

  return 0;
}
