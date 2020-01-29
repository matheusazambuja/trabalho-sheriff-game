#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <time.h>
#include <math.h>
// CONSTANTES
#define LINHASPAREDE 24
#define COLUNASPAREDE 80
#define NOME 15
#define XERIFE 'x'
#define BANDIDO_ 'B'
#define RAIO 2
#define NUM_ROCHAS 30
#define NUM_ROCHAS_DIFICIL 42
#define MAX_BANDIDOS_FACIL 4
#define MAX_BANDIDOS_DIFICIL 7
#define MAX_LINHA 80
#define TAMSTR 30
#define SCORE 10000
#define LARGURA_PRETO 35
#define ALTURA_PRETO 6
#define MAX_NOME 30
#define MAX_TAMANHO_VETOR 10

typedef struct
{
    int x;
    int y;
}COORDENADA;

typedef struct
{
    char nome[NOME];
    COORDENADA posicao;
    int velocidade;
    int score;
    int venceu;
    int perdeu;
}JOGADOR;

typedef struct
{
    COORDENADA posicao_b;
    int na_cadeia;
    int velocidade;
}BANDIDO;

typedef struct
{
    JOGADOR player1;
    BANDIDO bandidos[MAX_BANDIDOS_DIFICIL];
    int segundos;
    int modo_jogo;
    int num_bandidos;
    int bandidos_cadeia;
}JOGO;

typedef struct
{
    char nome_jogador[MAX_NOME];
    int score_jogador;
}RANKING;
