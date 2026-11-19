
#ifndef MUSICAS_H
#define MUSICAS_H
#define TAM_NOME 100
#define TAM_ARTISTA 100
typedef struct Musica {
    char nome[TAM_NOME];
    char artista[TAM_ARTISTA];
    int duracao;

    struct Musica *anterior;
    struct Musica *proximo;
} Musica;

#endif
