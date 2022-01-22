#include "keypad.h"
#include "oled.h"
#define GET_BIT(val,n)   ( ( (val) & (1<<(n)) )?1:0 )
extern long time,counter;
extern long date,alarm[4],alarmctl;
extern char x,y,mode;
extern char update;

//有do while，读取必须的输入，如设置时间、闹钟
char getch()//无回显
{
    char ch;
    do{
        ch=key();
        if(ch=='#'){mode/=10;OLED_Clear();return 127;}
    }while(ch==127);
    return ch;
}
char getche()//有回显
{
    char ch;
    do{
        ch=key();
        if(ch=='#'){mode/=10;OLED_Clear();return 127;}
    }while(ch==127);
    OLED_ShowChar(8*x,y,ch);
    x = (x + 1) % 16;
    if(!x)y+=2;
    return ch;
}
char getchar()//没有dowhile，读取可选的输入，如暂停，关停铃声
{
    char ch=key();
    if(ch=='#')
        {mode/=10;OLED_Clear();}
    return ch;
}
char getnum()
{
    char ch;
    do{
        ch=getch();
        if(ch==127){OLED_Clear();return 127;}
    }while(ch<'0'||ch>'9');
    return ch-'0';
}
char getnume()
{
    char ch;
    do{
        ch=getch();
        if(ch==127){OLED_Clear();return 127;}
    }while(ch<'0'||ch>'9');
    OLED_ShowChar(8*x,y,ch);
    x = (x + 1) % 16;
    if(!x)y+=2;
    return ch-'0';
}
void bell_on()
{
    P1DIR |=BIT6;
    TA1CTL |= ID_0 +TASSEL_1 +MC_1;
    TA1CCR0=32;
    TA1CCTL0 |= CCIE;
}
//void led_on(){}

void led_on()
{
    P3DIR |= BIT5+BIT6+BIT7;
    P2DIR |= BIT3+BIT6;
    P8DIR |= BIT1+BIT2;
    P4DIR |= BIT0;
    
    TA2CTL |= ID_0 +TASSEL_1 +MC_1;
    TA2CCR0=3276;
    TA2CCTL0 |= CCIE;
}
#pragma vector=TIMER2_A0_VECTOR
__interrupt void LED_ISR(void)
{
    P3OUT ^= BIT5+BIT6+BIT7;
    P2OUT ^= BIT3+BIT6;
    P8OUT ^= BIT1+BIT2;
    P4OUT ^= BIT0;
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void BELL_ISR(void)
{
    P1OUT^=BIT6;
}
void bell_off()
{
    TA1CTL |= ID_0 +TACLR +MC_0;
    TA1CCTL0 &=~ CCIE;
}
void led_off()
{
    TA2CTL |= ID_0 +TACLR +MC_0;
    TA2CCTL0 &=~ CCIE;
    P3OUT |= (BIT5+BIT6+BIT7);
    P2OUT |= (BIT3+BIT6);
    P8OUT |= (BIT1+BIT2);
    P4OUT |= (BIT0);
}
void flash_erase(char* p){
    FCTL1=FWKEY+ERASE;
    FCTL3=FWKEY;
    *p=0;
}
void flash_write_long(long *p,long x)
{
    FCTL1=FWKEY+BLKWRT;
    FCTL3=FWKEY;
    *p=x;
    FCTL1=FWKEY;
    FCTL3=FWKEY+LOCK;
}
