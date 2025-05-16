#include "raylib.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA 1200
#define ALTURA 860


int main()
{
    int respostaMenu;
    InitWindow(LARGURA, ALTURA, "ZINF");
    SetTargetFPS(30);
    while (!WindowShouldClose())
    {
        respostaMenu = menu(0);
        if(respostaMenu == 2)
        {
            CloseWindow(); //Fecha jogo
        } else if(respostaMenu == 0){
            if(StartGame() == 0){//Incia Jogo
                CloseWindow();
            }
        } else {
            //Mostra Scoreboard
        }

    }
    return 0;
}
