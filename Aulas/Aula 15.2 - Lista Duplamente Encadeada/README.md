# Aula 15.2: Lista Duplamente Encadeada

## 🎯 Objetivos

* Entender a diferença entre **lista simples** e **lista duplamente encadeada**.
* Aprender a estruturar um nó com ponteiros para **próximo** e **anterior**.
* Implementar operações básicas:

  * Inserir no início e no fim.
  * Percorrer da esquerda → direita e da direita → esquerda.
  * Remover nós.
* Visualizar ganhos práticos dessa estrutura.

---

## 🧠 Fundamento Teórico

* **Lista simples:** cada nó aponta apenas para o próximo.
* **Lista dupla:** cada nó aponta para o próximo **e** para o anterior.

  * Facilita percorrer para trás.
  * Remoções no meio podem ser feitas sem percorrer desde o início.
* **Custo extra:** cada nó gasta mais memória (2 ponteiros).
* **Complexidade:**

  * Inserção/remoção locais: O(1).
  * Busca: O(n).

---

## 🧱 Estrutura do Nó

```c
typedef struct No {
    int valor;
    struct No *ant;   // ponteiro para anterior
    struct No *prox;  // ponteiro para próximo
} No;
```

---

## 💻 Exemplo Passo a Passo

### Inserir no início

```c
void inserirInicio(No **head, int valor) {
    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->ant = NULL;
    novo->prox = *head;
    if (*head != NULL) (*head)->ant = novo;
    *head = novo;
}
```

### Inserir no fim

```c
void inserirFim(No **head, int valor) {
    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    if (*head == NULL) {
        novo->ant = NULL;
        *head = novo;
        return;
    }
    No *tmp = *head;
    while (tmp->prox != NULL) tmp = tmp->prox;
    tmp->prox = novo;
    novo->ant = tmp;
}
```

### Imprimir na ordem normal

```c
void imprimir(No *head) {
    No *tmp = head;
    while (tmp != NULL) {
        printf("%d <-> ", tmp->valor);
        tmp = tmp->prox;
    }
    printf("NULL\n");
}
```

### Imprimir ao contrário

```c
void imprimirReverso(No *head) {
    if (head == NULL) return;
    No *tmp = head;
    while (tmp->prox != NULL) tmp = tmp->prox; // vai até o último
    while (tmp != NULL) {
        printf("%d <-> ", tmp->valor);
        tmp = tmp->ant;
    }
    printf("NULL\n");
}
```

---

## 🧪 Programa de Demonstração

```c
int main() {
    No *lista = NULL;

    inserirInicio(&lista, 10);
    inserirInicio(&lista, 20);
    inserirFim(&lista, 30);

    printf("Ordem normal: ");
    imprimir(lista);

    printf("Ordem reversa: ");
    imprimirReverso(lista);

    return 0;
}
```

**Saída esperada:**

```
Ordem normal: 20 <-> 10 <-> 30 <-> NULL
Ordem reversa: 30 <-> 10 <-> 20 <-> NULL
```

---

## 🧪 Atividade em Sala

1. Implemente a lista duplamente encadeada.
2. Insira:

   * 2 valores no início,
   * 3 valores no fim.
3. Imprima nos **dois sentidos**.
4. Compare com a lista simples: o que mudou? O que ficou mais fácil?

---

## 🏠 Desafio para Casa

* Implemente a função `removerValor(No **head, int valor)` que:

  * Remove a **primeira ocorrência** de `valor`.
  * Ajusta corretamente os ponteiros `ant` e `prox`.
* Teste removendo:

  * O primeiro nó,
  * O último nó,
  * Um nó do meio.
* Explique em um parágrafo: **quais vantagens a lista dupla oferece em relação à simples**?

---

## 📚 Referências

* [Programiz – Doubly Linked List](https://www.programiz.com/dsa/doubly-linked-list)
* [GeeksforGeeks – Doubly Linked List](https://www.geeksforgeeks.org/doubly-linked-list/)
