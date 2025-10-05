# Aula 16.2: Estruturas Lineares

## Listas, Pilhas e Filas com Simulação de Memória

---

## 🎯 Objetivos

* Entender **como os dados são organizados na memória**.
* Visualizar o comportamento interno das **estruturas lineares**.
* Associar **teoria (conceito)** ↔ **prática (memória e ponteiros)**.
* Aprender a “pensar como o computador” ao manipular nós, índices e endereços.

---

## 🌿 PARTE 1 — LISTA ENCADEADA

### 💡 Conceito:

Uma **lista encadeada** é como uma corrente: cada nó sabe **onde está o próximo**.
Os nós não precisam estar lado a lado na memória.

---

### 🧱 Estrutura:

```c
typedef struct No {
    int valor;
    struct No *prox;
} No;
```

Cada nó ocupa **um espaço separado na memória**, com dois campos:

```
+--------+----------+
| valor  |  prox -> |
+--------+----------+
```

---

### 🧩 Passo a Passo na Memória

**Código:**

```c
No *lista = NULL;
lista = inserir_inicio(lista, 10);
lista = inserir_inicio(lista, 20);
lista = inserir_inicio(lista, 30);
```

### 🔍 Visualização após cada passo:

#### Passo 1 – Inserir 10

```
[10 | NULL]
 ↑
lista
```

* Cria um nó com valor 10 e `prox = NULL`
* O ponteiro `lista` aponta para esse nó.

---

#### Passo 2 – Inserir 20

```
[20 | * ] → [10 | NULL]
 ↑
lista
```

* Novo nó 20 aponta para o antigo início (10).
* Agora `lista` aponta para 20.

---

#### Passo 3 – Inserir 30

```
[30 | * ] → [20 | * ] → [10 | NULL]
 ↑
lista
```

* Novo nó 30 aponta para o nó 20.
* A lista se expande dinamicamente.

---

### 📦 Visualização na Memória (endereços simbólicos)

```
lista → 0xA1  [valor=30 | prox=0xB2]
0xB2  [valor=20 | prox=0xC3]
0xC3  [valor=10 | prox=NULL]
```

Cada nó está em um **endereço diferente** (malloc).
Mas o encadeamento mantém a ordem lógica dos dados.

---

### 💬 Dica pedagógica:

> “Uma lista encadeada é como uma caça ao tesouro — cada nó te dá o endereço do próximo.”

---

## 🥞 PARTE 2 — PILHA (STACK)

### 💡 Conceito:

Uma **pilha** é como uma pilha de pratos 🍽️:

* Você **coloca** um em cima do outro (**push**)
* E **retira** sempre o de cima (**pop**)

---

### ⚙️ Estrutura:

```c
typedef struct {
    int topo;
    int dados[5];
} Pilha;
```

* `dados[]`: armazena os valores.
* `topo`: indica a **última posição ocupada**.

---

### 🔍 Simulação de execução

**Código:**

```c
empilhar(&p, 10);
empilhar(&p, 20);
empilhar(&p, 30);
```

**Memória do vetor (dados):**

```
Índice:   0   1   2   3   4
          -----------------
dados → [10][20][30][ ][ ]
Topo = 2
```

**Visualização LIFO:**

```
Topo ↓
[30]
[20]
[10]
```

**Desempilhar (pop):**

```c
int x = desempilhar(&p);
```

Saída visual:

```
Removendo [30]
Topo ↓
[20]
[10]
```

💬 O último que entrou (30) é o primeiro a sair.
Por isso o nome: **LIFO – Last In, First Out**.

---

### 🧠 Analogia Visual:

> “Pense na pilha como uma pilha de pratos ou um histórico de ações (Ctrl + Z).
> Só o prato do topo está acessível — você não pode tirar o de baixo sem remover os de cima.”

---

## 🚦 PARTE 3 — FILA (QUEUE)

### 💡 Conceito:

Uma **fila** segue a regra do **mundo real**:

> O **primeiro a chegar é o primeiro a ser atendido**.

👉 Essa é a regra **FIFO – First In, First Out**.
Fila de banco, fila de impressão, fila de ônibus 🚌.

---

### ⚙️ Estrutura:

```c
typedef struct {
    int ini, fim;
    int dados[5];
} Fila;
```

* `ini`: posição do primeiro elemento.
* `fim`: próxima posição livre para inserir.
* Implementação **circular**: quando o vetor chega ao fim, ele “volta ao início”.

---

### 🔍 Execução passo a passo

**Código:**

```c
enfileirar(&f, 10);
enfileirar(&f, 20);
enfileirar(&f, 30);
```

**Memória (dados):**

```
Índice:   0   1   2   3   4
          -----------------
dados → [10][20][30][ ][ ]
ini = 0, fim = 3
```

**Fluxo FIFO:**

```
Frente → [10] [20] [30] → Fim
```

**Desenfileirar:**

```c
int x = desenfileirar(&f);
```

Visual:

```
Removendo [10]
Frente → [20] [30] → Fim
```

Se enfileirarmos novamente:

```
enfileirar(&f, 40);
```

A memória circular “reutiliza” o espaço:

```
Índice:   0   1   2   3   4
          -----------------
dados → [ ][20][30][40][ ]
ini = 1, fim = 4
```

---

### 💬 Analogia:

> “A fila é como a fila do bandejão:
> quem chega primeiro é servido primeiro.
> Ninguém fura a fila — nem o algoritmo!”

---

## 📊 COMPARAÇÃO VISUAL

| Estrutura | Ordem de Acesso                     | Visualização          | Analogia            |
| --------- | ----------------------------------- | --------------------- | ------------------- |
| **Lista** | Qualquer posição (encadeada)        | `[A]->[B]->[C]->NULL` | Corrente de nós 🔗  |
| **Pilha** | LIFO (Último entra, primeiro sai)   | `[Topo: C, B, A]`     | Pilha de pratos 🍽️ |
| **Fila**  | FIFO (Primeiro entra, primeiro sai) | `[Frente: A, B, C]`   | Fila de banco 🏦    |

---

## 🔬 VISUALIZAÇÃO DE MEMÓRIA (RESUMO GERAL)

| Operação              | Representação           | Memória (conceitual)              |        |       |                                  |
| --------------------- | ----------------------- | --------------------------------- | ------ | ----- | -------------------------------- |
| **Lista** (encadeada) | [10                     | *]→[20                            | *]→[30 | NULL] | Ponteiros (endereços diferentes) |
| **Pilha**             | topo ↓ [30][20][10]     | Vetor fixo, topo se move          |        |       |                                  |
| **Fila**              | frente→[10][20][30]→fim | Vetor circular (ini/fim se movem) |        |       |                                  |

---

## 🧩 Atividade Guiada (em Dupla)

1. **Simule no papel:**

   * Crie 3 vetores desenhados no caderno representando Lista, Pilha e Fila.
   * Faça passo a passo as operações (`inserir`, `remover`, `mostrar`) e **anote o topo, ini e fim**.

2. **Desafio no Replit:**

   * Faça a pilha e a fila com **tamanho dinâmico** (`malloc`).
   * Mostre os endereços da memória (`printf("%p", ptr)`) para ver onde estão os elementos.

3. **Pergunta reflexiva:**

   * O que acontece se eu desempilhar uma pilha vazia?
   * O que acontece se eu enfileirar em uma fila cheia?
   * Por que a lista não precisa de tamanho fixo?

---

## 🏠 Tarefa para Casa

Implemente um **menu interativo**:

```c
1 - Inserir elemento
2 - Remover elemento
3 - Mostrar estrutura
4 - Sair
```

O usuário deve escolher:

* **Pilha** → comportamento LIFO
* **Fila** → comportamento FIFO

Cada operação deve mostrar a **memória visual (índices ou ponteiros)** após cada ação.

💡 Dica: use `printf` com desenhos ASCII, ex.:

```
[ 10 ][ 20 ][ 30 ]
Topo -> 30
```

---

## 📚 Referências

* TANENBAUM, A. *Data Structures in C*.
* NAKAMURA, K. *Estruturas de Dados com Visualização Mental*.
* [Programiz – Stack and Queue in C](https://www.programiz.com/dsa/stack)
* [GeeksForGeeks – Linked List vs Stack vs Queue](https://www.geeksforgeeks.org/data-structures/)

---
