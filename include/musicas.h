
#ifndef MUSICAS_H
#define MUSICAS_H

typedef struct Musica {
    char nome[100];
    char artista[100];
    int duracao;

    struct Musica *anterior;
    struct Musica *proximo;
} Musica;

#endif
