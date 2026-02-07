// SISTEMA DE GUERRA COM MISSÕES ESTRATÉGICAS - WAR GAME MESTRE
//
// OBJETIVO:
// Implementar um sistema completo de jogo de guerra com:
// - Cadastro e exibição de territórios com alocação dinâmica de memória
// - Sistema de ataques com simulação de dados aleatórios
// - Atribuição de missões estratégicas individuais para cada jogador
// - Verificação de objetivos e condição de vitória baseada em missões
// - Estrutura modular com funções especializadas
// - Gerenciamento adequado de ponteiros e memória

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// CONSTANTES
// ============================================================================
#define MAX_NOME 30
#define MAX_COR 10
#define MAX_MISSAO 100
#define DADOS_ATAQUE 6 // Simulação de dados (1 a 6)

// ============================================================================
// ESTRUTURA: Territorio
// Armazena informações sobre um território no jogo de guerra
// ============================================================================
typedef struct
{
    char nome[MAX_NOME];      // Nome do território
    char cor[MAX_COR];        // Cor do exército que controla o território
    int tropas;               // Quantidade de tropas no território
    char corInicial[MAX_COR]; // Cor inicial no cadastro
    int tropasInicial;        // Tropas iniciais no cadastro
} Territorio;

// ============================================================================
// VETOR DE MISSÕES PRÉ-DEFINIDAS
// Contém 5 missões estratégicas diferentes para o jogo
// ============================================================================
char *missoesPredefinidas[] = {
    "Conquistar 3 territórios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Expandir para pelo menos 4 territórios diferentes",
    "Manter 15 tropas em um único território",
    "Conquistar o território com maior número inicial de tropas"};

#define TOTAL_MISSOES 5

// ============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================================================
int lancarDado();
void atribuirMissao(char **destino, char *missoes[], int totalMissoes, int tamanhoMapa);
void exibirMissao(char *missao, const char *nomeJogador);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void cadastrarTerritorios(Territorio *territorios, int quantidade);
void exibirTerritorios(Territorio *territorios, int quantidade);
int selecionarTerritorio(int quantidade, const char *mensagem);
void atacar(Territorio *atacante, Territorio *defensor);
int verificarVencedor(char **missoes, Territorio *mapa, int quantidadeJogadores, int quantidadeTerritorios);
void liberarMemoria(Territorio *mapa, char **missoes, int quantidadeJogadores);
void exibirStatusMissoes(char **missoes, int quantidadeJogadores);
void exibirMenu();

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
// FUNÇÃO: atribuirMissao
// DESCRIÇÃO: Sorteia uma missão aleatória e copia para a variável destino
//            usando strcpy. A missão é alocada dinamicamente.
// PARÂMETROS: destino (ponteiro para string onde será armazenada a missão)
//             missoes[] (vetor de strings contendo as missões disponíveis)
//             totalMissoes (quantidade de missões disponíveis)
// NOTA: Passagem por referência - modifica o ponteiro destino
// ============================================================================
// Atribui uma missão compatível com o tamanho do mapa
// Se o mapa tiver poucos territórios, filtra missões que exigem mais territórios
void atribuirMissao(char **destino, char *missoes[], int totalMissoes, int tamanhoMapa)
{
    // Cria um vetor temporário de índices compatíveis
    int indices[TOTAL_MISSOES];
    int count = 0;

    for (int i = 0; i < totalMissoes; i++)
    {
        // Missões que exigem pelo menos 3 territórios
        if (strstr(missoes[i], "Conquistar 3 territórios seguidos") != NULL)
        {
            if (tamanhoMapa >= 3)
            {
                indices[count++] = i;
            }
            continue;
        }

        // Missões que exigem pelo menos 4 territórios
        if (strstr(missoes[i], "Expandir para pelo menos 4 territórios diferentes") != NULL)
        {
            if (tamanhoMapa >= 4)
            {
                indices[count++] = i;
            }
            continue;
        }

        // Outras missões são consideradas compatíveis independentemente do tamanho
        indices[count++] = i;
    }

    // Se nenhuma missão for compatível (caso extremo), permita qualquer uma
    int escolha;
    if (count == 0)
    {
        escolha = rand() % totalMissoes;
    }
    else
    {
        escolha = indices[rand() % count];
    }

    // Aloca memória dinamicamente para armazenar a missão
    *destino = (char *)malloc((strlen(missoes[escolha]) + 1) * sizeof(char));

    // Verifica se a alocação foi bem-sucedida
    if (*destino == NULL)
    {
        printf("❌ Erro: Falha na alocação de memória para a missão!\n");
        return;
    }

    // Copia a missão sorteada para a variável do jogador
    strcpy(*destino, missoes[escolha]);
}

// ============================================================================
// FUNÇÃO: exibirMissao
// DESCRIÇÃO: Exibe a missão atribuída ao jogador
// PARÂMETROS: missao (passagem por valor - apenas leitura)
//             nomeJogador (identificador do jogador)
// ============================================================================
void exibirMissao(char *missao, const char *nomeJogador)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║           MISSÃO ESTRATÉGICA DESIGNADA         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("🎯 Jogador: %s\n", nomeJogador);
    printf("📋 Missão: %s\n\n", missao);
}

// ============================================================================
// FUNÇÃO: verificarMissao
// DESCRIÇÃO: Verifica se a missão do jogador foi cumprida analisando
//            o estado atual do mapa de territórios
// PARÂMETROS: missao (string contendo a descrição da missão)
//             mapa (ponteiro para array de territórios)
//             tamanho (quantidade total de territórios)
// RETORNO: 1 se a missão foi cumprida, 0 caso contrário
// ============================================================================
int verificarMissao(char *missao, Territorio *mapa, int tamanho)
{
    // Verifica qual tipo de missão o jogador tem

    // Missão: Conquistar 3 territórios seguidos
    if (strstr(missao, "Conquistar 3 territórios seguidos") != NULL)
    {
        // Procura por 3 territórios consecutivos da mesma cor
        for (int i = 0; i <= tamanho - 3; i++)
        {
            if (strcmp(mapa[i].cor, mapa[i + 1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i + 2].cor) == 0)
            {
                return 1;
            }
        }
        return 0;
    }

    // Missão: Eliminar todas as tropas da cor vermelha
    if (strstr(missao, "Eliminar todas as tropas da cor vermelha") != NULL)
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, "vermelho") == 0 ||
                strcmp(mapa[i].cor, "Vermelho") == 0 ||
                strcmp(mapa[i].cor, "vermelha") == 0 ||
                strcmp(mapa[i].cor, "Vermelha") == 0)
            {
                return 0; // Ainda há territórios vermelhos
            }
        }
        return 1;
    }

    // Missão: Expandir para pelo menos 4 territórios diferentes
    if (strstr(missao, "Expandir para pelo menos 4 territórios diferentes") != NULL)
    {
        // Conta quantos territórios a cor do primeiro jogador controla
        char corJogador[MAX_COR];
        strcpy(corJogador, "");

        // Encontra a primeira cor não vazia
        for (int i = 0; i < tamanho; i++)
        {
            if (strlen(mapa[i].cor) > 0)
            {
                strcpy(corJogador, mapa[i].cor);
                break;
            }
        }

        // Conta territórios da cor do jogador
        int territoriosControlados = 0;
        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, corJogador) == 0)
            {
                territoriosControlados++;
            }
        }

        return territoriosControlados >= 4;
    }

    // Missão: Manter 15 tropas em um único território
    if (strstr(missao, "Manter 15 tropas em um único território") != NULL)
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (mapa[i].tropas >= 15)
            {
                return 1;
            }
        }
        return 0;
    }

    // Missão: Conquistar o território com maior número inicial de tropas
    if (strstr(missao, "Conquistar o território com maior número inicial de tropas") != NULL)
    {
        // Esta simples verificação assume que a primeira cor encontrada é do jogador
        // Encontra o território com mais tropas
        int maxTropas = 0;
        char corMaiorTerritorio[MAX_COR] = "";

        for (int i = 0; i < tamanho; i++)
        {
            if (mapa[i].tropas > maxTropas)
            {
                maxTropas = mapa[i].tropas;
                strcpy(corMaiorTerritorio, mapa[i].cor);
            }
        }

        // Retorna 1 se a cor atual possui o maior território
        return maxTropas > 0;
    }

    return 0;
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

        // Salva a cor inicial
        strcpy(territorios[i].corInicial, territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        // Salva as tropas iniciais
        territorios[i].tropasInicial = territorios[i].tropas;
        getchar();

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
// PARÂMETROS: ponteiros para territórios atacante e defensor (passagem por referência)
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

        // Transfere a cor para o defensor
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
// FUNÇÃO: verificarVencedor
// DESCRIÇÃO: Verifica se algum jogador completou sua missão ao final do turno
// PARÂMETROS: ponteiro para array de strings com missões dos jogadores
//             ponteiro para array de territórios
//             quantidade de jogadores
//             quantidade de territórios
// RETORNO: índice do jogador vencedor (-1 se nenhum venceu ainda)
// ============================================================================
int verificarVencedor(char **missoes, Territorio *mapa, int quantidadeJogadores, int quantidadeTerritorios)
{
    for (int i = 0; i < quantidadeJogadores; i++)
    {
        if (missoes[i] != NULL && verificarMissao(missoes[i], mapa, quantidadeTerritorios))
        {
            return i;
        }
    }
    return -1;
}

// ============================================================================
// FUNÇÃO: liberarMemoria
// DESCRIÇÃO: Libera toda a memória alocada dinamicamente
// PARÂMETROS: ponteiro para array de territórios
//             ponteiro para array de strings com missões dos jogadores
//             quantidade de jogadores
// ============================================================================
void liberarMemoria(Territorio *mapa, char **missoes, int quantidadeJogadores)
{
    // Liberar memória dos territórios
    if (mapa != NULL)
    {
        free(mapa);
        mapa = NULL;
        printf("✅ Memória dos territórios liberada com sucesso!\n");
    }

    // Liberar memória de cada missão
    if (missoes != NULL)
    {
        for (int i = 0; i < quantidadeJogadores; i++)
        {
            if (missoes[i] != NULL)
            {
                free(missoes[i]);
                missoes[i] = NULL;
            }
        }

        // Liberar o array de missões
        free(missoes);
        missoes = NULL;
        printf("✅ Memória das missões liberada com sucesso!\n");
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
    printf("3. Verificar status das missões\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

// ============================================================================
// FUNÇÃO: exibirStatusMissoes
// DESCRIÇÃO: Exibe o status atual de todas as missões dos jogadores
// PARÂMETROS: ponteiro para array de strings com missões
//             quantidade de jogadores
// ============================================================================
void exibirStatusMissoes(char **missoes, int quantidadeJogadores)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║         STATUS DAS MISSÕES ATUAIS              ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    for (int i = 0; i < quantidadeJogadores; i++)
    {
        printf("Jogador %d: %s\n", i + 1, missoes[i] != NULL ? missoes[i] : "Sem missão");
    }
    printf("\n");
}

// ============================================================================
// FUNÇÃO: main
// DESCRIÇÃO: Função principal que controla o fluxo do programa
// Inicializa o jogo, atribui missões, gerencia o menu e verifica condições
// de vitória ao final de cada turno
// ============================================================================
int main()
{
    // Inicializar o gerador de números aleatórios com seed baseado no tempo
    srand(time(NULL));

    int quantidadeTerritorios = 0;
    int quantidadeJogadores = 0;
    Territorio *mapa = NULL;
    char **missoes = NULL;

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║      BEM-VINDO AO JOGO DE GUERRA              ║\n");
    printf("║    COM MISSÕES ESTRATÉGICAS - VERSÃO 3.0      ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    // Solicitar quantidade de territórios
    printf("\nDigite a quantidade de territórios a criar: ");
    scanf("%d", &quantidadeTerritorios);
    getchar();

    // Validar entrada
    if (quantidadeTerritorios <= 0)
    {
        printf("❌ Quantidade inválida! Deve ser maior que zero.\n");
        return 1;
    }

    // Solicitar quantidade de jogadores
    printf("Digite a quantidade de jogadores: ");
    scanf("%d", &quantidadeJogadores);
    getchar();

    // Validar entrada
    if (quantidadeJogadores <= 0)
    {
        printf("❌ Quantidade inválida! Deve ser maior que zero.\n");
        return 1;
    }

    // Alocação dinâmica de memória para os territórios
    mapa = (Territorio *)calloc(quantidadeTerritorios, sizeof(Territorio));

    // Verificar se a alocação foi bem-sucedida
    if (mapa == NULL)
    {
        printf("❌ Erro: Falha na alocação de memória para territórios!\n");
        return 1;
    }

    printf("✅ Memória alocada com sucesso para %d territórios!\n\n", quantidadeTerritorios);

    // Alocação dinâmica de memória para as missões dos jogadores
    missoes = (char **)malloc(quantidadeJogadores * sizeof(char *));

    // Verificar se a alocação foi bem-sucedida
    if (missoes == NULL)
    {
        printf("❌ Erro: Falha na alocação de memória para missões!\n");
        liberarMemoria(mapa, NULL, 0);
        return 1;
    }

    printf("✅ Memória alocada com sucesso para %d missões!\n\n", quantidadeJogadores);

    // Cadastrar os territórios
    cadastrarTerritorios(mapa, quantidadeTerritorios);

    // Atribuir missões para cada jogador
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║        ATRIBUIÇÃO DE MISSÕES AOS JOGADORES     ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    for (int i = 0; i < quantidadeJogadores; i++)
    {
        // Atribui a missão de forma aleatória compatível com a quantidade de territórios
        atribuirMissao(&missoes[i], missoesPredefinidas, TOTAL_MISSOES, quantidadeTerritorios);

        // Exibe a missão ao jogador
        exibirMissao(missoes[i], "Jogador");
    }

    // Menu de interação
    int opcao = 0;
    int continuar = 1;
    int vencedor = -1;
    int turno = 0; // contador de turnos para evitar verificar vitória imediatamente após atribuição

    while (continuar)
    {
        // Não verificar vitória no primeiro ciclo imediatamente após atribuição
        if (turno > 0)
        {
            // Verificar se algum jogador venceu (após cada ação)
            vencedor = verificarVencedor(missoes, mapa, quantidadeJogadores, quantidadeTerritorios);

            if (vencedor != -1)
            {
                printf("\n");
                printf("╔════════════════════════════════════════════════╗\n");
                printf("║              TEMOS UM VENCEDOR!               ║\n");
                printf("╚════════════════════════════════════════════════╝\n");
                printf("🎉 Jogador %d cumpriu sua missão: %s\n\n", vencedor + 1, missoes[vencedor]);
                printf("Parabéns! Você venceu o jogo!\n\n");
                continuar = 0;
                break;
            }
        }

        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            // Exibir territórios
            exibirTerritorios(mapa, quantidadeTerritorios);
            break;

        case 2:
        {
            // Realizar ataque
            if (quantidadeTerritorios < 2)
            {
                printf("❌ Erro: É necessário pelo menos 2 territórios para atacar!\n");
                break;
            }

            exibirTerritorios(mapa, quantidadeTerritorios);

            int idAtacante = selecionarTerritorio(quantidadeTerritorios,
                                                  "\nDigite o ID do território atacante: ");
            int idDefensor = selecionarTerritorio(quantidadeTerritorios,
                                                  "Digite o ID do território defensor: ");

            // Validar se são territórios diferentes
            if (idAtacante == idDefensor)
            {
                printf("❌ Erro: Atacante e defensor devem ser territórios diferentes!\n");
                break;
            }

            // Realizar o ataque
            atacar(&mapa[idAtacante], &mapa[idDefensor]);
            turno++;

            break;
        }

        case 3:
            // Exibir status das missões
            exibirStatusMissoes(missoes, quantidadeJogadores);
            break;

        case 4:
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
    liberarMemoria(mapa, missoes, quantidadeJogadores);

    return 0;
}
