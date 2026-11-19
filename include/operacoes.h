#ifndef OPERACOES_H
#define OPERACOES_H
#include "musicas.h"
#include "playlist.h"
// TODO: Criar definicao das funcoes das operacoes principais

//status de navegação:
typedef enum {
    NAV_OK = 0,
    NAV_PLAYLIST_INVALIDA = 1,
    NAV_PLAYLIST_VAZIA = 2,
    NAV_FIM_LISTA = 3
} NavegacaoStatus;


//menu
void exibirMenu(Playlist *playlist);

int inserirMusica(Playlist *playlist, const char *nome, const char *artista, int duracao);
int removerMusica(Playlist *playlist, const char *nome);
NavegacaoStatus avancarMusica(Playlist *playlist, Musica **out_musica);
NavegacaoStatus retrocederMusica(Playlist *playlist, Musica **out_musica);
NavegacaoStatus consultarAtual(Playlist *playlist, Musica **out_musica);
#endif