#include "screen.h"
#include "Snake.h"
#include "Arduino.h"
#include "telasJogo.h"
#include "const.h"

void LCD_ON()
{

  pinMode(LCD_CE, OUTPUT);
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_DC, OUTPUT);
  pinMode(LCD_DIN, OUTPUT);
  pinMode(LCD_CLK, OUTPUT);

  digitalWrite(LCD_RST, LOW);
  digitalWrite(LCD_RST, HIGH);

  LCD_Write(LCD_C, 0x21 );  // LCD Extended Commands.
  LCD_Write(LCD_C, 0xB9 );  // Set LCD Vop (Contrast).
  LCD_Write(LCD_C, 0x04 );  // Set Temp coefficent.
  LCD_Write(LCD_C, 0x14 );  // LCD bias mode 1:48.
  LCD_Write(LCD_C, 0x20 );  // LCD Basic Commands
  LCD_Write(LCD_C, 0x0C );  // LCD in normal mode.

  LCD_Write(LCD_C, 0x40 );  // Set cursor to 0 x 0
  LCD_Write(LCD_C, 0x80 );

}

void LCD_Write(byte dc, byte data) //Inicia a tela pelo spreadSheet
{
  digitalWrite(LCD_DC, dc);
  digitalWrite(LCD_CE, LOW);
  shiftOut(LCD_DIN, LCD_CLK, MSBFIRST, data);
  digitalWrite(LCD_CE, HIGH);
}

void LCD_Tela(byte* data) // Desenhas telas Prontas
{
  for (int i(0); i < (84 * 48 / 8); i++) // numero de bytes na tela
  {
    LCD_Write(LCD_D, pgm_read_byte_near(data + i)); // le o byte da memoria flash(nao dinamica)
  }
}

void LCD_Change() // Pisca a tela 
{
  LCD_Tela(grapChange); 
  for (int i(0); i < 4 ; i++)
  {
    LCD_Write(LCD_C, 0x0D);
    delay(250);
    LCD_Write(LCD_C, 0x0C);
    delay(250);
  }
}
