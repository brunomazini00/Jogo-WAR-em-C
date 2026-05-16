#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==========================================
// ESTRUTURA DO TERRITORIO
// ==========================================

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==========================================
// VETOR DE MISSOES
// ==========================================

char *missoes[] =
{
    "Conquistar 2 territorios",
    "Possuir 10 tropas no total",
    "Eliminar o exercito Verde",
    "Ter pelo menos 3 territorios",
    "Dominar 4 territorios"
};

int totalMissoes = 5;

// ==========================================
// FUNCOES AUXILIARES
// ==========================================

// Limpa buffer do teclado
void limparBufferEntrada()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// Remove quebra de linha do fgets
void removerQuebraLinha(char *texto)
{
    texto[strcspn(texto, "\n")] = '\0';
}

// ==========================================
// FUNCOES DE EXIBICAO
// ==========================================

// Exibe mapa formatado
void exibirMapa(Territorio *mapa, int total)
{
    printf("\n=========== MAPA DO MUNDO ===========\n\n");

    if (total == 0)
    {
        printf("Nenhum territorio cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("%d. %-15s ",
               i + 1,
               mapa[i].nome);

        printf("(Exercito: %-10s",
               mapa[i].cor);

        printf(", Tropas: %d)\n",
               mapa[i].tropas);
    }

    printf("\n=====================================\n");
}

// Exibe missão apenas no início
void exibirMissao(char *missao,
                  char *corJogador)
{
    printf("\n--- SUA MISSAO (Exercito %s) ---\n",
           corJogador);

    printf("%s\n",
           missao);
}

// Exibe menu
void exibirMenu()
{
    printf("\n--- MENU DE ACOES ---\n");

    printf("1 - Cadastrar territorio\n");
    printf("2 - Atacar\n");
    printf("0 - Sair\n");
}

// ==========================================
// CADASTRO DE TERRITORIOS
// ==========================================

void cadastrarTerritorio(Territorio *territorio)
{
    printf("\n===== CADASTRO DE TERRITORIO =====\n");

    printf("Nome do territorio: ");
    fgets(territorio->nome,
          30,
          stdin);

    removerQuebraLinha(territorio->nome);

    printf("Cor do exercito: ");
    fgets(territorio->cor,
          10,
          stdin);

    removerQuebraLinha(territorio->cor);

    printf("Numero de tropas: ");
    scanf("%d",
          &territorio->tropas);

    limparBufferEntrada();

    printf("\nTerritorio cadastrado com sucesso!\n");
}

// ==========================================
// MISSOES
// ==========================================

// Sorteia missão
void atribuirMissao(char *destino,
                    char *missoes[],
                    int totalMissoes)
{
    int sorteio =
        rand() % totalMissoes;

    strcpy(destino,
           missoes[sorteio]);
}

// Verifica se missão foi cumprida
int verificarMissao(char *missao,
                    Territorio *mapa,
                    int tamanho,
                    char *corJogador)
{
    int territorios = 0;
    int tropasTotais = 0;
    int exercitoVerdeExiste = 0;

    for (int i = 0; i < tamanho; i++)
    {
        // Conta apenas territórios do jogador
        if (strcmp(mapa[i].cor,
                   corJogador) == 0)
        {
            territorios++;

            tropasTotais +=
                mapa[i].tropas;
        }

        // Verifica existência do exército verde
        if (strcmp(mapa[i].cor,
                   "Verde") == 0)
        {
            exercitoVerdeExiste = 1;
        }
    }

    // ===============================
    // MISSAO 1
    // ===============================

    if (strcmp(missao,
               "Conquistar 2 territorios") == 0)
    {
        return territorios >= 2;
    }

    // ===============================
    // MISSAO 2
    // ===============================

    if (strcmp(missao,
               "Possuir 10 tropas no total") == 0)
    {
        return tropasTotais >= 10;
    }

    // ===============================
    // MISSAO 3
    // ===============================

    if (strcmp(missao,
               "Eliminar o exercito Verde") == 0)
    {
        return exercitoVerdeExiste == 0;
    }

    // ===============================
    // MISSAO 4
    // ===============================

    if (strcmp(missao,
               "Ter pelo menos 3 territorios") == 0)
    {
        return territorios >= 3;
    }

    // ===============================
    // MISSAO 5
    // ===============================

    if (strcmp(missao,
               "Dominar 4 territorios") == 0)
    {
        return territorios >= 4;
    }

    return 0;
}

// ==========================================
// ATAQUE
// ==========================================

void atacar(Territorio *atacante,
             Territorio *defensor)
{
    int dadoAtacante;
    int dadoDefensor;

    // Não pode atacar territórios aliados
    if (strcmp(atacante->cor,
               defensor->cor) == 0)
    {
        printf("\nVoce nao pode atacar um territorio da mesma cor!\n");

        return;
    }

    // Precisa de tropas suficientes
    if (atacante->tropas <= 1)
    {
        printf("\nO territorio atacante nao possui tropas suficientes!\n");

        return;
    }

    // Sorteia dados
    dadoAtacante =
        (rand() % 6) + 1;

    dadoDefensor =
        (rand() % 6) + 1;

    printf("\n========== BATALHA ==========\n");

    printf("\nAtacante (%s) tirou: %d\n",
           atacante->nome,
           dadoAtacante);

    printf("Defensor (%s) tirou: %d\n",
           defensor->nome,
           dadoDefensor);

    // ==================================
    // ATACANTE VENCE
    // ==================================

    if (dadoAtacante > dadoDefensor)
    {
        printf("\nO atacante venceu a rodada!\n");

        defensor->tropas--;

        printf("%s perdeu 1 tropa.\n",
               defensor->nome);

        // Conquista território
        if (defensor->tropas <= 0)
        {
            printf("\nTerritorio conquistado!\n");

            // Troca cor do território
            strcpy(defensor->cor,
                   atacante->cor);

            // Transfere metade das tropas
            int tropasTransferidas =
                atacante->tropas / 2;

            defensor->tropas =
                tropasTransferidas;

            atacante->tropas -=
                tropasTransferidas;

            printf("%s agora pertence ao exercito %s!\n",
                   defensor->nome,
                   defensor->cor);
        }
    }

    // ==================================
    // DEFENSOR VENCE
    // ==================================

    else
    {
        printf("\nO defensor venceu a rodada!\n");

        atacante->tropas--;

        printf("%s perdeu 1 tropa.\n",
               atacante->nome);
    }

    // ==================================
    // ESTADO ATUAL
    // ==================================

    printf("\n======= ESTADO ATUAL =======\n");

    printf("\nATACANTE\n");

    printf("Territorio: %s\n",
           atacante->nome);

    printf("Cor: %s\n",
           atacante->cor);

    printf("Tropas: %d\n",
           atacante->tropas);

    printf("\nDEFENSOR\n");

    printf("Territorio: %s\n",
           defensor->nome);

    printf("Cor: %s\n",
           defensor->cor);

    printf("Tropas: %d\n",
           defensor->tropas);
}

// ==========================================
// LIBERAR MEMORIA
// ==========================================

void liberarMemoria(Territorio *mapa,
                    char *missao)
{
    free(mapa);

    free(missao);
}

// ==========================================
// MAIN
// ==========================================

int main()
{
    srand(time(NULL));

    int totalTerritorios;
    int cadastrados = 0;
    int opcao;

    // ======================================
    // COR DO JOGADOR
    // ======================================

    char corJogador[10];

    printf("Digite a cor do seu exercito: ");

    fgets(corJogador,
          10,
          stdin);

    removerQuebraLinha(corJogador);

    // ======================================
    // QUANTIDADE DE TERRITORIOS
    // ======================================

    printf("\nQuantos territorios deseja cadastrar? ");

    scanf("%d",
          &totalTerritorios);

    limparBufferEntrada();

    // ======================================
    // ALOCACAO DOS TERRITORIOS
    // ======================================

    Territorio *mapa =
        (Territorio *)calloc(totalTerritorios,
                             sizeof(Territorio));

    if (mapa == NULL)
    {
        printf("Erro ao alocar memoria.\n");

        return 1;
    }

    // ======================================
    // ALOCACAO DA MISSAO
    // ======================================

    char *missaoJogador =
        (char *)malloc(100 * sizeof(char));

    if (missaoJogador == NULL)
    {
        printf("Erro ao alocar memoria da missao.\n");

        free(mapa);

        return 1;
    }

    // ======================================
    // SORTEIO DA MISSAO
    // ======================================

    atribuirMissao(missaoJogador,
                   missoes,
                   totalMissoes);

    // Exibe missão apenas uma vez
    exibirMissao(missaoJogador,
                 corJogador);

    // ======================================
    // LOOP PRINCIPAL
    // ======================================

    do
    {
        exibirMapa(mapa,
                   cadastrados);

        exibirMenu();

        printf("\nEscolha uma opcao: ");

        scanf("%d",
              &opcao);

        limparBufferEntrada();

        // ==================================
        // CADASTRAR TERRITORIO
        // ==================================

        if (opcao == 1)
        {
            if (cadastrados < totalTerritorios)
            {
                cadastrarTerritorio(
                    &mapa[cadastrados]);

                cadastrados++;
            }
            else
            {
                printf("\nLimite de territorios atingido.\n");
            }
        }

        // ==================================
        // ATACAR
        // ==================================

        else if (opcao == 2)
        {
            if (cadastrados < 2)
            {
                printf("\nCadastre pelo menos 2 territorios.\n");
            }
            else
            {
                int atacante;
                int defensor;

                exibirMapa(mapa,
                           cadastrados);

                printf("\n===== FASE DE ATAQUE =====\n");

                printf("\nEscolha o territorio atacante (1 a %d): ",
                       cadastrados);

                scanf("%d",
                      &atacante);

                printf("Escolha o territorio defensor (1 a %d): ",
                       cadastrados);

                scanf("%d",
                      &defensor);

                limparBufferEntrada();

                atacante--;
                defensor--;

                // ==========================
                // VALIDACAO
                // ==========================

                if (atacante < 0 ||
                    atacante >= cadastrados ||
                    defensor < 0 ||
                    defensor >= cadastrados)
                {
                    printf("\nIndice invalido.\n");
                }
                else if (atacante == defensor)
                {
                    printf("\nUm territorio nao pode atacar a si mesmo.\n");
                }
                else
                {
                    atacar(&mapa[atacante],
                            &mapa[defensor]);

                    // ======================
                    // VERIFICACAO AUTOMATICA
                    // ======================

                    if (verificarMissao(missaoJogador,
                                        mapa,
                                        cadastrados,
                                        corJogador))
                    {
                        printf("\n🏆 MISSAO CUMPRIDA!\n");

                        printf("Voce venceu o jogo!\n");

                        opcao = 0;
                    }
                }
            }
        }

        // ==================================
        // SAIR
        // ==================================

        else if (opcao == 0)
        {
            printf("\nSaindo do jogo...\n");
        }

        // ==================================
        // OPCAO INVALIDA
        // ==================================

        else
        {
            printf("\nOpcao invalida.\n");
        }

        // ==================================
        // PAUSA
        // ==================================

        if (opcao != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    }
    while (opcao != 0);

    // ======================================
    // LIBERAR MEMORIA
    // ======================================

    liberarMemoria(mapa,
                   missaoJogador);

    return 0;
}