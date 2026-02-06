// SISTEMA DE GUERRA COM SIMULAÇÃO DE ATAQUES - WAR GAME AVENTUREIRO
//
// OBJETIVO:
// Implementar um sistema de jogabilidade com cadastro, exibição e simula
// de ataques entre territórios. O sistema utiliza alocação dinâmica de memória
// (calloc) e ponteiros para manipular os territórios, proporcionando maior
// flexibilidade e realismo ao jogo de guerra. Os ataques são resolvidos
// por simulação de dados aleatórios.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// CONSTANTES
// ============================================================================
#define MAX_NOME 30
#define MAX_COR 10
#define DADOS_ATAQUE 6 // Simulação de dados (1 a 6)

// ============================================================================
// ESTRUTURA: Territorio
// Armazena informações sobre um território no jogo de guerra
// ============================================================================
typedef struct
{
    char nome[MAX_NOME]; // Nome do território
    char cor[MAX_COR];   // Cor do exército que controla o território
    int tropas;          // Quantidade de tropas no território
} Territorio;

// ============================================================================
// FUNÇÃO: lancarDado
// DESCRIÇÃO: Simula o lançamento de um dado de 6 faces
// RETORNO: número aleatório entre 1 e 6
// ============================================================================
int lancarDado()
{
    return (rand() % DADOS_ATAQUE) + 1;
}

// ============================================================================
// FUNÇÃO: cadastrarTerritorios
// DESCRIÇÃO: Solicita ao usuário informações dos territórios
// PARÂMETROS: ponteiro para array de Territorio, quantidade de territórios
// ============================================================================
void cadastrarTerritorios(Territorio *territorios, int quantidade)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║    CADASTRO DE TERRITÓRIOS - %d REGIÕES       ║\n", quantidade);
    printf("╚════════════════════════════════════════════════╝\n\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf("--- Território %d de %d ---\n", i + 1, quantidade);

        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, MAX_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, MAX_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o buffer de entrada

        printf("\n");
    }
}

// ============================================================================
// FUNÇÃO: exibirTerritorios
// DESCRIÇÃO: Exibe as informações de todos os territórios cadastrados
// PARÂMETROS: ponteiro para array de Territorio, quantidade de territórios
// ============================================================================
void exibirTerritorios(Territorio *territorios, int quantidade)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║        TERRITÓRIOS CADASTRADOS - RESUMO        ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf("┌────────────────────────────────────────────┐\n");
        printf("│ Território %d [ID: %d]                      │\n", i + 1, i);
        printf("├────────────────────────────────────────────┤\n");
        printf("│ Nome:  %-35s │\n", territorios[i].nome);
        printf("│ Cor:   %-35s │\n", territorios[i].cor);
        printf("│ Tropas: %-34d │\n", territorios[i].tropas);
        printf("└────────────────────────────────────────────┘\n\n");
    }
}

// ============================================================================
// FUNÇÃO: selecionarTerritorio
// DESCRIÇÃO: Solicita ao usuário a seleção de um território com validação
// PARÂMETROS: quantidade de territórios disponíveis, mensagem de seleção
// RETORNO: índice do território selecionado
// ============================================================================
int selecionarTerritorio(int quantidade, const char *mensagem)
{
    int territorio;

    while (1)
    {
        printf("%s", mensagem);
        scanf("%d", &territorio);
        getchar();

        // Validação de entrada
        if (territorio < 0 || territorio >= quantidade)
        {
            printf("❌ Seleção inválida! Digite um ID entre 0 e %d.\n\n", quantidade - 1);
        }
        else
        {
            return territorio;
        }
    }
}

// ============================================================================
// FUNÇÃO: atacar
// DESCRIÇÃO: Simula um ataque entre dois territórios
// PARÂMETROS: ponteiros para territórios atacante e defensor
// NOTA: O resultado do ataque altera os dados do território defensor
// ============================================================================
void atacar(Territorio *atacante, Territorio *defensor)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║            SIMULAÇÃO DE ATAQUE                 ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    // Validação: não atacar próprio território
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("❌ ERRO: Você não pode atacar um território de sua própria cor!\n\n");
        return;
    }

    // Verificar se atacante tem tropas
    if (atacante->tropas <= 0)
    {
        printf("❌ ERRO: O território atacante não tem tropas!\n\n");
        return;
    }

    printf("🎲 %s [%s] (%d tropas) atacando %s [%s] (%d tropas)...\n\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    // Lançar dados
    int dadoAtacante = lancarDado();
    int dadoDefensor = lancarDado();

    printf("🎲 Dados de ataque:\n");
    printf("   • %s [%s] lançou: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("   • %s [%s] lançou: %d\n\n", defensor->nome, defensor->cor, dadoDefensor);

    // Determinar resultado do ataque
    if (dadoAtacante > dadoDefensor)
    {
        printf("✅ VITÓRIA! %s conquistou %s!\n\n", atacante->nome, defensor->nome);

        // Calcula tropas transferidas (metade das tropas do defensor)
        int tropasTransferidas = defensor->tropas / 2;

        // Atualizar territórios
        // Defensor perde todas as tropas
        defensor->tropas = tropasTransferidas;

        // Atacante ganha metade das tropas do defensor (que permanece no defensor)
        // e transfere sua cor para o defensor
        strcpy(defensor->cor, atacante->cor);

        printf("📊 Resultado:\n");
        printf("   • %s agora controla %s!\n", atacante->cor, defensor->nome);
        printf("   • Tropas transferidas: %d\n", tropasTransferidas);
        printf("   • Novas tropas em %s: %d\n\n", defensor->nome, defensor->tropas);
    }
    else if (dadoAtacante < dadoDefensor)
    {
        printf("❌ DERROTA! %s repeliu o ataque de %s!\n\n",
               defensor->nome, atacante->nome);

        // Atacante perde uma tropa
        if (atacante->tropas > 0)
        {
            atacante->tropas--;
            printf("📊 Resultado:\n");
            printf("   • %s perdeu 1 tropa na batalha.\n", atacante->nome);
            printf("   • Tropas restantes em %s: %d\n\n", atacante->nome, atacante->tropas);
        }
        else
        {
            printf("⚠️  %s não tinha tropas para perder!\n\n", atacante->nome);
        }
    }
    else
    {
        printf("🤝 EMPATE! Nenhum território muda de controle.\n");
        printf("   • %s mantém %s\n\n", defensor->cor, defensor->nome);
    }
}

// ============================================================================
// FUNÇÃO: liberarMemoria
// DESCRIÇÃO: Libera a memória alocada dinamicamente para os territórios
// PARÂMETROS: ponteiro para array de Territorio
// ============================================================================
void liberarMemoria(Territorio *mapa)
{
    if (mapa != NULL)
    {
        free(mapa);
        mapa = NULL;
        printf("✅ Memória liberada com sucesso!\n");
    }
}

// ============================================================================
// FUNÇÃO: exibirMenu
// DESCRIÇÃO: Exibe o menu de opções do jogo
// ============================================================================
void exibirMenu()
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║              MENU PRINCIPAL                    ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("1. Exibir territórios\n");
    printf("2. Realizar ataque\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

// ============================================================================
// FUNÇÃO: main
// DESCRIÇÃO: Função principal que controla o fluxo do programa
// ============================================================================
int main()
{
    // Inicializar o gerador de números aleatórios
    srand(time(NULL));

    int quantidade = 0;
    Territorio *mapa = NULL;

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║      BEM-VINDO AO JOGO DE GUERRA              ║\n");
    printf("║      SISTEMA COM ATAQUES - VERSÃO 2.0         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    // Solicitar quantidade de territórios
    printf("\nDigite a quantidade de territórios a criar: ");
    scanf("%d", &quantidade);
    getchar();

    // Validar entrada
    if (quantidade <= 0)
    {
        printf("❌ Quantidade inválida! Deve ser maior que zero.\n");
        return 1;
    }

    // Alocação dinâmica de memória para os territórios
    mapa = (Territorio *)calloc(quantidade, sizeof(Territorio));

    // Verificar se a alocação foi bem-sucedida
    if (mapa == NULL)
    {
        printf("❌ Erro: Falha na alocação de memória!\n");
        return 1;
    }

    printf("✅ Memória alocada com sucesso para %d territórios!\n", quantidade);

    // Cadastrar os territórios
    cadastrarTerritorios(mapa, quantidade);

    // Menu de interação
    int opcao = 0;
    int continuar = 1;

    while (continuar)
    {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            // Exibir territórios
            exibirTerritorios(mapa, quantidade);
            break;

        case 2:
        {
            // Realizar ataque
            if (quantidade < 2)
            {
                printf("❌ Erro: É necessário pelo menos 2 territórios para atacar!\n");
                break;
            }

            exibirTerritorios(mapa, quantidade);

            int idAtacante = selecionarTerritorio(quantidade,
                                                  "\nDigite o ID do território atacante: ");
            int idDefensor = selecionarTerritorio(quantidade,
                                                  "Digite o ID do território defensor: ");

            // Validar se são territórios diferentes
            if (idAtacante == idDefensor)
            {
                printf("❌ Erro: Atacante e defensor devem ser territórios diferentes!\n");
                break;
            }

            // Realizar o ataque
            atacar(&mapa[idAtacante], &mapa[idDefensor]);

            break;
        }

        case 3:
            // Sair do programa
            printf("\n");
            printf("╔════════════════════════════════════════════════╗\n");
            printf("║              PROGRAMA FINALIZADO               ║\n");
            printf("║         Obrigado por jogar! Até logo!          ║\n");
            printf("╚════════════════════════════════════════════════╝\n");
            continuar = 0;
            break;

        default:
            printf("❌ Opção inválida! Tente novamente.\n");
        }
    }

    // Liberar memória alocada
    liberarMemoria(mapa);

    return 0;
}
