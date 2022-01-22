#pragma once
#include "display.h"
#define TEMP_30C  *((unsigned int *)0x1A1A) //温度传感器校准后 1.5V,30C时 数据的地址
#define TEMP_85C  *((unsigned int *)0x1A1C)
void date_to_str(char* str)
{
    str[0]=date/10000000+'0';
    str[1]=date%10000000/1000000+'0';
    str[2]=date%1000000/100000+'0';
    str[3]=date%100000/10000+'0';
    str[5]=date%10000/1000+'0';
    str[6]=date%1000/100+'0';
    str[8]=date%100/10+'0';
    str[9]=date%10+'0';
    str[4]=str[7]='.';str[10]='\0';
    update=0;
}
void time_to_str(long t,char* str)//将时间转化为字符
{
  char hour=t/3600,minute=t%3600/60,second=t%60;
  if(hour==24)hour=0;
  str[0]=hour/10+'0';str[1]=hour%10+'0';
  str[2]=':';
  str[3]=minute/10+'0';str[4]=minute%10+'0';
  str[5]=':';
  str[6]=second/10+'0';str[7]=second%10+'0';
  str[8]='\0';
}
void show_homepage()
{
    static char _date[11],_week;
    char _time[9],_temp[6];
	time_to_str(time,_time);
	OLED_ShowString(0*8, 2, _time);//时间

    if(update){date_to_str(_date);_week=week();}
	OLED_ShowString(0*8,0, _date);//日期
    
    OLED_ShowCHinese(9*8,2,17);
    OLED_ShowCHinese(11*8,2,_week+18);//星期
    
    get_temp(_temp);
    OLED_ShowString(11*8,0, _temp);

    OLED_ShowCHinese(0,6,14);
    OLED_ShowCHinese(16,6,15);
    OLED_ShowCHinese(32,6,16);
}
void show_menu()
{
    OLED_Clear();
    OLED_ShowString(0, 0,"1.");//1.设置时间
    OLED_ShowCHinese(2*8, 0, 3);
    OLED_ShowCHinese(4*8, 0, 4);
    OLED_ShowCHinese(6*8, 0, 5);
    OLED_ShowCHinese(8*8, 0, 6);

    OLED_ShowString(0, 2,"2.");//2.闹钟
    OLED_ShowCHinese(2*8, 2, 7);
    OLED_ShowCHinese(4*8, 2, 8);

    OLED_ShowString(0, 4,"3.");//3.秒表
    OLED_ShowCHinese(2*8, 4, 9);
    OLED_ShowCHinese(4*8, 4, 10);

    OLED_ShowString(0, 6,"4.");//4.倒计时
    OLED_ShowCHinese(2*8, 6, 11);
    OLED_ShowCHinese(4*8, 6, 12);
    OLED_ShowCHinese(6*8, 6, 13);

    char ch;
    do{
        ch=getnum();
        if(mode!=1){OLED_Clear();return;}
    }while(ch<0||ch>4);
    //if(ch=='#')mode/=10;
    mode=10*mode+ch;
    OLED_Clear();
}

void choose_alarm()
{
    char i=0;
    char ala[11];ala[1]='.';
    for(i=0;i<4;i++)
    {
        ala[0]='1'+i;
        time_to_str(alarm[i],ala+2);
	    OLED_ShowString(0*8, i*2, ala);
        OLED_ShowCHinese(14*8,i*2,GET_BIT(alarmctl,i)+27);
    }
    do{
        i=getch();
        if(i>='A'&&i<='D')
            {alarmctl ^= 1<<(i-'A');
            OLED_ShowCHinese(14*8,(i-'A')*2,GET_BIT(alarmctl,i-'A')+27);}
        if(i>='0'&&i<='9')
            mode=10*mode+i-'0';
    }while(mode==12);
    flash_erase(0x1900);
    save_alarm();
    flash_write_long((long*)0x1910,alarmctl);
}
char second_10=0,_timer[12];//0.1s
void show_timer()
{
    //static char _time[12];
    if(timer==-1)
    {
	    time_to_str(0,_timer);
        _timer[8]='\0',_timer[9]='0',_timer[10]='\0';
	    OLED_ShowString(0*8, 2, _timer);
        OLED_ShowCHinese(8*12,0,28);OLED_ShowCHinese(8*14,0,29);//开始
        do{
            _timer[11]=getch();
            if(mode!=13){OLED_Clear();return;}
        }while(_timer[11]!='A');
        timer=0;
    }
    if(timer<99999){OLED_ShowCHinese(8*12,2,30);OLED_ShowCHinese(8*14,2,31);}//暂停
    else    {OLED_ShowCHinese(8*12,2,34);OLED_ShowCHinese(8*14,2,35);
            OLED_ShowCHinese(8*12,4,32);OLED_ShowCHinese(8*14,4,33);}

    //TA2CTL |= ID_0 +TASSEL_1 +MC_1;
    //TA2CCR0=3276;
    //TA2CCTL0 |= CCIE;
    
    if(getchar()=='B')
    {
        //TA2CTL |= MC_0;
        //TA2CCTL0 &=~ CCIE;
        if(timer<99999)timer+=100000;
        else timer-=100000;
    }
    if(getchar()=='C')
        timer=-1;

    if(timer<99999)
	    time_to_str(timer,_timer);
	OLED_ShowString(0*8, 2, _timer);
}
/*
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER_ISR(void)
{
    second_10=second_10+1;
    if(second_10==10){
        second_10=0;timer++;
	    time_to_str(timer,_timer);
    }
    if(mode==13){
        _timer[9]=second_10+'0';
	    OLED_ShowString(0*8, 2, _timer);
    }
}*/

void show_counter()
{
    //OLED_Clear();
    //OLED_ShowCHinese(8*0,6,25);OLED_ShowCHinese(8*2,6,26);//确认
    //OLED_ShowCHinese(8*12,0,28);OLED_ShowCHinese(8*14,0,29);//开始
    if(counter<99999)
        {OLED_ShowCHinese(8*12,2,30);OLED_ShowCHinese(8*14,2,31);}//暂停
    else {OLED_ShowCHinese(8*12,2,34);OLED_ShowCHinese(8*14,2,35);}
    OLED_ShowCHinese(8*12,4,32);OLED_ShowCHinese(8*14,4,33);//清零
    
    //counter--;
    static char _time[9];
    if(getchar()=='B')
        {if(counter<99999)counter+=100000;
        else counter-=100000;}
    else if(getchar()=='C')
        counter=-1;
    if(counter<99999)
	    time_to_str(counter,_time);
	OLED_ShowString(0*8, 2, _time);
    if(counter==0)
        {belling=10;bell_on();led_on();return;}
}

int temp;  
void get_temp(char* _temp)
{
    //temp=( 30+(temp-TEMP_30C)*55.0/(TEMP_85C-TEMP_30C) )*10;
    temp=(30+(temp-2225)*11.0/69.0)*10;
    _temp[5]='\0';_temp[4]='C';
    _temp[0]=temp/100+'0';_temp[1]=temp%100/10+'0';
    _temp[2]='.';_temp[3]=temp%10+'0';
}
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    if(__even_in_range(ADC12IV,34)==6)
        temp=ADC12MEM0;
}
