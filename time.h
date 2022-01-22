#pragma once
#include "msp430.h"
#include "display.h"
#define GET_BIT(val,n)   ( ( (val) & (1<<(n)) )?1:0 )

void set_time();//设置时间
void get_time();//从flash中读取时间
void save_time();//将时间存至flash
char week();//计算星期
void set_alarm(char n);//设置第n个闹钟
void save_alarm();//将闹钟存至infoB flash :0x1900
void get_alarm();//从flash中读取闹钟
char check_alarm();//判断是否触发闹钟