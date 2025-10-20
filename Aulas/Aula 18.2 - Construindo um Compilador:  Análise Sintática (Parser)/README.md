# Aula 18.2: Análise Sintática (Parser)

Nesta segunda aula do compilador/língua **FIAP** (extensão `.fiap`) avançamos para o módulo de **análise sintática (parser)**, que recebe os tokens gerados na Aula 1 e verifica se eles seguem a gramática da linguagem. Também iniciaremos a construção de uma estrutura que permitirá as próximas fases (AST, semântica, geração de código).

---

## 🎯 Objetivos de Aprendizagem

Ao final desta aula, os alunos deverão ser capazes de:

- Descrever o papel do parser no pipeline do compilador:  
```

Código-fonte (.fiap) → [Lexer] → Tokens → [Parser] → Verificação Sintática → …

```
- Definir uma gramática simplificada para FIAP (instruções de atribuição, print, if, while, expressões aritméticas).  
- Implementar um *parser recursivo-descendente* em C que:
- Consome tokens via `lexer_next(&L)` e mantém um `current_token`.  
- Implementa funções correspondentes a regras gramaticais (ex: `parse_statement()`, `parse_expr()`, `parse_term()`, `parse_factor()`).  
- Detecta e reporta erros sintáticos com linha e coluna (via `current_token.line/col`).  
- Integrar o parser ao código da Aula 1 (lexer) para que o programa faça: ler arquivo `.fiap`, tokenizar, parsear, e relatar se o código está sintaticamente correto ou não.  
- Testar casos positivos e negativos de sintaxe (por exemplo, bloco if-else, loops, expressões com erro).  
- Preparar terreno para a próxima aula (AST, semântica, geração de código).

---

## 🧠 Contexto Teórico

### O que é parsing?

Parsing (análise sintática) é o processo de “dar sentido” à sequência de tokens, verificando se ela obedece à gramática da linguagem e construindo uma representação estrutural (como árvore de derivação ou AST).  
Uma técnica comum para linguagens didáticas é o *recursive-descent parser* (top-down) — fácil de entender e implementar em C. :contentReference[oaicite:0]{index=0}

### Gramática de exemplo para FIAP

A seguir está uma gramática simplificada (em notação BNF/EBNF) para a linguagem **FIAP** que iremos usar nesta aula:

```

program        → statement_list
statement_list → statement statement_list | ε

statement      → "let" identifier "=" expr ";"
| identifier "=" expr ";"
| "print" expr ";"
| "if" "(" expr ")" "{" statement_list "}" [ "else" "{" statement_list "}" ]
| "while" "(" expr ")" "{" statement_list "}"

expr           → term ( ("+" | "-") term )*
term           → factor ( ("*" | "/" | "%") factor )*
factor         → number | identifier | "(" expr ")"

````

Explicações:
- `let identifier = expr ;` declara ou inicializa uma variável.  
- `print expr ;` imprime uma expressão.  
- `if (…) { … } else { … }` controle condicional.  
- `while (…) { … }` loop.  
- A parte de expressões (`expr`, `term`, `factor`) segue a precedência comum: multiplicação/divisão antes de soma/subtração.

---

## 🧩 Estrutura de Implementação

### Arquivos envolvidos

- `include/parser.h` — cabeçalho do parser (novo)  
- `src/parser.c` — implementação do parser  
- `src/main.c` — modificado para integrar lexer + parser  
- Arquivos já existentes: `include/token.h`, `include/lexer.h`, `src/lexer.c`  

### Passos de código (bloco-a-bloco)

#### parser.h  
```c
#pragma once
#include "lexer.h"
#include "token.h"

void parser_init(Lexer *L);
void parse_program(Lexer *L);
````

#### parser.c

```c
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

static Token current;

static void advance_token(Lexer *L) {
    current = lexer_next(L);
}

// Declaração das funções para cada regra
static void parse_statement_list(Lexer *L);
static void parse_statement(Lexer *L);
static void parse_expr(Lexer *L);
static void parse_term(Lexer *L);
static void parse_factor(Lexer *L);

void parser_init(Lexer *L) {
    advance_token(L);
}

void parse_program(Lexer *L) {
    parse_statement_list(L);
    if (current.type != T_EOF) {
        fprintf(stderr, "Erro sintático: token inesperado '%s' em %d:%d\n",
                token_name(current.type), current.line, current.col);
        exit(1);
    }
}

// Implementações das outras funções …
```

*(As funções `parse_statement_list`, `parse_statement`, `parse_expr`, `parse_term`, `parse_factor` seguem conforme a gramática acima.)*

#### main.c (modificado para integração)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"
#include "parser.h"

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
      perror("fopen");
      exit(1);
    }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(n + 1);
    if (fread(buf, 1, n, f) != (size_t)n) {
      perror("fread");
      exit(1);
    }
    buf[n] = '\0';
    fclose(f);
    return buf;
}

int main(int argc, char **argv) {
    if (argc < 3 || strcmp(argv[1], "--parse") != 0) {
        fprintf(stderr, "Uso: %s --parse <arquivo.fiap>\n", argv[0]);
        return 1;
    }
    char *src = read_file(argv[2]);
    Lexer L;
    lexer_init(&L, src);
    parser_init(&L);
    parse_program(&L);
    printf("Parsing concluído com sucesso.\n");
    free(src);
    return 0;
}
```

> Nota: no comando de execução usamos `--parse` (ou você pode manter `--tokens` se quiser dualidade e especificar outro flag) para indicar que o programa fará a etapa de parsing.

---

## 🧪 Exemplos de arquivo `.fiap` para teste

* **exemplo_if.fiap**

  ```fiap
  let a = 10;
  if (a < 20) {
      print a;
  } else {
      print 0;
  }
  ```

* **exemplo_while.fiap**

  ```fiap
  let x = 5;
  while (x > 0) {
      print x;
      x = x - 1;
  }
  ```

* **exemplo_error.fiap**

  ```fiap
  let a = 1 + ;
  print a;
  ```

  Esse último arquivo tem erro de sintaxe e deve disparar mensagem como:

  ```
  Erro: esperado número ou identificador em linha X, coluna Y
  ```

---

## ✅ Boas práticas e dicas:

* Trabalhe em pares (“pair programming”) para que cada um explique o que cada função faz e o outro implemente.
* Mantenha cada função de parsing curta e focada (um “unit” por regra gramatical). Isso favorece clareza.
* Se o programa falhar no meio, utilize a linha/coluna de `current` para localizar o erro no código-fonte `.fiap`.
* Grave um ou dois casos de erro sintático propositalmente para validar se o parser detecta e relata corretamente.
* Ainda não se preocupe com geração de código ou AST — foco desta aula é *reconhecer a sintaxe*.

---

## 📚 Referências e leituras recomendadas

* “Recursive descent parser” — Wikipedia: implementação top-down, procedimentos recursivos por regra gramatical. ([Wikipedia][1])
* Tutorialspoint — “What is Recursive Descent Parser?”: conceito e exemplo. ([Tutorials Point][2])
* GeeksforGeeks — “Recursive Descent Parser”: explicações passo-a-passo. ([GeeksforGeeks][3])

[1]: https://en.wikipedia.org/wiki/Recursive_descent_parser?utm_source=chatgpt.com "Recursive descent parser - Wikipedia"
[2]: https://www.tutorialspoint.com/what-is-recursive-descent-parser?utm_source=chatgpt.com "What is Recursive Descent Parser? - Tutorialspoint"
[3]: https://www.geeksforgeeks.org/recursive-descent-parser/?utm_source=chatgpt.com "Recursive Descent Parser - GeeksforGeeks"
