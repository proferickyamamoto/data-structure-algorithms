# 🚀 Aula 02.1: Variáveis, Tipos de Dados e Operadores em C

## 📌 Objetivos da Aula
Nesta semana, vamos aprender sobre **como armazenar e manipular dados** em C usando variáveis e operadores.

### ✅ O que você aprenderá:
- O que são variáveis e como declára-las.
- Tipos de dados e seus tamanhos.
- Entrada e saída de dados (`printf()` e `scanf()`).
- Operadores matemáticos, relacionais e lógicos.
- Exercícios práticos para fixar o conteúdo.

---

## 📚 Conteúdo da Aula

### 📌 1. O que são Variáveis?
- Variáveis são **espaços na memória** usados para armazenar valores.
- Cada variável tem um **tipo de dado** associado (inteiro, decimal, caractere etc.).
- **Regras para nomear variáveis:**
  - Deve começar com uma **letra ou `_`**.
  - Não pode conter **espaços** ou caracteres especiais.
  - Sensível a **maiúsculas/minúsculas** (`idade` ≠ `Idade`).

#### Exemplo de declaração e inicialização de variáveis:
```c
int idade = 20;       // Número inteiro
float altura = 1.75;  // Número decimal
char inicial = 'A';   // Caractere único
```

---

### 📌 2. Tipos de Dados em C
| Tipo        | Tamanho (bytes) | Exemplo       |
|------------|----------------|---------------|
| `int`      | 4              | 10, -5, 100   |
| `float`    | 4              | 3.14, -2.5    |
| `double`   | 8              | 3.14159265    |
| `char`     | 1              | 'A', 'z'      |

#### Exemplo de uso:
```c
#include <stdio.h>

int main() {
    int idade = 25;
    float altura = 1.75;
    char inicial = 'M';

    printf("Idade: %d anos\n", idade);
    printf("Altura: %.2f metros\n", altura);
    printf("Inicial do nome: %c\n", inicial);
    return 0;
}
```

---

### 📌 3. Especificadores de Formato no printf() e scanf()

Os **especificadores de formato** são usados para exibir e capturar valores corretamente.

| Especificador | Tipo de Dado | Exemplo |
|--------------|--------------|---------------|
| `%d`, `%i`   | `int` (inteiros) | `printf("%d", 42);` |
| `%f`         | `float` (decimais) | `printf("%.2f", 3.14);` |
| `%lf`        | `double` (mais precisão) | `printf("%lf", 3.1415);` |
| `%c`         | `char` (caracteres) | `printf("%c", 'A');` |
| `%s`         | `char[]` (strings) | `printf("%s", "Texto");` |

#### 📌 Exemplo – Uso em printf()

```c
#include <stdio.h>

int main() {
    int idade = 25;
    float altura = 1.75;
    char inicial = 'M';
    char nome[] = "João";

    printf("Idade: %d anos\n", idade);
    printf("Altura: %.2f metros\n", altura);
    printf("Inicial do nome: %c\n", inicial);
    printf("Nome: %s\n", nome);
    return 0;
}
```

#### 📌 Exemplo – Uso em scanf()
```c
#include <stdio.h>

int main() {
    int idade;
    float peso;
    char nome[50];

    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Digite sua idade: ");
    scanf("%d", &idade);
    printf("Digite seu peso: ");
    scanf("%f", &peso);

    printf("Nome: %s, Idade: %d, Peso: %.2f kg\n", nome, idade, peso);
    return 0;
}
```
#### ⚠ Atenção: O scanf("%s", nome); não captura espaços em branco. Para ler strings com espaços, use fgets().
```c
fgets(nome, 50, stdin);
```

---

### 📌 4. Operadores em C

#### 🔋 4.1 Operadores Aritméticos
| Operador | Operação      | Exemplo (`a = 5, b = 2`) |
|----------|--------------|--------------------------|
| `+`      | Adição       | `a + b` → `7`   |
| `-`      | Subtração    | `a - b` → `3`   |
| `*`      | Multiplicação | `a * b` → `10`  |
| `/`      | Divisão      | `a / b` → `2` (inteiro) |
| `%`      | Módulo (resto) | `a % b` → `1`  |

#### Exemplo de uso:
```c
#include <stdio.h>

int main() {
    int a = 10, b = 3;
    printf("Soma: %d\n", a + b);
    printf("Subtração: %d\n", a - b);
    printf("Multiplicação: %d\n", a * b);
    printf("Divisão: %d\n", a / b);
    printf("Resto da divisão: %d\n", a % b);
    return 0;
}
```
#### 🔋 4.2 Operadores Aritméticos - Divisão com `float`

Quando realizamos uma **divisão em C**, devemos garantir que pelo menos um dos operandos seja `float`, caso contrário, a divisão pode resultar em um número inteiro.

#### 📌 Exemplo – Divisão Correta entre `float`
```c
#include <stdio.h>

int main() {
    float num1 = 5.0, num2 = 2.0;
    float resultado = num1 / num2;

    printf("Resultado: %.2f\n", resultado); // Exibe 2.50
    return 0;
}
```

#### 📌 Problema – Divisão de `int` Retornando Valor Incorreto
```c
#include <stdio.h>

int main() {
    int a = 5, b = 2;
    float resultado = a / b; // Problema: resultado será 2, não 2.50

    printf("Resultado incorreto: %.2f\n", resultado);
    return 0;
}
```
✅ **Solução:** Converter um dos operandos para `float`:
```c
float resultado = (float) a / b;
```
📌 **Exemplo Corrigido:**
```c
#include <stdio.h>

int main() {
    int a = 5, b = 2;
    float resultado = (float) a / b;

    printf("Resultado correto: %.2f\n", resultado); // Exibe 2.50
    return 0;
}
```


---

## 📝 Exercícios Práticos

### 📈 **1. Calculadora Simples**
Crie um programa que solicite dois números ao usuário e exiba:
- Soma
- Subtração
- Multiplicação
- Divisão

### 👥 **2. Comparando Idades**
Solicite a idade de duas pessoas e exiba:
- Quem é mais velho
- Se as idades são iguais

### 🎯 **3. Par ou Ímpar?**
Peça um número ao usuário e exiba se ele é **par ou ímpar**.

---
## 🎯 Desafio para Casa

### 📌 Calculadora de IMC (Índice de Massa Corporal)

Crie um programa que solicite ao usuário seu peso e altura e calcule seu IMC, usando a fórmula:

IMC = peso / (altura * altura)

Após calcular o IMC, exiba a classificação com base nos seguintes critérios:

Abaixo de 18.5 → Abaixo do peso

Entre 18.5 e 24.9 → Peso normal

Entre 25 e 29.9 → Sobrepeso

30 ou mais → Obesidade

---
## 📚 Recursos Adicionais
- 📖 **Livro:** "The C Programming Language" – Brian Kernighan e Dennis Ritchie.
- 📹 **Vídeo:** [Playlist de C no YouTube](https://www.youtube.com/watch?v=3Xq4sPu6vKA).
- 🌐 **Documentação:** [C Programming Reference](https://en.cppreference.com/w/).

---

## 🔥 Próxima Aula: **Estruturas Condicionais e Laços de Repetição**

**💡 Dúvidas? Comente no repositório ou pergunte no grupo de estudos!** 🌟

---
📝 Autor: **Prof. Erick Toshio Yamamoto**
📅 Data: 14/03/2025
📌 Disciplina: Data Structure and Algorithms
