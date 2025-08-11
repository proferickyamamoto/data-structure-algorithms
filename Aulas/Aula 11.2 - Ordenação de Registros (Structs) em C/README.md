# Aula 11.2: Ordenação de Registros (Structs) em C

## 🎯 Objetivos da Semana

* Entender **por que ordenar** registros (consultas mais rápidas, relatórios, busca eficiente).
* Diferenciar **algoritmos estáveis/instáveis** e impactos práticos ao ordenar structs.
* Comparar **complexidade**: melhores/medianos/piores casos e uso de memória.
* Implementar ordenação **manual** (Bubble e Insertion) em **vetores de `struct`**.
* Usar a biblioteca padrão com **`qsort`** e um **comparador** para ordenar por chaves específicas.
* (Bônus) Aplicar **busca binária** após ordenar por RM.

---

## 📚 Fundamentação Teórica

1. **Por que ordenar?** Em sistemas com cadastros (alunos, clientes, produtos), ordenar os registros melhora a leitura humana (relatórios) e viabiliza algoritmos de busca mais rápidos, como a **busca binária**. Em geral, mantemos dados ordenados por uma chave (ex.: RM, nome, média) para responder perguntas com eficiência.

2. **Structs e chaves de ordenação.** Ao ordenar um vetor de `struct`, definimos uma **chave**: por exemplo, ordenar por `media` (decrescente) ou por `nome` (crescente). Em C, não há genéricos; portanto, criamos funções de ordenação específicas para o nosso tipo ou usamos **`qsort`** da biblioteca padrão com uma função **comparadora** que conhece como comparar dois elementos do nosso tipo.

3. **Estabilidade.** Um algoritmo de ordenação é **estável** quando mantém a **ordem relativa** de elementos que têm a mesma chave (ex.: dois alunos com a mesma média permanecem na mesma ordem em que estavam). Estabilidade é essencial quando fazemos **ordenação por múltiplas chaves** em etapas (primeiro por nome, depois por média, etc.), pois a primeira ordenação não deve ser destruída pela segunda se as chaves empatarem.

4. **Complexidade assintótica.** Ordenações simples como **Bubble Sort** e **Insertion Sort** têm pior caso **O(n²)** e consomem espaço **O(1)** adicional. Porém, **Insertion Sort** é muito eficiente em coleções **pequenas** ou **quase ordenadas** (melhor caso **O(n)**), enquanto o Bubble Sort, apesar de didático e estável, raramente é a melhor escolha prática em coleções grandes. Já `qsort` geralmente emprega estratégias mais avançadas sob o capô, com desempenho médio **O(n log n)**, mas **não garante estabilidade**.

5. **Escolhas práticas.** Em vetores pequenos (ex.: uma turma), **Insertion Sort** é simples e rápido o suficiente. Quando o requisito é **genérico** (ordenar qualquer tipo) e com bom desempenho, usamos **`qsort`** com um comparador. Se precisarmos de **estabilidade**, preferimos um algoritmo estável (ex.: Insertion) ou simulamos estabilidade no comparador com **chaves secundárias** (ex.: ordenar por média, e em caso de empate, por nome).

---

## 📏 O que significa O(n²)?

**Big-O** descreve como o **custo** (tempo/operações) cresce quando o tamanho da entrada **n** aumenta. Quando dizemos que um algoritmo é **O(n²)**, significa que esse custo cresce **proporcional ao quadrado de n**. Na prática, isso costuma aparecer em algoritmos com **dois laços aninhados**, como o Bubble Sort e, no pior/medio caso, o Insertion Sort. Em muitos cenários, o número de comparações aproxima-se de `n(n−1)/2`, que é da ordem de **n²**.

### Visualizando rapidamente

* Se **n = 10**, comparações ≈ `10×9/2 = 45`.
* Se **n = 100**, comparações ≈ `100×99/2 = 4.950`.
* Se **n = 1.000**, comparações ≈ `1.000×999/2 ≈ 499.500`.

Repare que **duplicar n** tende a **quadruplicar** o trabalho (`(2n)² = 4n²`). Por isso, **O(n²)** é aceitável para **vetores pequenos** ou **quase ordenados** (onde o Insertion pode chegar a **O(n)** no melhor caso), mas torna-se **lento** para coleções grandes — aí preferimos algoritmos **O(n log n)** (ex.: QuickSort via `qsort`).

> Lembre-se: a **busca binária** funciona em **O(log n)**, mas **exige o vetor ordenado**.

---

## 🧩 Exemplo completo

> Vamos ordenar um vetor de alunos por **média (decrescente)** com **Bubble**, por **nome (crescente)** com **Insertion** e por **RM (crescente)** com **`qsort`**. Em seguida, faremos **busca binária** por RM.

### 1) Cabeçalhos e `struct`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   rm;
    char  nome[32];
    float media;
} Aluno;
```

**O que faz:** Importamos bibliotecas para E/S, utilidades e strings. Definimos `Aluno` com três campos: `rm` (chave numérica), `nome` (chave textual) e `media` (chave numérica). O `typedef` simplifica o uso do tipo.

---

### 2) Utilitário de impressão

```c
void imprimir(const Aluno *v, int n, const char *titulo) {
    printf("\n%s\n", titulo);
    for (int i = 0; i < n; i++) {
        printf("RM:%d | Nome:%-10s | Média: %.2f\n", v[i].rm, v[i].nome, v[i].media);
    }
}
```

**O que faz:** Função de apoio para mostrar o estado do vetor em diferentes momentos, facilitando comparar antes/depois das ordenações.

---

### 3) Bubble Sort (média decrescente, estável)

```c
void bubble_media_desc(Aluno *v, int n) {
    int trocou;
    do {
        trocou = 0;
        for (int i = 0; i < n - 1; i++) {
            if (v[i].media < v[i+1].media) { // troca só quando for estritamente menor
                Aluno tmp = v[i];
                v[i] = v[i+1];
                v[i+1] = tmp;
                trocou = 1;
            }
        }
        n--; // último elemento já está na posição correta
    } while (trocou);
}
```

**O que faz:** Compara pares adjacentes e “borbulha” a maior média para o final a cada passagem. A condição **estrita** (`<`) ajuda a manter estabilidade quando as médias empatam (não trocamos elementos iguais).

---

### 4) Insertion Sort (nome crescente, estável)

```c
void insertion_nome_asc(Aluno *v, int n) {
    for (int i = 1; i < n; i++) {
        Aluno chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].nome, chave.nome) > 0) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
}
```

**O que faz:** Insere `v[i]` na posição correta da parte já ordenada `[0..i-1]`. Em arrays pequenos ou quase ordenados, costuma ser bem eficiente. Como desloca itens **maiores** para a direita e insere a **chave** no lugar, preserva a ordem relativa de empates (estável).

---

### 5) `qsort` por RM (crescente) e comparador

```c
int cmp_rm_asc(const void *a, const void *b) {
    const Aluno *x = (const Aluno*)a;
    const Aluno *y = (const Aluno*)b;
    return (x->rm > y->rm) - (x->rm < y->rm); // evita overflow de subtração
}
```

**O que faz:** Define um **comparador** no formato exigido por `qsort`: retorna negativo se `x<y`, zero se iguais, positivo se `x>y`. A expressão com booleanos evita problemas de overflow que poderiam acontecer ao retornar `x->rm - y->rm` diretamente.

---

### 6) Busca binária por RM (vetor ordenado por RM)

```c
int busca_binaria_rm(const Aluno *v, int n, int rm) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (v[m].rm == rm) return m;
        if (v[m].rm < rm) l = m + 1; else r = m - 1;
    }
    return -1; // não encontrado
}
```

**O que faz:** Divide e conquista: compara no meio; se a chave procurada for maior, busca na metade direita; caso contrário, na esquerda. Requer **vetor previamente ordenado por RM**.

---

### 7) `main`: dados de exemplo e demonstração

```c
int main(void) {
    Aluno turma[] = {
        {321, "Ana",    8.5f},
        {215, "Bruno",  6.7f},
        {405, "Clara",  9.2f},
        {198, "Diego",  6.7f}, // mesma média de Bruno (para ver estabilidade)
        {377, "Eva",    10.0f},
        {142, "Lia",     7.3f}
    };
    int n = (int)(sizeof turma / sizeof turma[0]);

    imprimir(turma, n, "Estado inicial");

    bubble_media_desc(turma, n);
    imprimir(turma, n, "Ordenado por média (decrescente) – Bubble (estável)");

    insertion_nome_asc(turma, n);
    imprimir(turma, n, "Ordenado por nome (crescente) – Insertion (estável)");

    qsort(turma, n, sizeof(Aluno), cmp_rm_asc);
    imprimir(turma, n, "Ordenado por RM (crescente) – qsort");

    int alvo = 198;
    int idx = busca_binaria_rm(turma, n, alvo);
    printf("\nBusca binária por RM=%d → %s (índice %d)\n", alvo,
           (idx >= 0 ? turma[idx].nome : "não encontrado"), idx);

    return 0;
}
```

**O que faz:** Monta um vetor com dados variados, incluindo **médias iguais** para observar estabilidade. Mostra o vetor inicial, aplica as três ordenações (explicando o critério) e demonstra **busca binária** após ordenar por RM.

---

## 🧪 Atividade em Sala (individual ou dupla)

1. **Selection Sort por média crescente** em vetor de `Aluno` (implemente `selection_media_asc`).
2. Conte **comparações** e **trocas** em cada algoritmo (Bubble × Insertion × Selection) para o mesmo conjunto de dados e discuta os resultados.
3. Explique em 3–5 linhas **quando** você escolheria cada algoritmo (tamanho do vetor, ordenação parcial, necessidade de estabilidade).

---

## 🏠 Tarefa para Casa

1. Transforme o exemplo para ler `n` alunos do teclado (**alocação dinâmica** com `malloc`).
2. Ordene por **média decrescente** com Bubble e, **em caso de empate**, por **nome crescente** (defina a regra no `if` usando chave secundária).
3. Reescreva a ordenação por RM usando **`qsort`** e um comparador **com chaves múltiplas**: primeiro RM, em empate, `nome` (crescentemente).

---

## 🚩 Desafio

Implemente um **relatório multifiltro**:

* A) Ordene por **média decrescente** e mostre os **Top 3**.
* B) Ordene por **nome crescente** e permita **buscar por prefixo** (primeiras letras) imprimindo todos os que batem.
* C) Compare o tempo (ou número de comparações) de **Insertion** × **Bubble** para vetores: já ordenado, quase ordenado e reverso.

---

## 📝 Observações Didáticas

* Use prints intermediários apenas durante o desenvolvimento para depurar o comportamento dos algoritmos.
* Garanta que o comparador de `qsort` **nunca retorne diferença por subtração** direta em tipos inteiros grandes; prefira comparações compostas.
* Se precisar de **estabilidade com múltiplas chaves** usando `qsort` (que não garante estabilidade), **inclua a chave secundária no comparador** (ex.: comparar média; se empatar, comparar nome), simulando o efeito desejado.
