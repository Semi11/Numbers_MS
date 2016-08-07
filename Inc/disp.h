/*NMS_disp.h*/

#ifndef _INCLUDE_NMS_DISP_
#define _INCLUDE_NMS_DISP_

#include <stdio.h>

#define ESC 0x1B
#define _CLRDISP()  printf("%c[2J",ESC);//画面をクリア

#endif
