#include <stdio.h>
#include "../include/operacoes.h"
#include "playlist.h"

void exibirMenu(Playlist *playlist)
{
    int opcao;
    do
    {
        printf("\n===| MENU |===\n\n");
        printf("Selecione a opção desejada:\n");
        printf("( 1 ) - Adicionar música\n");
        printf("( 2 ) - Remover música\n");
        printf("( 3 ) - Avançar música\n");
        printf("( 4 ) - Retroceder música\n");
        printf("( 5 ) - Consultar música atual\n");
        printf("( 0 ) - Sair\n");

        if (scanf("%d", &opcao) != 1)
        {
            break;
        }
        switch (opcao)
        {
        case 1:
            char nome[100];
            char artista[100];
            int duracao;
            // printf("Implementação em breve...\n");
            printf("Nome da música: ");
            scanf(" %[^\n]", nome);

            printf("Artista: ");
            scanf(" %[^\n]", artista);

            printf("Duração (segundos): ");
            scanf("%d", &duracao);
            if (inserirMusica(playlist, nome, artista, duracao))
            {
                printf("Música adicionada!\n");
            }
            else
            {
                printf("Erro ao alocar memória para música\n");
            }
            break;
        case 2:
            char musicaRemover[100];
            // printf("Implementação em breve...\n");
            printf("Nome da música: ");
            scanf(" %[^\n]", musicaRemover);
            if (removerMusica(playlist, musicaRemover))
            {
                printf("Música removida\n");
            }
            else
            {
                printf("Erro ao remover música\n");
            }
            break;
        case 3:
            Musica *proxima = avancarMusica(playlist);
            if (proxima != NULL)
            {
                printf("Anvançando...Agora tocando: %s - %s\n", proxima->nome, proxima->artista);
            }
            else
            {
                printf("Erro ao avançar música\n");
            }
            break;
        case 4:
            Musica *anterior = retrocederMusica(playlist);
            if (anterior != NULL)
            {
                printf("Voltando...Agora tocando: %s - %s\n", anterior->nome, anterior->artista);
            }
            else
            {
                printf("Erro ao retroceder música\n");
            }
            break;
        case 5:
            Musica *atual = consultarAtual(playlist);
            if (atual != NULL)
            {
                printf("Tocando agora: %s - %s - %ds\n", atual->nome, atual->artista, atual->duracao);
            }
            else
            {
                printf("Erro ao consultar atual\n");
            }
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