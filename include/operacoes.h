#ifndef OPERACOES_H
#define OPERACOES_H
#include "musicas.h"
#include "playlist.h"

//enumerators para melhor leitura
// do retorno das funções

//status da inserção
typedef enum {
    INSERCAO_OK,
    INSERCAO_PLAYLIST_INVALIDA,
    INSERCAO_NOME_INVALIDO,
    INSERCAO_ARTISTA_INVALIDO,
    INSERCAO_DURACAO_INVALIDA,
    INSERCAO_NOME_MUITO_LONGO,
    INSERCAO_ARTISTA_MUITO_LONGO,
    INSERCAO_FALHA_ALOCACAO
} InsercaoStatus;
//status da remocao
typedef enum {
    REMOCAO_OK,
    REMOCAO_PLAYLIST_INVALIDA,
    REMOCAO_NOME_INVALIDO,
    REMOCAO_PLAYLIST_VAZIA,
    REMOCAO_MUSICA_NAO_ENCONTRADA
} RemocaoStatus;

//status da navegação
typedef enum {
    NAV_OK = 0,
    NAV_PLAYLIST_INVALIDA = 1,
    NAV_PLAYLIST_VAZIA = 2,
    NAV_FIM_LISTA = 3
} NavegacaoStatus;


//menu
void exibirMenu(Playlist *playlist);


//funcoes principais
InsercaoStatus inserirMusica(Playlist *playlist, const char *nome, const char *artista, int duracao);
RemocaoStatus removerMusica(Playlist *playlist, const char *nome);
NavegacaoStatus avancarMusica(Playlist *playlist, Musica **out_musica);
NavegacaoStatus retrocederMusica(Playlist *playlist, Musica **out_musica);
NavegacaoStatus consultarAtual(Playlist *playlist, Musica **out_musica);
#endif