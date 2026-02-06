# 🎮 WAR GAME NOVATO - VERSÃO 1.0

## 📋 Descrição

O **WAR GAME Novato** é o primeiro passo na construção de um sistema de jogo de guerra em C. Este programa implementa um **sistema básico de cadastro e visualização de territórios**, focando em aprender os conceitos fundamentais de estruturas de dados (structs), vetores de structs e manipulação de entrada/saída.

O programa permite que o usuário:
- Cadastre 5 territórios com informações simples
- Visualize todos os territórios registrados
- Compreenda como organizar dados estruturados em C

---

## 🚀 Funcionalidades Principais

### 1. **Definição de Struct**
- Cria uma estrutura chamada `Territorio` com 3 campos
- Armazena informações de forma organizada
- Base para programas mais complexos

### 2. **Cadastro de Territórios**
- Interface amigável para entrada de dados
- Cadastra exatamente 5 territórios
- Coleta: nome, cor do exército e quantidade de tropas

### 3. **Visualização de Dados**
- Exibe todos os territórios após o cadastro
- Formatação clara com bordas visuais
- Apresentação organizada das informações

### 4. **Limpeza de Buffer**
- Remove quebras de linha após entrada de strings
- Remove buffer do stdin após entrada de inteiros
- Garante entrada de dados correta

---

## 📁 Estrutura do Código

### **Struct: Territorio**
```c
struct Territorio
{
    char nome[30];   // Nome do território (até 30 caracteres)
    char cor[10];    // Cor do exército (até 10 caracteres)
    int tropas;      // Quantidade de tropas
};
```

### **Funções Implementadas**

#### **`void cadastrarTerritorios(struct Territorio territorios[])`**
- Função que solicita informações do usuário
- Recebe um array de 5 estruturas
- Usa um loop `for` para preencher cada território
- Remove caracteres especiais de entrada com `strcspn()`
- Limpa o buffer com `getchar()` após ler inteiros

**Linha por linha:**
```c
fgets(territorios[i].nome, MAX_NOME, stdin);
// Lê até 30 caracteres (nome)

territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
// Remove a quebra de linha do final

scanf("%d", &territorios[i].tropas);
// Lê um inteiro

getchar();
// Remove a quebra de linha deixada por scanf()
```

#### **`void exibirTerritorios(struct Territorio territorios[])`**
- Exibe dados de todos os 5 territórios
- Usa formatação com `printf()` para criar bordas
- Mostra os dados em uma tabela visualmente agradável
- Loop `for` percorre todos os territórios

---

## 💻 Como Usar

### **Compilação**
```bash
gcc -o WarGame1novato WarGame1novato.c
```

Ou com avisos:
```bash
gcc -Wall -Wextra -o WarGame1novato WarGame1novato.c
```

### **Execução**
```bash
./WarGame1novato
```

No Windows:
```bash
WarGame1novato.exe
```

### **Passo a Passo de Uso**

1. **Inicialização**:
   - O programa exibe uma mensagem de boas-vindas formatada

2. **Cadastro de Territórios**:
   - Para cada um dos 5 territórios, digite:
     - Nome do território (ex: Brasil, França, Japão)
     - Cor do exército (ex: Vermelho, Azul, Verde)
     - Quantidade inicial de tropas (ex: 10, 15, 20)

3. **Visualização**:
   - Após o cadastro, o programa exibe todos os 5 territórios
   - Cada território é mostrado em uma caixa formatada

4. **Encerramento**:
   - O programa exibe mensagem de conclusão

---

## 📊 Exemplo de Execução

```
╔════════════════════════════════════════════════╗
║      BEM-VINDO AO SISTEMA DE TERRITÓRIOS      ║
║           JOGO DE GUERRA - VERSÃO 1.0         ║
╚════════════════════════════════════════════════╝

╔════════════════════════════════════════════════╗
║       CADASTRO DE TERRITÓRIOS - 5 REGIÕES      ║
╚════════════════════════════════════════════════╝

--- Território 1 de 5 ---
Digite o nome do território: Brasil
Digite a cor do exército: Vermelho
Digite a quantidade de tropas: 10

--- Território 2 de 5 ---
Digite o nome do território: Argentina
Digite a cor do exército: Azul
Digite a quantidade de tropas: 8

--- Território 3 de 5 ---
Digite o nome do território: Chile
Digite a cor do exército: Verde
Digite a quantidade de tropas: 6

--- Território 4 de 5 ---
Digite o nome do território: Colômbia
Digite a cor do exército: Amarelo
Digite a quantidade de tropas: 7

--- Território 5 de 5 ---
Digite o nome do território: Peru
Digite a cor do exército: Roxo
Digite a quantidade de tropas: 9

╔════════════════════════════════════════════════╗
║        TERRITÓRIOS CADASTRADOS - RESUMO        ║
╚════════════════════════════════════════════════╝

┌────────────────────────────────────────────┐
│ Território 1                              │
├────────────────────────────────────────────┤
│ Nome:  Brasil                              │
│ Cor:   Vermelho                            │
│ Tropas: 10                                 │
└────────────────────────────────────────────┘

[... mais territórios ...]

╔════════════════════════════════════════════════╗
║              PROGRAMA FINALIZADO               ║
╚════════════════════════════════════════════════╝
```

---

## 🔧 Requisitos Técnicos Implementados

### **Bibliotecas Utilizadas**
| Biblioteca | Função |
|-----------|--------|
| `stdio.h` | `printf()`, `scanf()`, `fgets()` |
| `stdlib.h` | Funções gerais (malloc, free, rand) |
| `string.h` | `strcspn()` para manipular strings |

### **Constantes Definidas**
```c
#define MAX_TERRITORIOS 5     // Fixa em 5 territórios
#define MAX_NOME 30          // Tamanho máximo do nome
#define MAX_COR 10           // Tamanho máximo da cor
```

### **Técnicas Utilizadas**
- ✅ Struct para organização de dados
- ✅ Vetores de structs
- ✅ Loops `for` para repetição
- ✅ Entrada com `scanf()` e `fgets()`
- ✅ Formatação de strings com `printf()`
- ✅ Limpeza de buffer com `getchar()`
- ✅ Remoção de quebras de linha com `strcspn()`

---

## 📚 Conceitos Aprendidos

Este programa ensina:

### **1. Estruturas de Dados (Structs)**
```c
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};
// Agrupa dados relacionados em uma única entidade
```

### **2. Vetores de Structs**
```c
struct Territorio territorios[5];
// Array de 5 estruturas do tipo Territorio
// Acessar campo: territorios[i].nome
```

### **3. Entrada de Dados**
```c
fgets(territorios[i].nome, MAX_NOME, stdin);
// Lê string do usuário com limite de caracteres
scanf("%d", &territorios[i].tropas);
// Lê inteiro do usuário
```

### **4. Manipulação de Strings**
```c
territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
// Remove caractere de quebra de linha ('\n') da string
```

### **5. Formatação de Saída**
```c
printf("│ Nome:  %-35s │\n", territorios[i].nome);
// %-35s = alinha à esquerda em 35 caracteres
```

---

## ⚠️ Pontos Importantes

### **Buffer de Entrada**
O programa remove quebras de linha após cada entrada para evitar problemas:
```c
fgets(...);  // Lê string (deixa \n no buffer)
nome[strcspn(nome, "\n")] = '\0';  // Remove \n

scanf(...);  // Lê inteiro (deixa \n no buffer)
getchar();   // Remove \n
```

### **Tamanho Fixo**
- O programa sempre cadastra 5 territórios
- Limite de 30 caracteres para nome
- Limite de 10 caracteres para cor
- Evita complicações para iniciantes

### **Segurança de Strings**
- `fgets()` evita buffer overflow ao especificar tamanho máximo
- `strcspn()` encontra quebra de linha de forma segura

---

## 🎓 Próximos Passos

Após dominar este programa, você pode aprender:
- **Alocação dinâmica de memória** (malloc, calloc)
- **Ponteiros** para manipulação de dados
- **Simulação de ataques** entre territórios
- **Menus interativos** com múltiplas opções
- **Números aleatórios** (rand, srand)

Veja o programa **WarGame2_aventureiro.c** para evolução com estes conceitos!

---

## 🏗️ Estrutura de Arquivos

```
Entrega desafios/
└── WarsGame/
    └── Novato/
        ├── WarGame1novato.c           (código fonte)
        ├── README_WarsGame_novato1.md (este arquivo)
        └── output/
            └── WarGame1novato.exe     (programa compilado)
```

---

## 📝 Informações do Programa

| Aspecto | Detalhes |
|--------|----------|
| **Nome** | War Game - Nível Novato |
| **Versão** | 1.0 |
| **Idioma** | C (C99+) |
| **Tipo** | Console Application |
| **Entrada** | Teclado (stdin) |
| **Saída** | Terminal (stdout) |
| **Memória** | Alocação estática |
| **Tempo Aprox.** | 2-3 minutos de execução |

---

## 🐛 Solução de Problemas

### **Problema: "Fgets não funciona após scanf"**
**Solução**: Use `getchar()` para limpar o buffer após `scanf()`:
```c
scanf("%d", &variavel);
getchar();  // Remove \n deixado por scanf
```

### **Problema: "String saiu cortada"**
**Solução**: Comprimento de fgets deve ser maior que a entrada esperada:
```c
fgets(nome, MAX_NOME, stdin);  // MAX_NOME >= comprimento esperado
```

### **Problema: Compilação com erro**
**Verificar**:
- Todas as bibliotecas estão incluídas?
- Sintaxe correta de structs?
- Chaves e parênteses fechados?

---

## 📖 Referências de Funções

```c
// Entrada/Saída
printf(format, ...);      // Exibe formatado
scanf(format, &var);      // Lê do teclado
fgets(str, n, stdin);     // Lê string com limite

// Strings
strcspn(str, set);        // Encontra posição de caractere
strcpy(dest, src);        // Copia string

// Loops e Controle
for (int i = 0; i < n; i++)    // Loop com índice
```

---

## ✅ Checklist de Funcionalidades

- ✅ Programa compila sem erros
- ✅ Cadastra 5 territórios
- ✅ Lê entrada do usuário corretamente
- ✅ Exibe dados de forma formatada
- ✅ Remove caracteres indesejados
- ✅ Código bem comentado
- ✅ Nomes descritivos de variáveis

---

**Desenvolvido como parte do desafio Novato da disciplina de Estruturas de Dados.**
