/*
    DESAFIO ESTRUTURADO - TEMA 4: DETECTIVE QUEST
    Disciplina: Programação Estruturada - Estácio
    Linguagem: C
    Nível: Novato
    Autor: Exemplo Educacional (ChatGPT)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===== CONSTANTES =====
#define QTD_SUSPEITOS 5

// ===== ESTRUTURA =====
typedef struct {
    char nome[30];
    char ocupacao[30];
    char pista[100];
} Suspeito;

// ===== PROTÓTIPOS =====
void menu();
void jogar();
void mostrarRegras();
int escolherOpcao(int min, int max);
void limparTela();

// ===== FUNÇÃO PRINCIPAL =====
int main() {
    int opcao;
    srand(time(NULL));

    do {
        menu();
        opcao = escolherOpcao(0, 2);

        switch (opcao) {
            case 1:
                jogar();
                break;
            case 2:
                mostrarRegras();
                break;
            case 0:
                printf("\n👋 Encerrando o jogo. Até logo, detetive!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

// ===== FUNÇÕES =====

void menu() {
    printf("\n=============================\n");
    printf("     🕵️ DETECTIVE QUEST\n");
    printf("=============================\n");
    printf("[1] Iniciar Investigação\n");
    printf("[2] Ver Regras\n");
    printf("[0] Sair\n");
    printf("=============================\n");
    printf("Escolha uma opção: ");
}

void mostrarRegras() {
    limparTela();
    printf("\n📜 REGRAS DO JOGO:\n");
    printf("1️⃣ Há 5 suspeitos, cada um com uma ocupação e um comportamento.\n");
    printf("2️⃣ O sistema escolhe um culpado aleatoriamente.\n");
    printf("3️⃣ Você pode interrogar os suspeitos e ler suas pistas.\n");
    printf("4️⃣ Depois de analisar, você deve fazer sua acusação final.\n");
    printf("5️⃣ Se acertar, vence o jogo! Caso contrário, o culpado foge...\n\n");
}

void jogar() {
    limparTela();

    Suspeito suspeitos[QTD_SUSPEITOS] = {
        {"Carlos",  "Mecânico",   "Tinha graxa nas mãos, mas parecia nervoso."},
        {"Marina",  "Chef",       "Disse que estava na cozinha, mas não havia cheiro de comida."},
        {"Paulo",   "Professor",  "Tinha um livro sobre venenos na mochila."},
        {"Fernanda","Médica",     "Estava de jaleco, porém sem crachá do hospital."},
        {"João",    "Artista",    "Foi visto perto da cena do crime com uma mochila pesada."}
    };

    int culpado = rand() % QTD_SUSPEITOS;
    int interrogatorio, tentativa;
    int chances = 2;

    printf("🔍 Bem-vindo, detetive! O crime ocorreu esta noite...\n");
    printf("Há %d suspeitos.\n", QTD_SUSPEITOS);

    for (int i = 0; i < QTD_SUSPEITOS; i++) {
        printf("%d - %s (%s)\n", i + 1, suspeitos[i].nome, suspeitos[i].ocupacao);
    }

    while (chances > 0) {
        printf("\nVocê tem %d interrogatório(s) restante(s).\n", chances);
        printf("Digite o número do suspeito que deseja interrogar: ");
        interrogatorio = escolherOpcao(1, QTD_SUSPEITOS);

        printf("\n🗣️ %s (%s) diz: \"%s\"\n",
               suspeitos[interrogatorio - 1].nome,
               suspeitos[interrogatorio - 1].ocupacao,
               suspeitos[interrogatorio - 1].pista);

        chances--;
    }

    printf("\n🕵️ Agora é hora de acusar!\n");
    printf("Quem é o culpado? Escolha o número do suspeito: ");
    tentativa = escolherOpcao(1, QTD_SUSPEITOS);

    if (tentativa - 1 == culpado) {
        printf("\n🎉 Parabéns, detetive! Você prendeu o verdadeiro culpado: %s!\n",
               suspeitos[culpado].nome);
    } else {
        printf("\n❌ Você errou! O verdadeiro culpado era %s (%s).\n",
               suspeitos[culpado].nome, suspeitos[culpado].ocupacao);
    }
}

int escolherOpcao(int min, int max) {
    int opcao;
    while (1) {
        if (scanf("%d", &opcao) == 1 && opcao >= min && opcao <= max)
            return opcao;
        else {
            printf("Opção inválida. Escolha entre %d e %d: ", min, max);
            while (getchar() != '\n');
        }
    }
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
