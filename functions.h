#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include "raylib.h"
#include "functions.c"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860


void ShowTopBar(int lifes, int level, int score, int sword);

int menu(int gameInProgress);

void desenhaQuadrado(int x, int y);

void geraQuadrados(int matriz[60][40]);

int conferePosicao(int x, int y, int matriz[60][40]);

int StartGame();

#endif
