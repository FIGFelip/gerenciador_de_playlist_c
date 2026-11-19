#include "operacoes.h"
#include "playlist.h"
#include "musicas.h"
#include <stdlib.h>
#include <assert.h>

NavegacaoStatus avancarMusica(Playlist *playlist, Musica **out_musica) {
    if (out_musica) {
        *out_musica = NULL;
    }
    if (!playlist) {
        return NAV_PLAYLIST_INVALIDA;
    }
    if (!playlist->atual) {
        return NAV_PLAYLIST_VAZIA;
    }
    if (!playlist->atual->proximo) {
        return NAV_FIM_LISTA;
    }
    //verificando integridade da playlist
    assert(playlist->atual->proximo->anterior == playlist->atual);

    playlist->atual = playlist->atual->proximo;

    if (out_musica) {
        *out_musica = playlist->atual;
    }

    return NAV_OK;
}


NavegacaoStatus retrocederMusica( Playlist *playlist, Musica **out_musica) {
    if (out_musica) {
        *out_musica = NULL;
    }

    if (!playlist) {
        return NAV_PLAYLIST_INVALIDA;
    }

    if (!playlist->atual) {
        return NAV_PLAYLIST_VAZIA;
    }

    if (!playlist->atual->anterior) {
        return NAV_FIM_LISTA;
    }

    //integridade da playlist
    assert(playlist->atual->anterior->proximo == playlist->atual);

    playlist->atual = playlist->atual->anterior;

    if (out_musica) {
        *out_musica = playlist->atual;
    }

    return NAV_OK;
}

NavegacaoStatus consultarAtual(Playlist *playlist, Musica **out_musica) {
    if (out_musica) {
        *out_musica = NULL;
    }

    if (!playlist) {
        return NAV_PLAYLIST_INVALIDA;
    }

    if (!playlist->atual) {
        return NAV_PLAYLIST_VAZIA;
    }

    if (out_musica) {
        *out_musica = playlist->atual;
    }

    return NAV_OK;
}