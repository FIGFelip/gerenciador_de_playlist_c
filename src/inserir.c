#include "operacoes.h"
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

int inserirMusica(Playlist *playlist, const char *nome, const char *artista, int duracao) {
    if (playlist == NULL || nome == NULL || artista == NULL || duracao <= 0) {
        return 0;
    }

    Musica *nova = malloc(sizeof(*nova));
    if (nova == NULL) {
        return 0;
    }

    strcpy(nova->nome, nome);
    strcpy(nova->artista, artista);
    nova->duracao = duracao;
    nova->anterior = playlist->fim;
    nova->proximo = NULL;

    if (playlist->fim == NULL) {
        playlist->inicio = nova;
        playlist->atual = nova;
    } else {
        playlist->fim->proximo = nova;
    }

    playlist->fim = nova;
    playlist->tamanho++;
    return 1;
}