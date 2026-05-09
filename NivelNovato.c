#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constante global
#define MAX_TERRITORIOS 5

// Estrutura (Struct)
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};
// Limpeza de Buffer
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
// Função Principal
int main()
{

    struct Territorio Territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;
    // Menu Iterativo
    do
    {
        printf("==================WAR=====================\n\n");
        printf("1 - Cadastrar novo territorio \n");
        printf("2 - Listar todos os territorios \n");
        printf("0 - sair \n");
        printf("\nEscolha a opcao desejada: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case 1:
            printf("------------Cadastro de novo territorio------------\n\n");

            if (totalTerritorios < MAX_TERRITORIOS)
            {
                printf("Digite o nome do territorio: ");
                fgets(Territorios[totalTerritorios].nome, 30, stdin);
                printf("Digite a cor do Exercito: ");
                fgets(Territorios[totalTerritorios].cor, 10, stdin);
                printf("Digite o numero de tropas: ");
                scanf("%d", &Territorios[totalTerritorios].tropas);
                limparBufferEntrada();
                totalTerritorios++;
            }
            else
            {
                printf("Limite de territorios atingido. Nao e possivel cadstrar mais territorios.\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 2:
            printf("------------Consulta de territorios cadastrados------------\n\n");
            if (totalTerritorios == 0)
            {
                printf("Nenhum territorio cadastrado.\n");
            }
            else
            {
                for (int i = 0; i < totalTerritorios; i++)
                {
                    printf("Territorio: %s", Territorios[i].nome);
                    printf("Cor do exercito: %s", Territorios[i].cor);
                    printf("Numero de tropas: %d\n", Territorios[i].tropas);
                }
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida. Por favor, tente novamente.\n");
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        }
    } while (opcao != 0);

    return 0;
}