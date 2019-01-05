
/*
 * G14
 * Eduardo 2018112986
 * Alexandre 2015261034
 * Virgilio 2018263302
 * 
 * O Jogo foi separado na nas files:
 * Mapa.cpp onde esta a classe cls_mapa que contem as informacoes para o desenho da tela
 * Snake.cpp onde esta a classe cls_snake que contem as informacoes para a construcao e movimentacao da cobra pelo ecra
 * const.h onde se encontra as constantes e estruturas usadas no jogo
 * function.cpp onde estao as funcoes que sao usadas pelas classes do jogo
 * screen.cpp onde estao as funcoes usadas para desenhar no display
 * telasjogo.h onde estao as telas do jogo como manual, start, troca, nivel, pausa, e fim
 */

#include "Snake.h"
#include "function.h"
#include "screen.h"
#include "Mapa.h"
#include "const.h"
#include "telasjogo.h"

enm_direcao stick; // contem a direcao do joystick
cls_mapa mapaJogo; // o mapa a ser ultilizado no jogo


// botoes usados pelo jogo

bool botaoReset(false);
bool pause = false;
bool pauseLast = false;
bool pauseAtual = false;


// timer interno
unsigned long time0(0);

void setup()
{
  Serial.begin(9600);

  Serial.print("SETUP1");

  pinMode(START, INPUT);
  pinMode(RESET, INPUT);
  pinMode(SOM, OUTPUT);
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);

  LCD_ON();

  LCD_Tela(grapManual); // Tela Manual
  delay(2000);
  do {
    LCD_Tela(grapStart); // Tela Start
  } while (!digitalRead(START));
  playTone(musicaA);
}

void loop()
{
  do // Pausa do jogo
  {
    pauseAtual = digitalRead(START);
    if (pauseLast != pauseAtual)
    {
      if (pauseAtual)
      {
        if (pause)
          pause = false;
        else
          pause = true;
      }
      pauseLast = pauseAtual;
    }
    if(pause)
    LCD_Tela(grapPause);
  }
  while (pause);

  if ((millis() - time0) > (400 / mapaJogo.checkNivel())) // temporizador para velocidade do jogo
  {
    stick = getStick(analogRead(JOY_X), analogRead(JOY_Y), mapaJogo.snake.ultDirecao());// pega o input do jogado
    mapaJogo.snake.moveSnake(stick); //Atualiza Cobra
    mapaJogo.snake.checkLugar(mapaJogo.checkLugar(mapaJogo.snake.lugarSnake()[0]), &mapaJogo.ovo, mapaJogo.snake, mapaJogo.parede); //Compara Cabeca com o mapa
    mapaJogo.atualizaMapa(); // Atualiza mapa
    mapaJogo.drawMapa(); // Desenha mapa

    //Prints para controle de Bugs
    Serial.println(" ");
    Serial.print(mapaJogo.ovo.x);
    Serial.print(" - ");
    Serial.print(mapaJogo.ovo.y);
    Serial.print(" --- ");
    Serial.print(mapaJogo.snake.lugarSnake()[0].x);
    Serial.print(" - ");
    Serial.print(mapaJogo.snake.lugarSnake()[0].y);
    Serial.print(" --- ");
    Serial.print(mapaJogo.snake.checkPontos());
    Serial.print(" --- ");
    Serial.print(mapaJogo.checkNivel());

    if (digitalRead(RESET) && !botaoReset) //botao Reset
    {
      botaoReset = true;
    } else botaoReset = false;

    if (!mapaJogo.snake.checkVida() || botaoReset)//  Reset e morte da cobra
    {

      Serial.print(" GAMEOVER "); // teste interno
      LCD_Change();
      if (!botaoReset)
      {
        LCD_Tela(grapEnd); //Tela Final
        playTone(musicaB);
      }
      mapaJogo.~cls_mapa(); //Apaga mapa
      LCD_Tela(grapStart); //Tela inicial
      if (botaoReset)
      {
        playTone(musicaA);
      }
      mapaJogo = cls_mapa(); // Cria novo mapa
    }

    if (mapaJogo.snake.checkPontos() >= 5) // checa pontos
    {
      int tempN = (mapaJogo.checkNivel() + 1) ; // salva nivel
      Serial.print(tempN);
      LCD_Change();
      LCD_Tela(grapNivel); // tela novo nivel
      playTone(musicaC);
      mapaJogo.~cls_mapa(); // destroe mapa antigo
      mapaJogo = cls_mapa(tempN); // mapa com novo nivel
    }

    time0 = millis();
  }
}
