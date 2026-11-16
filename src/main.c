#include <stdio.h>
#include "../include/operacoes.h"

int main(){
    Playlist minhaPlaylist;
    inicializarPlaylist(&minhaPlaylist);
    exibirMenu(&minhaPlaylist);
    destruirPlaylist(&minhaPlaylist);
    return 0;
}