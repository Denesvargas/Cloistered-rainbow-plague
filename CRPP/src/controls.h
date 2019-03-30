#include <stdio.h>
#include <stdlib.h>

struct ball{
    int raio, colored, power;
    float r, g, b, pow_r, pow_g, pow_b, x, y, last[2][4];
    float movement;
    float dir[2];
};

typedef struct ball Ball;

void mouse_ball();

void set_balls(Ball *balls, int tam);

void set_colors(Ball *balls, int i, int ball1, int ball2, int ball3);

int tem_colisao(Ball *balls, int i, float temp_x, float temp_y);

void draw_balls(Ball *balls, int tam);

void set_mouse(float x, float y);

void circleColorFill(float x, float y, int radius, int dots, float r, float g, float b);

void move_balls(Ball *balls, int tam);

int colided(float x1, float y1, float x2, float y2);

void verif_colis(Ball *balls, int tam);

void change_dir(Ball *balls, int a, int b);

void calc_dir_reflex(Ball *balls, int a, int b);

float dist_twodots(float x1, float y1, float x2, float y2);

void telep_ball(Ball *b, int x, int y);
