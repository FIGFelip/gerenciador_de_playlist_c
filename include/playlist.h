
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "musicas.h"

typedef struct Playlist {
    Musica *inicio;
    Musica *fim;
    Musica *atual;
    int tamanho;
} Playlist;

void inicializarPlaylist(Playlist *playlist);
void destruirPlaylist(Playlist *playlist);

#endif
