#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Arduino.h"
#include "Snake.h"
#include "const.h"
#include "function.h"

void LCD_ON();

void LCD_Write(byte dc, byte data);

void LCD_Tela(byte* data);

void LCD_Change();

#endif
