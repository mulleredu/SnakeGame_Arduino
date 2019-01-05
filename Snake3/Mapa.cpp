#include "Mapa.h"
#include "function.h"
#include "Arduino.h"
#include "screen.h"

/*
 * Como o foi pedido um pixel de tamanho 4*4 todos os valores maximos foram divididos por 4 para salvar memoria
 * e a funcao drawMapa() espande ele para 4  vezes maior
 * Na hora de desenhar a tela esses valores sao espandidos para caber na tela do 5110
 */

cls_mapa::cls_mapa() // construtor da tela
{
  nivel = 1;
  snake = cls_snake();
  ovo = novoOvo(snake, parede);
  encheParede(nivel, parede);
}

cls_mapa::cls_mapa(int nivelVelho) // construtor da tela Overload
{
  nivel = nivelVelho;
  snake = cls_snake();
  encheParede(nivel, parede);
  ovo = novoOvo(snake, parede);
}

cls_mapa::~cls_mapa() // Destroe o mapa
{
  snake.~cls_snake();
}

int cls_mapa::checkNivel() // retorna qual nivel o jogo esta
{
  return nivel;
}

void cls_mapa::atualizaMapa() // preenche o array bidimencional com as informacoes dos objetos SNAKE, OVO e PAREDE
{
  for (int i(0); i < 21 ; i++)
  {
    for (int j(0); j < 12 ; j++)
    {
      str_posicao temp {i, j};
      if (comparaPosicao(temp, ovo))
      {
        mapaJogo[i][j] = OVO;
      } else if (snake.checkSnake(temp))
      {
        mapaJogo[i][j] = SNAKE;
      } else if (checkParede(parede, temp))
      {
        mapaJogo[i][j] = PAREDE;
      } else mapaJogo[i][j] = VAZIO;
    }
  }
}

enm_tipo cls_mapa::checkLugar(str_posicao temp) // Checka que objeto esta no endereco X Y
{
  int x = temp.x;
  int y = temp.y;
  return mapaJogo[x][y];
}

void cls_mapa::drawMapa() // Desenha os Bytes do mapa
{
  byte temp(0);

  for (int k(0); k < 6 ; k++)
  {
    for (int i(0); i < 84; i++)
    {
      for (int j(7); j >= 0 ; j--) // Faz a varredura do mapa de acordo com a divisao da tela especificada no Datasheet do 5110
      {
        int y = (j + 8 * k); //Cria um byte de informacao para ser interpretado pelo display
        temp <<= 1; // Bitshift para a esquerda
        temp = temp | (bool)mapaJogo[((int)(i / 4))][((int)(y / 4))]; // caso exista um objeto nesse pixel ele e mandado como 1 para o byte
      }
      LCD_Write(LCD_D, temp); //poe o byte no display
      temp = 0;
    }
  }
}
