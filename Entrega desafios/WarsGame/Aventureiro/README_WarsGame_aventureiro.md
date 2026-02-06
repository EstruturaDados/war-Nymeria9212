# 🎮 WAR GAME AVENTUREIRO - VERSÃO 2.0

## 📋 Descrição

O **WAR GAME Aventureiro** é uma evolução do sistema básico de cadastro de territórios. Esta versão implementa um **sistema completo de batalhas entre territórios** utilizando alocação dinâmica de memória, ponteiros e simulação de combate com dados aleatórios.

O programa permite que jogadores:
- Cadastrem uma quantidade dinâmica de territórios
- Visualizem o mapa de territórios
- Realizem ataques entre territórios com simulação de dados
- Conquistem novos territórios ao vencerem as batalhas

---

## 🚀 Funcionalidades Principais

### 1. **Alocação Dinâmica de Memória**
- Utiliza `calloc()` para alocar um vetor de estruturas `Territorio`
- O usuário define a quantidade de territórios a ser criada
- Maior flexibilidade e eficiência de memória

### 2. **Sistema de Cadastro de Territórios**
- Registra nome, cor do exército e quantidade de tropas
- Interface amigável com validações de entrada
- Suporta qualquer quantidade de territórios

### 3. **Simulação de Ataques**
- **Mecânica**: Lançamento de dados aleatórios (1-6) para ambos os lados
- **Vitória do Atacante**: 
  - Conquistar o território defensor
  - Transferir metade das tropas do defensor para o território atacado
  - Mudar a cor do território para a cor do atacante
- **Derrota do Atacante**:
  - O defensor mantém o controle
  - O atacante perde 1 tropa
- **Empate**: Nenhuma alteração no mapa

### 4. **Validações de Segurança**
- Impede ataque a territórios da própria cor
- Valida se o território atacante tem tropas
- Verifica se atacante e defensor são diferentes
- Valida índices de entrada do usuário

### 5. **Menu Interativo**
- Exibir todos os territórios com seus dados
- Realizar ataques
- Encerrar o programa

### 6. **Gerenciamento de Memória**
- Libera toda memória alocada ao finalizar
- Uso correto de `free()` para prevenir vazamento de memória

---

## 📁 Estrutura do Código

### **Struct: Territorio**
```c
typedef struct
{
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;
```

### **Funções Principais**

#### **`int lancarDado()`**
Simula um lançamento de dado (1-6) usando `rand()`.

#### **`void cadastrarTerritorios(Territorio* territorios, int quantidade)`**
- Recebe ponteiro para array de territórios
- Solicita informações para cada território
- Parametrizado com quantidade dinâmica

#### **`void exibirTerritorios(Territorio* territorios, int quantidade)`**
- Exibe todos os territórios com suas informações
- Mostra ID, nome, cor e quantidade de tropas
- Formatação visual com bordas

#### **`int selecionarTerritorio(int quantidade, const char* mensagem)`**
- Solicita e valida a seleção de um território
- Retorna o índice válido

#### **`void atacar(Territorio* atacante, Territorio* defensor)`**
- **Core do jogo**: Simula a batalha
- Valida condições de ataque
- Lança dados aleatórios para ambos
- Atualiza dados dos territórios conforme resultado
- Exibe relatório detalhado da batalha

#### **`void liberarMemoria(Territorio* mapa)`**
- Libera memória alocada dinamicamente
- Importante para evitar memory leaks

---

## 💻 Como Usar

### **Compilação**
```bash
gcc -o WarGame2_aventureiro WarGame2_aventureiro.c
```

### **Execução**
```bash
./WarGame2_aventureiro
```

### **Passo a Passo**

1. **Inicialização**:
   - O programa solicita a quantidade de territórios
   - Aloca memória dinamicamente

2. **Cadastro**:
   - Para cada território, insira:
     - Nome (ex: Brasil, França, China)
     - Cor do exército (ex: Vermelho, Azul, Verde)
     - Quantidade inicial de tropas

3. **Menu Principal**:
   - **Opção 1**: Ver mapa de territórios
   - **Opção 2**: Realizar ataques
   - **Opção 3**: Sair

4. **Ataque**:
   - Selecione o território atacante (por ID)
   - Selecione o território defensor (por ID)
   - Sistema simula a batalha
   - Resultado é exibido com detalhes

### **Exemplo de Execução**

```
╔════════════════════════════════════════════════╗
║      BEM-VINDO AO JOGO DE GUERRA              ║
║      SISTEMA COM ATAQUES - VERSÃO 2.0         ║
╚════════════════════════════════════════════════╝

Digite a quantidade de territórios a criar: 3
✅ Memória alocada com sucesso para 3 territórios!

--- Território 1 de 3 ---
Digite o nome do território: Brasil
Digite a cor do exército: Vermelho
Digite a quantidade de tropas: 10

--- Território 2 de 3 ---
Digite o nome do território: Argentina
Digite a cor do exército: Azul
Digite a quantidade de tropas: 8

--- Território 3 de 3 ---
Digite o nome do território: Chile
Digite a cor do exército: Verde
Digite a quantidade de tropas: 6

[Menu aparece]
...
```

---

## 🎲 Exemplo de Simulação de Ataque

```
╔════════════════════════════════════════════════╗
║            SIMULAÇÃO DE ATAQUE                 ║
╚════════════════════════════════════════════════╝

🎲 Brasil [Vermelho] (10 tropas) atacando Argentina [Azul] (8 tropas)...

🎲 Dados de ataque:
   • Brasil [Vermelho] lançou: 5
   • Argentina [Azul] lançou: 2

✅ VITÓRIA! Brasil conquistou Argentina!

📊 Resultado:
   • Vermelho agora controla Argentina!
   • Tropas transferidas: 4
   • Novas tropas em Argentina: 4
```

---

## 🔧 Requisitos Técnicos Implementados

### **Bibliotecas**
- `stdio.h` - Entrada e saída
- `stdlib.h` - Alocação de memória (`calloc`, `free`)
- `string.h` - Manipulação de strings
- `time.h` - Seed para números aleatórios

### **Técnicas Utilizadas**
- ✅ Alocação dinâmica com `calloc()`
- ✅ Uso extensivo de ponteiros
- ✅ `srand(time(NULL))` para aleatoriedade
- ✅ Validações de entrada
- ✅ `free()` para liberação de memória
- ✅ Modularização com funções
- ✅ Comentários explicativos

### **Boas Práticas**
- Funções com responsabilidade única
- Nomes descritivos de variáveis e funções
- Validações de entrada e alocação de memória
- Interface clara para o usuário
- Mensagens de erro e sucesso

---

## 📊 Fluxo do Programa

```
Início
  ↓
Inicializar seed aleatória
  ↓
Solicitar quantidade de territórios
  ↓
Alocar memória (calloc)
  ↓
Cadastrar territórios
  ↓
Exibir menu
  ├→ Opção 1: Exibir territórios
  ├→ Opção 2: 
  │   ├→ Exibir mapa
  │   ├→ Selecionar atacante
  │   ├→ Selecionar defensor
  │   └→ Executar ataque
  └→ Opção 3: Liberar memória e sair
```

---

## ⚠️ Considerações Importantes

### **Validações Implementadas**
- Quantidade de territórios deve ser > 0
- Atacante e defensor não podem ser iguais
- Não é permitido atacar próprio território
- Índices devem estar dentro do intervalo válido

### **Aleatoriedade**
- `srand(time(NULL))` garante sequências diferentes a cada execução
- `rand() % 6 + 1` gera valores de 1 a 6

### **Atualização de Dados Após Ataque**
| Resultado | Atacante | Defensor |
|-----------|----------|----------|
| Vitória | Sem mudança | Muda cor, perde tropas |
| Derrota | Perde 1 tropa | Sem mudança |
| Empate | Sem mudança | Sem mudança |

---

## 🎓 Conceitos de Aprendizado

Este programa reforça:
- **Alocação dinâmica de memória** com `malloc()` e `calloc()`
- **Ponteiros** e manipulação de dados via referência
- **Structs** e organização de dados estruturados
- **Funções modulares** para código organizado
- **Validações** de entrada e segurança
- **Números aleatórios** com `rand()` e `srand()`
- **Gerenciamento de memória** com `free()`
- **Simulação** de lógica de jogo complexa

---

## 🚀 Possíveis Melhorias Futuras

- Salvar/carregar estado do jogo em arquivo
- Suporte a múltiplos turnos com rodadas
- Histórico de batalhas
- Ranking de jogadores
- Modo AI com jogador controlado por computador
- Sistema de movimentação de tropas
- Visualização gráfica com ncurses ou SDL

---

## 📝 Autor

Desenvolvido como parte do desafio Aventureiro da disciplina de Estruturas de Dados.

**Versão**: 2.0  
**Data**: 2026  
**Linguagem**: C  
**Padrão**: C99+

---

## 📧 Contato e Suporte

Para dúvidas ou sugestões sobre este programa, verifique se:
- As bibliotecas necessárias estão instaladas
- O compilador GCC está disponível no sistema
- Todos os arquivos estão no mesmo diretório

---

** Bom jogo! 🎮 **
