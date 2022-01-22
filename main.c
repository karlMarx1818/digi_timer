#pragma once
#include <msp430.h> 
#include "time.h"
#define GET_BIT(val,n)   ( ( (val) & (1<<(n)) )?1:0 )
//#include "IO.h"
//#include "display.h"


long time;//save in infoD 0x1800
long timer=-1,counter=-1;
long date;//save in infoC 0x1880
long alarm[4],alarmctl;//save in 0x1900
//date:yyyymmddw	time:0-86399s
char x,y,mode,belling;//当前屏幕坐标; 功能模式; 响铃时间
char update=1;//更新日期字符串

//mode :0-主页		1-一级菜单：设置、闹钟、秒表、定时器
//二级菜单：11-设置日期 12-选择闹钟 13-秒表 14-定时器
//三级菜单：121,122,123,124-设置闹钟

/**
 * main.c
 */
void initialize()
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	OLED_Init();OLED_Clear();
	init_keypad();
	x=y=mode=0;
	counter=timer=-1;
	get_time();
	get_alarm();

	__bis_SR_register(GIE);//计时中断 freq=1Hz
	TA0CTL|=TASSEL_1+TACLR+MC_1;
	TA0CCR0=32768;TA0CCTL0=CCIE;

	REFCTL0 &=~ REFMSTR;//温度传感器 ADC init
    ADC12CTL0=ADC12SHT0_8+ADC12REFON+ADC12ON;
    ADC12CTL1=ADC12SHP;
    ADC12MCTL0=ADC12SREF_1+ADC12INCH_10;
    ADC12IE=ADC12IE0;
    _delay_cycles(100);
    ADC12CTL0 |= ADC12ENC;

	TB0CTL = TBSSEL_1 + TBCLR + MC_1;
	TB0CCR0=3277;
	TB0CCTL0 = CCIE;
}
int main(void)
{
	initialize();
	while (1)
	{
		if(!mode&&getchar()=='*')mode=1;
		if(getchar()=='D')alarmctl ^= BIT5;//12/24h
		if(mode==1)show_menu();
		if(mode==11)set_time();
		if(mode==12)choose_alarm();
		if(mode>120)set_alarm(mode%120);
		if(mode==13)show_timer();
		if(mode==14&&counter==-1)set_counter();
		if(mode==14&&counter>=0)show_counter();
		if(belling>0&&(getchar()!=127))belling=0;//按任意键停止闹钟 
	}
	return 0;
}
#pragma vector=TIMER0_A0_VECTOR//每秒触发
__interrupt void TIMER0_A0_ISR(void)
{
	ADC12CTL0 &=~ ADC12SC;//收集温度传感器数据
    ADC12CTL0 |= ADC12SC;

	if(mode==0)show_homepage();
	//if(mode==14&&counter>=0)show_counter();
	if(counter>0&&counter<99999)counter--;
	if(counter==0){counter--;belling=10;bell_on();led_on();}
	if(timer>=0&&timer<99999)timer++;
	if(check_alarm())
		{belling=20;bell_on();led_on();}
	if(belling--==0){bell_off();led_off();}
	save_time();
}
