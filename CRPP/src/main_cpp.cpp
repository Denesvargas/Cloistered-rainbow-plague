
#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "controls.h"

#include "Bola.h"
#include "Relogio.h"

Bola    *b = NULL;
Relogio *r = NULL;

const int Num_balls = 40;

int LARGURA_TELA = 800, ALTURA_TELA = 600;
Ball balls[5];
int   opcao  = 50;
float global = 0;

void render()
{
    verif_colis(balls, Num_balls);
    draw_balls(balls, Num_balls);
    move_balls(balls, Num_balls);
    mouse_ball();
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   printf("\nTecla: %d" , key);
   if( key < 200 )
   {
      opcao = key;
   }

   switch(key)
   {
      case 27:
	     exit(0);
	  break;

	  //seta para a esquerda
      case 200:
         b->move(-10);
	  break;

	  //seta para a direita
	  case 202:
         b->move(10);
	  break;
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    set_mouse(x, y);
    if(state == 1)
        telep_ball(balls, x, y);
}

int main(void)
{
   initCanvas(LARGURA_TELA, ALTURA_TELA, "Cloistered rainbow plague physics");

   b = new Bola();
   r = new Relogio();
   set_balls(balls, Num_balls);
   runCanvas();
}
