# Aula13.2: Revisão + Mini‑Projeto Integrador (CRUD + Ordenação + Busca)

## 🎯 Objetivos

* Consolidar `structs`, vetores (estáticos e dinâmicos), ponteiros e `malloc/realloc/free`.
* Revisar **ordenação** (Bubble/Insertion/`qsort`) e **busca** (linear/binária/`bsearch`).
* Desenvolver um **mini‑projeto** em C com **CRUD**, **ordenação por múltiplos critérios** e **busca eficiente**.
* Escrever código limpo, modular e com comentários didáticos.

---

## 📚 Revisão Rápida (conceitos‑chave)

* **Struct + vetor:** agrupar campos (ex.: `rm`, `nome`, `media`) e armazenar vários registros.
* **Dinâmica:** `malloc(n*sizeof(T))`, `realloc` para crescer/encolher, `free` ao final.
* **Ordenação:**

  * **Bubble/Insertion:** didáticos (O(n²)); Insertion é ótimo em vetores pequenos/quase ordenados.
  * **`qsort`:** genérico, bom desempenho médio O(n log n); exige **comparador**.
* **Busca:** Linear (O(n), sem ordem) × Binária (O(log n), **requer ordenado** pelo mesmo critério).

---

## 🧱 Escopo do Mini‑Projeto (em sala)

**Aplicativo de Terminal – Cadastro de Alunos Pro**

* Campos: `rm (int)`, `nome[32]`, `notas[3]`, `media (float)`.
* Funcionalidades:

  1. **Cadastrar** aluno (com cálculo automático da média).
  2. **Listar** alunos.
  3. **Ordenar** por: (a) média ↓, (b) nome ↑, (c) RM ↑.
  4. **Buscar por RM** (binária – exige estar ordenado por RM).
  5. **Remover por RM**.
* **Estratégia:** vetor **dinâmico** que cresce com `realloc` (dobrando capacidade quando necessário). Marcar um **estado de ordenação** (por RM, por nome, por média ou “desordenado”) para lembrar quando reordenar.

---

## 🛠️ Passo‑a‑Passo de Implementação

1. **Defina o tipo** `Aluno` e um "vetor dinâmico" com `dados`, `tamanho`, `capacidade` e um marcador `ordenadoPor`.
2. **Funções utilitárias:** `calcularMedia`, `garantirCapacidade` (faz `realloc`), `swap` (com `memcpy`).
3. **CRUD:** `inserirAluno`, `listarAlunos`, `removerPorRM` (use `memmove` para fechar o buraco).
4. **Ordenação:** implemente comparadores para `qsort` e versões didáticas de Bubble/Insertion para praticar.
5. **Busca:**

   * Linear: quando não estiver ordenado.
   * Binária: **após** ordenar por RM (ou use `bsearch`).
6. **Menu** com `do…while` e `switch`.

> Dica: mantenha o código **compilando e rodando** a cada passo; teste cada função isoladamente.

---

## 💻 Código Base (arquivo único – pronto para Replit)

> **Objetivo didático**: compacto, comentado e funcional. Depois, pode ser modularizado (`aluno.h/.c`, `ord.h/.c`, etc.).

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================= TIPOS E ESTADO ========================= */
typedef struct {
    int   rm;
    char  nome[32];
    float notas[3];
    float media;
} Aluno;

typedef enum { DESORDENADO=0, ORDENADO_RM, ORDENADO_NOME, ORDENADO_MEDIA } Ordenacao;

typedef struct {
    Aluno *dados;
    int tamanho;
    int capacidade;
    Ordenacao ordenadoPor;
} VetorAlunos;

/* ========================= UTILITÁRIOS ========================= */
static float calcularMedia(const float n[3]) {
    return (n[0] + n[1] + n[2]) / 3.0f;
}

static void garantirCapacidade(VetorAlunos *v) {
    if (v->tamanho < v->capacidade) return;
    int novaCap = (v->capacidade == 0 ? 4 : v->capacidade * 2);
    Aluno *novo = (Aluno*)realloc(v->dados, (size_t)novaCap * sizeof(Aluno));
    if (!novo) { fprintf(stderr, "Erro de memoria\n"); exit(1); }
    v->dados = novo;
    v->capacidade = novaCap;
}

static void swapAluno(Aluno *a, Aluno *b) {
    Aluno tmp;
    memcpy(&tmp, a, sizeof tmp);
    memcpy(a, b,   sizeof tmp);
    memcpy(b, &tmp,sizeof tmp);
}

/* ========================= CRUD ========================= */
static void inserirAluno(VetorAlunos *v) {
    garantirCapacidade(v);
    Aluno *a = &v->dados[v->tamanho];

    printf("RM: "); scanf("%d", &a->rm);
    printf("Nome: "); scanf(" %31[^\n]", a->nome);
    for (int i = 0; i < 3; i++) {
        printf("Nota %d: ", i+1);
        scanf("%f", &a->notas[i]);
    }
    a->media = calcularMedia(a->notas);

    v->tamanho++;
    v->ordenadoPor = DESORDENADO; // após inserir, precisa reordenar se necessário
}

static void listarAlunos(const VetorAlunos *v) {
    if (v->tamanho == 0) { puts("(vazio)"); return; }
    printf("\n--- LISTA (%d alunos) ---\n", v->tamanho);
    for (int i = 0; i < v->tamanho; i++) {
        printf("RM:%d | Nome:%-12s | Media: %.2f\n",
               v->dados[i].rm, v->dados[i].nome, v->dados[i].media);
    }
}

static int removerPorRM(VetorAlunos *v, int rm) {
    for (int i = 0; i < v->tamanho; i++) {
        if (v->dados[i].rm == rm) {
            /* fecha o buraco deslocando à esquerda */
            memmove(&v->dados[i], &v->dados[i+1], (size_t)(v->tamanho - i - 1) * sizeof(Aluno));
            v->tamanho--;
            v->ordenadoPor = DESORDENADO;
            return 1;
        }
    }
    return 0;
}

/* ========================= ORDENACAO (Bubble/Insertion/qsort) ========================= */
/* Comparadores p/ qsort */
static int cmp_rm_asc(const void *a, const void *b) {
    const Aluno *x = (const Aluno*)a, *y = (const Aluno*)b;
    return (x->rm > y->rm) - (x->rm < y->rm);
}
static int cmp_nome_asc(const void *a, const void *b) {
    const Aluno *x = (const Aluno*)a, *y = (const Aluno*)b;
    return strcmp(x->nome, y->nome);
}
static int cmp_media_desc(const void *a, const void *b) {
    const Aluno *x = (const Aluno*)a, *y = (const Aluno*)b;
    if (x->media > y->media) return -1;
    if (x->media < y->media) return  1;
    return strcmp(x->nome, y->nome); // desempate por nome
}

/* Bubble por media CRESCENTE (exemplo didático) */
static void bubble_media_asc(Aluno *v, int n) {
    int trocou;
    do {
        trocou = 0;
        for (int i = 0; i < n - 1; i++) {
            if (v[i].media > v[i+1].media) {
                swapAluno(&v[i], &v[i+1]);
                trocou = 1;
            }
        }
        n--;
    } while (trocou);
}

/* Insertion por nome DECRESCENTE (para praticar inversão de critério) */
static void insertion_nome_desc(Aluno *v, int n) {
    for (int i = 1; i < n; i++) {
        Aluno chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].nome, chave.nome) < 0) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
}

/* Funções de alto nível para ordenar conforme menu */
static void ordenarPorRM(VetorAlunos *v) {
    qsort(v->dados, (size_t)v->tamanho, sizeof(Aluno), cmp_rm_asc);
    v->ordenadoPor = ORDENADO_RM;
}
static void ordenarPorNome(VetorAlunos *v) {
    qsort(v->dados, (size_t)v->tamanho, sizeof(Aluno), cmp_nome_asc);
    v->ordenadoPor = ORDENADO_NOME;
}
static void ordenarPorMedia(VetorAlunos *v) {
    qsort(v->dados, (size_t)v->tamanho, sizeof(Aluno), cmp_media_desc);
    v->ordenadoPor = ORDENADO_MEDIA;
}

/* ========================= BUSCA ========================= */
static int buscaLinearRM(const VetorAlunos *v, int rm) {
    for (int i = 0; i < v->tamanho; i++) if (v->dados[i].rm == rm) return i;
    return -1;
}
static int buscaBinariaRM(const VetorAlunos *v, int rm) {
    int l = 0, r = v->tamanho - 1;
    while (l <= r) {
        int m = l + (r - l)/2;
        if (v->dados[m].rm == rm) return m;
        if (v->dados[m].rm < rm) l = m + 1; else r = m - 1;
    }
    return -1;
}

/* ========================= MENU ========================= */
static void menu(void) {
    puts("\n===== CADASTRO DE ALUNOS PRO =====");
    puts("1) Cadastrar aluno");
    puts("2) Listar alunos");
    puts("3) Ordenar por média (desc)");
    puts("4) Ordenar por nome (asc)");
    puts("5) Ordenar por RM (asc)");
    puts("6) Buscar por RM");
    puts("7) Remover por RM");
    puts("0) Sair");
    printf("Escolha: ");
}

int main(void) {
    VetorAlunos v = { .dados=NULL, .tamanho=0, .capacidade=0, .ordenadoPor=DESORDENADO };

    int opc;
    do {
        menu();
        if (scanf("%d", &opc) != 1) break;
        if (opc == 1) {
            inserirAluno(&v);
        } else if (opc == 2) {
            listarAlunos(&v);
        } else if (opc == 3) {
            ordenarPorMedia(&v); puts("Ordenado por média (desc).");
        } else if (opc == 4) {
            ordenarPorNome(&v); puts("Ordenado por nome (asc).");
        } else if (opc == 5) {
            ordenarPorRM(&v); puts("Ordenado por RM (asc).");
        } else if (opc == 6) {
            int rm; printf("RM a buscar: "); scanf("%d", &rm);
            int idx = -1;
            if (v.ordenadoPor == ORDENADO_RM) idx = buscaBinariaRM(&v, rm);
            else idx = buscaLinearRM(&v, rm);
            if (idx >= 0) printf("Encontrado: %s (RM:%d, média: %.2f)\n", v.dados[idx].nome, v.dados[idx].rm, v.dados[idx].media);
            else puts("Não encontrado.");
        } else if (opc == 7) {
            int rm; printf("RM a remover: "); scanf("%d", &rm);
            puts(removerPorRM(&v, rm) ? "Removido." : "RM não localizado.");
        }
    } while (opc != 0);

    free(v.dados);
    return 0;
}
```

---

## 🧪 Atividade em Sala

1. Implementar todas as opções do menu e **testar** (inserir ≥ 5 alunos).
2. Verificar a diferença de **buscar por RM** antes e depois de ordenar por RM (linear × binária).
3. Mostrar **Top 3** por média após `ordenarPorMedia`.

---

## 🏠 Desafio (para casa)

* **Persistência:** salvar e carregar alunos de um arquivo CSV simples.
* **Case‑insensitive:** ordenar por nome ignorando maiúsculas/minúsculas (normalizar).
* **Relatórios:**

  * Top 3 por média (já com desempate por nome).
  * Listagem por faixas (≥ 8.0, 6.0–7.9, < 6.0).
* **Métrica extra:** contar comparações/trocas nas ordenações didáticas e comparar com `qsort` (relacionar com Big‑O).

---

## 📝 Observações Didáticas

* **Após inserir/remover**, considere o vetor **desordenado** até escolher uma ordenação.
* **Busca binária** só é válida quando **ordenado por RM**.
* Prefira `qsort` no aplicativo real; use Bubble/Insertion para fins didáticos.
* Em **Replit**, teste com poucos registros antes de escalar.
