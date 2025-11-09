/*
    DESAFIO ESTRUTURADO - TEMA 2: FREE FIRE
    Disciplina: Programação Estruturada - Estácio
    Linguagem: C
    Nível: Novato
    Autor: Exemplo Educacional - ChatGPT (modelo de referência)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_JOGADORES 5

// Estrutura que representa um jogador
typedef struct {
    char nome[30];
    int vida;
    int dano;
    int ativo; // 1 = vivo, 0 = eliminado
} Jogador;

// ======= PROTÓTIPOS =======
void menu();
void cadastrarJogadores(Jogador j[], int *qtd);
void mostrarJogadores(Jogador j[], int qtd);
void simularPartida(Jogador j[], int qtd);
int vivosRestantes(Jogador j[], int qtd);
void limparTela();

// ======= FUNÇÃO PRINCIPAL =======
int main() {
    Jogador jogadores[MAX_JOGADORES];
    int qtd = 0;
    int opcao;

    srand(time(NULL));

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                cadastrarJogadores(jogadores, &qtd);
                break;
            case 2:
                mostrarJogadores(jogadores, qtd);
                break;
            case 3:
                simularPartida(jogadores, qtd);
                break;
            case 0:
                printf("\nEncerrando o jogo... Obrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ======= FUNÇÕES =======

void menu() {
    printf("\n==============================\n");
    printf("     FREE FIRE - ESTÁCIO\n");
    printf("==============================\n");
    printf("[1] Cadastrar jogadores\n");
    printf("[2] Mostrar jogadores\n");
    printf("[3] Simular partida\n");
    printf("[0] Sair\n");
    printf("==============================\n");
}

void cadastrarJogadores(Jogador j[], int *qtd) {
    if (*qtd >= MAX_JOGADORES) {
        printf("Limite máximo de jogadores atingido (%d)\n", MAX_JOGADORES);
        return;
    }

    printf("Quantos jogadores deseja cadastrar (1 a %d)? ", MAX_JOGADORES);
    int n;
    scanf("%d", &n);
    getchar();

    if (n < 1 || n > MAX_JOGADORES) {
        printf("Quantidade inválida.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\nNome do jogador %d: ", *qtd + 1);
        fgets(j[*qtd].nome, 30, stdin);
        j[*qtd].nome[strcspn(j[*qtd].nome, "\n")] = '\0'; // remove \n
        j[*qtd].vida = 100;
        j[*qtd].dano = (rand() % 20) + 10; // dano aleatório entre 10 e 30
        j[*qtd].ativo = 1;
        (*qtd)++;
    }

    printf("\n✅ Jogadores cadastrados com sucesso!\n");
}

void mostrarJogadores(Jogador j[], int qtd) {
    if (qtd == 0) {
        printf("Nenhum jogador cadastrado.\n");
        return;
    }

    printf("\n===== LISTA DE JOGADORES =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %-15s | Vida: %3d | Dano: %2d | %s\n",
               i + 1, j[i].nome, j[i].vida, j[i].dano,
               j[i].ativo ? "Ativo" : "Eliminado");
    }
}

void simularPartida(Jogador j[], int qtd) {
    if (qtd < 2) {
        printf("Cadastre pelo menos 2 jogadores para iniciar a partida!\n");
        return;
    }

    printf("\n🔥 Iniciando partida com %d jogadores...\n", qtd);
    int rodada = 1;

    while (vivosRestantes(j, qtd) > 1) {
        printf("\n===== RODADA %d =====\n", rodada);

        int atacante = rand() % qtd;
        int alvo = rand() % qtd;

        // garantir que o atacante e o alvo sejam diferentes e ativos
        while (alvo == atacante || j[alvo].ativo == 0 || j[atacante].ativo == 0) {
            atacante = rand() % qtd;
            alvo = rand() % qtd;
        }

        printf("%s atacou %s causando %d de dano!\n",
               j[atacante].nome, j[alvo].nome, j[atacante].dano);

        j[alvo].vida -= j[atacante].dano;

        if (j[alvo].vida <= 0) {
            j[alvo].ativo = 0;
            j[alvo].vida = 0;
            printf("💀 %s foi eliminado!\n", j[alvo].nome);
        }

        rodada++;
    }

    // encontrar o vencedor
    for (int i = 0; i < qtd; i++) {
        if (j[i].ativo == 1) {
            printf("\n🏆 O vencedor foi: %s com %d de vida restante!\n", j[i].nome, j[i].vida);
            break;
        }
    }
}

int vivosRestantes(Jogador j[], int qtd) {
    int cont = 0;
    for (int i = 0; i < qtd; i++) {
        if (j[i].ativo == 1) cont++;
    }
    return cont;
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
