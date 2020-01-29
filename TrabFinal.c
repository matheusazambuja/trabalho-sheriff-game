#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#define LINHASPAREDE 24
#define COLUNASPAREDE 80
#define NOME 15
#define XERIFE 'x'
#define RAIO 2

void escondecursor();
void desenha_cenario(void);
void desenha_infos_jogador(char nome[NOME + 1], int modo_de_jogo, int bandidos_na_cadeia);
void desenha_info_tempo(clock_t inicio);
void desenha_jogador(int y, int x);
void desenha_rocha(int y, int x);
void apaga_elemento(int y, int x);
void movimenta_jogador(int *y_atual, int *x_atual, int desloc_y, int desloc_x);
int testa_proximidade(int y1, int x1, int y2, int x2, int raio);
void testa_captura(int y_jogador, int x_jogador, int *y_bandido, int *x_bandido, int *bandidos_na_cadeia);

int main()
{
    char nome[NOME];
    int posiX = 4, posiY = 4;
    int modo_jogo = 1;
    int num_bandidos = 0;
    clock_t inicio;
    int y_bandido = 12, x_bandido = 20;
    int y_rocha = 40, x_rocha = 15;

    escondecursor();

    printf("Entre com seu nome: ");
    gets(nome);

    clrscr();//limpando a tela

    desenha_cenario();
    desenha_infos_jogador(nome, modo_jogo, num_bandidos);

    //Teste desenhando e apagando rochas
    desenha_rocha(y_rocha, x_rocha);
    desenha_rocha(41, 15);
    apaga_elemento(41, 15);

    inicio = clock(); //iniciando o contador de tempo

    putchxy(y_bandido, x_bandido, 'B');

    // Movimentacao
    while(!(GetKeyState (VK_ESCAPE) & 0x80))
    {
        desenha_infos_jogador(nome, 1, num_bandidos);
        desenha_info_tempo(inicio);
        desenha_jogador(posiY, posiX);
        testa_captura(posiY, posiX, &y_bandido, &x_bandido, &num_bandidos);

        if(GetKeyState (VK_RIGHT) & 0x80)
            {
                if((posiY + 1) != COLUNASPAREDE && (posiY + 1 != y_rocha || posiX != x_rocha))
                {
                    movimenta_jogador(&posiY, &posiX, 1, 0);
                }
                else
                {
                   movimenta_jogador(&posiY, &posiX, 0, 0);
                }
            }
        if (GetKeyState (VK_LEFT) & 0x80)
        {
            if((posiY - 1)  != 1 && (posiY -1 != y_rocha || posiX != x_rocha))
            {
                movimenta_jogador(&posiY, &posiX, -1, 0);
            }
            else
            {
                movimenta_jogador(&posiY, &posiX, 0, 0);
            }

        }

        if(GetKeyState (VK_UP) & 0x80)
        {
            if((posiX - 1) != 1 && (posiY != y_rocha || posiX -1 != x_rocha))
            {
                movimenta_jogador(&posiY, &posiX, 0, - 1);
            }
            else
            {
                movimenta_jogador(&posiY, &posiX, 0, 0);
            }

        }

        if (GetKeyState (VK_DOWN) & 0x80)
        {
            if((posiX + 1) != LINHASPAREDE && (posiY != y_rocha || posiX + 1 != x_rocha))
            {
                movimenta_jogador(&posiY, &posiX, 0, 1);
            }
            else
            {
                movimenta_jogador(&posiY, &posiX, 0, 0);
            }

        }

        Sleep(120);
    }

    clrscr();

    return 0;

}

void escondecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void desenha_cenario(void)
{
    int i;

    textbackground(BROWN);

    for(i = 1; i <= LINHASPAREDE; i ++)
    {
        putchxy(1,i,' ');
        putchxy(COLUNASPAREDE,i,' ');
    }

    for(i = 1; i <= COLUNASPAREDE; i++)
    {
        putchxy(i,1,' ');
        putchxy(i,LINHASPAREDE,' ');
    }
    textbackground(BLACK);
}

void desenha_infos_jogador(char nome[NOME + 1], int modo_de_jogo, int bandidos_na_cadeia)
{
    char* modo[] = {"Facil", "Dificil"};
    int i;
    int aux = 50;

    cputsxy(1, 25, "Nome: ");
    cputsxy(6, 25, nome);
    cputsxy(20, 25, "Modo: ");
    if(modo_de_jogo == 1)
        cputsxy(25, 25, modo[0]);
    if(modo_de_jogo == 2)
        cputsxy(25, 25, modo[1]);

    cputsxy(43, 25, "Cadeia: ");
    for(i = 0; i < bandidos_na_cadeia; i++, aux ++)
    {
        putchxy(aux, 25, 'B');
    }
    printf("\t");
}

void desenha_info_tempo(clock_t inicio)
{
    clock_t fim;
    int segundos_decorridos = 0;
    fim = clock();
    segundos_decorridos = (fim - inicio) / CLOCKS_PER_SEC;

    cputsxy(71, 25, "Tempo:");
    gotoxy(77,25);
    printf("%d:", (2 - (segundos_decorridos / 60)));
    gotoxy(79,25);
    printf("%02d", (59 - (segundos_decorridos % 60)));

}

void desenha_jogador(int y, int x)
{
    textbackground(BLUE);
    putchxy(y, x, XERIFE);
    textbackground(BLACK);
}

void desenha_rocha(int y, int x)
{
    textbackground(BROWN);
    textcolor(BROWN);
    putchxy(y, x, 'R');
    textcolor(WHITE);
    textbackground(BLACK);
}

void apaga_elemento(int y, int x)
{
    putchxy(y, x, ' ');
}

void movimenta_jogador(int *y_atual, int *x_atual, int desloc_y, int desloc_x)
{

    putchxy(*y_atual, *x_atual, ' ');
    *y_atual += desloc_y;
    *x_atual += desloc_x;
    textbackground(BLUE);
    putchxy(*y_atual, *x_atual, XERIFE);
    textbackground(BLACK);

}

int testa_proximidade(int y1, int x1, int y2, int x2, int raio)
{
    int distanciaVertical, distanciaHorizontal;
    distanciaVertical = abs(x2 - x1);
    distanciaHorizontal = abs(y2 - y1);


    if(distanciaVertical <= raio && distanciaHorizontal <= raio)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void testa_captura(int y_jogador, int x_jogador, int *y_bandido, int *x_bandido, int *bandidos_na_cadeia)
{
    int teste = testa_proximidade(y_jogador, x_jogador, *y_bandido, *x_bandido, RAIO);

    if(teste == 1 && GetKeyState (VK_SPACE) & 0x80)
    {
        *bandidos_na_cadeia += 1;
        apaga_elemento(*y_bandido, *x_bandido);
        *y_bandido = -1;
        *x_bandido = -1;

    }

}
