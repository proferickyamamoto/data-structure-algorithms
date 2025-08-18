# Aula 12.2: Busca Linear, Busca Binária e `bsearch`

## 🎯 Objetivos da Semana

* Compreender **quando** usar busca linear e quando usar **busca binária**.
* Saber os **requisitos** da busca binária (vetor ordenado e comparador consistente).
* Implementar versões **iterativas** de busca linear e binária em **vetores de `struct`**.
* Utilizar as funções da **biblioteca padrão**: `qsort` (para ordenar) e `bsearch` (para buscar).
* Medir a **complexidade** na prática com contadores (comparações).

---

## 📚 Fundamentação Teórica (resumo)

* **Busca Linear**: percorre elemento a elemento até achar (ou terminar). Funciona em **qualquer vetor** (ordenado ou não). Custo típico: **O(n)**.
* **Busca Binária**: em vetor **ordenado**, compara com o meio e descarta **metade** do espaço a cada passo. Custo típico: **O(log n)**. Requer um **critério de ordenação** consistente (mesmo usado na comparação).
* `qsort`: ordena um vetor genérico usando um **comparador** (`int cmp(const void*,const void*)`).
* `bsearch`: faz **busca binária** em vetor **já ordenado** conforme o **mesmo comparador**.
* Em vetores **pequenos** ou quando a busca é **pontual**, a linear pode ser suficiente. Para muitas buscas, **ordenar uma vez** e usar binária costuma compensar.

---

## 🧱 Modelo de dados

```c
typedef struct {
    int   rm;
    char  nome[32];
    float media;
} Aluno;
```

---

## 🔎 Busca Linear por RM (qualquer ordem)

```c
int busca_linear_rm(const Aluno *v, int n, int alvo_rm, long *comps) {
    for (int i = 0; i < n; i++) {
        if (comps) (*comps)++;
        if (v[i].rm == alvo_rm) return i; // encontrado
    }
    return -1; // não encontrado
}
```

**Como ler:** varre `0..n-1`, compara `rm` de cada registro com `alvo_rm`. Não exige ordenação; custo proporcional a `n` no pior caso.

---

## ⚖️ Comparadores para ordenar/buscar por RM

```c
int cmp_rm_asc(const void *a, const void *b) {
    const Aluno *x = (const Aluno*)a;
    const Aluno *y = (const Aluno*)b;
    // evita overflow: retorna -1, 0, 1
    return (x->rm > y->rm) - (x->rm < y->rm);
}
```

> Usaremos esse comparador **tanto** no `qsort` quanto no `bsearch`.

---

## 🧮 Ordenando por RM com `qsort`

```c
#include <stdlib.h>

void ordenar_por_rm(Aluno *v, int n) {
    qsort(v, (size_t)n, sizeof(Aluno), cmp_rm_asc);
}
```

**Como ler:** `qsort` reordena o vetor usando nosso comparador. Após isso, o vetor fica em **ordem crescente de RM**.

---

## 🚀 Busca Binária Iterativa por RM

```c
int busca_binaria_rm(const Aluno *v, int n, int alvo_rm, long *comps) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2; // meio seguro
        if (comps) (*comps)++;
        if (v[m].rm == alvo_rm) return m;      // achou
        if (v[m].rm <  alvo_rm) l = m + 1;     // busca à direita
        else                     r = m - 1;     // busca à esquerda
    }
    return -1;
}
```

**Como ler:** pressupõe vetor **ordenado por RM**. Compara no meio; se o meio for menor que o alvo, ignora a metade esquerda, senão a direita. Repete até encontrar ou esgotar.

---

## 🧰 `bsearch` em C (após ordenar)

```c
#include <stdlib.h>

// comparador reusado: cmp_rm_asc

int buscar_com_bsearch(const Aluno *v, int n, int alvo_rm) {
    Aluno chave = { .rm = alvo_rm };
    const Aluno *p = bsearch(
        &chave,               // chave
        v,                    // vetor já ordenado por RM
        (size_t)n,
        sizeof(Aluno),
        cmp_rm_asc            // mesmo comparador da ordenação
    );
    return p ? (int)(p - v) : -1; // índice ou -1
}
```

**Como ler:** `bsearch` implementa a busca binária **genérica** para vetores já ordenados. Se encontrar, devolve **ponteiro** para o elemento; convertemos para **índice**.

---

## 🧪 Programa‑guia (integração e contadores)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   rm;
    char  nome[32];
    float media;
} Aluno;

int cmp_rm_asc(const void *a, const void *b) {
    const Aluno *x = (const Aluno*)a;
    const Aluno *y = (const Aluno*)b;
    return (x->rm > y->rm) - (x->rm < y->rm);
}

int busca_linear_rm(const Aluno *v, int n, int alvo_rm, long *comps) {
    for (int i = 0; i < n; i++) {
        if (comps) (*comps)++;
        if (v[i].rm == alvo_rm) return i;
    }
    return -1;
}

void ordenar_por_rm(Aluno *v, int n) {
    qsort(v, (size_t)n, sizeof(Aluno), cmp_rm_asc);
}

int busca_binaria_rm(const Aluno *v, int n, int alvo_rm, long *comps) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (comps) (*comps)++;
        if (v[m].rm == alvo_rm) return m;
        if (v[m].rm < alvo_rm) l = m + 1; else r = m - 1;
    }
    return -1;
}

int buscar_com_bsearch(const Aluno *v, int n, int alvo_rm) {
    Aluno chave = { .rm = alvo_rm };
    const Aluno *p = bsearch(&chave, v, (size_t)n, sizeof(Aluno), cmp_rm_asc);
    return p ? (int)(p - v) : -1;
}

void imprimir(const Aluno *v, int n, const char *titulo) {
    printf("\n%s\n", titulo);
    for (int i = 0; i < n; i++) {
        printf("RM:%d | Nome:%-10s | Média: %.2f\n", v[i].rm, v[i].nome, v[i].media);
    }
}

int main(void) {
    Aluno turma[] = {
        {321, "Ana",    8.5f},
        {215, "Bruno",  6.7f},
        {405, "Clara",  9.2f},
        {198, "Diego",  6.7f},
        {377, "Eva",   10.0f},
        {142, "Lia",    7.3f}
    };
    int n = (int)(sizeof turma / sizeof turma[0]);

    imprimir(turma, n, "Estado inicial (não ordenado)");

    long c_lin = 0;
    int alvo = 198;
    int i_lin = busca_linear_rm(turma, n, alvo, &c_lin);
    printf("\nLinear: alvo=%d -> idx=%d | comparações=%ld\n", alvo, i_lin, c_lin);

    ordenar_por_rm(turma, n);
    imprimir(turma, n, "Ordenado por RM (qsort)");

    long c_bin = 0;
    int i_bin = busca_binaria_rm(turma, n, alvo, &c_bin);
    printf("Binária: alvo=%d -> idx=%d | comparações=%ld\n", alvo, i_bin, c_bin);

    int i_bs = buscar_com_bsearch(turma, n, alvo);
    printf("bsearch: alvo=%d -> idx=%d\n", alvo, i_bs);

    return 0;
}
```

---

## 🧪 Atividade em Sala (individual ou dupla)

1. Gere um vetor de **`n` alunos** digitados em sala (RM, nome, média).
2. Implemente **busca linear** e **binária** por RM com **contadores** de comparações.
3. Compare o nº de comparações para diferentes **n** e diferentes **RM** (início, meio, fim, ausente).
4. Explique em 3–5 linhas **quando** a busca binária supera a linear e **por que**.

---

## 🏠 Tarefa para Casa

1. Ordene a turma por **nome (crescente)** usando `qsort` (comparador com `strcmp`).
2. Implemente **busca binária por nome** (iterativa) e uma versão com **`bsearch`**.
3. Trate **empates** de nome (múltiplos alunos com o mesmo nome):

   * Versão **leftmost**: devolve o **primeiro índice** do nome encontrado.
   * Versão **rightmost**: devolve o **último índice**.
4. (Bônus) Torne a busca **case‑insensitive** (normalizar para minúsculas antes de ordenar/buscar).

---

## 🚩 Desafio

Implemente um **módulo de índice**:

* Mantenha o vetor de alunos **ordenado por RM** o tempo todo (insira no lugar certo).
* Forneça operações: `inserir`, `remover`, `buscar (binária)`, `listar ordenado`.
* Compare o nº de comparações da busca linear (em vetor desordenado) vs. binária (no índice ordenado) para 1.000, 5.000 e 10.000 elementos (dados sintéticos).

---

## 📝 Observações:

* **Busca binária exige vetor ordenado** pelo **mesmo critério** do comparador.
* Ao calcular o meio, use `l + (r - l) / 2` para evitar overflow em índices grandes.
* Para **leftmost/rightmost**, ajuste a condição da binária: ao encontrar o alvo, continue na metade que pode conter outras ocorrências.
* Meça comparações para “ver” empiricamente **O(n)** vs **O(log n)**.
