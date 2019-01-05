#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "const.h"
#include "Snake.h"

str_posicao novaPosicao(const enm_direcao stick,const str_posicao cabeca, enm_direcao *ult);

bool comparaPosicao(const str_posicao a,const str_posicao b);

enm_direcao getStick(int x, int y, enm_direcao ult);

str_posicao novoOvo(const cls_snake snake, const str_posicao* parede);

enm_direcao opostoUlt(const enm_direcao ult);

bool checkParede(const str_posicao* parede, const str_posicao teste);

void encheParede(const int nivel, str_posicao* parede);

void playTone(const enm_nota* musica);

#endif
