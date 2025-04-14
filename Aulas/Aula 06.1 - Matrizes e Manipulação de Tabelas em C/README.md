# 🚀 Aula 06.1: Matrizes e Manipulação de Tabelas em C

## 📌 Objetivos da Aula
Nesta semana, vamos expandir o conceito de vetores e trabalhar com **matrizes** em C, que são estruturas bidimensionais muito utilizadas para representar tabelas, planilhas e dados tabulares em geral.

### ✅ O que você aprenderá:
- O que são matrizes e como são representadas na memória.
- Como declarar, inicializar e acessar elementos de uma matriz.
- Como percorrer uma matriz usando laços aninhados.
- Aplicações práticas: tabelas de notas, multiplicação de matrizes, busca e soma de elementos.

---

## 📖 1. O que é uma Matriz?
Uma **matriz** é uma coleção bidimensional de elementos do mesmo tipo, organizados em **linhas e colunas**.

### 📌 Declaração de matriz:
```c
int matriz[3][4]; // 3 linhas, 4 colunas
```

### 📌 Inicialização:
```c
int matriz[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

### 📌 Acesso aos elementos:
```c
printf("Elemento na posição [0][2]: %d\n", matriz[0][2]); // imprime 3
```

---

## 🔄 2. Preenchendo e exibindo matrizes com `for`
```c
#include <stdio.h>

int main() {
    int matriz[2][2];

    // Entrada de dados
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("Digite o valor para [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    // Exibição da matriz
    printf("\nMatriz digitada:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

---

## 📊 3. Aplicação Prática: Tabela de Notas
- Crie uma matriz `float notas[3][4]`, onde:
  - 3 = número de alunos
  - 4 = número de avaliações

- Calcule a média de cada aluno usando um laço adicional.

---

## 📝 Exercícios para Desenvolver em Sala

### 1️⃣ Matrizes fixas
- Crie uma matriz 3x3 com valores fornecidos pelo usuário.
- Exiba a matriz formatada.

### 2️⃣ Soma dos elementos
- Após preencher a matriz 3x3, calcule e exiba a **soma de todos os elementos**.

### 3️⃣ Média por linha
- Para uma matriz `float notas[3][4]`, calcule a média de cada aluno (linha).

### 4️⃣ Matrizes iguais
- Peça duas matrizes 2x2 ao usuário e diga se são **iguais ou diferentes**.

---

## 🎯 Desafio para Casa

### 📌 Sistema de Notas
- Crie um programa com uma matriz `float notas[3][2]` para armazenar **2 notas de 3 alunos**.
- Calcule a média de cada aluno.
- Mostre a tabela final com:
```
Aluno | Nota 1 | Nota 2 | Média
------|--------|--------|------
1     |  7.5   |  8.0   | 7.75
2     |  6.0   |  5.5   | 5.75
3     |  9.0   |  9.5   | 9.25
```

---

## 📚 Recursos Adicionais
- 📘 Livro: "Algoritmos em C" – Paulo Feofiloff
- 🎥 Vídeo: [Matrizes em C - Curso em Vídeo]([https://www.youtube.com/watch?v=Xu1sZbnTntM](https://www.youtube.com/watch?v=OPa3tY4ne38&pp=ygUfTWF0cml6ZXMgZW0gQyAtIEN1cnNvIGVtIFbDrWRlbw%3D%3D))
- 🌐 Documentação: [Matrizes em C - cppreference](https://en.cppreference.com/w/c/language/array)

---

## 🔥 Próxima Aula: Ponteiros e Endereçamento de Memória

**💡 Dúvidas? Comente no repositório ou fale com o professor ou monitor!**
