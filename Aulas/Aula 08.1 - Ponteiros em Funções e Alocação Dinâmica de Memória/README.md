# 🚀 Aula 08.1 - Ponteiros em Funções e Alocação Dinâmica de Memória

## 📌 Objetivos das Aulas
Nestas semanas, você irá consolidar o uso de ponteiros em funções e aprender a gerenciar dinamicamente a memória com `malloc`, `calloc`, `realloc` e `free`.

### ✅ O que você aprenderá:
- Diferença entre passagem por valor e por referência.
- Como utilizar ponteiros para alterar valores em funções.
- Conceitos e usos da alocação dinâmica de memória.
- Utilização das funções `malloc`, `calloc`, `realloc` e `free`.
- Exercícios práticos e desafios com ponteiros e memória dinâmica.

---

## 📖 1. Passagem por Valor x Referência

### 📌 Passagem por Valor
```c
void dobrar(int x) {
    x = x * 2;
}

int main() {
    int num = 10;
    dobrar(num);
    printf("%d\n", num); 
}
```

### 📌 Passagem por Referência com Ponteiros
```c
void dobrar(int *x) {
    *x = *x * 2;
}

int main() {
    int num = 10;
    dobrar(&num);
    printf("%d\n", num); 
}
```

---

## 🛠️ 2. Funções com Ponteiros

### 📌 Trocar valores
```c
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

### 📌 Atualizar múltiplos valores
```c
void atualizar(int *idade, float *nota) {
    *idade = *idade + 1;
    *nota = *nota + 0.5;
}
```

### 📌 Maior valor entre dois
```c
void maior(int *a, int *b, int *resultado) {
    *resultado = (*a > *b) ? *a : *b;
}
```

---

## 🧠 3. Alocação Dinâmica de Memória

### 📌 Por que usar?
A alocação dinâmica permite:
- Criar vetores/matrizes em tempo de execução.
- Otimizar o uso da memória.
- Trabalhar com estruturas de dados mais flexíveis.

### 📌 Funções principais
```c
#include <stdlib.h>

int *vetor = malloc(n * sizeof(int));    // aloca memória
int *vetor2 = calloc(n, sizeof(int));    // aloca e zera
vetor = realloc(vetor, novo_tamanho);    // realoca
free(vetor);                             // libera
```
### 📘 Explicação Detalhada das Funções

#### `malloc(size)` – *Memory Allocation*
- Aloca um bloco de memória com o número de bytes especificado.
- Retorna um ponteiro para o início da memória alocada.
- O conteúdo da memória alocada **não é inicializado** (valores aleatórios).

```c
int *vetor = malloc(5 * sizeof(int));
```

#### `calloc(n, size)` – *Contiguous Allocation*
- Aloca memória para um vetor de `n` elementos, cada um com `size` bytes.
- Inicializa todos os bytes com zero.
- Retorna um ponteiro para a área de memória alocada.

```c
int *vetor = calloc(5, sizeof(int));
```

#### `realloc(ptr, new_size)` – *Reallocation*
- Redimensiona um bloco de memória previamente alocado com `malloc` ou `calloc`.
- Preserva os dados existentes (até o menor tamanho entre o antigo e o novo).
- Pode mover a memória para outro endereço (retorna novo ponteiro).

```c
vetor = realloc(vetor, 10 * sizeof(int));
```

#### `free(ptr)` – *Libera Memória*
- Libera a memória previamente alocada.
- Após o uso, deve-se liberar a memória com `free()` para evitar **vazamentos de memória**.

```c
free(vetor);
```

### 📌 Exemplo completo
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int *vetor = malloc(n * sizeof(int));

    if (vetor == NULL) {
        printf("Erro de alocação!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        vetor[i] = i * 2;
        printf("%d ", vetor[i]);
    }

    free(vetor);
    return 0;
}
```
Esse trecho ocorre quando o `malloc` falha em alocar a memória requisitada. Isso pode acontecer, por exemplo:
- Quando o sistema está com pouca memória RAM disponível;
- Quando é solicitada uma quantidade muito grande de memória;
- Quando há fragmentação da memória heap.

Em ambientes com restrições de alocação (como sistemas embarcados). O teste if (vetor == NULL) é uma boa prática de segurança para evitar que o programa continue usando um ponteiro inválido, o que poderia causar falhas graves, como segmentation faults.

---

## 📝 Exercícios para Desenvolver em Sala

### 1️⃣ Dobrar valor
```c
void dobrar(int *x);
```

### 2️⃣ Atualizar idade e altura
```c
void atualizar(int *idade, float *altura);
```

### 3️⃣ Maior entre dois números
```c
void maior(int *a, int *b, int *resultado);
```

### 4️⃣ Criar vetor dinamicamente
- Leia um valor `n`.
- Alocar vetor com `malloc`.
- Preencher com valores digitados.
- Calcular média dos valores.

### 5️⃣ Redimensionar vetor
- Peça novos dados e realoque o vetor com `realloc`.

---

## 🎯 Desafio para Casa

### 📌 Cadastro Dinâmico de Alunos
Crie um programa que:
- Pergunte quantos alunos deseja cadastrar.
- Aloca dinamicamente:
  - vetor de nomes (`char **nomes`)
  - vetor de idades (`int *idades`)
  - vetor de notas (`float *notas`)
- Após o cadastro, permita aplicar bônus (idade +1, nota +0.5) usando funções com ponteiros.
- Mostre os dados atualizados.
- Libere toda a memória alocada ao final.

---

## 📚 Recursos Adicionais
- 📘 Livro: "C Como Programar" – Deitel & Deitel
- 🎥 Vídeos:
  - [Ponteiros e Funções](https://www.youtube.com/watch?v=Ab9XMWZzvYk)
  - [malloc e calloc](https://www.youtube.com/watch?v=ICh3LG7mHZM)
- 🌐 Documentação: [Pointers & Dynamic Memory - cppreference](https://en.cppreference.com/w/c/memory)

---

## 🔥 Próxima Aula: Structs em C – Introdução a tipos personalizados

**💬 Dúvidas? Comente no repositório ou fale com o professor ou monitor!**
