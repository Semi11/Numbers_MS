#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ESC 0x1B
#define ARROW 0xe0
#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define LEFT_ARROW 0x4b
#define RIGHT_ARROW 0x4d
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37
#define INIT_STA STA_CLOSE
#define WIDTH_MAX 80
#define HEIGHT_MAX 30
#define EASY 0
#define NORMAL 1
#define HARD 2
#define WALL_SIZE 2
#define WIDTH ((10) + (WALL_SIZE))
#define HEIGHT ((10) + (WALL_SIZE))
#define SIZE (WIDTH) * (HEIGHT)
#define MINE_NUM 9
#define TREASURE_NUM 1
#define BOARD_POS_X 4
#define BOARD_POS_Y 5
#define NONE 0
#define TREASURE 100
#define MINE 101
#define WALL 102
#define SLC_OPEN 0
#define SLC_FLG 1
#define STA_CLOSE 0
#define STA_OPEN 1
#define STA_FLG 2
#define STA_WALL 3
#define AROUND_SQUARE_NUM 8
#define _GETPOS(x,y,w) ((y)*(w)+(x))
#define _CLRDISP()  printf("%c[2J",ESC);//画面をクリア
#define _PRESSENTER() while(getchar()!='\n');//Enterキー入力待機

int title();//タイトル処理
void disp_str(char str[],int x,int y,int color);//座標、文字色を指定して文字列を出力
void disp_num(int num,int x,int y,int color);//座標、文字色を指定して数字を出力
int input_num();//数字の入力
void init_ran_num();//seed値を設定
void init_disp();//画面の初期化
void init_board(int squares_dat[], int squares_sta[]);//ボードの初期化
void count_around_mines(int squares_dat[], int pos);//マスの周りの地雷をカウントする
int get_ran_num(int min,int max);//乱数を取得する
void game_main();//ゲームのメインループ
void disp_board(const int squares_dat[], const int squares_sta[]);//ボードの表示
void disp_wall(int x,int y,int width,int height);//壁の表示
void select_square(int squares_dat[], int squares_sta[]);//マスの選択
void open_square(int squares_dat[], int squares_sta[],int pos);//マスを開く
int should_continue_game(const int squares_dat[], const int squares_sta[]);//ゲームの続行判定
void process_game_cleaed();//ゲームクリア時の処理
void process_game_over();//ゲームオーバー時の処理

const int around_square_idx[AROUND_SQUARE_NUM] = {-WIDTH-1,-WIDTH,-WIDTH+1,-1,+1,+WIDTH-1,WIDTH,WIDTH+1};

int main(void){
  init_ran_num();
  init_disp();
  
  while(1){
    if(title())break;
    game_main();
  }

  return 0;
}

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

int input_num(){
  char buf[100];
  int i=0;  

  fgets(buf,sizeof(buf),stdin);

  while(buf[i]!='\n'){
    if(buf[i] < '0' || buf[i] > '9')return -1;
    i++;
  }

  return atoi(buf);
}

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
	}else if(cnt < MINE_NUM + TREASURE_NUM){
	  squares_dat[pos]=TREASURE;
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

  /* 周りにある地雷と宝物の数をカウント */
  for(i=0;i<SIZE;i++){
    if(squares_dat[i] == NONE){
      count_around_mines(squares_dat,i);
    }
  }

}

void count_around_mines(int squares_dat[],int pos){
  int i;

  for(i=0;i<AROUND_SQUARE_NUM;i++){
    if(squares_dat[pos + around_square_idx[i]] == MINE || 
       squares_dat[pos + around_square_idx[i]] == TREASURE)
      squares_dat[pos]++;
  }
}

int get_ran_num(int min,int max){
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

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
  int i,cnt=0;

  if(squares_sta[pos] != STA_OPEN && squares_sta[pos] != STA_CLOSE)return;
  
  squares_sta[pos] = STA_OPEN;

  for(i=0;i<AROUND_SQUARE_NUM;i++){
    if(squares_sta[pos + around_square_idx[i]] == STA_FLG)cnt++;
  }
  if(cnt == squares_dat[pos]){
    for(i=0;i<AROUND_SQUARE_NUM;i++){
      if(squares_sta[pos + around_square_idx[i]]==STA_CLOSE) open_square(squares_dat,squares_sta,pos + around_square_idx[i]);
    }
  }
  
}

int should_continue_game(const int squares_dat[], const int squares_sta[]){
  int i;
  
  for(i=0;i<SIZE;i++){
    if(squares_sta[i] == STA_OPEN){
      switch(squares_dat[i]){
      case MINE:
	process_game_over();
	return 0;   
      case TREASURE:
	process_game_cleaed();
	return 0;
      }
    }
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
















