#pragma once
#include "msp430.h"
//#include "oled.h"
#include "IO.h"
#define GET_BIT(val,n)   ( ( (val) & (1<<(n)) )?1:0 )
#define TEMP_30C  *((unsigned int *)0x1A1A) //温度传感器校准后 1.5V,30C时 数据的地址                                   
#define TEMP_85C  *((unsigned int *)0x1A1C) 

extern long time,counter,timer;
extern long date,alarm[4],alarmctl;
extern char x,y,mode,belling;
extern char update;


void time_to_str(long t,char* str);//将时间(s)转化为字符 "hh:mm:ss\0"

void date_to_str(char* str);//将日期yyyymmdd转为字符 "yyyy.mm.dd\0"

void show_homepage();//mode==0 首页 时间 日期 星期 温度

void show_menu();//mode==1   功能表

void choose_alarm();//mode==12 选择闹钟

void show_timer();//mode==13 秒表 /精度0.1s的写挂了，改为了1s

void show_counter();//mode==14 倒计时（已开始）

void get_temp();
