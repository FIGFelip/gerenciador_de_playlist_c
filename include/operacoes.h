#ifndef OPERACOES_H
#define OPERACOES_H
#include "musicas.h"
#include "playlist.h"
// TODO: Criar definicao das funcoes das operacoes principais
typedef enum {
    REMOCAO_OK,
    REMOCAO_PLAYLIST_INVALIDA,
    REMOCAO_NOME_INVALIDO,
    REMOCAO_PLAYLIST_VAZIA,
    REMOCAO_MUSICA_NAO_ENCONTRADA
} RemocaoStatus;

//menu

void exibirMenu(Playlist *playlist);
int inserirMusica(Playlist *playlist, const char *nome, const char *artista, int duracao);
RemocaoStatus removerMusica(Playlist *playlist, const char *nome);
Musica* avancarMusica(Playlist *playlist);
Musica* retrocederMusica(Playlist *playlist);
Musica* consultarAtual(Playlist *playlist);
#endif