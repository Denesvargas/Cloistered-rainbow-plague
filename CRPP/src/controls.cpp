#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gl_canvas2d.h"
#include "controls.h"

/**
*   Programa para demonstrar colisões elásticas bidimensionais aleatórias
*
*
*   Autor: Dênes Vargas
*   UFSM - 2019
**/

const int RAIO = 6;
const int DOTS = 50;

float mouse_x, mouse_y;

void mouse_ball(){
    circleColorFill(mouse_x, get_height() - mouse_y, 5, 50, 1, 0, 0);
}

void set_balls(Ball *balls, int tam){
    srand(time(NULL));
    int i, ball1 = rand() % tam, ball2 = rand() % tam, ball3 = rand() % tam;
    while(ball2 == ball1)
        ball2 = rand() % tam;
    while(ball3 == ball1 || ball3 == ball2)
        ball3 = rand() % tam;
    for(i = 0; i < tam; i++){
        float temp_x = (rand() % (750 - RAIO)) + RAIO;
        float temp_y = get_height() - ((rand() % (550 - RAIO)) + RAIO);
        while(tem_colisao(balls, i, temp_x, temp_y)){
            temp_x = (rand() % (750 - RAIO)) + RAIO;
            temp_y = get_height() - ((rand() % (550 - RAIO)) + RAIO);
        }
        balls[i].x = temp_x;
        balls[i].y = temp_y;
        set_colors(balls, i, ball1, ball2, ball3);
        balls[i].movement = 1;
        if(i % 4 == 0){
            balls[i].dir[0] = 1;
            balls[i].dir[1] = 0;
        }
        else if(i % 4 == 1){
            balls[i].dir[0] = 0;
            balls[i].dir[1] = 1;
        }
        else if(i % 4 == 2){
            balls[i].dir[0] = -1;
            balls[i].dir[1] = 0;
        }
        else{
            balls[i].dir[0] = 0;
            balls[i].dir[1] = -1;
        }
    }
}

void set_colors(Ball *balls, int i, int ball1, int ball2, int ball3){
    balls[i].colored = 0;
    if(ball1 == i){
        balls[i].r = 1;
        balls[i].g = 0;
        balls[i].b = 0;
        balls[i].colored = 1;
    }
    else if(ball2 == i){
        balls[i].r = 0;
        balls[i].g = 1;
        balls[i].b = 0;
        balls[i].colored = 1;
    }
    else if(ball3 == i){
        balls[i].r = 0;
        balls[i].g = 0;
        balls[i].b = 1;
        balls[i].colored = 1;
    }
    else{
        balls[i].r = 0.66;
        balls[i].g = 0.66;
        balls[i].b = 0.66;
    }
}

int tem_colisao(Ball *balls, int i, float temp_x, float temp_y){
    int j;
    for(j = 0; j < i; j++){
        if(dist_twodots(balls[j].x, balls[j].y, temp_x, temp_y) < RAIO*3)
            return 1;
    }
    return 0;
}

void draw_balls(Ball *balls, int tam){
    int i;
    for(i = 0; i < tam; i++){
        circleColorFill(balls[i].x, balls[i].y, RAIO, DOTS, balls[i].r, balls[i].g, balls[i].b);
    }
}

void move_balls(Ball *balls, int tam){
    int i;
    for(i = 0; i < tam; i++){
        if(balls[i].x < RAIO && balls[i].dir[0] < 0)
            balls[i].dir[0] *= -1;
        else if(balls[i].x > get_width() - RAIO && balls[i].dir[0] > 0)
            balls[i].dir[0] *= -1;
        else if(balls[i].y < RAIO && balls[i].dir[1] < 0)
            balls[i].dir[1] *= -1;
        else if(balls[i].y > get_height() - RAIO && balls[i].dir[1] > 0)
            balls[i].dir[1] *= -1;
        if(balls[i].movement > 0){
            balls[i].x += balls[i].dir[0] * balls[i].movement;
            balls[i].y += balls[i].dir[1] * balls[i].movement;
            //balls[i].movement -= 0.0001;
        }
    }
}

void set_mouse(float x, float y){
    mouse_x = x;
    mouse_y = y;
}

void circleColorFill(float x, float y, int radius, int dots, float r, float g, float b){
    color(r, g, b);
    circleFill(x, y, radius, dots);
}

int colided(float x1, float y1, float x2, float y2){
    if(dist_twodots(x1, y1, x2, y2) <= RAIO*2)
        return 1;
    return 0;
}

void verif_colis(Ball *balls, int tam){
    int i, j;
    for(i = 0; i < tam; i++){
        for(j = i + 1; j < tam; j++){
            if(colided(balls[i].x, balls[i].y, balls[j].x, balls[j].y)){
                change_dir(balls, i, j);
                if(balls[i].colored && balls[j].colored){
                    balls[i].power = 1;
                    balls[j].power = 1;
                    balls[i].pow_r = (float) (balls[i].r + balls[j].r) / 2;
                    balls[i].pow_g = (float) (balls[i].g + balls[j].g) / 2;
                    balls[i].pow_b = (float) (balls[i].b + balls[j].b) / 2;
                    balls[j].pow_r = (float) (balls[i].r + balls[j].r) / 2;
                    balls[j].pow_g = (float) (balls[i].g + balls[j].g) / 2;
                    balls[j].pow_b = (float) (balls[i].b + balls[j].b) / 2;
                }
                if(balls[i].power == 1 && balls[j].colored == 0){
                    balls[j].r = balls[i].pow_r;
                    balls[j].g = balls[i].pow_g;
                    balls[j].b = balls[i].pow_b;
                    balls[j].colored = 1;
                    balls[i].power = 0;
                }
                if(balls[j].power == 1 && balls[i].colored == 0){
                    balls[i].r = balls[j].pow_r;
                    balls[i].g = balls[j].pow_g;
                    balls[i].b = balls[j].pow_b;
                    balls[i].colored = 1;
                    balls[j].power = 0;
                }
            }
        }
    }
}

void change_dir(Ball *balls, int a, int b){
    float dir_x_vermelho = balls[b].x - balls[a].x;
    float dir_y_vermelho = balls[b].y - balls[a].y;
    dir_x_vermelho += balls[a].dir[0];
    dir_y_vermelho += balls[a].dir[1];
    float norma_vermelho = sqrt(dir_x_vermelho*dir_x_vermelho+ dir_y_vermelho*dir_y_vermelho);
    float dir_x_vermelho_norm = dir_x_vermelho / norma_vermelho;
    float dir_y_vermelho_norm = dir_y_vermelho / norma_vermelho;
    float dir_x_azul = balls[a].dir[0];
    float dir_y_azul = balls[a].dir[1];
    float norma_azul = sqrt(dir_x_azul*dir_x_azul+ dir_y_azul*dir_y_azul);
    float dir_x_azul_norm = dir_x_azul / norma_azul;
    float dir_y_azul_norm = dir_y_azul / norma_azul;
    float dir_x_res_fim = balls[a].x + dir_x_azul_norm;
    float dir_y_res_fim = balls[a].y + dir_y_azul_norm;
    float dir_x_res_ini = balls[a].x + dir_x_vermelho_norm;
    float dir_y_res_ini = balls[a].y + dir_y_vermelho_norm;
    float dir_x_res = dir_x_res_fim - dir_x_res_ini;
    float dir_y_res = dir_y_res_fim - dir_y_res_ini;
    dir_x_res += balls[b].dir[0];
    dir_y_res += balls[b].dir[1];
    float norma_res = sqrt(dir_x_res*dir_x_res+ dir_y_res*dir_y_res);
    float dir_x_res_norm = dir_x_res / norma_res;
    float dir_y_res_norm = dir_y_res / norma_res;
    balls[a].dir[0] = dir_x_res_norm;
    balls[a].dir[1] = dir_y_res_norm;
    balls[b].dir[0] = dir_x_vermelho_norm;
    balls[b].dir[1] = dir_y_vermelho_norm;
}

float dist_twodots(float x1, float y1, float x2, float y2){
    return (sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)));
}

void telep_ball(Ball *b, int x, int y){
    b[0].x = (float) x;
    b[0].y = (float) get_height() - y;
}
