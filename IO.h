#include "keypad.h"
#include "oled.h"
#define GET_BIT(val,n)   ( ( (val) & (1<<(n)) )?1:0 )
extern long time,counter;
extern long date,alarm[4],alarmctl;
extern char x,y,mode,belling;
extern char update;

//有do while，读取必须的输入，如设置时间、闹钟
char getch();//无回显

char getche();//有回显

char getchar();//没有dowhile，读取可选的输入，如暂停，关停铃声

char getnum();

char getnume();

void bell_on();

//void led_on(){}

void led_on();


void bell_off();

void led_off();

void flash_erase(char* p);

void flash_write_long(long *p,long x);
