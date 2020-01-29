///                                     MATHEUS AZAMBUJA E ANDREW BORGES
///                                                 TURMA G

/// O jogo esta com um bug na ultima posicao do vetor que guarda os pontos dos jogadores;
/// Nao foi implementado os power ups.

#include "bibliotecas.h"

// PROTOTIPOS DAS FUNCOES
void altera_velocidade(JOGADOR *xerife, int aceleracao);
void apaga_elemento(int y, int x);
void desenha_bandido(int y, int x);
void desenha_bandidos(BANDIDO bandido[], int modo_jogo);
void desenha_cenario();
void desenha_infos_jogador(char nome[NOME + 1], int modo_de_jogo, int bandidos_na_cadeia);
void desenha_info_tempo(clock_t inicio);
void desenha_jogador(int y, int x);
void desenhaGameOver();
void desenhaInicio();
void desenhaVitoria();
void desenha_rochas(COORDENADA rochas[]);
void escondecursor();
void laco_menu();
void movimenta_jogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[]);
int testa_proximidade(COORDENADA coord_a, COORDENADA coord_b, int raio);
void testa_captura(JOGADOR xerife, BANDIDO bandido[], int *bandidos_na_cadeia, int modo_jogo);

int main()
{
    escondecursor(); // Esconde o cursor durante a execucao do jogo

    desenhaInicio(); // Desenha a tela de inicio do jogo
    getch();

    laco_menu();
    clrscr();

    return 0;
}
