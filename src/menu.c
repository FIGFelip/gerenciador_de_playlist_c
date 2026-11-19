#include <stdio.h>
#include "operacoes.h"
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
        {
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
        }
        case 2:
        {
            char musicaRemover[100];

            printf("Nome da música: ");
            scanf(" %[^\n]", musicaRemover);

            RemocaoStatus status = removerMusica(
                playlist,
                musicaRemover);

            switch (status)
            {

            case REMOCAO_OK:
                printf("Música removida!\n");
                break;

            case REMOCAO_PLAYLIST_INVALIDA:
                printf("Playlist inválida.\n");
                break;

            case REMOCAO_NOME_INVALIDO:
                printf("Nome inválido.\n");
                break;

            case REMOCAO_PLAYLIST_VAZIA:
                printf("Playlist vazia.\n");
                break;

            case REMOCAO_MUSICA_NAO_ENCONTRADA:
                printf("Música não encontrada.\n");
                break;
            }

            break;
        }

        case 3:
        {
            Musica *proxima = NULL;

            NavegacaoStatus status = avancarMusica(playlist, &proxima);

            switch (status)
            {
            case NAV_OK:
                printf("Avancando... Agora tocando: %s - %s\n", proxima->nome, proxima->artista);
                break;

            case NAV_PLAYLIST_INVALIDA:
                printf("Playlist invalida.\n");
                break;

            case NAV_PLAYLIST_VAZIA:
                printf("Playlist vazia.\n");
                break;

            case NAV_FIM_LISTA:
                printf("Ja na ultima musica.\n");
                break;
            }

            break;
        }

        case 4:
        {
            Musica *anterior = NULL;

            NavegacaoStatus status = retrocederMusica(playlist, &anterior);

            switch (status)
            {
            case NAV_OK:
                printf("Voltando... Agora tocando: %s - %s\n", anterior->nome, anterior->artista);
                break;

            case NAV_PLAYLIST_INVALIDA:
                printf("Playlist invalida.\n");
                break;

            case NAV_PLAYLIST_VAZIA:
                printf("Playlist vazia.\n");
                break;

            case NAV_FIM_LISTA:
                printf("Ja na primeira musica.\n");
                break;
            }

            break;
        }

        case 5:
        {
            Musica *atual = NULL;

            NavegacaoStatus status = consultarAtual(
                playlist,
                &atual);

            switch (status)
            {
            case NAV_OK:
                printf(
                    "Tocando agora: %s - %s - %ds\n",
                    atual->nome,
                    atual->artista,
                    atual->duracao);
                break;

            case NAV_PLAYLIST_INVALIDA:
                printf("Playlist invalida.\n");
                break;

            case NAV_PLAYLIST_VAZIA:
                printf("Playlist vazia.\n");
                break;

            default:
                break;
            }

            break;
        }

        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
    } while (opcao != 0);
}