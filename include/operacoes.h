#ifndef OPERACOES_H
#define OPERACOES_H
#include "musicas.h"
#include "playlist.h"
// TODO: Criar definicao das funcoes das operacoes principais

//menu

void exibirMenu(Playlist *playlist);
int inserirMusica(Playlist *playlist, const char *nome, const char *artista, int duracao);
int removerMusica(Playlist *playlist, const char *nome);
Musica* avancarMusica(Playlist *playlist);
Musica* retrocederMusica(Playlist *playlist);
Musica* consultarAtual(Playlist *playlist);
#endif