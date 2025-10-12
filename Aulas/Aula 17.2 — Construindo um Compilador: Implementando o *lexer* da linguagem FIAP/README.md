# Linguagem FIAP — Aula 17.2: Implementando o Lexer

Este repositório contém o código-base e instruções para a **primeira aula** do compilador/linguagem FIAP (em homenagem à FIAP).  
O foco é construir o módulo de **análise léxica (lexer)** em linguagem C, explicando cada trecho do código para facilitar o entendimento dos alunos.

---

## 📖 Visão geral

### O que é FIAP

FIAP é uma linguagem didática desenvolvida para o curso de compiladores. A extensão de código-fonte será `.fiap`.  
Ao longo das aulas, vamos construir do zero: **lexer → parser → AST → geração de código (bytecode) → VM**.

### Por que começar pelo lexer?

- O lexer é a porta de entrada do compilador: converte texto bruto em tokens com significado (números, identificadores, operadores etc.).  
- Permite aos alunos entenderem conceitos fundamentais de manipulação de strings, estados e lógica.  
- É relativamente independente — erros em lexer não “derrubam” todo o compilador.

---

## 🎯 Objetivos desta aula

Ao final desta aula, os alunos deverão ser capazes de:

1. Explicar o papel do lexer no pipeline de compilação.  
2. Implementar funções básicas: `peek`, `advance`, `match`, `skip_spaces`, `lexer_next`.  
3. Reconhecer:
   - identificadores e palavras-chave  
   - números inteiros  
   - operadores simples e compostos (`+`, `-`, `==`, `<=`, `&&` etc.)  
   - delimitadores (`(`, `)`, `{`, `}`, `;`)  
4. Lidar com espaços, quebras de linha e comentários `// …`.  
5. Rastrear linha e coluna para cada token ou erro.  
6. Gerar mensagens de erro léxico com posição.  
7. Compilar e executar no terminal arquivos `.fiap` para visualizar tokens.

---

## 🗺 Estrutura do repositório e arquivos

```

fiap/
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

| Pasta / arquivo       | Função principal                                                             |
|-----------------------|-------------------------------------------------------------------------------|
| `include/token.h`     | Define `TokenType`, estrutura `Token` e utilitário `token_name(...)`         |
| `include/lexer.h`     | Declarações de `lexer_init()` e `lexer_next()`                                |
| `src/lexer.c`         | Implementação do lexer (peek, advance, match, skip_spaces etc.)               |
| `src/main.c`          | Aplicativo de teste que lê `.fiap`, percorre tokens e imprime no terminal     |
| `tests/samples/*.fiap`| Arquivos de exemplo para testes (aritmética, controle, loop etc.)             |
| `Makefile`            | Regras de compilação e limpeza                                                 |

---

## 🧩 Explicação detalhada do código (lexer + main)

A seguir, os trechos de código com comentários explicativos bloco a bloco. Os alunos devem acompanhar cada linha durante a aula.

### lexer.c

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
````

* `stdio.h`: entrada/saída (printf, fprintf, perror).
* `ctype.h`: funções de caracteres (isspace, isdigit, isalpha etc.).
* `string.h`: manipulação de strings (memcpy, strcmp).
* `stdlib.h`: alocação de memória (malloc, free), exit.
* `lexer.h`: nosso cabeçalho com definições de `Lexer` e `Token`.

```c
static int peek(Lexer *L) {
  return L->src[L->pos];
}
```

* Retorna o caractere atual sem avançar `L->pos`.
* Se `pos` apontar para `'\0'`, peek retorna `0` (fim da string).

```c
static int advance(Lexer *L) {
  int c = L->src[L->pos++];
  if (c == '\n') {
    L->line++;
    L->col = 1;
  } else {
    L->col++;
  }
  return c;
}
```

* Move `pos` para frente, consumindo o caractere.
* Se for nova linha (`\n`), incrementa `line` e reinicia `col = 1`.
* Caso contrário, incrementa `col`.
* Retorna o caractere consumido.

```c
static int match(Lexer *L, char expected) {
  if (peek(L) == expected) {
    advance(L);
    return 1;
  }
  return 0;
}
```

* Verifica se o próximo caractere é `expected`.
* Se sim, consome-o (`advance`) e retorna 1 (verdadeiro).
* Caso contrário, não consome nada e retorna 0.

```c
static Token make(Lexer *L, TokenType t, const char *lex) {
  Token tok = { t, lex, L->line, L->col, 0 };
  return tok;
}
```

* Cria um `Token` simples com tipo `t`, lexema `lex`, linha/coluna atuais, valor = 0.
* Ideal para tokens fixos (operadores, símbolos simples).

```c
void lexer_init(Lexer *L, const char *src) {
  L->src = src;
  L->pos = 0;
  L->line = 1;
  L->col = 1;
}
```

* Inicializa o lexer: aponta para a string `src`, zera `pos`, e inicia rastreamento de linha e coluna.

```c
static void skip_spaces(Lexer *L) {
  for (;;) {
    int c = peek(L);
    if (c == '\0') break;
    if (isspace(c)) {
      advance(L);
      continue;
    }
    if (c == '/' && L->src[L->pos + 1] == '/') {
      while (peek(L) != '\0' && peek(L) != '\n') {
        advance(L);
      }
      continue;
    }
    break;
  }
}
```

* Ignora espaços, tabs, novas linhas via `isspace`.
* Se detectar `//`, consome até encontrar `\n` ou fim da string.
* Sai quando tiver um caractere relevante para tokenização.

```c
Token lexer_next(Lexer *L) {
  skip_spaces(L);
  int c = peek(L);
  if (c == '\0') {
    return make(L, T_EOF, "");
  }
```

* Esta função é o coração do lexer: retorna o próximo token.
* Primeiro, chama `skip_spaces`.
* Se `peek` indica fim de arquivo (`'\0'`), retorna token `T_EOF`.

```c
  if (isalpha(c) || c == '_') {
    int start = L->pos;
    while (isalnum(peek(L)) || peek(L) == '_') {
      advance(L);
    }
    int len = L->pos - start;
    char *buf = malloc(len + 1);
    memcpy(buf, &L->src[start], len);
    buf[len] = '\0';
```

* Reconhece identificador ou palavra-chave: começa por letra ou underscore `_`.
* Consome enquanto for alfanumérico ou `_`.
* Calcula comprimento, aloca buffer + terminador `\0`.
* Copia trecho da fonte para `buf`.

```c
    if (strcmp(buf, "let") == 0) {
      free(buf);
      return (Token){ T_LET, "let", L->line, L->col, 0 };
    }
    // repita para print, if, else, while
    Token tk = (Token){ T_IDENT, buf, L->line, L->col, 0 };
    return tk;
  }
```

* Compara com palavras-chave: se coincidir, libera `buf` e retorna token fixo.
* Caso contrário, retorna `T_IDENT` com `lexeme = buf`.

```c
  if (isdigit(c)) {
    long v = 0;
    while (isdigit(peek(L))) {
      v = v * 10 + (advance(L) - '0');
    }
    return (Token){ T_NUMBER, "", L->line, L->col, v };
  }
```

* Se o caractere for dígito, começa a leitura de número inteiro.
* Acumula valor numérico `v`.
* Retorna token `T_NUMBER` com `value = v`.

```c
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
```

* Consome o caractere `c` e entra no `switch`.
* Para casos como `=`, verifica se o próximo caractere forma `==` (via `match`).
* Se sim, retorna token `T_EQ`; senão `T_ASSIGN`.
* Para operadores simples, retorna token diretamente.

```c
  fprintf(stderr, "[lex] caractere inválido '%c' em %d:%d\\n",
          c, L->line, L->col);
  return (Token){ T_EOF, "", L->line, L->col, 0 };
}
```

* Se nenhum `case` foi acionado, considera caractere inválido.
* Imprime mensagem de erro com linha e coluna.
* Retorna `T_EOF` para encerrar a leitura.

````

### main.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"
````

* Inclusão de bibliotecas padrão e nossos headers.

```c
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
```

* Lê o arquivo `.fiap` completo em memória.
* `fopen("rb")`: abre em modo binário para ler bytes.
* `fseek` + `ftell` para descobrir tamanho.
* `malloc(n+1)` para alocar buffer com espaço extra para `\0`.
* `fread` para ler conteúdo; se falhar, aborta.
* `buf[n] = '\0'` forma string C.
* Retorna ponteiro para buffer.

```c
int main(int argc, char **argv) {
  if (argc < 3 || strcmp(argv[1], "--tokens") != 0) {
    fprintf(stderr, "Uso: %s --tokens <arquivo.fiap>\\n", argv[0]);
    return 1;
  }
  char *src = read_file(argv[2]);
  Lexer L;
  lexer_init(&L, src);
```

* Verifica se os argumentos estão corretos (`--tokens arquivo.fiap`).
* Se não, imprime uso correto e termina.
* Lê o conteúdo do arquivo para `src`.
* Inicializa o lexer com esse buffer.

```c
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
             token_name(t.type),
             t.lexeme ? t.lexeme : "",
             t.line, t.col);
    }
  }
```

* Loop: chama `lexer_next()` repetidamente até `T_EOF`.
* Se `T_NUMBER`, imprime número.
* Se `T_IDENT`, imprime identificador e libera `lexeme`.
* Para outros tokens, imprime tipo + lexema.
* No final, sai do loop.

```c
  free(src);
  return 0;
}
```

* Libera o buffer `src`.
* Retorna 0 (sucesso).

---

## 🧪 Exemplos de arquivos `.fiap`

* **arith.fiap**

  ```fiap
  let a = 1 + 2 * 3;
  print a;
  ```
* **cond.fiap**

  ```fiap
  let a = 3;
  if (a == 3) { print 42; } else { print 0; }
  ```
* **loops.fiap**

  ```fiap
  let x = 5;
  while (x > 0) { print x; x = x - 1; }
  ```

Teste no terminal:

```bash
./fiappp --tokens tests/samples/arith.fiap
```

Exemplo de saída esperada:

```
T_LET 'let' (l=1 c=1)
T_IDENT 'a' (l=1 c=5)
T_ASSIGN '=' (l=1 c=7)
T_NUMBER 1 (l=1 c=9)
…
T_EOF (l=1 c=…)
```

Se um caractere inválido aparece:

```
[lex] caractere inválido '@' em 2:5
```

---

## ✅ Dicas úteis!

* Se `malloc` for usado para `lexeme`, sempre faça `free` depois.
* A função `match()` permite “ler um caractere à frente” somente quando necessário.
* Erros léxicos não devem travar a aula — trate-os com gentileza para mostrar ao aluno como pensar em recuperação.
* Leve um ou dois exemplos com erro proposital para testar tratamento de erro.
* Faça revisões em pares (“pair programming”) para que um aluno explique ao outro o que cada função faz.
