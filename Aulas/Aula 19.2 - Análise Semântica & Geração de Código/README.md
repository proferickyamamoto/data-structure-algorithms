# Aula 19.2 - Análise Semântica & Geração de Código

Nesta aula final do curso da linguagem **FIAP** (extensão `.fiap`) nós avançaremos para as fases **análise semântica** e **geração de código**, completando o pipeline do compilador didático que você tem desenvolvido (Lexer + Parser até aqui). Vamos agora verificar “o significado” dos programas e gerar saídas que simulam execução ou compilação.

---

## 🎯 Objetivos de Aprendizagem

Ao final desta aula, os alunos deverão ser capazes de:

- Explicar o papel da análise semântica em um compilador:  
  “Depois de lexar e parsear, verificar se o programa *tem sentido*.”  
- Implementar uma **tabela de símbolos** simples para a linguagem FIAP e verificar pelo menos:  
  - Variáveis declaradas antes de uso  
  - Atribuições válidas  
- Gerar uma **saída de código/intermediário** simples do programa `.fiap`, simulando a execução ou compilação (por exemplo: instruções internas, pseudo-assembly, imprimir variáveis).  
- Integrar essa fase ao código existente (Lexer + Parser) e testar com programas corretos e com erros semânticos.  
- Refletir sobre como essas fases finais preparam o caminho para otimização e geração de código real em compiladores “de verdade”.

---

## 🧠 Contexto Teórico

### O que é análise semântica?

A análise semântica ocorre **após** a análise sintática (parsing) e verifica aspectos que não podem ser totalmente capturados por gramáticas livres de contexto — como “uma variável foi declarada antes de uso” ou “tipo de dado compatível com operação”. :contentReference[oaicite:1]{index=1}  
Por exemplo:  
- Verificar se um identificador está declarado.  
- Verificar compatibilidade de tipo em atribuições.  
- Verificar escopos e uso correto de variáveis.  
A seguir, a fase de geração de código transforma o resultado da front-end (lexer + parser + semântica) em uma forma que pode ser executada ou traduzida para máquina.

### Por que precisamos dessa fase?

Porque muitos erros não são visíveis no nível de sintaxe — por exemplo:

```fiap
print x;
````

é lexicamente e sintaticamente válido (identificador, ponto-e-vírgula), mas *x* nunca foi declarado — esse erro é semântico. ([Wikipédia][1])

---

## 🧩 Estrutura de Implementação

### Arquivos envolvidos

* `include/semantic.h` — cabeçalho da análise semântica.
* `include/codegen.h` — cabeçalho para geração de código (opcional).
* `src/semantic.c` — implementação da semântica (tabela de símbolos, verificações).
* `src/codegen.c` — implementação da geração de código simples.
* `src/main.c` — modificado para uso das novas fases.
* Arquivos anteriores: `include/lexer.h`, `include/parser.h`, `include/token.h`, `src/lexer.c`, `src/parser.c`.

### Passos de código (bloco-a-bloco)

#### semantic.h

```c
#pragma once        // garante que o header seja incluído apenas uma vez
#include "token.h"  // precisamos dos tipos TokenType, Token, token_name
#include "lexer.h"  // talvez precisemos da estrutura Lexer para integração

// Inicializa a tabela de símbolos (variáveis, etc)
void semantic_init();

// Verifica declaração de uma variável (nome, linha, coluna) — se já está declarada ou não
void semantic_check_declaration(const char *name, int line, int col);

// Verifica uso de uma variável (nome, linha, coluna) — se foi declarada antes do uso
void semantic_check_usage(const char *name, int line, int col);

// Finaliza a análise semântica, libera recursos se necessário
void semantic_finalize();

```

#### semantic.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

// Estrutura para representar símbolo (variável) na tabela
typedef struct Sym {
    char *name;
    struct Sym *next;
} Sym;

static Sym *sym_table = NULL;   // ponteiro para o início da lista de símbolos

void semantic_init() {
    sym_table = NULL;            // inicia com tabela vazia
}

static void sym_insert(const char *name) {
    Sym *s = malloc(sizeof(Sym));     // aloca novo símbolo
    s->name = strdup(name);            // copia o nome
    s->next = sym_table;               // insere no início da lista
    sym_table = s;
}

static int sym_exists(const char *name) {
    for (Sym *s = sym_table; s != NULL; s = s->next) {
        if (strcmp(s->name, name) == 0) return 1;
    }
    return 0;
}

void semantic_check_declaration(const char *name, int line, int col) {
    if (sym_exists(name)) {
        fprintf(stderr, "Erro semântico: variável '%s' já declarada em %d:%d\n", name, line, col);
        exit(1);
    }
    sym_insert(name);
}

void semantic_check_usage(const char *name, int line, int col) {
    if (!sym_exists(name)) {
        fprintf(stderr, "Erro semântico: variável '%s' não declarada em %d:%d\n", name, line, col);
        exit(1);
    }
}

void semantic_finalize() {
    Sym *s = sym_table;
    while (s) {
        Sym *next = s->next;
        free(s->name);
        free(s);
        s = next;
    }
    sym_table = NULL;
}
```

#### codegen.h

```c
#pragma once
#include "lexer.h"
#include "token.h"

// Inicializa geração de código
void codegen_init();

// Emite código (pseudo-assembly) para atribuição de variável nome = valor
void codegen_emit_assignment(const char *name, long value);

// Emite código para comando print de variável nome
void codegen_emit_print(const char *name);

// Finaliza geração de código
void codegen_finalize();

```

#### codegen.c

```c
#include <stdio.h>
#include "codegen.h"

void codegen_init() {
    printf("; Código gerado para FIAP\n");
}

void codegen_emit_assignment(const char *name, long value) {
    printf("LOAD_CONST %ld\n", value);
    printf("STORE_VAR %s\n", name);
}

void codegen_emit_print(const char *name) {
    printf("LOAD_VAR %s\n", name);
    printf("PRINT_VAR %s\n", name);
}

void codegen_finalize() {
    printf("; Fim do código gerado\n");
}

```

#### main.c (modificado para a nova fase)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "semantic.h"
#include "codegen.h"

// Função para ler todo o arquivo <path> de uma vez
static char* read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("fopen");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(n + 1);
    if (!buf) {
        perror("malloc");
        exit(1);
    }
    if (fread(buf, 1, n, f) != (size_t)n) {
        perror("fread");
        exit(1);
    }
    buf[n] = '\0';
    fclose(f);
    return buf;
}

int main(int argc, char **argv) {
    if (argc < 3 || strcmp(argv[1], "--codegen") != 0) {
        fprintf(stderr, "Uso: %s --codegen <arquivo.fiap>\n", argv[0]);
        return 1;
    }
    char *src = read_file(argv[2]);           // lê arquivo-fonte
    Lexer L;
    lexer_init(&L, src);                       // inicializa lexer com o texto
    parser_init(&L);                           // inicializa parser (gera primeiro token)
    semantic_init();                           // inicia análise semântica
    codegen_init();                            // inicia geração de código

    parse_program(&L);                         // chama parser (que deverá chamar semântica + codegen nos momentos certos)
    codegen_finalize();                        // finaliza geração de código
    semantic_finalize();                       // finaliza a tabela de símbolos / libera memória

    printf("Geração de código concluída com sucesso.\n");
    free(src);                                 // libera buffer do arquivo
    return 0;
}

```

> Nota: Para simplificar, dentro de `parser.c` você pode invocar `semantic_check_declaration`, `semantic_check_usage`, `codegen_emit_assignment`, `codegen_emit_print` nos locais correspondentes às regras para declaração, atribuição e print.

---

## 🧪 Exemplos de arquivo `.fiap` para testes finais

* **ex_final_ok.fiap**

  ```fiap
  let a = 10;
  let b = a + 20;
  print b;
  ```

* **ex_final_error.fiap**

  ```fiap
  print x;
  let x = 5;
  ```

* **ex_final_codegen.fiap**

  ```fiap
  let x = 2;
  let y = x * 3 + 4;
  print y;
  ```

Para `ex_final_codegen.fiap`, ao executar:

```
.\fiap.exe --codegen ex_final_codegen.fiap
```

A saída de geração de código poderá ser:

```
; Código gerado para FIAP
LOAD_CONST 2
STORE_VAR x
LOAD_VAR x
LOAD_CONST 3
… (outros passos)
STORE_VAR y
LOAD_VAR y
PRINT_VAR y
; Fim do código gerado
Geração de código concluída com sucesso.
```
---

## 📚 Referências e leituras recomendadas

* “Semantic Analysis in Compiler Design” – GeeksforGeeks. ([GeeksforGeeks][2])
* “Compiler Design – Semantic Analysis” – Tutorialspoint. ([tutorialspoint.com][3])
* “Lecture 8 – Semantic Analysis” (Robert Siegfried) – pdf. ([home.adelphi.edu][4])

[1]: https://en.wikipedia.org/wiki/Semantic_analysis_%28compilers%29?utm_source=chatgpt.com "Semantic analysis (compilers)"
[2]: https://www.geeksforgeeks.org/compiler-design/semantic-analysis-in-compiler-design/?utm_source=chatgpt.com "Semantic Analysis in Compiler Design - GeeksforGeeks"
[3]: https://www.tutorialspoint.com/compiler_design/compiler_design_semantic_analysis.htm?utm_source=chatgpt.com "Semantic Analysis in Compiler Design - Tutorialspoint"
[4]: https://home.adelphi.edu/~siegfried/cs372/372l8.pdf?utm_source=chatgpt.com "[PDF] Compiler Construction - Lecture 8 – Semantic Analysis"
