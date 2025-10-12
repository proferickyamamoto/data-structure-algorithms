# Aula 17.2 — Projeto Compilador FIAP: Implementando o *lexer* da linguagem FIAP

Este repositório é a base do compilador/linguagem **FIAP**, em homenagem à FIAP.  
Nesta aula, vamos desenvolver o primeiro módulo: o **analisador léxico (lexer)**.

---

## 🎯 Objetivos de Aprendizado

Ao final desta aula, os alunos deverão:

1. Explicar o papel do *lexer* no pipeline da FIAP++.  
2. Implementar funções básicas em C: leitura, avanço, lookahead, emissão de tokens.  
3. Reconhecer identificadores, números, operadores simples e compostos, delimitadores e palavras-chave.  
4. Tratar espaços em branco, quebras de linha e comentários (`// …`).  
5. Rastrear linha e coluna para cada token.  
6. Detectar caracteres inválidos com mensagens claras.  
7. Testar com exemplos `.fiap` e conferir a saída de tokens.

---

## 🧠 Contexto Teórico

### Pipeline do compilador FIAP++

O compilador da linguagem FIAP++ seguirá etapas assim:

```

Código-fonte (.fiap) → [ LEXER ] → Tokens → [ PARSER ] → AST → [ CODEGEN ] → Bytecode → [ VM ] → Execução

```

Hoje faremos apenas o módulo **lexer**, que transforma caracteres em tokens com significado.

### Token

Um **token** representa um trecho significativo do código. Cada token inclui:

- **Tipo** (um `enum`, por exemplo `T_IDENT`, `T_NUMBER`, `T_LET`)  
- **Lexema** (texto original ou parte dele)  
- **Linha** e **coluna** de origem  
- **Valor numérico**, no caso de tokens do tipo número

Por exemplo:

```

let x = 10;

```

→ tokens: `T_LET("let")`, `T_IDENT("x")`, `T_ASSIGN("=")`, `T_NUMBER(10)`, `T_SEMI(";")`

### Palavras-chave vs identificadores

Identificadores seguem padrão `[A-Za-z_][A-Za-z0-9_]*`. Se o lexema coincide com uma palavra reservada (`let`, `print`, `if`, `else`, `while`), o token emitido é da palavra-chave específica, não `T_IDENT`.

### Operadores simples e compostos

Símbolos simples: `+ - * / % ( ) { } ;`  
Operadores compostos com lookahead:

- `=` → `==` ou `=`  
- `!` → `!=` ou `!`  
- `<` → `<=` ou `<`  
- `>` → `>=` ou `>`  
- `&` → `&&`  
- `|` → `||`

Usamos função auxiliar `match()` que verifica o próximo caractere.

### Espaços e comentários

- Ignorar espaços brancos via `isspace()`.  
- Comentários `// …` devem ser pulados até o fim da linha.  
- Muito importante manter `line` e `col` atualizados corretamente.

### Linha e coluna

- Ao consumir um caractere com `\n`, incrementar `line` e resetar `col = 1`.  
- Para outros caracteres, apenas `col++`.  
- Ao criar o token, podemos usar a posição **inicial** ou **final** — escolha consistente é importante para mensagens de erro.

### Erros léxicos

Se um caractere não for reconhecível como início de token válido, emitir mensagem como:

```

[lex] caractere inválido ‘@’ em linha 3, coluna 7

```

Pode-se optar por abortar ou continuar ignorando o caractere.

---

## 🧱 Estrutura de Arquivos

```

fiapp/
├── include/
│   ├ token.h
│   └ lexer.h
├── src/
│   ├ lexer.c
│   └ main.c
├── tests/
│   └ samples/
│       ├ arith.fiap
│       ├ cond.fiap
│       └ loops.fiap
└── Makefile

````

- `token.h`: define `TokenType`, `Token`, função `token_name()`.  
- `lexer.h`: define `lexer_init()` e `lexer_next()`.  
- `lexer.c`: contém a implementação do lexer: funções auxiliares, `skip_spaces`, `lexer_next`.  
- `main.c`: utilitário para leitura de arquivo `.fiap` e impressão de tokens.  
- `Makefile`: regras de compilação.  
- Pasta `tests/samples`: exemplos de entrada `.fiap`.

---

## 🛠️ Implementação Comentada

### 1. token.h

```c
#pragma once
#include <stdint.h>

typedef enum {
  T_EOF = 0,
  T_IDENT,
  T_NUMBER,
  T_LET, T_PRINT, T_IF, T_ELSE, T_WHILE,
  T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE,
  T_SEMI, T_ASSIGN,
  T_PLUS, T_MINUS, T_STAR, T_SLASH, T_PERCENT,
  T_EQ, T_NEQ, T_LT, T_LTE, T_GT, T_GTE,
  T_AND, T_OR, T_NOT
} TokenType;

typedef struct {
  TokenType type;
  const char *lexeme;
  int line, col;
  long value;
} Token;

static inline const char* token_name(TokenType t) {
  switch (t) {
    case T_EOF: return "T_EOF";
    case T_IDENT: return "T_IDENT";
    case T_NUMBER: return "T_NUMBER";
    case T_LET: return "T_LET";
    case T_PRINT: return "T_PRINT";
    case T_IF: return "T_IF";
    case T_ELSE: return "T_ELSE";
    case T_WHILE: return "T_WHILE";
    case T_LPAREN: return "T_LPAREN";
    case T_RPAREN: return "T_RPAREN";
    case T_LBRACE: return "T_LBRACE";
    case T_RBRACE: return "T_RBRACE";
    case T_SEMI: return "T_SEMI";
    case T_ASSIGN: return "T_ASSIGN";
    case T_PLUS: return "T_PLUS";
    case T_MINUS: return "T_MINUS";
    case T_STAR: return "T_STAR";
    case T_SLASH: return "T_SLASH";
    case T_PERCENT: return "T_PERCENT";
    case T_EQ: return "T_EQ";
    case T_NEQ: return "T_NEQ";
    case T_LT: return "T_LT";
    case T_LTE: return "T_LTE";
    case T_GT: return "T_GT";
    case T_GTE: return "T_GTE";
    case T_AND: return "T_AND";
    case T_OR: return "T_OR";
    case T_NOT: return "T_NOT";
    default: return "T_UNKNOWN";
  }
}
````

### 2. lexer.h

```c
#pragma once
#include "token.h"

typedef struct {
  const char *src;
  int pos;
  int line, col;
} Lexer;

void lexer_init(Lexer *L, const char *src);
Token lexer_next(Lexer *L);
```

### 3. Funções auxiliares em lexer.c

```c
static int peek(Lexer *L) {
  return L->src[L->pos];
}

static int advance(Lexer *L) {
  int c = L->src[L->pos++];
  if (c == '\\n') {
    L->line++;
    L->col = 1;
  } else {
    L->col++;
  }
  return c;
}

static int match(Lexer *L, char expected) {
  if (peek(L) == expected) {
    advance(L);
    return 1;
  }
  return 0;
}
```

### 4. skip_spaces

```c
static void skip_spaces(Lexer *L) {
  for (;;) {
    int c = peek(L);
    if (c == '\\0') break;
    if (isspace(c)) {
      advance(L);
      continue;
    }
    if (c == '/' && L->src[L->pos + 1] == '/') {
      while (peek(L) != '\\0' && peek(L) != '\\n') {
        advance(L);
      }
      continue;
    }
    break;
  }
}
```

### 5. lexer_next

```c
Token lexer_next(Lexer *L) {
  skip_spaces(L);
  int c = peek(L);

  if (c == '\\0') {
    return (Token){ T_EOF, "", L->line, L->col, 0 };
  }

  if (isalpha(c) || c == '_') {
    int start = L->pos;
    while (isalnum(peek(L)) || peek(L) == '_') {
      advance(L);
    }
    int len = L->pos - start;
    char *buf = malloc(len + 1);
    memcpy(buf, &L->src[start], len);
    buf[len] = '\\0';

    if (strcmp(buf, "let") == 0) {
      free(buf);
      return (Token){ T_LET, "let", L->line, L->col, 0 };
    }
    if (strcmp(buf, "print") == 0) {
      free(buf);
      return (Token){ T_PRINT, "print", L->line, L->col, 0 };
    }
    if (strcmp(buf, "if") == 0) {
      free(buf);
      return (Token){ T_IF, "if", L->line, L->col, 0 };
    }
    if (strcmp(buf, "else") == 0) {
      free(buf);
      return (Token){ T_ELSE, "else", L->line, L->col, 0 };
    }
    if (strcmp(buf, "while") == 0) {
      free(buf);
      return (Token){ T_WHILE, "while", L->line, L->col, 0 };
    }

    Token tk = (Token){ T_IDENT, buf, L->line, L->col, 0 };
    return tk;
  }

  if (isdigit(c)) {
    long v = 0;
    while (isdigit(peek(L))) {
      v = v * 10 + (advance(L) - '0');
    }
    return (Token){ T_NUMBER, "", L->line, L->col, v };
  }

  advance(L);
  switch (c) {
    case '=':
      if (match(L, '=')) return (Token){ T_EQ, "==", L->line, L->col, 0 };
      return (Token){ T_ASSIGN, "=", L->line, L->col, 0 };
    case '!':
      if (match(L, '=')) return (Token){ T_NEQ, "!=", L->line, L->col, 0 };
      return (Token){ T_NOT, "!", L->line, L->col, 0 };
    case '<':
      if (match(L, '=')) return (Token){ T_LTE, "<=", L->line, L->col, 0 };
      return (Token){ T_LT, "<", L->line, L->col, 0 };
    case '>':
      if (match(L, '=')) return (Token){ T_GTE, ">=", L->line, L->col, 0 };
      return (Token){ T_GT, ">", L->line, L->col, 0 };
    case '&':
      if (match(L, '&')) return (Token){ T_AND, "&&", L->line, L->col, 0 };
      break;
    case '|':
      if (match(L, '|')) return (Token){ T_OR, "||", L->line, L->col, 0 };
      break;
    case '+': return (Token){ T_PLUS, "+", L->line, L->col, 0 };
    case '-': return (Token){ T_MINUS, "-", L->line, L->col, 0 };
    case '*': return (Token){ T_STAR, "*", L->line, L->col, 0 };
    case '/': return (Token){ T_SLASH, "/", L->line, L->col, 0 };
    case '%': return (Token){ T_PERCENT, "%", L->line, L->col, 0 };
    case '(': return (Token){ T_LPAREN, "(", L->line, L->col, 0 };
    case ')': return (Token){ T_RPAREN, ")", L->line, L->col, 0 };
    case '{': return (Token){ T_LBRACE, "{", L->line, L->col, 0 };
    case '}': return (Token){ T_RBRACE, "}", L->line, L->col, 0 };
    case ';': return (Token){ T_SEMI, ";", L->line, L->col, 0 };
  }

  fprintf(stderr, "[lex] caractere inválido '%c' em %d:%d\n",
          c, L->line, L->col);
  return (Token){ T_EOF, "", L->line, L->col, 0 };
}
```

### 6. main.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

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
  if (fread(buf, 1, n, f) != (size_t)n) {
    perror("fread");
    exit(1);
  }
  buf[n] = '\\0';
  fclose(f);
  return buf;
}

int main(int argc, char **argv) {
  if (argc < 3 || strcmp(argv[1], "--tokens") != 0) {
    fprintf(stderr, "Uso: %s --tokens <arquivo.fiap>\\n", argv[0]);
    return 1;
  }
  char *src = read_file(argv[2]);
  Lexer L;
  lexer_init(&L, src);
  while (1) {
    Token t = lexer_next(&L);
    if (t.type == T_EOF) {
      printf("T_EOF (l=%d c=%d)\\n", t.line, t.col);
      break;
    }
    if (t.type == T_NUMBER) {
      printf("%s %ld (l=%d c=%d)\\n",
             token_name(t.type), t.value, t.line, t.col);
    } else if (t.type == T_IDENT) {
      printf("%s '%s' (l=%d c=%d)\\n",
             token_name(t.type), t.lexeme, t.line, t.col);
      free((void*)t.lexeme);
    } else {
      printf("%s '%s' (l=%d c=%d)\\n",
             token_name(t.type), t.lexeme ? t.lexeme : "",
             t.line, t.col);
    }
  }
  free(src);
  return 0;
}
```

### 7. Makefile

```makefile
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2 -Iinclude

SRC = src/main.c src/lexer.c
OBJ = $(SRC:.c=.o)

fiappp: $(OBJ)
    $(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
    rm -f $(OBJ) fiappp
```

---

## 🧪 Exemplos de Teste

Em `tests/samples`:

**arith.fiap**

```c
let a = 1 + 2 * 3;
print a;
```

**cond.fiap**

```c
let a = 3;
if (a == 3) { print 42; } else { print 0; }
```

**loops.fiap**

```c
let x = 5;
while (x > 0) { print x; x = x - 1; }
```

Comando de teste:

```bash
./fiappp --tokens tests/samples/arith.fiap
```

E também um teste com erro proposital, por exemplo:

```c
let 123 = x;
```

---

## ⚠️ Dúvidas Extras sobre `#pragma once`

`#pragma once` é uma diretiva de pré-processador (não-padrão) que instrui que aquele header seja incluído apenas uma vez por unidade de tradução, evitando duplicações de definição.
Equivalente ao uso de *include guards* (`#ifndef / #define / #endif`), mas com sintaxe mais limpa.
Embora não esteja formalmente no padrão C, é amplamente suportado pelos compiladores modernos.
