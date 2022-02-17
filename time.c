#pragma once
#include "time.h"

extern long time,counter;
extern long date,alarm[4],alarmctl;
extern char x,y,mode;
extern char update;

void set_time()//设置时间
{
    OLED_Clear();
    OLED_ShowString(0,0,"____  __  __  ");
    OLED_ShowCHinese(8*4,0,0);//年
    OLED_ShowCHinese(8*8,0,1);//月
    OLED_ShowCHinese(8*12,0,2);//日
    OLED_ShowCHinese(8*0,6,25);//确
    OLED_ShowCHinese(8*2,6,26);//认
    OLED_ShowString(8*0,2,"__:__:__");
    OLED_ShowString(12*8, 2, "PM");
    x=y=0;time=date=0;
    char month,day,hh,mm,ss,ch;month=day=hh=mm=ss=0;int year=0;
    //yyyy mm dd
    year=getnume();if(mode!=11){OLED_Clear();return;}
    year=10*year+getnume();if(mode!=11){OLED_Clear();return;}
    year=10*year+getnume();if(mode!=11){OLED_Clear();return;}
    year=10*year+getnume();if(mode!=11){OLED_Clear();return;}
    x=6;
    month=getnume();if(mode!=11){OLED_Clear();return;}
    month=10*month+getnume();if(mode!=11){OLED_Clear();return;}
    x=10;
    day=getnume();if(mode!=11){OLED_Clear();return;}
    day=10*day+getnume();if(mode!=11){OLED_Clear();return;}

    //hh:mm:ss
    x=0,y=2;
    hh=getnume();if(mode!=11){OLED_Clear();return;}
    hh=10*hh+getnume();if(mode!=11){OLED_Clear();return;}
    x=3;
    mm=getnume();if(mode!=11){OLED_Clear();return;}
    mm=10*mm+getnume();if(mode!=11){OLED_Clear();return;}
    x=6;
    ss=getnume();if(mode!=11){OLED_Clear();return;}
    ss=10*ss+getnume();if(mode!=11){OLED_Clear();return;}
    do{
        ch=getch();
        if(ch=='B')
        {
            OLED_ShowCHinese(14*8,2,36);
            if(hh!=12)hh+=12;
        }
        if(mode!=11){OLED_Clear();return;}
    }while(ch!='*');
    if(error_check(year,month,day,hh,mm,ss))return;
    update=1;
    char i=0;date=time=0;
    date=(long)year*10000+(long)month*100+day;
    time=(long)hh*3600+(long)mm*60+ss;
    save_time();mode/=10;
}
void get_time()//从flash中读取时间
{
    time= *((long*)0x1800);
    date= *((long*)0x1880);
}
void save_time()//将时间存至flash
{
    time++;
    if(time==86400){
        do{time=0,date++;update=1;
        int day=date%100,month=date%10000/100,year=date/10000;
        if(day<29)break;//C不能break出if，加个do while(0)
        if(day==29&&month==2&&(!((year%4==0&&year%100!=0)||year%400==0)) )
            date+=72;//2.29 -> 301
        else if(day==30&&month==2&&((year%4==0&&year%100!=0)||year%400==0))
            date+=71;//2.30->301
        else if(day==31&&(month==4||month==6||month==9||month==11))
            date+=70;//431->501
        else if(day==32&&month!=12)
            date+=69;//532->601
        else if(day==32&&month==12)
            date+=8869;//20211232->20220101
        }while(0);
    }
    flash_erase(0x1800);flash_write_long((long*)0x1800,time);
    if(update){flash_erase(0x1880);flash_write_long((long*)0x1880,date);}
}

char week()
{
    int year=date/10000;char month=date%10000/100,day=date%100,_week;
    if(month==1||month==2)year--,month+=12;
    _week=((year/100)/4-2*(year/100)+(year%100)+(year%100)/4+26*(month+1)/10+day-1 )%7;
    return _week;
}
void set_alarm(char n)
{
    OLED_Clear();
    OLED_ShowCHinese(8*0,6,25);//确
    OLED_ShowCHinese(8*2,6,26);//认
    char str2[]="__:__";
    OLED_ShowString(8*4,2,str2);
    char num[5];
    x=4,y=2;
    num[0]=getnume();if(mode<120){OLED_Clear();return;}
    num[1]=getnume();if(mode<120){OLED_Clear();return;}
    x=7;
    num[2]=getnume();if(mode<120){OLED_Clear();return;}
    num[3]=getnume();if(mode<120){OLED_Clear();return;}
   
    do{
        num[4]=getch();
        if(mode<120){OLED_Clear();return;}
    }while(num[4]!='*');
    
    alarm[n-1]=num[0]*36000+num[1]*3600+num[2]*600+num[3]*60;
    save_alarm();mode/=10;
}
void save_alarm()
{
    char i=0;long* p=(long*)0x1900;
    flash_erase(0x1900);
    for(;i<4;i++)
        flash_write_long(p++,alarm[i]);
    flash_write_long(p,alarmctl);
}
void get_alarm(){
    char i=0;long* p=0x1900;
    for(;i<4;i++)
        alarm[i]=*p++;
    alarmctl=*((long*)0x1910);
}
char check_alarm(){
    char i=0;
    for(;i<4;i++)
		if(GET_BIT(alarmctl,i)&&(time==alarm[i]))
            return 1;
    return 0;
}

void set_counter()
{
    OLED_Clear();
    //OLED_ShowCHinese(8*0,6,25);OLED_ShowCHinese(8*2,6,26);//确认
    OLED_ShowCHinese(8*12,0,28);OLED_ShowCHinese(8*14,0,29);//开始
    //OLED_ShowCHinese(8*12,2,30);OLED_ShowCHinese(8*12,2,31);//暂停
    //OLED_ShowCHinese(8*12,4,32);OLED_ShowCHinese(8*12,4,33);//清零
    char str2[]="__:__:__";
    OLED_ShowString(8*0,0,str2);
    char num[7];
    
    x=0,y=0;//hh:mm:ss
    num[0]=getnume();if(mode!=14){OLED_Clear();return;}
    num[1]=getnume();if(mode!=14){OLED_Clear();return;}
    x=3;
    num[2]=getnume();if(mode!=14){OLED_Clear();return;}
    num[3]=getnume();if(mode!=14){OLED_Clear();return;}
    x=6;
    num[4]=getnume();if(mode!=14){OLED_Clear();return;}
    num[5]=getnume();if(mode!=14){OLED_Clear();return;}
    
    do{
        num[6]=getch();
        if(mode!=14){OLED_Clear();return;}
    }while(num[6]!='A');
    counter=num[0]*36000+num[1]*3600+num[2]*600+num[3]*60+num[4]*10+num[5];
    OLED_Clear();
}

char error_check(int year,char month,char day,char hh,char mm,char ss)//1-error;0-no-error
{
    do{
        if(day>28&&month==2&&(!((year%4==0&&year%100!=0)||year%400==0)) )
            break;//平年2月超过28
        if(day>29&&month==2&&((year%4==0&&year%100!=0)||year%400==0))
            break;//闰年2月超过29
        if(day>30&&(month==4||month==6||month==9||month==11))
            break;//小月超过30
        if(day>31)break;
        if(month>12)break;
        if(hh>23)break;
        if(mm>59)break;
        if(ss>59)break;
        return 0;
    }while(0);
    OLED_Clear();
    OLED_ShowString(0,2,"ILLEGAL INPUT!");
    getch();
    return 1;
}
