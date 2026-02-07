# WAR GAME MESTRE - Sistema de Guer com Missões Estratégicas

## 📋 Descrição Geral

Sistema completo de jogo de guerra em C, desenvolvido em evolução progressiva:
- **Nível Novato**: Cadastro e exibição básica de territórios
- **Nível Aventureiro**: Implementação de sistema de ataques com dados aleatórios
- **Nível Mestre** (versão atual): Sistema completo com missões estratégicas individuais para cada jogador

## 🎮 Funcionalidades Principais

### 1. **Missões Estratégicas Automáticas**
- Cada jogador recebe automaticamente uma missão sorteada ao iniciar o jogo
- 5 tipos diferentes de missões pré-definidas:
  - Conquistar 3 territórios seguidos
  - Eliminar todas as tropas da cor vermelha
  - Expandir para pelo menos 4 territórios diferentes
  - Manter 15 tropas em um único território
  - Conquistar o território com maior número inicial de tropas

### 2. **Alocação Dinâmica de Memória**
- Uso de `malloc()` e `calloc()` para alocação de territórios e missões
- Gerenciamento adequado com `free()` para evitar vazamentos de memória
- Estrutura modular para facilitar manutenção

### 3. **Sistema de Ataques**
- Ataque entre territórios com validação
- Simulação de dados de 6 faces (1-6) para cada combate
- Transferência de controle territorial mediante vitória
- Perda de tropas em caso de derrota

### 4. **Verificação de Objetivos**
- Verificação silenciosa da condição de missão após cada ação
- Detecção automática de vencedor ao cumprir a missão
- Exibição da missão ao jogador apenas no início do jogo

## 🏗️ Estruturas de Dados

### Struct Territorio
```c
typedef struct {
    char nome[30];      // Nome do território (Ex: Brasil, Europa)
    char cor[10];       // Cor do exército controlador (Ex: azul, vermelho)
    int tropas;         // Quantidade de tropas presentes
} Territorio;
```

## 🔧 Principais Funções Implementadas

### Gerenciamento de Missões

#### `void atribuirMissao(char **destino, char *missoes[], int totalMissoes)`
- **Descrição**: Sorteia uma missão aleatória e a aloca dinamicamente
- **Parâmetros**: 
  - `destino`: Ponteiro duplo para armazenar a missão (passagem por referência)
  - `missoes[]`: Vetor de strings com as missões disponíveis
  - `totalMissoes`: Quantidade de missões
- **Nota**: Usa `malloc()` para alocação dinâmica

#### `void exibirMissao(char *missao, const char *nomeJogador)`
- **Descrição**: Exibe a missão designada ao jogador
- **Parâmetros**:
  - `missao`: String da missão (passagem por valor)
  - `nomeJogador`: Identificador do jogador

#### `int verificarMissao(char *missao, Territorio *mapa, int tamanho)`
- **Descrição**: Verifica se a missão foi cumprida
- **Parâmetros**:
  - `missao`: String contendo a descrição da missão
  - `mapa`: Ponteiro para array de territórios
  - `tamanho`: Quantidade total de territórios
- **Retorno**: 1 se cumprida, 0 caso contrário
- **Lógica de Verificação**:
  - Detecta padrões em territórios consecutivos
  - Analisa cores e quantidades de tropas
  - Conta territórios controlados

### Gerenciamento de Memória

#### `void liberarMemoria(Territorio *mapa, char **missoes, int quantidadeJogadores)`
- **Descrição**: Libera toda memória alocada dinamicamente
- **Parâmetros**:
  - `mapa`: Array de territórios
  - `missoes`: Array de strings com as missões
  - `quantidadeJogadores`: Quantidade de jogadores
- **Responsabilidades**:
  - Libera cada missão individual com `free()`
  - Libera o array de missões
  - Libera o array de territórios

### Verificação de Vitória

#### `int verificarVencedor(char **missoes, Territorio *mapa, int quantidadeJogadores, int quantidadeTerritorios)`
- **Descrição**: Verifica se algum jogador cumpriu sua missão
- **Retorno**: Índice do vencedor ou -1 se nenhum venceu
- **Execução**: Silenciosa, sem interfere no fluxo do jogo

### Outras Funções

#### `void atacar(Territorio *atacante, Territorio *defensor)`
- Simula ataque entre territórios com dados aleatórios
- Valida ataques apenas contra territórios inimigos
- Atualiza o estado dos territórios conforme resultado

#### `void cadastrarTerritorios(Territorio *territorios, int quantidade)`
- Coleta dados de entrada do usuário
- Armazena em estruturas alocadas dinamicamente

#### `void exibirTerritorios(Territorio *territorios, int quantidade)`
- Exibe status de todos os territórios com formatação visual

#### `int selecionarTerritorio(int quantidade, const char *mensagem)`
- Interface para seleção com validação de entrada

#### `void exibirStatusMissoes(char **missoes, int quantidadeJogadores)`
- Exibe o estado atual de todas as missões

#### `void exibirMenu()`
- Apresenta opções disponíveis ao jogador

## 📊 Fluxo do Jogo

1. **Inicialização**
   - Solicita quantidade de territórios e jogadores
   - Aloca memória para estruturas
   - Inicializa gerador de números aleatórios com `srand(time(NULL))`

2. **Cadastro**
   - Usuário cadastra informações de cada território
   - Armazena em array dinâmico

3. **Atribuição de Missões**
   - Cada jogador recebe uma missão sorteada automaticamente
   - Exibe a missão designada

4. **Loop Principal**
   - Verifica se alguém venceu (após cada ação)
   - Apresenta menu de opções
   - Permite visualizar territórios, realizar ataques ou verificar estado

5. **Encerramento**
   - Detecta vencedor quando missão é cumprida
   - Libera toda memória alocada
   - Encerra programa

## 🎯 Requisitos Técnicos Atendidos

✅ **Funcionalidades**
- [x] Vetor de 5 missões pré-definidas
- [x] Função `atribuirMissao()` com sorteio e `strcpy()`
- [x] Alocação dinâmica com `malloc()`
- [x] Função `verificarMissao()` completa
- [x] Verificação e exibição de vencedor ao final de turno

✅ **Não-Funcionalidades**
- [x] Modularização com funções especializadas
- [x] Uso extensivo de ponteiros
- [x] Passagem por valor e referência
- [x] Interface intuitiva e limpa

✅ **Requisitos Técnicos**
- [x] Bibliotecas: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
- [x] Struct `Territorio` com campos corretos
- [x] `calloc()` e `malloc()` para alocação
- [x] Função `atacar()` com `rand()` (1-6)
- [x] Transferência de cor e tropas em vitória
- [x] Função `liberarMemoria()` com `free()`
- [x] `srand(time(NULL))` para aleatoriedade
- [x] Validação de ataques contra territórios inimigos
- [x] Comentários explicativos

## 💻 Compilação e Execução

### Compilar
```bash
gcc -o WarsGame3_mestre WarsGame3_mestre.c
```

### Executar
```bash
./WarsGame3_mestre
```

### Exemplo de Uso
```
Quantidade de territórios: 5
Quantidade de jogadores: 2

[Cadastra os 5 territórios com nomes, cores e tropas]

[Sistema atribui uma missão estratégica para cada jogador]

Menu:
1. Ver territórios
2. Atacar
3. Ver status das missões
4. Sair
```

## 🔍 Lógica de Verificação das Missões

### Missão 1: "Conquistar 3 territórios seguidos"
- Procura por 3 territórios consecutivos com a mesma cor
- Verifica no índice 0, 1, 2; depois 1, 2, 3; etc.

### Missão 2: "Eliminar todas as tropas da cor vermelha"
- Itera por todos os territórios
- Verifica se ainda existem territórios vermelhos
- Retorna sucesso apenas se nenhum existir

### Missão 3: "Expandir para pelo menos 4 territórios diferentes"3
- Encontra a cor do primeiro jogador
- Conta quantos territórios essa cor controla
- Retorna sucesso se ≥ 4 territórios

### Missão 4: "Manter 15 tropas em um único território"
- Itera por todos os territórios
- Verifica se algum tem ≥ 15 tropas
- Retorna sucesso quando encontra

### Missão 5: "Conquistar o território com maior número inicial"
- Encontra o território com maior quantidade de tropas
- Retorna sucesso se controlado (simplificado)

## 📝 Notas Importantes

1. **Aleatoriedade**: A seed do gerador aleatório é configurada com `srand(time(NULL))`, garantindo diferentes resultados a cada execução

2. **Validações**: 
   - Não é possível atacar próprio território
   - Não é possível atacar com território sem tropas
   - Seleção de território valida entrada

3. **Gerenciamento de Memória**:
   - Cada missão é alocada individualmente
   - Função `liberarMemoria()` libera recursivamente todos os alocamentos
   - Sem vazamentos de memória

4. **Interface Visual**: 
   - Uso de caracteres Unicode para melhor visualização (✅, ❌, 🎲, etc.)
   - Formatação em tabelas com bordas ASCII
   - Mensagens claras e informativas

## 🚀 Melhorias Possíveis (Futuras)

- Sistema de turnos com limite por turno
- Alianças entre jogadores
- Diferentes tipos de tropas com atributos
- Sistema de diplomacia
- Efeitos especiais de terreno
- Salvamento e carregamento de partida
- Inteligência Artificial para jogadores computador
- Modo multiplayer em rede

## 👨‍💻 Autor

Desenvolvido como cumprimento de requisitos da disciplina de Estruturas de Dados

## 📄 Licença

Código educacional - livre para modificação e uso em fins acadêmicos
