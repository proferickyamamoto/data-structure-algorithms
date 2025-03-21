# 🚀 Aula 03.1: Estruturas Condicionais e Laços de Repetição em C

## 📌 Objetivos da Aula
Nesta semana, vamos aprender sobre **estruturas de decisão** e **laços de repetição**, fundamentais para a construção de algoritmos dinâmicos e interativos.

### ✅ O que você aprenderá:
- Como tomar decisões no código usando `if`, `else`, `else if` e `switch`.
- Como repetir instruções com `for`, `while` e `do-while`.
- Diferenças entre os tipos de laços de repetição.
- Aplicações práticas das estruturas condicionais e dos loops.
- Como funciona o operador `&` e sua importância na função `scanf()`.
- Exercícios práticos para fixar o conteúdo.

---

## 📂 Estrutura da Aula

### 📌 1. Estruturas Condicionais (`if`, `else`, `else if`)
As estruturas condicionais permitem que o código **tome decisões** com base em certas condições.

#### 📌 Exemplo – Uso do `if` e `else`
```c
#include <stdio.h>

int main() {
    int idade;
    printf("Digite sua idade: ");
    scanf("%d", &idade); // O & passa o endereço da variável para scanf()

    if (idade >= 18) {
        printf("Você é maior de idade.\n");
    } else {
        printf("Você é menor de idade.\n");
    }
    return 0;
}
```

Explicação:
- `int idade;` → Declara a variável `idade` para armazenar um número inteiro.
- `printf("Digite sua idade: ");` → Exibe a mensagem pedindo entrada do usuário.
- `scanf("%d", &idade);` → Captura o número digitado e armazena em `idade`.
   - `%d` → Indica que será lido um número inteiro.
   - `&idade` → Passa o **endereço de memória** da variável para `scanf()`.
   - Sem o `&`, o programa pode apresentar erro de segmentação.
- `if (idade >= 18) {...}` → Verifica se a idade é maior ou igual a 18.
- `else {...}` → Executa outra ação se a idade for menor que 18.

#### 📌 Exemplo – Uso do `else if`
```c
#include <stdio.h>

int main() {
    int nota;
    printf("Digite sua nota: ");
    scanf("%d", &nota);

    if (nota >= 90) {
        printf("Aprovado com excelência!\n");
    } else if (nota >= 70) {
        printf("Aprovado!\n");
    } else {
        printf("Reprovado!\n");
    }
    return 0;
}
```

Explicação:
- `if (nota >= 90)`: Se a nota for **90 ou mais**, exibe "Aprovado com excelência".
- `else if (nota >= 70)`: Se a nota estiver entre **70 e 89**, exibe "Aprovado".
- `else`: Qualquer nota abaixo de **70** resulta em "Reprovado".

---

### 📌 2. Estruturas Condicionais (`switch`)
O `switch` é utilizado quando temos **múltiplas condições** para um mesmo valor.

#### 📌 Exemplo – Uso do `switch`
```c
#include <stdio.h>

int main() {
    int opcao;
    printf("Escolha uma opção (1-3): ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Opção 1 escolhida.\n");
            break;
        case 2:
            printf("Opção 2 escolhida.\n");
            break;
        case 3:
            printf("Opção 3 escolhida.\n");
            break;
        default:
            printf("Opção inválida.\n");
    }
    return 0;
}
```

Explicação:
- `case 1:` → Se o usuário escolher `1`, exibe "Opção 1 escolhida".
- `case 2:` → Se for `2`, exibe "Opção 2 escolhida".
- `case 3:` → Se for `3`, exibe "Opção 3 escolhida".
- `default:` → Se o usuário digitar qualquer outro número, exibe "Opção inválida".

---

### 📌 3. Laços de Repetição (`for`, `while`, `do-while`)
Os **loops** permitem repetir instruções várias vezes, facilitando a automação de tarefas repetitivas.

#### 📌 Exemplo – Uso do `for`
```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 5; i++) {
        printf("Número: %d\n", i);
    }
    return 0;
}
```
Explicação:
- `for (int i = 1; i <= 5; i++)`: O loop **inicia em 1** e **vai até 5**.
- `printf("Número: %d\n", i)`: Exibe o número atual a cada repetição.

#### 📌 Exemplo – Uso do `while`
```c
#include <stdio.h>

int main() {
    int contador = 1;
    while (contador <= 5) {
        printf("Número: %d\n", contador);
        contador++;
    }
    return 0;
}
```
Explicação:
- O loop **continua executando enquanto** `contador <= 5`.
- `contador++` **incrementa o valor** até atingir `5`.

#### 📌 Exemplo – Uso do `do-while`
```c
#include <stdio.h>

int main() {
    int numero;
    do {
        printf("Digite um número positivo: ");
        scanf("%d", &numero);
    } while (numero <= 0);

    printf("Você digitou um número positivo: %d\n", numero);
    return 0;
}
```
Explicação:
- O bloco **`do`** sempre executa pelo menos uma vez, independentemente da condição.
- O `while (numero <= 0);` impede que valores negativos sejam aceitos.

---

## 📝 Exercícios para Desenvolver em Sala

### 1️⃣ **Simulador de Notas Escolares**
Crie um programa que:
- Peça ao usuário sua nota.
- Exiba a classificação conforme a tabela abaixo:
  - **90 a 100** → Aprovado com excelência
  - **70 a 89** → Aprovado
  - **Menos de 70** → Reprovado

### 2️⃣ **Contagem Progressiva e Regressiva**
Crie um programa que:
- Use um **loop `for`** para contar de **1 a 10**.
- Depois, use um **loop `while`** para contar de **10 a 1**.

### 3️⃣**Tabuada de um Número**
Crie um programa que:
- Peça um número ao usuário.
- Exiba a tabuada de **1 a 10** desse número usando um **loop `for`**.

### 4️⃣ **Calculadora Simples**
- Peça dois números e uma operação (soma, subtração, multiplicação, divisão).
- Use `switch` para realizar a operação.

---

## 🎯 Desafio para Casa

### 📌 Jogo de Adivinhação
Crie um programa que gere um número aleatório entre **1 e 10** e peça ao usuário para adivinhar:
- Se o usuário acertar, exiba "Parabéns, você acertou!".
- Se errar, informe "Tente novamente!" e continue pedindo até acertar.
- Utilize `do-while` para repetir a entrada até que o usuário acerte.

Dica: Use a biblioteca `<stdlib.h>` e a função `rand()` para gerar números aleatórios.
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int numeroSecreto = rand() % 10 + 1; // Número entre 1 e 10
    int tentativa;

    do {
        printf("Adivinhe o número (1 a 10): ");
        scanf("%d", &tentativa);

        if (tentativa != numeroSecreto) {
            printf("Errado! Tente novamente.\n");
        }
    } while (tentativa != numeroSecreto);

    printf("Parabéns, você acertou!\n");
    return 0;
}
```

---
## 📚 Recursos Adicionais
- 📖 **Livro:** "The C Programming Language" – Brian Kernighan e Dennis Ritchie.
- 🎥 **Vídeo:** [Playlist de C no YouTube](https://www.youtube.com/watch?v=3Xq4sPu6vKA).
- 🌎 **Documentação:** [C Programming Reference](https://en.cppreference.com/w/).

---

## 🔥 Próxima Aula: **Funções e Modularização**

**💡 Dúvidas? Comente no repositório ou pergunte no grupo de estudos!** 🌟

---
📝 Autor: **Prof. Erick Toshio Yamamoto**
📅 Data: 19/03/2025
📌 Disciplina: Data Structure and Algorithms
