/*
    DESAFIO ESTRUTURADO - TEMA 3: TETRIS STACK
    Disciplina: Programação Estruturada - Estácio
    Linguagem: C
    Nível: Novato
    Autor: Exemplo Educacional (ChatGPT)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 10
#define COLUNAS 7

// ===== PROTÓTIPOS =====
void inicializarCampo(int campo[LINHAS][COLUNAS]);
void mostrarCampo(int campo[LINHAS][COLUNAS]);
void soltarBloco(int campo[LINHAS][COLUNAS]);
int removerLinhasCompletas(int campo[LINHAS][COLUNAS]);
int campoCheio(int campo[LINHAS][COLUNAS]);
void limparTela();

// ===== FUNÇÃO PRINCIPAL =====
int main() {
    int campo[LINHAS][COLUNAS];
    int pontuacao = 0;
    int rodada = 1;

    srand(time(NULL));
    inicializarCampo(campo);

    printf("=== DESAFIO ESTRUTURADO - TETRIS STACK (TEMA 3) ===\n");

    while (!campoCheio(campo)) {
        printf("\n--- Rodada %d ---\n", rodada);
        soltarBloco(campo);
        mostrarCampo(campo);
        int linhasRemovidas = removerLinhasCompletas(campo);
        if (linhasRemovidas > 0) {
            pontuacao += linhasRemovidas * 100;
            printf("\n💥 Linha completa! +%d pontos!\n", linhasRemovidas * 100);
        }
        printf("Pontuação atual: %d\n", pontuacao);
        rodada++;
    }

    printf("\n🧱 O campo encheu! Fim de jogo.\n");
    printf("🏆 Pontuação final: %d\n", pontuacao);
    return 0;
}

// ===== FUNÇÕES =====

// Preenche o campo com zeros (vazio)
void inicializarCampo(int campo[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            campo[i][j] = 0;
        }
    }
}

// Exibe o campo de jogo
void mostrarCampo(int campo[LINHAS][COLUNAS]) {
    printf("\n");
    for (int i = 0; i < LINHAS; i++) {
        printf("| ");
        for (int j = 0; j < COLUNAS; j++) {
            if (campo[i][j] == 0)
                printf(". ");
            else
                printf("# ");
        }
        printf("|\n");
    }
    for (int j = 0; j < COLUNAS + 2; j++) printf("--");
    printf("\n");
}

// Simula a queda de um bloco em uma coluna aleatória
void soltarBloco(int campo[LINHAS][COLUNAS]) {
    int coluna = rand() % COLUNAS;
    printf("Bloco caindo na coluna %d...\n", coluna + 1);

    // o bloco cai até encontrar uma posição ocupada
    for (int i = LINHAS - 1; i >= 0; i--) {
        if (campo[i][coluna] == 0) {
            campo[i][coluna] = 1; // bloco fixado
            return;
        }
    }
    // se chegar aqui, a coluna está cheia (bloco perdido)
    printf("⚠️  Coluna cheia! Bloco perdido.\n");
}

// Remove linhas completamente cheias e retorna quantas foram removidas
int removerLinhasCompletas(int campo[LINHAS][COLUNAS]) {
    int removidas = 0;

    for (int i = LINHAS - 1; i >= 0; i--) {
        int completa = 1;
        for (int j = 0; j < COLUNAS; j++) {
            if (campo[i][j] == 0) {
                completa = 0;
                break;
            }
        }

        if (completa) {
            removidas++;
            // desce as linhas acima
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < COLUNAS; j++) {
                    campo[k][j] = campo[k - 1][j];
                }
            }
            // limpa a primeira linha
            for (int j = 0; j < COLUNAS; j++) {
                campo[0][j] = 0;
            }
            i++; // reavaliar linha após deslocamento
        }
    }
    return removidas;
}

// Verifica se o campo está cheio (linha superior ocupada)
int campoCheio(int campo[LINHAS][COLUNAS]) {
    for (int j = 0; j < COLUNAS; j++) {
        if (campo[0][j] != 0)
            return 1;
    }
    return 0;
}

// Limpa tela (opcional)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
