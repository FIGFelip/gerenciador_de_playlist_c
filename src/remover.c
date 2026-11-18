#include "operacoes.h"
#include "playlist.h"
#include <stdlib.h>
#include <string.h>


int removerMusica(Playlist *playlist, const char *nome){

    if (playlist == NULL || nome == NULL){
        return 0;
    }

    //1. Identificar a música que será removida
    Musica *alvo = playlist->inicio;
    while (alvo !=NULL && strcmp(alvo->nome, nome) != 0)
    {
        alvo = alvo -> proximo;
    }
    if(alvo == NULL){
        return 0; // Música não encontrada
    }   

    if(playlist->atual == alvo){

        if( alvo->proximo != NULL){
            playlist->atual = alvo->proximo;
            
        }
        else if(alvo->anterior != NULL){
            playlist->atual = alvo->anterior;
        } 
        
        else {
            playlist->atual = NULL;// A playlist está vazia
        }
    }
    //3. Alterar os ponteiros dos vizinhos
    if (alvo->anterior !=NULL){
        alvo->anterior->proximo = alvo->proximo;

    }
    else{
        playlist->inicio = alvo-> proximo;

    }

    if (alvo->proximo !=NULL){
        alvo->proximo->anterior = alvo->anterior;
    }
    else{
        playlist->fim = alvo->anterior;
    }
    //4. liberar a memória da música alvo

    free(alvo);
    playlist->tamanho--;


    return 1;


}
