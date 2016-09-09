/*NMS_io.c*/

#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include"NMS_io.h"

void disp_str(char str[],int x,int y,int color){
  printf("%c[%dm",ESC,color);
  printf("%c[%d;%dH %s",ESC,y,x,str);
  printf("%c[39m",ESC);//文字色を元に戻す
}

void disp_num(int num,int x,int y,int color){ 
  printf("%c[%dm",ESC,color);
  printf("%c[%d;%dH %d",ESC,y,x,num);
  printf("%c[39m",ESC);//文字色を元に戻す
}

int kbhit(void){
  struct termios old_termios_cfg,new_termios_cfg;
  int c,file_descriptor_flg;

  tcgetattr(STDIN_FILENO, &old_termios_cfg);//端末の設定を取得
  new_termios_cfg = old_termios_cfg;
  new_termios_cfg.c_lflag &= ~(ICANON | ECHO);//端末を非カノニカルモードかつ、エコーをしないように設定
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios_cfg);//設定を適応
  file_descriptor_flg = fcntl(STDIN_FILENO, F_GETFL);//ファイルディスクリプターフラグを読み出す
  fcntl (STDIN_FILENO, F_SETFL , file_descriptor_flg | O_NONBLOCK);//入出力操作でブロックしないように設定

  c = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &old_termios_cfg);//端末の設定を元に戻す
  fcntl(STDIN_FILENO, F_SETFL, file_descriptor_flg);//ファイルディスクリプターフラグを元に戻す

  if(c != EOF){
    ungetc(c, stdin);//ストリームに読み込んだ文字を押し戻す
    return 1;
  }

  return 0;
  
}

int input_num(int *num){
  char buf[100];
  int i=0;  

  *num='\0';

  fgets(buf,sizeof(buf),stdin);

  while(buf[i]!='\n'){
    if(buf[i] < '0' || buf[i] > '9')return 1;
    i++;
  }

  *num=atoi(buf);

  return 0;
}









