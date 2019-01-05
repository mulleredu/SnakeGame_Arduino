#ifndef _CONST_H_
#define _CONST_H_

#define LCD_CE        7
#define LCD_RST       6
#define LCD_DC        5
#define LCD_DIN       4
#define LCD_CLK       3
#define LCD_C       LOW
#define LCD_D      HIGH


#define START 12
#define RESET 13
#define SOM   11
#define JOY_X A0
#define JOY_Y A1
#define PAUSE 8

struct str_posicao //struct de posicao X Y
{
  int x;
  int y;
};

enum enm_direcao //direcao do joystick
{
  CIMA,
  DIREITA,
  BAIXO,
  ESQUERDA
};

enum  enm_tipo // Tipos de objetos encontrados na tela
{
  VAZIO,
  SNAKE,
  OVO,
  PAREDE
};

enum enm_nota // Notas musicais e suas frequencias
{
  c = 1915,
  d = 1700,
  e = 1519,
  f = 1432,
  g = 1275,
  a = 1136, 
  b = 1014,
  C = 956
};

constexpr int tamTelaX(84);
constexpr int tamTelaY(48);
constexpr int tamParede(12);
constexpr int tamMusica(10);
constexpr int timeNota(200);

#endif
