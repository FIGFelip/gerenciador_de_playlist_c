
#include <stdlib.h>
#include "playlist.h"

void inicializarPlaylist(Playlist *playlist) {
    if (playlist == NULL) {
        return;
    }

    playlist->inicio = NULL;
    playlist->fim = NULL;
    playlist->atual = NULL;
    playlist->tamanho = 0;
}

void destruirPlaylist(Playlist *playlist) {
    if (playlist == NULL) {
        return;
    }

    Musica *cursor = playlist->inicio;

    while (cursor != NULL) {
        Musica *proxima = cursor->proximo;
        free(cursor);
        cursor = proxima;
    }

    playlist->inicio = NULL;
    playlist->fim = NULL;
    playlist->atual = NULL;
    playlist->tamanho = 0;
}
