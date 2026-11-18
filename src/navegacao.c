#include "operacoes.h"
#include "playlist.h"
#include "musicas.h"
#include <stdlib.h>

Musica *avancarMusica(Playlist *playlist)
{
    if (!playlist || !playlist->atual || !playlist->atual->proximo) {
        return NULL;
    }
    playlist->atual = playlist->atual->proximo;
    return playlist->atual;
}

Musica *retrocederMusica(Playlist *playlist)
{
    if (!playlist || !playlist->atual || !playlist->atual->anterior) {
        return NULL;
    }
    playlist->atual = playlist->atual->anterior;
    return playlist->atual;
}

Musica *consultarAtual(Playlist *playlist)
{
    if (!playlist) {
        return NULL;
    }
    return playlist->atual;
}