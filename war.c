/*
    DESAFIO WAR ESTRUTURADO - CONQUISTA DE TERRITÓRIO
    Disciplina: Programação Estruturada - Estácio
    Linguagem: C
    Nível: Novato
    Autor: Exemplo educativo para estudo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 6
#define QTD_JOGADORES 2
#define REFORCOS_POR_TURNO 3

typedef struct {
    char nome[20];
    int dono;      // 1 = jogador 1, 2 = jogador 2
    int exercitos;
} Territorio;

// ==== Protótipos das funções ====
void inicializarTerritorios(Territorio t[]);
void distribuirTerritorios(Territorio t[]);
void mostrarMapa(Territorio t[]);
void turnoJogador(Territorio t[], int jogador);
void reforcar(Territorio t[], int jogador);
void atacar(Territorio t[], int jogador);
int verificaVencedor(Territorio t[]);
int escolherTerritorio(const char *msg, int min, int max);
void limparTela();

int main() {
    Territorio territorios[QTD_TERRITORIOS];
    int vencedor = 0;
    int jogadorAtual = 1;

    srand(time(NULL));

    inicializarTerritorios(territorios);
    distribuirTerritorios(territorios);

    printf("=== DESAFIO WAR ESTRUTURADO - CONQUISTA DE TERRITÓRIO ===\n");
    mostrarMapa(territorios);

    while ((vencedor = verificaVencedor(territorios)) == 0) {
        printf("\n---- TURNO DO JOGADOR %d ----\n", jogadorAtual);
        turnoJogador(territorios, jogadorAtual);
        mostrarMapa(territorio
