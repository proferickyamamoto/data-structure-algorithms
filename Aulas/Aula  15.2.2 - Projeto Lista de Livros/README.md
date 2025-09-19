# 📚 Projeto Prático – Lista de Livros (Lista Duplamente Encadeada)

## 🎯 Objetivos

* Modelar um **Livro** como `struct` (id, título, autor, ano, status).
* Implementar uma **lista duplamente encadeada** para armazenar livros.
* Criar operações: **inserir**, **listar**, **buscar**, **remover**, **emprestar/devolver**.
* Exercitar ponteiros, alocação dinâmica e modularização básica.

---

## 🧱 Modelo de dados

```c
typedef struct {
    int  id;
    char titulo[64];
    char autor[64];
    int  ano;
    int  emprestado; // 0 = disponível, 1 = emprestado
} Livro;

typedef struct No {
    Livro       dado;
    struct No  *ant;
    struct No  *prox;
} No;

typedef struct {
    No *ini;  // cabeça
    No *fim;  // cauda
    int tam;
} Lista;
```

---

## 🛠️ Passo a passo (com código incremental)

### PASSO 1 — Inicializar a lista

```c
void init(Lista *L) {
    L->ini = L->fim = NULL;
    L->tam = 0;
}
```

### PASSO 2 — Criar nó de livro

```c
No* novo_no(Livro x) {
    No *n = (No*)malloc(sizeof(No));
    if (!n) { perror("malloc"); exit(1); }
    n->dado = x;
    n->ant = n->prox = NULL;
    return n;
}
```

### PASSO 3 — Inserir no fim

```c
void push_back(Lista *L, Livro x) {
    No *n = novo_no(x);
    if (L->ini == NULL) { // lista vazia
        L->ini = L->fim = n;
    } else {
        n->ant   = L->fim;
        L->fim->prox = n;
        L->fim   = n;
    }
    L->tam++;
}
```

### PASSO 4 — Listar (frente → trás)

```c
void listar(const Lista *L) {
    if (L->ini == NULL) { puts("(lista vazia)"); return; }
    for (No *p = L->ini; p != NULL; p = p->prox) {
        printf("#%d | \"%s\" — %s (%d) [%s]\n",
               p->dado.id, p->dado.titulo, p->dado.autor, p->dado.ano,
               p->dado.emprestado ? "emprestado" : "disponível");
    }
}
```

### PASSO 5 — Buscar por ID

```c
No* buscar_id(const Lista *L, int id) {
    for (No *p = L->ini; p != NULL; p = p->prox)
        if (p->dado.id == id) return p;
    return NULL;
}
```

### PASSO 6 — Remover por ID

```c
int remover_id(Lista *L, int id) {
    No *p = buscar_id(L, id);
    if (!p) return 0;

    if (p->ant) p->ant->prox = p->prox; else L->ini = p->prox;
    if (p->prox) p->prox->ant = p->ant; else L->fim = p->ant;

    free(p);
    L->tam--;
    return 1;
}
```

### PASSO 7 — Emprestar / Devolver

```c
int emprestar(Lista *L, int id) {
    No *p = buscar_id(L, id);
    if (!p) return -1;            // não existe
    if (p->dado.emprestado) return 0; // já emprestado
    p->dado.emprestado = 1;
    return 1;                     // emprestado com sucesso
}

int devolver(Lista *L, int id) {
    No *p = buscar_id(L, id);
    if (!p) return -1;            // não existe
    if (!p->dado.emprestado) return 0; // já disponível
    p->dado.emprestado = 0;
    return 1;                     // devolvido
}
```

### PASSO 8 — Leitura segura de strings

```c
void ler_str(const char *rotulo, char *buf, int max) {
    printf("%s", rotulo);
    scanf(" %63[^\n]", buf); // lê até a quebra de linha (ajuste max se mudar)
}
```

### PASSO 9 — Cadastrar livro (entrada do usuário)

```c
Livro ler_livro(void) {
    Livro L; L.emprestado = 0;
    printf("ID: ");
    scanf("%d", &L.id);
    ler_str("Título: ", L.titulo, 64);
    ler_str("Autor: ",  L.autor,  64);
    printf("Ano: ");
    scanf("%d", &L.ano);
    return L;
}
```

### PASSO 10 — Liberar memória

```c
void liberar(Lista *L) {
    No *p = L->ini;
    while (p) {
        No *prox = p->prox;
        free(p);
        p = prox;
    }
    init(L);
}
```

---

## 💻 Programa completo - Coloque dentro do Replit ou outra IDE

> Cole tudo em um `main.c` e rode. Menu simples com `do..while`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==== MODELOS ==== */
typedef struct {
    int  id;
    char titulo[64];
    char autor[64];
    int  ano;
    int  emprestado; // 0 disp / 1 emprestado
} Livro;

typedef struct No {
    Livro       dado;
    struct No  *ant;
    struct No  *prox;
} No;

typedef struct {
    No *ini, *fim;
    int tam;
} Lista;

/* ==== ASSINATURAS ==== */
void  init(Lista *L);
No*   novo_no(Livro x);
void  push_back(Lista *L, Livro x);
void  listar(const Lista *L);
No*   buscar_id(const Lista *L, int id);
int   remover_id(Lista *L, int id);
int   emprestar(Lista *L, int id);
int   devolver(Lista *L, int id);
void  liberar(Lista *L);
void  ler_str(const char *rotulo, char *buf, int max);
Livro ler_livro(void);
void  menu(void);

/* ==== IMPLEMENTAÇÕES ==== */
void init(Lista *L) { L->ini = L->fim = NULL; L->tam = 0; }

No* novo_no(Livro x) {
    No *n = (No*)malloc(sizeof(No));
    if (!n) { perror("malloc"); exit(1); }
    n->dado = x; n->ant = n->prox = NULL;
    return n;
}

void push_back(Lista *L, Livro x) {
    No *n = novo_no(x);
    if (L->ini == NULL) L->ini = L->fim = n;
    else {
        n->ant = L->fim;
        L->fim->prox = n;
        L->fim = n;
    }
    L->tam++;
}

void listar(const Lista *L) {
    if (!L->ini) { puts("(lista vazia)"); return; }
    puts("\n--- CATÁLOGO ---");
    for (No *p = L->ini; p; p = p->prox) {
        printf("#%d | \"%s\" — %s (%d) [%s]\n",
               p->dado.id, p->dado.titulo, p->dado.autor, p->dado.ano,
               p->dado.emprestado ? "emprestado" : "disponível");
    }
}

No* buscar_id(const Lista *L, int id) {
    for (No *p = L->ini; p; p = p->prox)
        if (p->dado.id == id) return p;
    return NULL;
}

int remover_id(Lista *L, int id) {
    No *p = buscar_id(L, id);
    if (!p) return 0;
    if (p->ant) p->ant->prox = p->prox; else L->ini = p->prox;
    if (p->prox) p->prox->ant = p->ant; else L->fim = p->ant;
    free(p); L->tam--; return 1;
}

int emprestar(Lista *L, int id) {
    No *p = buscar_id(L, id);
    if (!p) return -1;
    if (p->dado.emprestado) return 0;
    p->dado.emprestado = 1; return 1;
}

int devolver(Lista *L, int id) {
    No *p = buscar_id(L, id);
    if (!p) return -1;
    if (!p->dado.emprestado) return 0;
    p->dado.emprestado = 0; return 1;
}

void liberar(Lista *L) {
    No *p = L->ini;
    while (p) { No *q = p->prox; free(p); p = q; }
    init(L);
}

void ler_str(const char *rotulo, char *buf, int max) {
    (void)max; // mantido para referência
    printf("%s", rotulo);
    scanf(" %63[^\n]", buf);
}

Livro ler_livro(void) {
    Livro L; L.emprestado = 0;
    printf("ID: "); scanf("%d", &L.id);
    ler_str("Título: ", L.titulo, 64);
    ler_str("Autor: ",  L.autor,  64);
    printf("Ano: "); scanf("%d", &L.ano);
    return L;
}

void menu(void) {
    puts("\n===== BIBLIOTECA =====");
    puts("1) Cadastrar livro");
    puts("2) Listar livros");
    puts("3) Remover por ID");
    puts("4) Emprestar por ID");
    puts("5) Devolver por ID");
    puts("0) Sair");
    printf("Escolha: ");
}

int main(void) {
    Lista L; init(&L);
    int op;
    do {
        menu();
        if (scanf("%d", &op) != 1) break;
        if (op == 1) {
            Livro x = ler_livro();
            // regra opcional: rejeitar ID duplicado
            if (buscar_id(&L, x.id)) puts("ID já existe.");
            else { push_back(&L, x); puts("Cadastrado!"); }
        } else if (op == 2) {
            listar(&L);
        } else if (op == 3) {
            int id; printf("ID: "); scanf("%d", &id);
            puts(remover_id(&L, id) ? "Removido." : "ID não encontrado.");
        } else if (op == 4) {
            int id; printf("ID: "); scanf("%d", &id);
            int r = emprestar(&L, id);
            if (r == 1) puts("Emprestado!");
            else if (r == 0) puts("Já estava emprestado.");
            else puts("ID não encontrado.");
        } else if (op == 5) {
            int id; printf("ID: "); scanf("%d", &id);
            int r = devolver(&L, id);
            if (r == 1) puts("Devolvido!");
            else if (r == 0) puts("Já estava disponível.");
            else puts("ID não encontrado.");
        }
    } while (op != 0);

    liberar(&L);
    return 0;
}
```

---

## 🧪 Atividade em sala

1. **Implemente** o código até o PASSO 4; cadastre 2 livros e liste.
2. Adicione o **buscar por ID** (PASSO 5) e **remover** (PASSO 6), teste removendo um ID inexistente e um existente.
3. Adicione **emprestar/devolver** (PASSO 7) e **simule o fluxo** de empréstimo e devolução.
4. Mostre como o **tamanho da lista** (`tam`) muda com inserções/remoções.

---

## 🏠 Extensões (para casa)

* **Buscar por título** (substring); dica: `strstr`.
* **Ordenar por título** (pode copiar para vetor, `qsort`, e imprimir ordem).
* **Persistência**: salvar/carregar em CSV (ID;TÍTULO;AUTOR;ANO;STATUS).
* **Relatórios**: listar emprestados vs. disponíveis; por ano; por autor.
