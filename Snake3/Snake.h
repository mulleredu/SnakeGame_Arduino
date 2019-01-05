#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "const.h"

class cls_snake
{
  private:

    str_posicao posicaoSnake[15] = {}; // array com as posicoes da cobra sendo
    bool vida;
    int pontos;
    enm_direcao ult; //ultima direacao da cobra

  public:

    cls_snake();
    ~cls_snake();
    
    void moveSnake(enm_direcao stick);
    bool checkSnake(str_posicao teste);
    void checkLugar(enm_tipo temp,  str_posicao* ovo, cls_snake snake, const str_posicao* parede);
    bool checkVida();
    enm_direcao ultDirecao(); 
    void atualizaSnake(const str_posicao temp);
    str_posicao* lugarSnake();
    int checkPontos();
};

#endif
