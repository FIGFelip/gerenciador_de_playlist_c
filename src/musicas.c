#include "musicas.h"
#include <stdlib.h>
#include <string.h>

// Esta é uma implementação simples de helper para alocação de música
// Na implementação real, as operações são incorporadas no inserir.c e remover.c

void inicializarMusica(Musica *musica, const char *nome, const char *artista, int duracao) {
    if (!musica || !nome || !artista) return;
    
    strncpy(musica->nome, nome, TAM_NOME - 1);
    musica->nome[TAM_NOME - 1] = '\0';
    
    strncpy(musica->artista, artista, TAM_ARTISTA - 1);
    musica->artista[TAM_ARTISTA - 1] = '\0';
    
    musica->duracao = duracao;
    musica->anterior = NULL;
    musica->proximo = NULL;
}