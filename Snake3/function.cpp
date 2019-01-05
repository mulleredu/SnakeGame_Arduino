#include "function.h"
#include "const.h"
#include "Snake.h"
#include "Arduino.h"

str_posicao novaPosicao(const enm_direcao stick, const str_posicao cabeca, enm_direcao *ult) //Pega endereco antigo da cabeca e atualiza com a nova direcao e altera o valor de ultima direcao
{
  str_posicao temp{cabeca};// Posicao TEMPoraria para a funcao

  switch (stick)
  {
    case CIMA:
      if (cabeca.y <= 0) temp.y = ((tamTelaY / 4) - 1); else temp.y -= 1;
      *ult = CIMA;
      break;
    case DIREITA:
      if (cabeca.x >= (tamTelaX / 4 - 1)) temp.x = 0; else temp.x += 1;
      *ult = DIREITA;
      break;
    case BAIXO:
      if (cabeca.y >= (tamTelaY / 4 - 1)) temp.y = 0; else temp.y += 1;
      *ult = BAIXO;
      break;
    case ESQUERDA:
      if (cabeca.x <= 0) temp.x = ((tamTelaX / 4) - 1); else temp.x -= 1;
      *ult = ESQUERDA;
      break;
    default: break;
  }

  return temp;
}

bool comparaPosicao(const str_posicao a, const str_posicao b) // Compara duas posicoes X e Y
{
  return ((a.x == b.x) && (a.y == b.y));
}

enm_direcao getStick(int x, int y, enm_direcao ult) // Interpreta o input do joystick
{
  if ( abs(x - 512) > abs (y - 512)) y = 512; else x = 512; // Transforma o valor 0-1023 para um modulo entre 0-512 e faz o menor ficar no zero do potenciometro (512)
  if (x > 612) return ESQUERDA; else if (x < 412) return DIREITA; else if (y > 612) return BAIXO; else if (y < 412) return CIMA; else return ult; //Caso Joystick parado retorna ultima direcao
}

str_posicao novoOvo(const cls_snake snake, const str_posicao* parede)//Gera nova posicao para o Ovo diferente do corpo da cobra
{
  str_posicao ovo;
  do
  {
    randomSeed(millis()); // Seed para a funcao random
    ovo.x = random(tamTelaX / 4);
    ovo.y = random(tamTelaY / 4);

  } while (snake.checkSnake(ovo) || checkParede(parede, ovo)); // enquanto ovo dentro da cobra
  return ovo;
}

bool checkParede(const str_posicao* parede, const str_posicao teste) // Testa endereco da parede
{
  for (int i(0); i < tamParede ; i++)
  {
    if (comparaPosicao(parede[i], teste)) return true;
  }
  return false;
}

enm_direcao opostoUlt(const enm_direcao ult) // Teste para nao voltar para tras, retorna inverso de ult
{
  switch (ult)
  {
    case CIMA:
      return BAIXO;
      break;
    case DIREITA:
      return ESQUERDA;
      break;
    case BAIXO:
      return CIMA;
      break;
    case ESQUERDA:
      return DIREITA;
      break;
    default: break;
  }
}

void encheParede(const int nivel, str_posicao* parede) // Cria os enderecos da Parede
{
  for (int i(0); i < tamParede; i++)
  {
    if (nivel > 2)
    {
      parede[i].x = i + 4;
      parede[i].y = 6;
    } else // Caso nao ultilizada fica fora do alcance do mapa
    {
      parede[i].x = 25; 
      parede[i].y = 25;
    }
  }
}

void playTone(const enm_nota* musica) // toca musica
{
  for(int i(0); i < tamMusica ; i++)
  {
    tone(SOM, musica[i],200);
    delay(200);
  }
}
