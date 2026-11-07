#include <stdio.h>
#include "../include/operacoes.h"

void exibirMenu()
{
    int opcao;
    do {
        printf("\n===| MENU |===\n\n");
        printf("Selecione a opção desejada:\n");
        printf("( 1 ) - Criar playlist\n");
        printf("( 2 ) - Excluir playlist\n");
        printf("( 3 ) - Adicionar música\n");
        printf("( 4 ) - Remover música\n");
        printf("( 5 ) - Avançar música\n");
        printf("( 6 ) - Retroceder música\n");
        printf("( 7 ) - Buscar música\n");
        printf("( 0 ) - Sair\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Implementação em breve...\n");
            break;
        case 2:
            printf("Implementação em breve...\n");
            break;
        case 3:
            printf("Implementação em breve...\n");
            break;
        case 4:
            printf("Implementação em breve...\n");
            break;
        case 5:
            printf("Implementação em breve...\n");
            break;
        case 6:
            printf("Implementação em breve...\n");
            break;
        case 7:
            printf("Implementação em breve...\n");
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
    } while (opcao != 0);
}