#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860

int menu()
{
    char text[40], *optionsText[3];
    int optionSelected, i, desenha;
    optionSelected = 0;
    desenha = 1;


    optionsText[0] = "Iniciar";
    optionsText[1] = "Scoreboard";
    optionsText[2] = "Sair";
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
void geraQuadrados(int matriz[60][43])
{
    int i, j;
    for(i = 0; i < 60; i++){
        for(j = 0; j < 43; j++){
            if(matriz[i][j]){
                DrawRectangle(i*20, j*20, 20, 20, RED);
            }
        }
    }
}
int conferePosicao(int x, int y, int matriz[60][43]){
    if(!matriz[(int) floor(x/20)][(int) floor(y/20)]){
        return 1;
	} else {
        return 0;
	}
}
int StartGame()
{
    int x, y, quadradosVermelhos[60][43], i, j, respostaMenu;
    InitWindow(LARGURA, ALTURA, "Quadrado"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(30);// Ajusta a janela para 60 frames por segundo

    srand(time(NULL));
    for(i = 0; i < 60; i++){
        for(j = 0; j < 43; j++){
            if(rand()%(3) == 1){
                quadradosVermelhos[i][j] = 1;
            } else {
                quadradosVermelhos[i][j] = 0;
            }
            if(((i < 35) && (i > 25)) && ((j < 26) && (j > 16))){
                quadradosVermelhos[i][j] = 0;
            }
        }
    }

    x = 600;
    y = 430;
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
	if((y > 860)||(y < 0)){
        CloseWindow();
	}
	if(IsKeyPressed(KEY_TAB)){
        respostaMenu = menu();
        if(respostaMenu == 2)
        {
            CloseWindow(); //Fecha jogo
        } else if(respostaMenu == 0){
            StartGame();//Incia Jogo
        } else {
            //Mostra Scoreboard
        }
    }

	desenhaQuadrado(x, y);
	geraQuadrados(quadradosVermelhos);

	// Atualiza o que eh mostrado na tela a partir do estado do jogo
	BeginDrawing(); //Inicia o ambiente de desenho na tela
	EndDrawing(); //Finaliza o ambiente de desenho na tela
	ClearBackground(RAYWHITE);
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
int main()
{
    int respostaMenu;
    InitWindow(LARGURA, ALTURA, "ZINF");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        respostaMenu = menu();
        if(respostaMenu == 2)
        {
            CloseWindow(); //Fecha jogo
        } else if(respostaMenu == 0){
            StartGame();//Incia Jogo
        } else {
            //Mostra Scoreboard
        }

    }
    return 0;
}
