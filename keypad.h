#pragma once
#include "msp430.h"
#define SETBIT(reg,bit)    (reg |= (1<<bit))
#define RESETBIT(reg,bit)    (reg &=~ (1<<bit))
#define TOGBIT(reg,bit)    (reg ^= (1<<bit))
#define GETBIT(reg,bit)    (reg & (1<<bit))

void init_keypad();

char key();