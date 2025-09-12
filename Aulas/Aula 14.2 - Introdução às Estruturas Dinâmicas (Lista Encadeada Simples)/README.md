# Aula 14.2: Introdução às Estruturas Dinâmicas (Lista Encadeada Simples)

## 🎯 Objetivos

* Entender a motivação de **estruturas dinâmicas** frente a vetores estáticos/dinâmicos.
* Definir o conceito de **nó (node)** e ponteiro para o próximo.
* Implementar operações básicas em uma **lista simplesmente encadeada**:

  * Inserção no início.
  * Inserção no fim.
  * Percorrer e imprimir.
* Visualizar a relação entre **ponteiros** e memória.

---

## 🧠 Fundamento Teórico

* **Vetor (array):** ocupa memória contínua → acesso rápido `O(1)`, mas **custo alto** para inserir/remover no meio (precisa deslocar elementos).
* **Lista encadeada:** cada elemento (nó) guarda **dados + ponteiro para o próximo**.

  * Ocupa memória **não-contínua**.
  * Cresce/encolhe dinamicamente.
  * Inserções/remoções locais podem ser **O(1)**.
  * Percorrer a lista → custo **O(n)**.

---

## 🧱 Estrutura de Dados (em C)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;           // dado armazenado
    struct No *prox;     // ponteiro para o próximo nó
} No;
```

* Cada nó contém um valor (`int`) e um ponteiro para o próximo nó (`No*`).
* O ponteiro inicial da lista é chamado de **cabeça** (*head*).

---

## 💻 Exemplo Passo-a-Passo

### 1. Criar lista vazia

```c
No *head = NULL; // lista inicialmente vazia
```

### 2. Inserir no início

```c
void inserirInicio(No **head, int valor) {
    No *novo = malloc(sizeof(No));
    if (!novo) { perror("malloc"); exit(1); }
    novo->valor = valor;
    novo->prox = *head;   // aponta para o antigo primeiro
    *head = novo;         // atualiza o head
}
```

### 3. Inserir no fim

```c
void inserirFim(No **head, int valor) {
    No *novo = malloc(sizeof(No));
    if (!novo) { perror("malloc"); exit(1); }
    novo->valor = valor;
    novo->prox = NULL;

    if (*head == NULL) { // lista vazia
        *head = novo;
    } else {
        No *tmp = *head;
        while (tmp->prox != NULL) tmp = tmp->prox; // vai até o último
        tmp->prox = novo;
    }
}
```

### 4. Percorrer e imprimir

```c
void imprimir(No *head) {
    No *tmp = head;
    while (tmp != NULL) {
        printf("%d -> ", tmp->valor);
        tmp = tmp->prox;
    }
    printf("NULL\n");
}
```

### 5. Liberar memória

```c
void liberar(No *head) {
    while (head != NULL) {
        No *tmp = head;
        head = head->prox;
        free(tmp);
    }
}
```

---

## 🧪 Programa de Demonstração

```c
int main(void) {
    No *lista = NULL;  // lista vazia

    inserirInicio(&lista, 10);
    inserirInicio(&lista, 20);
    inserirFim(&lista, 30);

    imprimir(lista); // esperado: 20 -> 10 -> 30 -> NULL

    liberar(lista);
    return 0;
}
```

---

## 📌 Atividade em Sala

1. Implemente uma lista encadeada de inteiros.
2. Teste inserindo:

   * 2 valores no início,
   * 3 valores no fim.
3. Imprima a lista após cada inserção.
4. Explique (em grupo) a diferença entre lista e vetor quanto a:

   * Inserção no meio,
   * Acesso direto por índice.

---

## 🏠 Desafio para Casa

* Expanda a lista para permitir **remoção do início** e **remoção do fim**.
* Escreva uma função `buscar(No *head, int valor)` que retorna:

  * Ponteiro para o nó se encontrado,
  * `NULL` caso contrário.
* Teste com valores existentes e não existentes.
* Faça um desenho mostrando os ponteiros após cada operação.

---

## 📚 Referências

* KERNIGHAN, B.; RITCHIE, D. *C Programming Language*.
* [GeeksforGeeks – Linked List](https://www.geeksforgeeks.org/data-structures/linked-list/)
* [Programiz – Linked List in C](https://www.programiz.com/dsa/linked-list)


