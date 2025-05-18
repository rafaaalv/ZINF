#include "raylib.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860

Image img_sword;
Texture2D swordTexture;

void ShowTopBar(int lifes, int level, int score, int sword)
{
    char l[10], lev[12], sc[15];
    sprintf(l, "Vidas: %d", lifes);
    sprintf(lev, "Nivel: %d", level);
    sprintf(sc, "Escores: %d", score);
    DrawRectangle(0, 0, 1200, 60, BLACK);
    DrawText(l, 40, 5, 50, WHITE);
    DrawText(lev, 280, 5, 50, WHITE);
    DrawText(sc, 480, 5, 50, WHITE);
    if(sword){
        DrawTexture(swordTexture, 840 , 0, WHITE);
    }

}
int menu(int gameInProgress)
{
    char text[40], *optionsText[3];
    int optionSelected, i, desenha;
    optionSelected = 0;
    desenha = 1;
    if(gameInProgress){
        optionsText[0] = "Continuar Jogo";
        optionsText[1] = "Voltar ao menu";
        optionsText[2] = "Sair";
    } else {
        optionsText[0] = "Iniciar";
        optionsText[1] = "Scoreboard";
        optionsText[2] = "Sair";
    }

    while(desenha){
        DrawText("ZINF", 100, 20, 100, WHITE);
        for(i = 0; i < 3; i++){
            if(optionSelected == i){
                DrawCircle(90, i*110 + 220, 5, RED);
                DrawText(optionsText[i], 100, i*110 + 200, 50, RED);
            } else {
                DrawText(optionsText[i], 100, i*110 + 200, 50, WHITE);
            }
        }
        //strcpy(texto,"Direita");
        if(IsKeyPressed(KEY_DOWN)){
            if(optionSelected == 2){
                optionSelected = 0;
            } else {
                optionSelected++;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            if(optionSelected == 0){
                optionSelected = 2;
            } else {
                optionSelected--;
            }
        }
        BeginDrawing();
	    EndDrawing();
	    ClearBackground(BLACK);
	    if(IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_LEFT)){
            desenha = 0;
	    }
    }
    return optionSelected;
}
void desenhaQuadrado(int x, int y)
{
    DrawRectangle(x, y, 20, 20, GREEN);
}
void geraQuadrados(int matriz[60][40])
{
    int i, j;
    for(i = 0; i < 60; i++){
        for(j = 0; j < 40; j++){
            if(matriz[i][j]){
                DrawRectangle(i*20, j*20 + 60, 20, 20, RED);
            }
        }
    }
}

int conferePosicao(int x, int y, int matriz[60][40]){
    if(!matriz[(int) floor(x/20)][(int) floor(y/20) - 3]){
        return 1;
	} else {
        return 0;
	}
}
int StartGame()
{
    int x, y, quadradosVermelhos[60][40], i, j, respostaMenu;
    InitWindow(LARGURA, ALTURA, "Quadrado"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(30);// Ajusta a janela para 60 frames por segundo

    img_sword = LoadImage("../assets/sword.png");
    ImageResize(&img_sword, 50, 50);
    swordTexture = LoadTextureFromImage(img_sword);
    srand(time(NULL));
    for(i = 0; i < 60; i++){
        for(j = 0; j < 40; j++){
            if(rand()%(3) == 1){
                quadradosVermelhos[i][j] = 1;
            } else {
                quadradosVermelhos[i][j] = 0;
            }
            if(((i < 35) && (i > 25)) && ((j < 25) && (j > 15))){
                quadradosVermelhos[i][j] = 0;
            }
        }
    }

    x = 600;
    y = 400;
    desenhaQuadrado(x, y);
    while (!WindowShouldClose())
    {
	// Trata entrada do usuario e atualiza estado do jogo
	if (IsKeyPressed(KEY_RIGHT)||IsKeyDown(KEY_RIGHT)) {
        if(conferePosicao((x + 20), y, quadradosVermelhos)){
            x += 20;
        }
    }
	if (IsKeyPressed(KEY_LEFT)||IsKeyDown(KEY_LEFT)) {
        if(conferePosicao((x -20), y, quadradosVermelhos)){
            x -= 20;
        }
	}
	if (IsKeyPressed(KEY_UP)||IsKeyDown(KEY_UP)) {
        if(conferePosicao(x, (y-20), quadradosVermelhos)){
            y -= 20;
        }
	}
	if (IsKeyPressed(KEY_DOWN)||IsKeyDown(KEY_DOWN)) {
        if(conferePosicao(x, (y+20), quadradosVermelhos)){
            y += 20;
        }
	}
	if((x > 1200)||(x < -20)){
        CloseWindow();
	}
	if((y > 800)||(y < 0)){
        CloseWindow();
	}
	if(IsKeyPressed(KEY_TAB)){
        respostaMenu = menu(1);
        if(respostaMenu == 2)
        {
            break; //Fecha jogo
        } else if(respostaMenu == 0){
            //Só fecha o menu e continua o jogo
        } else {
            //Chama o menu inicial
            respostaMenu = menu(0);
            if(respostaMenu == 2)
            {
                CloseWindow(); //Fecha jogo
            } else if(respostaMenu == 0){
                if(StartGame() == 0){//Incia Jogo
                    break;
                }
            } else {
                //Mostra Scoreboard
            }
        }
    }

	desenhaQuadrado(x, y);
	geraQuadrados(quadradosVermelhos);

	ShowTopBar(3, 1, 0, 1);
	// Atualiza o que eh mostrado na tela a partir do estado do jogo
	BeginDrawing(); //Inicia o ambiente de desenho na tela
	EndDrawing(); //Finaliza o ambiente de desenho na tela
	ClearBackground(RAYWHITE);
    }

    UnloadImage(img_sword);
    CloseWindow(); // Fecha a janela
    return 0;
}
