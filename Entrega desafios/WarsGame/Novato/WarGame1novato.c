// SISTEMA DE CADASTRO DE TERRITÓRIOS - WAR GAME
//
// OBJETIVO:
// Implementar um sistema simples de cadastro de territórios com informações
// sobre nome, cor do exército e quantidade de tropas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10

// ============================================================================
// ESTRUTURA: Territorio
// Armazena informações sobre um território no jogo de guerra
// ============================================================================
struct Territorio
{
    char nome[MAX_NOME];    // Nome do território
    char cor[MAX_COR];       // Cor do exército que controla o território
    int tropas;              // Quantidade de tropas no território
};

// ============================================================================
// FUNÇÃO: cadastrarTerritorios
// DESCRIÇÃO: Solicita ao usuário que registre informações de 5 territórios
// PARÂMETROS: array de struct Territorio
// ============================================================================
void cadastrarTerritorios(struct Territorio territorios[])
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║       CADASTRO DE TERRITÓRIOS - 5 REGIÕES      ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++)
    {
        printf("--- Território %d de %d ---\n", i + 1, MAX_TERRITORIOS);

        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, MAX_NOME, stdin);
        // Remove a quebra de linha do final
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, MAX_COR, stdin);
        // Remove a quebra de linha do final
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o buffer de entrada após ler um inteiro

        printf("\n");
    }
}

// ============================================================================
// FUNÇÃO: exibirTerritorios
// DESCRIÇÃO: Exibe as informações de todos os territórios cadastrados
// PARÂMETROS: array de struct Territorio
// ============================================================================
void exibirTerritorios(struct Territorio territorios[])
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║        TERRITÓRIOS CADASTRADOS - RESUMO        ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++)
    {
        printf("┌────────────────────────────────────────────┐\n");
        printf("│ Território %d                              │\n", i + 1);
        printf("├────────────────────────────────────────────┤\n");
        printf("│ Nome:  %-35s │\n", territorios[i].nome);
        printf("│ Cor:   %-35s │\n", territorios[i].cor);
        printf("│ Tropas: %-34d │\n", territorios[i].tropas);
        printf("└────────────────────────────────────────────┘\n\n");
    }
}

// ============================================================================
// FUNÇÃO: main
// DESCRIÇÃO: Função principal que controla o fluxo do programa
// ============================================================================
int main()
{
    // Array de estruturas para armazenar os 5 territórios
    struct Territorio territorios[MAX_TERRITORIOS];

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║      BEM-VINDO AO SISTEMA DE TERRITÓRIOS      ║\n");
    printf("║           JOGO DE GUERRA - VERSÃO 1.0         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    // Chamar função para cadastrar os territórios
    cadastrarTerritorios(territorios);

    // Chamar função para exibir os territórios cadastrados
    exibirTerritorios(territorios);

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║              PROGRAMA FINALIZADO               ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    return 0;
}
