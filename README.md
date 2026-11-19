# gerenciador_de_playlist_c

Projeto desenvolvido em linguagem C para gerenciamento de playlists musicais, utilizando uma **lista duplamente encadeada** como estrutura de dados.

## Como rodar o código

```bash
make run
```

## Para limpar arquivos de output

```bash
make clean
```

## Executando testes

```bash
make -f Makefile.test run
```

## Limpando arquivos residuais de testes

```bash
make -f Makefile.test clean
```

## Divisão de responsabilidades

| Integrante | Responsabilidades |
|---|---|
| **Felipe Santana (líder)** | Arquitetura do projeto (estrutura de diretórios e arquivos, declaração das funções e seus parâmetros); implementação do menu funcional; revisão, refatoração e integração das funcionalidades. |
| **Rian Alves** | Estrutura de dados de `Playlist` e `Musica`; funções de inicialização e destruição da playlist. |
| **Maria Eduarda** | Implementação da funcionalidade de inserção de músicas. |
| **Nicolas Santos** | Implementação da funcionalidade de remoção de músicas. |
| **Allan Minori** | Implementação das funcionalidades de navegação: avançar, retroceder e consultar a música atual. |
| **Wilson Brito** | Elaboração da documentação e apoio nas decisões do projeto. |
| **Raian Luz** | Elaboração da documentação e apoio nas decisões do projeto.  |