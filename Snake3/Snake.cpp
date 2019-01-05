#include "Snake.h"
#include "const.h"
#include "function.h"
#include "Arduino.h"

cls_snake::~cls_snake()
{
}

cls_snake::cls_snake() // Construtor da Cobra
{
  randomSeed(millis());
  posicaoSnake[0] = {11, 5};
  vida = true;
  pontos = 0;
  ult = DIREITA;
  Serial.print("SETUP COBRA"); // Teste interno
}

bool cls_snake::checkVida() // retorna se a cobra esta viva
{
  return vida;
}

void cls_snake::moveSnake(enm_direcao stick) // pega a direcao do stick e altera onde se encontra a cobra
{
  str_posicao temp;
  if (stick != opostoUlt(ult)) // nao deixa voltar para tras
  {
    temp = novaPosicao(stick, posicaoSnake[0], &ult); //Cria novo endereco
    atualizaSnake(temp); // Atualiza os enderecos da cobra
  } else moveSnake(ult); // Caso falha repete com valor da ultima direcao
}

bool cls_snake::checkSnake(const str_posicao teste) //Compara uma posica com o corpo da Cobra
{
  for (int i = 0 ; i <= pontos ; i++) // testa todo o corpo da cobra
  {
    if (comparaPosicao(teste, posicaoSnake[i]))
    {
      return true; // caso sai da funcao com true
    }
  }
  return false; // sai da funcao com false
}

str_posicao* cls_snake::lugarSnake() // retorna o ponteiro do array do corpo da cobra
{
  return posicaoSnake;
}

void cls_snake::checkLugar(enm_tipo temp, str_posicao* ovo, cls_snake snake, const str_posicao* parede) // Checa onde esta a cabeca da cobra
{
  Serial.print(temp);
  switch (temp)
  {
    case OVO: //OVO ganha um ponto e cria novo ovo
      {
        pontos++;
        atualizaSnake(*ovo);  // DEBUG teve que atualizar para evitar leitura fora de memoria
        *ovo = novoOvo(snake, parede);
        vida = true;
        tone(SOM,550,200);
        break;
      }
    case SNAKE: // mata a cobra
      {
        vida = false;
        break;
      }
    case PAREDE:
          {
        vida = false;
        break;
      }
    default: // faz nada
      vida = true;
      break;
  }
  Serial.print(vida);
}

int cls_snake::checkPontos() //Retorna numero de pontos
{
  return pontos;
}

enm_direcao cls_snake::ultDirecao() // Retorna ultima direcao
{
  return ult;
}
void cls_snake::atualizaSnake(const str_posicao temp) //PushBack para atualizar os enderecos das partes da Cobra
{
  for (int i = pontos ; i > 0; i--) // copia de tras para frente para evitar copiar o mesmo endereco
  {
    posicaoSnake[i] = posicaoSnake[i - 1];
  }
  posicaoSnake[0] = temp; // atualiza a cabeca por ultimo
}
