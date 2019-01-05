#ifndef _MAPA_H_
#define _MAPA_H_

#include "const.h"
#include "Snake.h"

/*
   classe mapa que contem os struct do ovo e a classe de cobra dentro dela para facilitar ultilizacao de funcoes
*/

class cls_mapa
{
  private:

    enm_tipo mapaJogo[21][12] = {}; // array de tipos com o tamanha reduzido da tela, com os enderecos X e Y
    int nivel; // Niveis para quando chega no valor maximo de pontos

  public:

    cls_snake snake; // SNAKE
    str_posicao ovo; // OVO
    str_posicao parede[tamParede]; //Parede

    cls_mapa();
    cls_mapa(int nivel);
    ~cls_mapa();

    int checkNivel();

    void atualizaMapa();
    enm_tipo checkLugar(str_posicao temp);
    void drawMapa();
};

#endif
