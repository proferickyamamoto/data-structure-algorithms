# 🧑‍🏫 Aula 10.2: Structs com Vetores e Ponteiros (Revisão)

## 🎯 Objetivos da Semana

* Compreender o uso de `struct` com vetores.
* Utilizar ponteiros para manipulação de dados compostos.
* Aplicar `malloc` para alocação dinâmica de memória.
* Implementar cadastro e exibição de alunos com múltiplas notas.

---

## 🧠 Fundamento Teórico

### 🔹 Structs e Arrays

Uma `struct` permite agrupar dados de tipos diferentes sob um único nome. Quando usamos um vetor de `structs`, temos a capacidade de armazenar vários registros semelhantes em sequência de memória.

### 🔹 Ponteiros para Struct

Um ponteiro para `struct` armazena o endereço da estrutura e permite acessar seus campos usando `->`. Isso é útil para passagem por referência, alocação dinâmica e modularização.

### 🔹 Alocação Dinâmica de Structs

Com `malloc(n * sizeof(struct Aluno))` estamos alocando dinamicamente memória para um vetor de `n` structs do tipo `Aluno`. Cada struct `Aluno` ocupa um espaço fixo na memória (dependente dos seus campos), e a função `sizeof(struct Aluno)` calcula esse tamanho em bytes. Ao multiplicar esse valor por `n`, determinamos quantos bytes precisamos no total. A função `malloc` retorna um ponteiro para o início desse bloco de memória alocado. Isso permite que, mesmo sem saber quantos alunos o programa irá armazenar no momento da compilação, seja possível definir e utilizar o vetor de alunos em tempo de execução. É importante sempre verificar se o retorno de `malloc` é diferente de `NULL`, indicando sucesso na alocação. Além disso, ao final do uso, deve-se liberar a memória com `free` para evitar vazamento de memória.

---

## 📘 Exemplo Prático (passo a passo)

### Contexto:

Criação de um sistema simples para cadastro de alunos, onde cada aluno possui 3 notas. A quantidade de alunos será informada pelo usuário.

### 🔹 Etapa 1: Inclusão das bibliotecas necessárias

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

Essas bibliotecas permitem:

* `stdio.h`: entrada e saída padrão (ex: `printf`, `scanf`)
* `stdlib.h`: funções como `malloc`, `free`, `EXIT_FAILURE`
* `string.h`: manipulação de strings (não usada neste exemplo, mas comum para `strcpy`, etc)

### 🔹 Etapa 2: Definição da struct Aluno

```c
struct Aluno {
    int rm;
    char nome[30];
    float notas[3];
};
```

Agrupamos os dados de um aluno: RM (registro), nome e um vetor de 3 notas.

### 🔹 Etapa 3: Solicitação da quantidade de alunos e alocação dinâmica

```c
int n;
printf("Quantos alunos na turma? ");
scanf("%d", &n);

struct Aluno *turma = malloc(n * sizeof *turma);
if (!turma) {
    perror("malloc falhou");
    return EXIT_FAILURE;
}
```

O usuário informa quantos alunos serão cadastrados (`n`). Alocamos memória para esse número de alunos usando `malloc(n * sizeof(struct Aluno))`, que calcula a quantidade de memória necessária multiplicando o número de alunos `n` pelo tamanho de cada struct `Aluno`. Por exemplo:

```c
int n = 3;
struct Aluno *turma = malloc(n * sizeof(struct Aluno));
```

Se `sizeof(struct Aluno)` for 40 bytes, então `malloc(3 * 40)` irá alocar 120 bytes. Isso garante espaço suficiente para armazenar todos os alunos. O ponteiro `turma` aponta para o início dessa área na memória. `malloc`. Se a alocação falhar, mostramos erro e encerramos o programa.

### 🔹 Etapa 4: Leitura dos dados de cada aluno

```c
for (int i = 0; i < n; i++) {
    printf("
🖋️ Aluno %d:
", i + 1);
    printf("RM: ");
    scanf("%d", &(turma[i].rm));

    printf("Nome: ");
    scanf(" %29[^
]", turma[i].nome);
```

Aqui, para cada aluno:

* Lemos o RM com `scanf("%d", ...)`.
* Lemos o nome com até 29 caracteres (usando o especificador ` %29[^
  ]` que consome espaços em branco e até nova linha).

```c
    for (int j = 0; j < 3; j++) {
        printf("Nota %d: ", j + 1);
        scanf("%f", &(turma[i].notas[j]));
    }
}
```

Esse laço interno coleta as 3 notas do aluno e armazena no vetor `notas[3]`.

### 🔹 Etapa 5: Exibição dos dados com média calculada

```c
printf("
🌟 Lista final de alunos:
");
for (int i = 0; i < n; i++) {
    float soma = 0;
    for (int j = 0; j < 3; j++) {
        soma += turma[i].notas[j];
    }
    float media = soma / 3;
```

Para cada aluno, somamos as 3 notas e calculamos a média. Em seguida:

```c
    printf("%d – RM:%d Nome:%s Média:%.2f
",
           i + 1, turma[i].rm, turma[i].nome, media);
}
```

Exibimos os dados formatados, incluindo a média com 2 casas decimais.

### 🔹 Etapa 6: Liberação da memória alocada

```c
free(turma);
return 0;
```

Libera a memória alocada dinamicamente com `free` e encerra o programa com sucesso.

### Contexto:

Criação de um sistema simples para cadastro de alunos, onde cada aluno possui 3 notas. A quantidade de alunos será informada pelo usuário.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Definição da estrutura Aluno
struct Aluno {
    int rm;            // Registro do aluno
    char nome[30];     // Nome do aluno
    float notas[3];    // Três notas
};

int main() {
    int n;
    printf("Quantos alunos na turma? ");
    scanf("%d", &n);

    // 2. Alocação dinâmica do vetor de structs
    struct Aluno *turma = malloc(n * sizeof *turma);
    if (!turma) {
        perror("malloc falhou");
        return EXIT_FAILURE;
    }

    // 3. Leitura dos dados dos alunos
    for (int i = 0; i < n; i++) {
        printf("\n🖋️ Aluno %d:\n", i + 1);
        printf("RM: ");
        scanf("%d", &(turma[i].rm));

        printf("Nome: ");
        scanf(" %29[^\n]", turma[i].nome); // lê até 29 caracteres ou nova linha

        for (int j = 0; j < 3; j++) {
            printf("Nota %d: ", j + 1);
            scanf("%f", &(turma[i].notas[j]));
        }
    }

    // 4. Cálculo da média e exibição
    printf("\n🌟 Lista final de alunos:\n");
    for (int i = 0; i < n; i++) {
        float soma = 0;
        for (int j = 0; j < 3; j++) {
            soma += turma[i].notas[j];
        }
        float media = soma / 3;

        printf("%d – RM:%d Nome:%s Média:%.2f\n",
               i + 1, turma[i].rm, turma[i].nome, media);
    }

    // 5. Liberação de memória
    free(turma);
    return 0;
}
```

---

## 🧪 Atividade em Sala (individual ou dupla)

Crie um programa que:

* Cadastre até 5 alunos.
* Cada aluno deve ter: `rm`, `nome` (até 20 caracteres) e `media`.
* Os dados devem ser armazenados em um vetor de structs.
* Exibir os dados com uma função `void exibir(struct Aluno *a, int n)`.

### Sugestão de struct:

```c
struct Aluno {
    int rm;
    char nome[20];
    float media;
};
```

---

## 🏠 Tarefa para Casa

Faça uma versão dinâmica (com `malloc`) da atividade em sala:

* Solicitar `n` ao usuário.
* Alocar memória para `n` alunos.
* Ler `rm`, `nome` e três notas.
* Calcular média e armazenar.
* Exibir os dados com uma função.
* Liberar memória ao final com `free()`.

---

## 🚩 Desafio (com base no conteúdo)

Crie um programa que:

1. Solicite a quantidade de alunos (`n`).
2. Aloca dinamicamente `n` structs.
3. Receba nome, RM e 3 notas por aluno.
4. Calcule a média de cada aluno.
5. Ordene os alunos por média (decrescente).
6. Exiba o "Top 3 alunos da turma".
7. Implemente busca binária por RM (supondo vetor ordenado).
8. Permita buscar um aluno pelo RM digitado e exibir seus dados.

---

## 📚 Referências

* [https://www.geeksforgeeks.org/c/c-array-of-structure/](https://www.geeksforgeeks.org/c/c-array-of-structure/)
* [https://www.programiz.com/c-programming/c-structures-pointers](https://www.programiz.com/c-programming/c-structures-pointers)
* [https://www.geeksforgeeks.org/c/how-to-create-dynamic-array-of-structs-in-c/](https://www.geeksforgeeks.org/c/how-to-create-dynamic-array-of-structs-in-c/)
