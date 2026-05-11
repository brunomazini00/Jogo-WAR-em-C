#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ================= FUNÇÕES =================

// Limpa buffer do teclado
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Remove \n do fgets
void removerQuebraLinha(char *texto)
{
    texto[strcspn(texto, "\n")] = '\0';
}

// Cadastro de territórios
void cadastrarTerritorio(Territorio *territorio)
{
    printf("\n===== CADASTRO DE TERRITORIO =====\n");

    printf("Nome do territorio: ");
    fgets(territorio->nome, 30, stdin);
    removerQuebraLinha(territorio->nome);

    printf("Cor do exercito: ");
    fgets(territorio->cor, 10, stdin);
    removerQuebraLinha(territorio->cor);

    printf("Numero de tropas: ");
    scanf("%d", &territorio->tropas);
    limparBufferEntrada();

    printf("\nTerritorio cadastrado com sucesso!\n");
}

// Exibe todos os territórios
void listarTerritorios(Territorio *mapa, int total)
{
    printf("\n===== LISTA DE TERRITORIOS =====\n");

    if (total == 0)
    {
        printf("Nenhum territorio cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("\n[%d]\n", i);
        printf("Territorio: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Numero de tropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor)
{
    int dadoAtacante;
    int dadoDefensor;

    // Não pode atacar mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("\nVoce nao pode atacar um territorio da mesma cor!\n");
        return;
    }

    // Atacante precisa ter pelo menos 2 tropas
    if (atacante->tropas <= 1)
    {
        printf("\nO territorio atacante nao possui tropas suficientes!\n");
        return;
    }

    // Rola os dados
    dadoAtacante = (rand() % 6) + 1;
    dadoDefensor = (rand() % 6) + 1;

    printf("\n===== BATALHA =====\n");

    printf("Atacante (%s) tirou: %d\n",
           atacante->nome,
           dadoAtacante);

    printf("Defensor (%s) tirou: %d\n",
           defensor->nome,
           dadoDefensor);

    // Resultado
    if (dadoAtacante > dadoDefensor)
    {
        printf("\nO atacante venceu a rodada!\n");

        // Defensor perde 1 tropa
        defensor->tropas--;

        printf("%s perdeu 1 tropa.\n", defensor->nome);

        // Se zerar tropas, conquista território
        if (defensor->tropas <= 0)
        {
            printf("\nTerritorio conquistado!\n");

            // Troca a cor
            strcpy(defensor->cor, atacante->cor);

            // Metade das tropas do atacante vai para o defensor
            int tropasTransferidas = atacante->tropas / 2;

            defensor->tropas = tropasTransferidas;

            atacante->tropas -= tropasTransferidas;

            printf("%s agora pertence ao exercito %s!\n",
                   defensor->nome,
                   defensor->cor);
        }
    }
    else
    {
        printf("\nO defensor venceu a rodada!\n");

        // Atacante perde 1 tropa
        atacante->tropas--;

        printf("%s perdeu 1 tropa.\n", atacante->nome);
    }

    // Exibe situação atual
    printf("\n===== ESTADO ATUAL =====\n");

    printf("\nATACANTE\n");
    printf("Territorio: %s\n", atacante->nome);
    printf("Cor: %s\n", atacante->cor);
    printf("Tropas: %d\n", atacante->tropas);

    printf("\nDEFENSOR\n");
    printf("Territorio: %s\n", defensor->nome);
    printf("Cor: %s\n", defensor->cor);
    printf("Tropas: %d\n", defensor->tropas);
}

// Libera memória alocada
void liberarMemoria(Territorio *mapa)
{
    free(mapa);
}

// ================= MAIN =================

int main()
{
    srand(time(NULL));

    int totalTerritorios;
    int opcao;

    // Quantidade dinâmica de territórios
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);
    limparBufferEntrada();

    // Alocação dinâmica
    Territorio *mapa = (Territorio *)calloc(totalTerritorios, sizeof(Territorio));

    // Verifica falha na memória
    if (mapa == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    int cadastrados = 0;

    do
    {
        printf("\n=========== WAR ===========\n");
        printf("1 - Cadastrar territorio\n");
        printf("2 - Listar territorios\n");
        printf("3 - Atacar territorio\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case 1:

            if (cadastrados < totalTerritorios)
            {
                cadastrarTerritorio(&mapa[cadastrados]);
                cadastrados++;
            }
            else
            {
                printf("\nLimite de territorios atingido.\n");
            }

            break;

        case 2:

            listarTerritorios(mapa, cadastrados);

            break;

        case 3:

            if (cadastrados < 2)
            {
                printf("\nCadastre pelo menos 2 territorios.\n");
                break;
            }

            listarTerritorios(mapa, cadastrados);

            int indiceAtacante;
            int indiceDefensor;

            printf("\nEscolha o indice do territorio atacante: ");
            scanf("%d", &indiceAtacante);

            printf("Escolha o indice do territorio defensor: ");
            scanf("%d", &indiceDefensor);

            limparBufferEntrada();

            // Validação dos índices
            if (indiceAtacante < 0 || indiceAtacante >= cadastrados ||
                indiceDefensor < 0 || indiceDefensor >= cadastrados)
            {
                printf("\nIndice invalido.\n");
                break;
            }

            // Não pode atacar a si mesmo
            if (indiceAtacante == indiceDefensor)
            {
                printf("\nUm territorio nao pode atacar a si mesmo.\n");
                break;
            }

            atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);

            break;

        case 0:

            printf("\nSaindo do jogo...\n");

            break;

        default:

            printf("\nOpcao invalida.\n");

            break;
        }

        if (opcao != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 0);

    // Libera memória
    liberarMemoria(mapa);

    return 0;
}