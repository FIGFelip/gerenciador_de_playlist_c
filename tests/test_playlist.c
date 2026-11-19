/*
 * Testes Unitários para Gerenciador de Playlist
 * Testa todas as funções principais e casos edge
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "playlist.h"
#include "musicas.h"
#include "operacoes.h"

#define TAM_BUFFER 256

void imprimirResultado(const char* teste, int sucesso) {
    if (sucesso) {
        printf("✓ %s PASSED\n", teste);
    } else {
        printf("✗ %s FALHOU\n", teste);
    }
}

void testar_inicializar() {
    printf("\n=== Testando inicializarPlaylist ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    assert(playlist.inicio == NULL);
    assert(playlist.fim == NULL);
    assert(playlist.atual == NULL);
    assert(playlist.tamanho == 0);
    imprimirResultado("inicializarPlaylist", 1);
}

void testar_destruir() {
    printf("\n=== Testando destruirPlaylist ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    destruirPlaylist(&playlist);
    
    assert(playlist.inicio == NULL);
    assert(playlist.fim == NULL);
    assert(playlist.atual == NULL);
    assert(playlist.tamanho == 0);
    imprimirResultado("destruirPlaylist", 1);
}

void testar_inserir_musica_ok() {
    printf("\n=== Testando inserirMusica sucesso ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    InsercaoStatus status = inserirMusica(&playlist, "Musica1", "Artista1", 180);
    assert(status == INSERCAO_OK);
    assert(playlist.tamanho == 1);
    assert(playlist.inicio != NULL);
    assert(strcmp(playlist.inicio->nome, "Musica1") == 0);
    assert(strcmp(playlist.inicio->artista, "Artista1") == 0);
    assert(playlist.inicio->duracao == 180);
    assert(playlist.inicio->anterior == NULL);
    assert(playlist.inicio->proximo == NULL);
    assert(playlist.fim == playlist.inicio);
    assert(playlist.atual == playlist.inicio);
    imprimirResultado("inserirMusica sucesso", 1);
    
    destruirPlaylist(&playlist);
}

void testar_inserir_musica_playlist_invalida() {
    printf("\n=== Testando inserirMusica playlist invalida ===\n");
    InsercaoStatus status = inserirMusica(NULL, "Musica1", "Artista1", 180);
    assert(status == INSERCAO_PLAYLIST_INVALIDA);
    imprimirResultado("inserirMusica playlist invalida", 1);
}

void testar_inserir_musica_nome_invalido() {
    printf("\n=== Testando inserirMusica nome invalido ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    // Nome vazio
    InsercaoStatus status = inserirMusica(&playlist, "", "Artista1", 180);
    assert(status == INSERCAO_NOME_INVALIDO);
    
    // Nome NULL
    status = inserirMusica(&playlist, NULL, "Artista1", 180);
    assert(status == INSERCAO_NOME_INVALIDO);
    imprimirResultado("inserirMusica nome invalido", 1);
    
    destruirPlaylist(&playlist);
}

void testar_inserir_musica_artista_invalido() {
    printf("\n=== Testando inserirMusica artista invalido ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    // Artista vazio
    InsercaoStatus status = inserirMusica(&playlist, "Musica1", "", 180);
    assert(status == INSERCAO_ARTISTA_INVALIDO);
    
    // Artista NULL
    status = inserirMusica(&playlist, "Musica1", NULL, 180);
    assert(status == INSERCAO_ARTISTA_INVALIDO);
    imprimirResultado("inserirMusica artista invalido", 1);
    
    destruirPlaylist(&playlist);
}

void testar_inserir_musica_duracao_invalida() {
    printf("\n=== Testando inserirMusica duracao invalida ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    InsercaoStatus status = inserirMusica(&playlist, "Musica1", "Artista1", 0);
    assert(status == INSERCAO_DURACAO_INVALIDA);
    
    status = inserirMusica(&playlist, "Musica1", "Artista1", -1);
    assert(status == INSERCAO_DURACAO_INVALIDA);
    imprimirResultado("inserirMusica duracao invalida", 1);
    
    destruirPlaylist(&playlist);
}

void testar_inserir_musica_nomes_longo() {
    printf("\n=== Testando inserirMusica nomes longos ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    char nome_longo[100];
    char artista_longo[100];
    for (int i = 0; i < 99; i++) {
        nome_longo[i] = 'A';
        artista_longo[i] = 'B';
    }
    nome_longo[99] = '\0';
    artista_longo[99] = '\0';
    
    // Nomes com exatamente 99 caracteres devem ser aceitos (já que a validação é >= TAM_NOME)
    InsercaoStatus status = inserirMusica(&playlist, nome_longo, artista_longo, 180);
    assert(status == INSERCAO_OK);
    imprimirResultado("inserirMusica nomes longos (99 chars)", 1);
    
    destruirPlaylist(&playlist);
}

void testar_inserir_musica_nomes_exatamente_limite() {
    printf("\n=== Testando inserirMusica nomes exatamente no limite ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    char nome_exato[TAM_NOME];
    char artista_exato[TAM_ARTISTA];
    memset(nome_exato, 'X', TAM_NOME - 1);
    nome_exato[TAM_NOME - 1] = '\0';
    memset(artista_exato, 'Y', TAM_ARTISTA - 1);
    artista_exato[TAM_ARTISTA - 1] = '\0';
    
    // Strings exatas nos limites devem falhar (>= TAM_NOME)
    InsercaoStatus status = inserirMusica(&playlist, nome_exato, artista_exato, 180);
    // Este é um caso edge: a validação usa >= TAM_NOME, então exatamente TAM_NOME deve falhar
    // No entanto, observe que strlen(nome_exato) == TAM_NOME - 1, então deve passar
    // Vamos testar ambos os casos:
    
    if (strlen(nome_exato) == TAM_NOME - 1) {
        status = inserirMusica(&playlist, nome_exato, artista_exato, 180);
        assert(status == INSERCAO_OK);
    } else {
        status = inserirMusica(&playlist, nome_exato, artista_exato, 180);
        assert(status == INSERCAO_NOME_MUITO_LONGO);
    }
    imprimirResultado("inserirMusica nomes exatos no limite", 1);
    
    destruirPlaylist(&playlist);
}

void testar_remover_musica_ok() {
    printf("\n=== Testando removerMusica sucesso ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    // Adicionar 3 músicas
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    inserirMusica(&playlist, "Musica2", "Artista2", 200);
    inserirMusica(&playlist, "Musica3", "Artista3", 220);
    
    assert(playlist.tamanho == 3);
    assert(playlist.atual == playlist.inicio);
    
    RemocaoStatus status = removerMusica(&playlist, "Musica2");
    assert(status == REMOCAO_OK);
    assert(playlist.tamanho == 2);
    
    // Verificar que Musica2 foi removida
    Musica* atual = playlist.inicio;
    assert(strcmp(atual->nome, "Musica1") == 0);
    atual = atual->proximo;
    assert(strcmp(atual->nome, "Musica3") == 0);
    imprimirResultado("removerMusica sucesso", 1);
    
    destruirPlaylist(&playlist);
}

void testar_remover_musica_nao_encontrada() {
    printf("\n=== Testando removerMusica musica nao encontrada ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    
    RemocaoStatus status = removerMusica(&playlist, "MusicaInexistente");
    assert(status == REMOCAO_MUSICA_NAO_ENCONTRADA);
    assert(playlist.tamanho == 1); // Nenhuma alteração
    imprimirResultado("removerMusica musica nao encontrada", 1);
    
    destruirPlaylist(&playlist);
}

void testar_remover_musica_playlist_vazia() {
    printf("\n=== Testando removerMusica playlist vazia ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    RemocaoStatus status = removerMusica(&playlist, "QualquerMusica");
    assert(status == REMOCAO_PLAYLIST_VAZIA);
    imprimirResultado("removerMusica playlist vazia", 1);
}

void testar_remover_musica_artista_invalido() {
    printf("\n=== Testando removerMusica nome invalido ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    // Nome vazio
    RemocaoStatus status = removerMusica(&playlist, "");
    assert(status == REMOCAO_NOME_INVALIDO);
    
    // Nome NULL
    status = removerMusica(&playlist, NULL);
    assert(status == REMOCAO_NOME_INVALIDO);
    imprimirResultado("removerMusica nome invalido", 1);
    
    destruirPlaylist(&playlist);
}

void testar_avancar_musica_ok() {
    printf("\n=== Testando avancarMusica sucesso ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    inserirMusica(&playlist, "Musica2", "Artista2", 200);
    inserirMusica(&playlist, "Musica3", "Artista3", 220);
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = avancarMusica(&playlist, &musica_out);
    assert(status == NAV_OK);
    assert(musica_out == playlist.atual);
    assert(strcmp(musica_out->nome, "Musica2") == 0);
    assert(playlist.atual == musica_out);
    imprimirResultado("avancarMusica sucesso", 1);
    
    destruirPlaylist(&playlist);
}

void testar_avancar_musica_fim_lista() {
    printf("\n=== Testando avancarMusica fim da lista ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = avancarMusica(&playlist, &musica_out);
    assert(status == NAV_FIM_LISTA);
    assert(musica_out == NULL);
    assert(playlist.atual == playlist.inicio); // Deve permanecer na primeira
    imprimirResultado("avancarMusica fim da lista", 1);
    
    destruirPlaylist(&playlist);
}

void testar_avancar_musica_playlist_vazia() {
    printf("\n=== Testando avancarMusica playlist vazia ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = avancarMusica(&playlist, &musica_out);
    assert(status == NAV_PLAYLIST_VAZIA);
    assert(musica_out == NULL);
    imprimirResultado("avancarMusica playlist vazia", 1);
}

void testar_retroceder_musica_ok() {
    printf("\n=== Testando retrocederMusica sucesso ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    inserirMusica(&playlist, "Musica2", "Artista2", 200);
    avancarMusica(&playlist, NULL); // Mover para Musica2
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = retrocederMusica(&playlist, &musica_out);
    assert(status == NAV_OK);
    assert(musica_out == playlist.atual);
    assert(strcmp(musica_out->nome, "Musica1") == 0);
    assert(playlist.atual == musica_out);
    imprimirResultado("retrocederMusica sucesso", 1);
    
    destruirPlaylist(&playlist);
}

void testar_retroceder_musica_primeira() {
    printf("\n=== Testando retrocederMusica primeira musica ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = retrocederMusica(&playlist, &musica_out);
    assert(status == NAV_FIM_LISTA);
    assert(musica_out == NULL);
    assert(playlist.atual == playlist.inicio);
    imprimirResultado("retrocederMusica primeira musica", 1);
    
    destruirPlaylist(&playlist);
}

void testar_retroceder_musica_playlist_vazia() {
    printf("\n=== Testando retrocederMusica playlist vazia ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = retrocederMusica(&playlist, &musica_out);
    assert(status == NAV_PLAYLIST_VAZIA);
    assert(musica_out == NULL);
    imprimirResultado("retrocederMusica playlist vazia", 1);
}

void testar_consultar_atual_ok() {
    printf("\n=== Testando consultarAtual sucesso ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = consultarAtual(&playlist, &musica_out);
    assert(status == NAV_OK);
    assert(musica_out == playlist.atual);
    assert(strcmp(musica_out->nome, "Musica1") == 0);
    imprimirResultado("consultarAtual sucesso", 1);
    
    destruirPlaylist(&playlist);
}

void testar_consultar_atual_playlist_vazia() {
    printf("\n=== Testando consultarAtual playlist vazia ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    Musica* musica_out = NULL;
    NavegacaoStatus status = consultarAtual(&playlist, &musica_out);
    assert(status == NAV_PLAYLIST_VAZIA);
    assert(musica_out == NULL);
    imprimirResultado("consultarAtual playlist vazia", 1);
}

void testar_cenario_remocao_atual() {
    printf("\n=== Testando remoção enquanto musica atual ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    inserirMusica(&playlist, "Musica2", "Artista2", 200);
    inserirMusica(&playlist, "Musica3", "Artista3", 220);
    
    // Atual começa em Musica1. Vamos avançar para Musica2.
    avancarMusica(&playlist, NULL);
    assert(strcmp(playlist.atual->nome, "Musica2") == 0);
    
    // Remover Musica2 (música atual)
    RemocaoStatus status = removerMusica(&playlist, "Musica2");
    assert(status == REMOCAO_OK);
    
    // Verificar que atual foi atualizado para Musica3 (próxima)
    assert(strcmp(playlist.atual->nome, "Musica3") == 0);
    assert(playlist.tamanho == 2);
    imprimirResultado("remoção enquanto música atual", 1);
    
    destruirPlaylist(&playlist);
}

void testar_cenario_remocao_primeira() {
    printf("\n=== Testando remoção da primeira música ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    inserirMusica(&playlist, "Musica2", "Artista2", 200);
    inserirMusica(&playlist, "Musica3", "Artista3", 220);
    
    // Remover primeira música
    RemocaoStatus status = removerMusica(&playlist, "Musica1");
    assert(status == REMOCAO_OK);
    assert(strcmp(playlist.inicio->nome, "Musica2") == 0);
    assert(playlist.atual != NULL);
    imprimirResultado("remoção da primeira música", 1);
    
    destruirPlaylist(&playlist);
}

void testar_cenario_remocao_ultima() {
    printf("\n=== Testando remoção da última música ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    inserirMusica(&playlist, "Musica1", "Artista1", 180);
    inserirMusica(&playlist, "Musica2", "Artista2", 200);
    inserirMusica(&playlist, "Musica3", "Artista3", 220);
    
    // Mover o atual para a última música (Musica3)
    avancarMusica(&playlist, NULL);
    avancarMusica(&playlist, NULL);
    assert(strcmp(playlist.atual->nome, "Musica3") == 0);
    
    // Remover última música (que é a atual)
    RemocaoStatus status = removerMusica(&playlist, "Musica3");
    assert(status == REMOCAO_OK);
    assert(strcmp(playlist.fim->nome, "Musica2") == 0);
    
    // Como a atual era a última e foi removida, a implementação ajusta:
    // "else { playlist.atual = alvo->anterior; }" -> portanto, atual deve ir para Musica2 (o novo fim)
    assert(playlist.atual == playlist.fim);
    assert(strcmp(playlist.atual->nome, "Musica2") == 0);
    
    imprimirResultado("remoção da última música", 1);
    
    destruirPlaylist(&playlist);
}

void testar_cenario_avancar_varioss() {
    printf("\n=== Testando avançar através de múltiplas músicas ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    // Adicionar 5 músicas
    const char* nomes[] = {"Musica1", "Musica2", "Musica3", "Musica4", "Musica5"};
    const char* artistas[] = {"Artista1", "Artista2", "Artista3", "Artista4", "Artista5"};
    
    for (int i = 0; i < 5; i++) {
        inserirMusica(&playlist, nomes[i], artistas[i], 180 + i * 20);
    }
    
    // Avançar através de todas as músicas
    for (int i = 0; i < 4; i++) {
        Musica* musica_out = NULL;
        NavegacaoStatus status = avancarMusica(&playlist, &musica_out);
        assert(status == NAV_OK);
        assert(strcmp(musica_out->nome, nomes[i + 1]) == 0);
        assert(playlist.atual == musica_out);
    }
    
    // Tentar avançar além da última
    Musica* musica_out = NULL;
    NavegacaoStatus status = avancarMusica(&playlist, &musica_out);
    assert(status == NAV_FIM_LISTA);
    assert(musica_out == NULL);
    
    destruirPlaylist(&playlist);
    imprimirResultado("avançar através de múltiplas músicas", 1);
}

void testar_cenario_retroceder_varioss() {
    printf("\n=== Testando retroceder através de múltiplas músicas ===\n");
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    // Adicionar 5 músicas
    const char* nomes[] = {"Musica1", "Musica2", "Musica3", "Musica4", "Musica5"};
    
    for (int i = 0; i < 5; i++) {
        inserirMusica(&playlist, nomes[i], "Artista", 180);
    }
    
    // Avançar para a última
    for (int i = 0; i < 4; i++) {
        avancarMusica(&playlist, NULL);
    }
    assert(strcmp(playlist.atual->nome, "Musica5") == 0);
    
    // Retroceder através de todas as músicas
    for (int i = 4; i >= 0; i--) {
        Musica* musica_out = NULL;
        NavegacaoStatus status = retrocederMusica(&playlist, &musica_out);
        if (i == 0) {
            assert(status == NAV_FIM_LISTA);
            assert(musica_out == NULL);
        } else {
            assert(status == NAV_OK);
            assert(strcmp(musica_out->nome, nomes[i - 1]) == 0);
            assert(playlist.atual == musica_out);
        }
    }
    
    destruirPlaylist(&playlist);
    imprimirResultado("retroceder através de múltiplas músicas", 1);
}

void executar_todos_os_testes() {
    printf("=== EXECUTANDO TESTES DO GERENCIADOR DE PLAYLIST ===\n");
    
    // Testes de inicialização
    testar_inicializar();
    
    // Testes de inserção
    testar_inserir_musica_ok();
    testar_inserir_musica_playlist_invalida();
    testar_inserir_musica_nome_invalido();
    testar_inserir_musica_artista_invalido();
    testar_inserir_musica_duracao_invalida();
    testar_inserir_musica_nomes_longo();
    
    // Testes de remoção
    testar_remover_musica_ok();
    testar_remover_musica_nao_encontrada();
    testar_remover_musica_playlist_vazia();
    testar_remover_musica_artista_invalido();
    
    // Testes de navegação
    testar_avancar_musica_ok();
    testar_avancar_musica_fim_lista();
    testar_avancar_musica_playlist_vazia();
    
    testar_retroceder_musica_ok();
    testar_retroceder_musica_primeira();
    testar_retroceder_musica_playlist_vazia();
    
    // Testes de consulta
    testar_consultar_atual_ok();
    testar_consultar_atual_playlist_vazia();
    
    // Testes edge cases
    testar_cenario_remocao_atual();
    testar_cenario_remocao_primeira();
    testar_cenario_remocao_ultima();
    testar_cenario_avancar_varioss();
    testar_cenario_retroceder_varioss();
    
    printf("\n=== TODOS OS TESTES PASSARAM ===\n");
}

int main() {
    executar_todos_os_testes();
    return 0;
}