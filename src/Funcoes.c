#include "bibliotecas.h"

void escondecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void apaga_elemento(int y, int x)
{
    putchxy(y, x, ' ');
}

///  ####################################################################
///                         FUNCOES DE CENARIO
///  ####################################################################

void colore_fundo()
{
    int i, l;

    for(i = 2; i< COLUNASPAREDE; i++)
    {
        for(l = 2; l< LINHASPAREDE; l++)
        {
            textbackground(DARKGRAY);
            putchxy(i, l, ' ');
            textbackground(BLACK);
        }
    }
}

void desenha_cenario()
{
    int i;

    textbackground(BLUE);

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

///  ####################################################################
///                         FUNCOES DE CENARIO
///  ####################################################################

void desenha_pedeNome()
{
    int i, j;
    int m = 20, n = 10;

    desenha_cenario();
    colore_fundo();

    textbackground(CYAN);

    // Fundo do nome
    for(i = 0; i < 5; i++){
        gotoxy(m, n);
        for(j = 0; j < 40; j++){
            if(j == 0 || j == 40 - 1){
                textcolor(BLUE);
                printf("|");
            } else {
                printf(" ");
            }
        }
        n++;
        printf("\n");
    }

    // Frases
    textcolor(BLACK);
    gotoxy(22, 12);
    printf("Digite seu nome: ");


    // Volta ao default
    textbackground(BLACK);
    textcolor(WHITE);
}

void desenha_erro_nome()
{
    desenha_cenario();
    colore_fundo();
    gotoxy(12, 12);
    printf("Escolha um nome com nome maximo %d caracteres!", NOME);
}

void pedeNome(JOGADOR *jogador)
{
    char nome[NOME + 1];

    clrscr();
    do
    {
        desenha_pedeNome();

        textbackground(CYAN);
        textcolor(BLACK);

        fflush(stdin);
        gets(nome);
        textbackground(BLACK);
        textcolor(WHITE);

        if(strlen(nome) > NOME)
        {
            desenha_erro_nome();
            Sleep(2000);
            fflush(stdin);
            clrscr();

        }
    }while(strlen(nome) > NOME);
    strcpy(jogador->nome, nome);
}

///  ####################################################################
///                         FUNCOES DE INFOS
///  ####################################################################

void ajuda()
{
    //contorno
    desenha_cenario();

    //colorindo o fundo
    colore_fundo();

    textbackground(DARKGRAY);
    textcolor(BLACK);

    gotoxy(13,8);
    printf("_______");
    gotoxy(12,9);
    printf("||  ^  ||");
    gotoxy(12,10);
    printf("||  |  ||");
    gotoxy(12,11);
    printf("||_____||");
    gotoxy(4,12);
    printf(" _______|/_____\\|_______");
    gotoxy(4,13);
    printf("||     |||  |  |||     ||");
    gotoxy(4,14);
    printf("|| <-- |||  v  ||| --> ||");
    gotoxy(4,15);
    printf("||_____|||_____|||_____||");
    gotoxy(4,16);
    printf("|/_____\\|/_____\\|/_____\\|");

    //Barra de espa�o
    gotoxy(41,12);
    printf(" ______________________________");
    gotoxy(41,13);
    printf("||                            ||");
    gotoxy(41,14);
    printf("||                            ||");
    gotoxy(41,15);
    printf("||____________________________||");
    gotoxy(41,16);
    printf("|/____________________________\\|");


    // Frases
    textbackground(CYAN);

    gotoxy(35, 5);
    printf("Instru%c%ces:", 135, 228);

    gotoxy(9, 19);
    printf("Move o Xerife");

    gotoxy(48, 19);
    printf("Captura o bandido");


    // Volta ao default
    textbackground(BLACK);
    textcolor(WHITE);
}

void desenha_infos_jogador(char nome[NOME + 1], int modo_de_jogo, int bandidos_na_cadeia)
{
    char* modo[] = {"Facil", "Dificil"};
    int i;
    int aux = 50;

    //modo_de_jogo = escolhe_op();

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

void desenha_info_tempo(clock_t inicio, int *segundos_jogo)
{
    clock_t fim;
    int segundos_decorridos = 0;
    fim = clock();
    segundos_decorridos = (fim - inicio) / CLOCKS_PER_SEC;

    *segundos_jogo = segundos_decorridos;

    cputsxy(71, 25, "Tempo:");
    gotoxy(77,25);
    printf("%d:", (2 - (segundos_decorridos / 60)));
    gotoxy(79,25);
    printf("%02d", (59 - (segundos_decorridos % 60)));
}

///  ####################################################################
///                  FUNCOES QUE ORGANIZAM O RANKING
///  ####################################################################

void instancia_vetor(RANKING vetor[])
{// Instancia vetor do ranking lendo o arquivo binário já ordenado
    FILE *rank;
    RANKING auxiliar;
    int cont = 0;

    rank = fopen("save_ranking.bin", "a+");
    if(!rank)
    {
        printf("Erro na abertura/criacao do arquivo");
    }
    else
    {
        while(!feof(rank))
        {
            if(fread(&auxiliar, sizeof(auxiliar), 1, rank) == 1)
            {
                strcpy(vetor[cont].nome_jogador, auxiliar.nome_jogador);
                vetor[cont].score_jogador = auxiliar.score_jogador;
                cont ++;
            }
            else if(!feof(rank))
            {
                printf("Erro na leitura do arquivo");
            }
        }
    }
    fclose(rank);
}

void inicializa_vetor_ranking(RANKING vetor[])
{ // Inicializa o vetor do Ranking com 0 no score e espaco em branco no nome
    // para print da opcao RANKING do menu
    int i;

    for(i = 0; i <= MAX_TAMANHO_VETOR; i++)
    {
        strcpy(vetor[i].nome_jogador, " ");
        vetor[i].score_jogador = 0;
    }
}

void ordena_vetor(RANKING vetor[])
{// Ordena vetor do Ranking
    int cont = 0;
    RANKING auxiliar;

    do
    {
        if(vetor[MAX_TAMANHO_VETOR -1].score_jogador >= vetor[cont].score_jogador)
        {

            strcpy(auxiliar.nome_jogador, vetor[cont].nome_jogador);
            auxiliar.score_jogador = vetor[cont].score_jogador;

            strcpy(vetor[cont].nome_jogador, vetor[MAX_TAMANHO_VETOR -1].nome_jogador );
            vetor[cont].score_jogador = vetor[MAX_TAMANHO_VETOR -1].score_jogador;

            strcpy(vetor[MAX_TAMANHO_VETOR - 1].nome_jogador, auxiliar.nome_jogador);
            vetor[MAX_TAMANHO_VETOR - 1].score_jogador = auxiliar.score_jogador;
        }
        cont ++;

    }while(auxiliar.score_jogador == 0 || cont < MAX_TAMANHO_VETOR - 2);

}

int compara_valores(RANKING vetor[], JOGADOR exemplo)
{// Compara o valor do menor elemento para a ordenação do RANKING
    if(exemplo.score >= vetor[MAX_TAMANHO_VETOR - 1].score_jogador)
    {
        vetor[MAX_TAMANHO_VETOR - 1].score_jogador = exemplo.score;
        strcpy(vetor[MAX_TAMANHO_VETOR - 1].nome_jogador, exemplo.nome);
        ordena_vetor(vetor);

        return 1;
    }

    return 0;
}

void salva_vetor(RANKING vetor[])
{// Salva o vetor(RANKING, ja ordenado) no arquivo binario do ranking
    FILE *arq;
    RANKING dummy;
    int cont = 0;

    arq = fopen("save_ranking.bin", "w + b");

    if(!arq)
    {
        printf("Erro na abertura do arquivo");
    }
    else
    {
        while(!feof(arq) && cont < MAX_TAMANHO_VETOR)
        {
            strcpy(dummy.nome_jogador, vetor[cont].nome_jogador);
            dummy.score_jogador = vetor[cont].score_jogador;
            fwrite(&dummy, sizeof(dummy), 1, arq);
            cont ++;
        }
    }
    fclose(arq);
}

void show_rank()
{
    FILE *arq;
    RANKING scores;
    int x = 7;
    int colocacao = 1;

    desenha_cenario();
    colore_fundo();

    textbackground(DARKGRAY);
    textcolor(BLACK);
    gotoxy(30, 4);
    printf("-----Ranking----- \n");

    arq = fopen("save_ranking.bin", "rb");
    if(!arq)
    {
        printf("Erro na abertura do arquivo");
    }
    else
    {
        rewind(arq);
        while(!feof(arq))
        {
            if(fread(&scores, sizeof(scores), 1, arq))
            {
                gotoxy(23, x);
                printf("%d. %s", colocacao, scores.nome_jogador);
                gotoxy(44, x);
                printf("Score: %d", scores.score_jogador);
                x ++;
                colocacao ++;
            }
        }
    }
    textbackground(BLACK);
    textcolor(WHITE);
    fclose(arq);
}

void calcula_score(JOGO *game)
{ // Calcula os pontos do jogador dependendo da dificuldade do jogo
    float bonus_dificuldade = 1;
    if(game->modo_jogo == 2)
        bonus_dificuldade = 1.2;

    game->player1.score -= (game->segundos * 55);
    game->player1.score *= bonus_dificuldade;
}

///  ####################################################################
///                    DESENHO E CONTORLE DO MENU DO JOGO
///  ####################################################################

void desenha_selecao_menu(void)
{
    int i, l;

    for(i = 25; i<= 52; i++)
    {
        for(l = 7; l<= 19; l++)
        {
            textbackground(CYAN);
            putchxy(i, l, ' ');
            textbackground(BLACK);
        }
    }

    for(i = 7; i<= 19; i++)
    {
        textcolor(BLUE);
        textbackground(CYAN);
        putchxy(25, i, '|');
        putchxy(52, i, '|');
        textcolor(WHITE);
        textbackground(BLACK);
    }
}

void desenha_menu_inicial()
{
    //contorno
    desenha_cenario();

    //colorindo o fundo
    colore_fundo();

    //parte central onde fica a coluna de selecao
    desenha_selecao_menu();

    textbackground(CYAN);
    textcolor(BLACK);
    gotoxy(26, 8);
    printf("Novo Jogo Modo Facil");
    gotoxy(26, 10);
    printf("Novo Jogo Modo Dificil");
    gotoxy(26, 12);
    printf("Carregar Partida");
    gotoxy(26, 14);
    printf("Ajuda");
    gotoxy(26, 16);
    printf("Ranking");
    gotoxy(26, 18);
    printf("Sair");
    textcolor(WHITE);
    textbackground(BLACK);

    textbackground(DARKGRAY);
    textcolor(LIGHTBLUE);
    gotoxy(22, 3);
    printf("Andrew Borges e Matheus Azambuja");
    gotoxy(21, 4);
    printf("Algoritmos e Programacao - INF01202");
    gotoxy(36, 5);
    printf("2018/2");

    gotoxy(10, 23);
    printf("CIMA e BAIXO para Navegar\t\t ENTER para Selecionar");
    textbackground(BLACK);
    textcolor(WHITE);
}

void imprime_seta_menu(int opcao)
{
    textbackground(CYAN);
    textcolor(BLACK);

    switch(opcao)
    {
        case 1:// Novo Modo Jogo F�cil
            putchxy(46, 8, '<');
            break;
        case 2:// Novo Modo Jogo F�cil
            putchxy(48, 10, '<');
            break;
        case 3:// Carregar Partida
            putchxy(42, 12, '<');
            break;
        case 4:// Ajuda
            putchxy(31, 14, '<');
            break;
        case 5:// Ranking
            putchxy(33, 16, '<');
            break;
        case 6:// Sair
            putchxy(30, 18, '<');
            break;
    }
    textbackground(BLACK);
    textcolor(WHITE);
}

void apaga_seta_menu(int opcao)
{
    textbackground(CYAN);

    switch(opcao)
    {
        case 1:// Novo Modo Jogo F�cil
            putchxy(46, 8, ' ');
            break;
        case 2:// Novo Modo Jogo F�cil
            putchxy(48, 10, ' ');
            break;
        case 3:// Carregar Partida
            putchxy(42, 12, ' ');
            break;
        case 4:// Ajuda
            putchxy(31, 14, ' ');
            break;
        case 5:// Ranking
            putchxy(33, 16, ' ');
            break;
        case 6:// Sair
            putchxy(30, 18, ' ');
            break;
    }
    textbackground(BLACK);
}

int seleciona_opcao()
{
    int loop = 1;
    int opcao = 1;
    char ch;

    imprime_seta_menu(opcao);
    do
    {
        ch = getch();
        switch(ch)
        {
            case 72:
                if(opcao == 1)
                {
                    apaga_seta_menu(opcao);
                    opcao = 6;
                    imprime_seta_menu(opcao);
                }
                else
                {
                    apaga_seta_menu(opcao);
                    opcao--;
                    imprime_seta_menu(opcao);
                }
                break;
            case 80:
                if(opcao == 6)
                {
                    apaga_seta_menu(opcao);
                    opcao = 1;
                    imprime_seta_menu(opcao);
                }
                else
                {
                    apaga_seta_menu(opcao);
                    opcao++;
                    imprime_seta_menu(opcao);
                }
                break;
            case 13:
            apaga_seta_menu(opcao);
                loop = 0;
                return opcao;
                break;
        }
    }
    while(loop);
}

int executa_menu()
{ // Executa as opcoes que o usuario selecionou
    char ch = 0;
    int opcao = 1;
    desenha_menu_inicial();
    opcao = seleciona_opcao();

    switch(opcao)
    {
        case 1:// Novo jogo facil
            clrscr();
            return 1;
            break;
        case 2: // Novo jogo dificil
            clrscr();
            return 2;
            break;
        case 3: // Carrega Partida
            return 3;
            break;
        case 4: // Ajuda
            ajuda();
            while(ch != 13)
            {
                ch = getch();
            }
            return executa_menu();
            break;
        case 5:// Ranking
            show_rank();
            while(ch != 13)
            {
                ch = getch();
            }
            return executa_menu();
            break;
        case 6: // Sair
            return -1;
            break;
    }
    return 0; // Para consistencia
}

///  ####################################################################
///                         FUNCOES DO JOGADOR
///  ####################################################################

void instancia_xerife(JOGADOR *xerife)
{
    xerife->posicao.x = 10;
    xerife->posicao.y = 4;
    xerife->velocidade = 0;
}

void desenha_jogador(int y, int x)
{
    textbackground(BLUE);
    putchxy(y, x, XERIFE);
    textbackground(BLACK);
}

void movimenta_jogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[])
{
    int i;
    for(i = 0; i<=NUM_ROCHAS_DIFICIL; i++)
    {
        if((xerife->posicao.x + desloc.x == rochas[i].x ) && (xerife->posicao.y + desloc.y == rochas[i].y))
        {
            desloc.x = 0;
            desloc.y = 0;
        }
    }
    putchxy(xerife->posicao.y, xerife->posicao.x, ' ');
    xerife->posicao.y += desloc.y;
    xerife->posicao.x += desloc.x;
    textbackground(BLUE);
    putchxy(xerife->posicao.y, xerife->posicao.x, XERIFE);
    textbackground(BLACK);
}

int testa_proximidade(COORDENADA coord_a, COORDENADA coord_b, int raio)
{ // Testa a proximidade de dois elementos quaisquer
    int distanciaVertical, distanciaHorizontal;
    distanciaVertical = abs(coord_b.x - coord_a.x);
    distanciaHorizontal = abs(coord_b.y - coord_a.y);

    if(distanciaVertical <= raio && distanciaHorizontal <= raio)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void testa_captura(JOGADOR xerife, BANDIDO bandido[], int *bandidos_na_cadeia, int modo_jogo, int *num_bandidos)
{
    int i, teste;
    int quant_bandidos;

    if(modo_jogo == 1)
        quant_bandidos = MAX_BANDIDOS_FACIL;
    else
        quant_bandidos = MAX_BANDIDOS_DIFICIL;

    for(i=0; i<quant_bandidos; i++)
    {
        teste = testa_proximidade(xerife.posicao, bandido[i].posicao_b, RAIO);

        if(teste == 1 && GetKeyState (VK_SPACE) & 0x80 && bandido[i].na_cadeia != 0)
        {
            *bandidos_na_cadeia += 1;
            apaga_elemento(bandido[i].posicao_b.y, bandido[i].posicao_b.x);
            bandido[i].posicao_b.x = -1;
            bandido[i].posicao_b.y = -1;
            bandido[i].na_cadeia = 0;
            *num_bandidos -= 1;
        }
    }
}

///  ####################################################################
///                         FUNCOES DOS BANDIDOS
///  ####################################################################

void instancia_bandidos(BANDIDO bandidos[], int quant_bandidos)
{
   int i;
   int vetor_posiy[MAX_BANDIDOS_DIFICIL] = {49, 11, 47, 12, 19, 22, 65};
   int vetor_posix[MAX_BANDIDOS_DIFICIL] = {12, 12, 10, 12, 20, 15, 5};

   for(i=0; i<quant_bandidos; i++)
   {
       bandidos[i].posicao_b.x = vetor_posix[i];
       bandidos[i].posicao_b.y = vetor_posiy[i];
       bandidos[i].na_cadeia = 1;
   }
}

void desenha_bandido(int y, int x)
{
    textbackground(YELLOW);
    putchxy(y, x, BANDIDO_);
    textbackground(BLACK);
}

void desenha_bandidos(BANDIDO bandido[], int quant_bandidos)
{
    int i;
    for(i = 0; i<quant_bandidos; i++)
    {
        if(bandido[i].na_cadeia == 0)
        {
            desenha_bandido(bandido[i].posicao_b.y, bandido[i].posicao_b.x);
        }
    }
}

void movimenta_bandido(BANDIDO bandidos[], COORDENADA desloc, int modo_jogo, COORDENADA rochas[])
{ // Controla a movimentacao dos bandidos
    int random, random2;
    int num_bandidos;
    int i, j;

    srand(time(NULL));

    if (modo_jogo == 1)
        num_bandidos = MAX_BANDIDOS_FACIL;
    else if (modo_jogo == 2)
        num_bandidos = MAX_BANDIDOS_DIFICIL;

    for (i = 0; i < num_bandidos; i++)
    {
        random = (rand() % 4); // Gera um numero random a cada volta do laco
        random2 = (rand() % 4);

        if (random == 0 && (bandidos[i].posicao_b.y +1) != COLUNASPAREDE && bandidos[i].na_cadeia != 0) // DIREITA
        {
            if(random2 == 3 && (bandidos[i].posicao_b.x + 1) != LINHASPAREDE) // BAIXO
            {
                desloc.x = 1;
                desloc.y = 1;
            }
            else
            {
                desloc.x = 0;
                desloc.y = 1;
            }
            if(random2 == 2 && (bandidos[i].posicao_b.x - 1) != 1) // CIMA
            {
                desloc.x = -1;
                desloc.y = 1;
            }
            else
            {
                desloc.x = 0;
                desloc.y = 1;
            }

        }
        else if (random == 1 && (bandidos[i].posicao_b.y - 1) != 1 && bandidos[i].na_cadeia != 0) // ESQUERDA
            {
                if(random2 == 3 && (bandidos[i].posicao_b.x + 1) != LINHASPAREDE) // BAIXO
                {
                    desloc.x = 1;
                    desloc.y = -1;
                }
                else
                {
                    desloc.x = 0;
                    desloc.y = -1;
                }
                if(random2 == 2 && (bandidos[i].posicao_b.x - 1) != 1) // BAIXO
                {
                    desloc.x = -1;
                    desloc.y = -1;
                }
                else
                {
                    desloc.x = 0;
                    desloc.y = -1;
                }
            }
        else if (random == 2 && (bandidos[i].posicao_b.x - 1) != 1 && bandidos[i].na_cadeia != 0) // CIMA
            {
                    if(random2 == 0 && (bandidos[i].posicao_b.y +1) != COLUNASPAREDE) // DIREITA
                    {
                        desloc.x = -1;
                        desloc.y = 1;
                    }
                    else
                    {
                        desloc.x = -1;
                        desloc.y = 0;
                    }
                    if(random2 == 1 && (bandidos[i].posicao_b.y - 1) != 1) // ESQUERDA
                    {
                        desloc.x = -1;
                        desloc.y = -1;
                    }
                    else
                    {
                        desloc.x = -1;
                        desloc.y = 0;
                    }
            }
        else if(random == 3 && (bandidos[i].posicao_b.x + 1) != LINHASPAREDE && bandidos[i].na_cadeia != 0) // BAIXO
            {
                if(random2 == 0 && (bandidos[i].posicao_b.y + 1) != COLUNASPAREDE) // DIREITA
                {
                    desloc.x = 1;
                    desloc.y = 1;
                }
                else
                {
                    desloc.x = 1;
                    desloc.y = 0;
                }
                if(random2 == 1 && (bandidos[i].posicao_b.y - 1) != 1)// ESQUERDA
                {
                    desloc.x = 1;
                    desloc.y = -1;
                }
                else
                {
                    desloc.x = 1;
                    desloc.y = 0;
                }
            }
        else
        {
            desloc.x = 0;
            desloc.y = 0;
        }

        for(j = 0; j<=NUM_ROCHAS_DIFICIL; j++)
        {
            if((bandidos[i].posicao_b.x + desloc.x == rochas[j].x ) && (bandidos[i].posicao_b.y + desloc.y == rochas[j].y))
            {
            desloc.x = 0;
            desloc.y = 0;
            }
        }
        if(bandidos[i].na_cadeia != 0)
        {
        putchxy(bandidos[i].posicao_b.y, bandidos[i].posicao_b.x, ' ');
        bandidos[i].posicao_b.x += desloc.x;
        bandidos[i].posicao_b.y += desloc.y;
        textbackground(YELLOW);
        putchxy(bandidos[i].posicao_b.y, bandidos[i].posicao_b.x, BANDIDO_);
        textbackground(BLACK);
        }
    }
}


void altera_velocidade(JOGADOR *xerife, int aceleracao)
{ // Essa funcao seria usada para implementacao dos alguns POWER UPS
    xerife->velocidade += aceleracao;
}

///  ####################################################################
///                         FUNCOES DAS ROCHAS
///  ####################################################################

void inicializa_rochas(COORDENADA rochas[], int modo_jogo)
{ // Le as rochas de um arquivo de texto e as inicializa
    FILE *arq;
    int max_rochas;
    int i;
    int x, y;

    if(modo_jogo == 1)
    {
         max_rochas = NUM_ROCHAS;
    }
    if(modo_jogo == 2)
    {
        max_rochas = NUM_ROCHAS_DIFICIL;
    }

    arq = fopen("rochas.txt", "r");
    if(!arq)
        printf("Erro na abertura do arquivo");
    else
    {
        i = 0;
        while(!feof(arq) || i < max_rochas)
        {
                fscanf(arq, "(%d,%d)\n", &x, &y);
                rochas[i].x = x;
                rochas[i].y = y;
                i ++;
        }
    }

    fclose(arq);
}

void desenha_rochas(COORDENADA rochas[], int modo_jogo)
{
    int i;

    if(modo_jogo == 1)
    {
        for(i = 0; i<NUM_ROCHAS; i++)
        {
            textbackground(BROWN);
            putchxy(rochas[i].y, rochas[i].x, ' ');
            textbackground(BLACK);
        }
    }
    if(modo_jogo == 2)
    {
        for(i = 0; i<NUM_ROCHAS_DIFICIL; i++)
        {
            textbackground(BROWN);
            putchxy(rochas[i].y, rochas[i].x, ' ');
            textbackground(BLACK);
        }
    }
}

///  ####################################################################
///                     FUNCOES DE SAVE E LOAD DO JOGO
///  ####################################################################

int nome_ja_usado(char nome[TAMSTR], char arquivo[TAMSTR])
{ // Testa se o nome ja foi usado por outro usuario
    // Se sim, retorna a posicao da sua struct no arquivo binario do jogo
    FILE *arq;
    JOGO jogo;
    int posicao = 0;
    int achou = 0;

    arq = fopen(arquivo, "rb");

    if(!arq)
        printf("Erro na abertura do arquivo na funcao NOME_JA_USADO");
    else
        while(!feof(arq) && !achou)
        {
            if(fread(&jogo, sizeof(JOGO), 1, arq) == 1)
            {
                if(strcmp(nome, jogo.player1.nome) == 0)
                    achou = 1;
                else
                    posicao += 1;
            }
        }

    if(!achou)
        return -1;

    return posicao;
}

int salva_jogo(JOGO jogo)
{ // Salva o estado das variaveis da estrutura jogo e armazena em um arquivo binario
    // Se houver o jogador ja tiver um jogo salvo sobrescreve ele
    // Senao salva o jogo no final do arquivo
    char nome_arq[TAMSTR];
    int posicao;
    int retorno;
    FILE *arq;

    strcpy(nome_arq, "jogo_save.bin");

    arq = fopen(nome_arq, "rb");

    if(arq)
        posicao = nome_ja_usado(jogo.player1.nome, nome_arq);
    else
        posicao = -1;

    if(posicao == -1)
    {
        arq = fopen(nome_arq, "ab");
        if(!arq)
        {
            printf("Erro ao abrir o arquivo");
            retorno = 0;
        }
        else
        {
            if(fwrite(&jogo, sizeof(JOGO), 1, arq) != 1)
            {
                printf("erro ao salvar o jogo no arquivo");
                retorno = 0;
            }
            else
                retorno = 1;
        }
        fclose(arq);
    }
    else
    {
        arq = fopen(nome_arq, "r+b");
        if(!arq)
        {
            printf("Erro ao abrir o arquivo na funcao SALVA_JOGO");
            retorno = 0;
        }
        else
        {
            if(posicao != 0)
            {
                if(!fseek(arq, posicao*sizeof(JOGO), SEEK_SET) != 1)
                {
                    printf("Erro ao mover o arquivo na funcao SALVA_JOGO");
                    retorno = 0;
                }
                else
                    retorno = 1;
            }
            else
                rewind(arq);

            if(fwrite(&jogo, sizeof(JOGO), 1, arq) != 1)
            {
                printf("erro ao salvar o jogo no arquivo");
                retorno = 0;
            }
            else
                retorno = 1;
        }
        fclose(arq);
    }
    return retorno;
}

void inicia_jogo(JOGO game, int modo_jogo, clock_t inicio)
{ // Recebe a estrutura do jogo, o modo de jogo e o clock inicial como parametro para iniciar o jogo
    COORDENADA desloc;
    COORDENADA posiRochas[NUM_ROCHAS_DIFICIL];
    game.modo_jogo = modo_jogo;
    game.player1.perdeu = 0;
    game.player1.venceu = 0;

    RANKING scores[MAX_TAMANHO_VETOR];
    inicializa_vetor_ranking(scores);
    instancia_vetor(scores);

    inicializa_rochas(posiRochas, game.modo_jogo);
    desenha_rochas(posiRochas, game.modo_jogo); // Desenha as rochas do jogo

    // Movimentacao do jogador
    while(!(GetKeyState (VK_ESCAPE) & 0x80) && game.player1.perdeu == 0 && game.player1.venceu == 0)
    {
        desenha_cenario();
        desenha_info_tempo(inicio, &game.segundos); // Desenha o tempo do jogo a cada volta do laco
        desenha_infos_jogador(game.player1.nome, game.modo_jogo, game.bandidos_cadeia);
        desenha_jogador(game.player1.posicao.y, game.player1.posicao.x);
        movimenta_bandido(game.bandidos, desloc, game.modo_jogo, posiRochas); // Movimentacao dos bandidos
        testa_captura(game.player1, game.bandidos, &game.bandidos_cadeia, game.modo_jogo, &game.num_bandidos);

        if(GetKeyState (VK_RIGHT) & 0x80)
        {
            if((game.player1.posicao.y + 1) != COLUNASPAREDE)
        {
                desloc.x = 0;
                desloc.y = 1;
                movimenta_jogador(&game.player1, desloc, posiRochas);
        }
                else
            {
                desloc.x = 0;
                desloc.y = 0;
                movimenta_jogador(&game.player1, desloc, posiRochas);
            }
        }
        if (GetKeyState (VK_LEFT) & 0x80)
        {
            if((game.player1.posicao.y - 1)  != 1)
            {   desloc.x = 0;
                desloc.y = -1;
                movimenta_jogador(&game.player1, desloc, posiRochas);
            }
            else
            {
                desloc.x = 0;
                desloc.y = 0;
                movimenta_jogador(&game.player1, desloc, posiRochas);
            }
        }
        if(GetKeyState (VK_UP) & 0x80)
        {
            if((game.player1.posicao.x - 1) != 1)
            {
                desloc.x = -1;
                desloc.y = 0;
                movimenta_jogador(&game.player1, desloc, posiRochas);
            }
            else
            {
                desloc.x = 0;
                desloc.y = 0;
                movimenta_jogador(&game.player1, desloc, posiRochas);
            }
        }
        if (GetKeyState (VK_DOWN) & 0x80)
        {
            if((game.player1.posicao.x + 1) != LINHASPAREDE)
            {
                desloc.x = 1;
                desloc.y = 0;
                movimenta_jogador(&game.player1, desloc, posiRochas);
            }
            else
            {
                desloc.x = 0;
                desloc.y = 0;
                movimenta_jogador(&game.player1, desloc, posiRochas);
            }
        }

        if(game.segundos == 179)
        {
            game.player1.perdeu = 1;
            clrscr();
            desenhaGameOver();
            Sleep(4000);
        }
        if(game.num_bandidos == 0)
        {
            game.player1.venceu = 1;
            clrscr();
            desenhaVitoria();
            Sleep(4000);
        }
        Sleep(120);
    }
    // Ao sair do laco do jogo, o jogo eh salvo
        calcula_score(&game);
        if(game.player1.venceu == 1)
        { // Se o jogador venceu, ele ira comparar com o ultimo colocado do Ranking
            if(compara_valores(scores, game.player1) == 1)
            {
                salva_vetor(scores);
            }
        }
        salva_jogo(game);
        clrscr();
}

void copia_jogador(JOGADOR* destino, JOGADOR origem)
{ // Copia o jogador do jogo que esta sendo carregado
    strcpy(destino->nome, origem.nome);
    destino->perdeu = origem.perdeu;
    destino->posicao.x = origem.posicao.x;
    destino->posicao.y = origem.posicao.y;
    destino->score = origem.score;
    destino->velocidade = origem.velocidade;
    destino->venceu = origem.venceu;
}

void copia_bandidos(BANDIDO destino[], BANDIDO origem[])
{ // Copia os bandidos do jogo que esta senod carregado
    int i;

    for(i=0; i<MAX_BANDIDOS_DIFICIL; i++)
    {
        destino[i].na_cadeia = origem[i].na_cadeia;
        destino[i].posicao_b.x = origem[i].posicao_b.x;
        destino[i].posicao_b.y = origem[i].posicao_b.y;
        destino[i].velocidade = origem[i].velocidade;
    }
}

int carrega_jogo(JOGO* game, char usuario_nome[MAX_NOME])
{ // Carrega o jogo salvo utilizando o nome do usuario
    FILE *save;
    JOGO buffer;
    int achou = 0;

    save = fopen("jogo_save.bin", "rb");

    if(!save)
        printf("erro ao abrir o arquivo na funcao CARREGA_JOGO");
    else
    {
        while(!feof(save) && achou == 0)
        {
            if(fread(&buffer, sizeof(buffer), 1, save) == 1)
            {
                if(strcmp(buffer.player1.nome, usuario_nome) == 0)
                {
                    copia_jogador(&(game->player1), buffer.player1);
                    copia_bandidos(game->bandidos, buffer.bandidos);
                    game->segundos = buffer.segundos;
                    game->modo_jogo = buffer.modo_jogo;
                    game->num_bandidos = buffer.num_bandidos;
                    game->bandidos_cadeia = buffer.bandidos_cadeia;

                    achou = 1;
                }
            }
        }
        fclose(save);
    }

    if(achou == 1)
        return 1;
    else
        return 0;
}

///  ####################################################################
///                     FUNCAO QUE CONTROLA O MENU DO JOGO
///  ####################################################################

// Instancia as variaveis necessarias para inicio do jogo ou carregamento de um jogo ja salvo

void laco_menu()
{ // Funcao que controla o loop do menu do jogo
    JOGO game;
    // TIMER DO JOGO
    clock_t inicio;

    pedeNome(&game.player1);

    int escolha_menu;

    do
    {
        clrscr();
        escolha_menu = executa_menu(); // Armazena a opcao escolhida pelo jogador no menu
        inicio = clock();
        switch(escolha_menu)
        {
            case 1: // NOVO JOGO FACIL
                // Instancia e desenha os bandidos
                instancia_xerife(&game.player1); // Instancia o xerife na sua posicao inicial
                instancia_bandidos(game.bandidos, MAX_BANDIDOS_FACIL);
                desenha_bandidos(game.bandidos, MAX_BANDIDOS_FACIL);

                game.num_bandidos = MAX_BANDIDOS_FACIL;
                game.player1.score = SCORE;
                game.segundos = inicio;
                game.bandidos_cadeia = 0;

                inicia_jogo(game, escolha_menu, inicio);
                break;
            case 2: // NOVO JOGO DIFICIL
                // Instancia e desenha os bandidos
                instancia_xerife(&game.player1); // Instancia o xerife na sua posicao inicial
                instancia_bandidos(game.bandidos, MAX_BANDIDOS_DIFICIL);
                desenha_bandidos(game.bandidos, MAX_BANDIDOS_DIFICIL);

                game.num_bandidos = MAX_BANDIDOS_DIFICIL;
                game.player1.score = SCORE;
                game.segundos = inicio;
                game.bandidos_cadeia = 0;

                inicia_jogo(game, escolha_menu, inicio);
                break;
            case 3: // CARREGA O JOGO
                pedeNome(&game.player1);
                if(carrega_jogo(&game, game.player1.nome) == 1)
                {
                    clrscr();
                    Sleep(2000);
                    if(game.modo_jogo == 1)
                        desenha_bandidos(game.bandidos, MAX_BANDIDOS_FACIL);
                    if(game.modo_jogo == 2)
                        desenha_bandidos(game.bandidos, MAX_BANDIDOS_DIFICIL);
                    desenha_jogador(game.player1.posicao.y, game.player1.posicao.x);

                    inicia_jogo(game, game.modo_jogo, game.segundos);
                }
                else
                {
                    gotoxy(30, 16);
                    textbackground(DARKGRAY);
                    printf("Jogo nao encontrado.");
                    textbackground(BLACK);
                    textcolor(WHITE);
                    Sleep(2000);
                }
                break;
        }
    }while(escolha_menu != -1);
}
