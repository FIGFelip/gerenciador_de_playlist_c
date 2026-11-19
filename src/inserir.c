#include "operacoes.h"
#include <stdlib.h>
#include <string.h>

InsercaoStatus inserirMusica(
    Playlist *playlist,
    const char *nome,
    const char *artista,
    int duracao)
{
    //checa playlist inválida
    if (playlist == NULL)
    {
        return INSERCAO_PLAYLIST_INVALIDA;
    }

    // valida se nome esta vazio
    if (nome == NULL || nome[0] == '\0')
    {
        return INSERCAO_NOME_INVALIDO;
    }
    //valida se artista esta vazio
    if (artista == NULL || artista[0] == '\0')
    {
        return INSERCAO_ARTISTA_INVALIDO;
    }
    //valida duracao
    if (duracao <= 0)
    {
        return INSERCAO_DURACAO_INVALIDA;
    }

    //valida tamanho das entradas
    if (strlen(nome) >= TAM_NOME)
    {
        return INSERCAO_NOME_MUITO_LONGO;
    }

    if (strlen(artista) >= TAM_ARTISTA)
    {
        return INSERCAO_ARTISTA_MUITO_LONGO;
    }

    Musica *nova = malloc(sizeof(*nova));

    if (nova == NULL)
    {
        return INSERCAO_FALHA_ALOCACAO;
    }

    strcpy(nova->nome, nome);
    strcpy(nova->artista, artista);
    nova->duracao = duracao;
    nova->anterior = playlist->fim;
    nova->proximo = NULL;

    if (playlist->fim == NULL)
    {
        playlist->inicio = nova;
        playlist->atual = nova;
    }
    else
    {
        playlist->fim->proximo = nova;
    }

    playlist->fim = nova;
    playlist->tamanho++;

    return INSERCAO_OK;
}