
#include "operacoes.h"
#include "playlist.h"
#include <stdlib.h>
#include <string.h>

RemocaoStatus removerMusica(Playlist *playlist, const char *nome) {

    // Valida os parâmetros
    if (playlist == NULL) {
        return REMOCAO_PLAYLIST_INVALIDA;
    }
    
    // Abaixo serve para impedir input com nome vazio
    if (nome == NULL || nome[0] == '\0') {
        return REMOCAO_NOME_INVALIDO;
    }

    // Verifica playlist vazia
    if (playlist->inicio == NULL) {
        return REMOCAO_PLAYLIST_VAZIA;
    }

    //Identifica a música a remover
    Musica *alvo = playlist->inicio;

    while (alvo != NULL && strcmp(alvo->nome, nome) != 0) {
        alvo = alvo->proximo;
    }

    if (alvo == NULL) {
        return REMOCAO_MUSICA_NAO_ENCONTRADA;
    }

    //Atualiza a música atual, se preciso
    if (playlist->atual == alvo) {

        if (alvo->proximo != NULL) {
            playlist->atual = alvo->proximo;
        }
        else {
            playlist->atual = alvo->anterior;
        }
    }

    // Reconecta os nós
    if (alvo->anterior != NULL) {
        alvo->anterior->proximo = alvo->proximo;
    }
    else {
        playlist->inicio = alvo->proximo;
    }

    if (alvo->proximo != NULL) {
        alvo->proximo->anterior = alvo->anterior;
    }
    else {
        playlist->fim = alvo->anterior;
    }

    // libera memoria e atualiza o tamanho
    free(alvo);
    playlist->tamanho--;

    return REMOCAO_OK;
}
