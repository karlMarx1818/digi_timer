#pragma once
#include "msp430.h"
#define SETBIT(reg,bit)    (reg |= (1<<bit))
#define RESETBIT(reg,bit)    (reg &=~ (1<<bit))
#define TOGBIT(reg,bit)    (reg ^= (1<<bit))
#define GETBIT(reg,bit)    (reg & (1<<bit))

void init_keypad()
{
    //row out 1.5 2.4 2.5 4.3
    SETBIT(P1DIR,5);SETBIT(P2DIR,4);SETBIT(P2DIR,5);SETBIT(P4DIR,3);
    //COL IN 2.0 1.2 1.3 1.4
    RESETBIT(P2DIR,0);RESETBIT(P1DIR,2);RESETBIT(P1DIR,3);RESETBIT(P1DIR,4);
    SETBIT(P2REN,0);SETBIT(P1REN,2);SETBIT(P1REN,3);SETBIT(P1REN,4);
    SETBIT(P2OUT,0);SETBIT(P1OUT,2);SETBIT(P1OUT,3);SETBIT(P1OUT,4);
}
char key()
{
    //row1
    RESETBIT(P1OUT,5);SETBIT(P2OUT,4);SETBIT(P2OUT,5);SETBIT(P4OUT,3);
    _delay_cycles(1000);
    if( !GETBIT(P2IN,0))
    {
        _delay_cycles(100000);
        if( !GETBIT(P2IN,0))
        return '1';
    }
    if( !GETBIT(P1IN,2))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,2))
        return '2';
    }
    if( !GETBIT(P1IN,3))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,3))
        return '3';
    }
    if( !GETBIT(P1IN,4))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,4))
        return 'A';
    }
    //row 2
    RESETBIT(P2OUT,4);SETBIT(P1OUT,5);SETBIT(P2OUT,5);SETBIT(P4OUT,3);
    _delay_cycles(1000);
    if( !GETBIT(P2IN,0))
    {
        _delay_cycles(100000);
        if( !GETBIT(P2IN,0))
        return '4';
    }
    if( !GETBIT(P1IN,2))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,2))
        return '5';
    }
    if( !GETBIT(P1IN,3))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,3))
        return '6';
    }
    if( !GETBIT(P1IN,4))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,4))
        return 'B';
    }
    //row3
    RESETBIT(P2OUT,5);SETBIT(P2OUT,4);SETBIT(P1OUT,5);SETBIT(P4OUT,3);
    _delay_cycles(1000);
    if( !GETBIT(P2IN,0))
    {
        _delay_cycles(100000);
        if( !GETBIT(P2IN,0))
        return '7';
    }
    if( !GETBIT(P1IN,2))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,2))
        return '8';
    }
    if( !GETBIT(P1IN,3))
    {
        _delay_cycles(100000);
         if( !GETBIT(P1IN,3))
        return '9';
    }
    if( !GETBIT(P1IN,4))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,4))
        return 'C';
    }
    //row 4
    RESETBIT(P4OUT,3);SETBIT(P2OUT,4);SETBIT(P1OUT,5);SETBIT(P2OUT,5);
    _delay_cycles(1000);
    if( !GETBIT(P2IN,0))
    {
        _delay_cycles(100000);
        if( !GETBIT(P2IN,0))
        return '*';
    }
    if( !GETBIT(P1IN,2))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,2))
        return '0';
    }
    if( !GETBIT(P1IN,3))
    {
        _delay_cycles(100000);
         if( !GETBIT(P1IN,3))
        return '#';
    }
    if( !GETBIT(P1IN,4))
    {
        _delay_cycles(100000);
        if( !GETBIT(P1IN,4))
        return 'D';
    }
    return 127;
}
