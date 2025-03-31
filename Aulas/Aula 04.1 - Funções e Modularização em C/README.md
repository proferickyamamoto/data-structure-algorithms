# 🚀 Aula 04.1 - Funções e Modularização em C

## 📌 Objetivos da Aula
Nesta semana, vamos aprender a criar **funções próprias** em C para organizar melhor o código, facilitar a manutenção e reaproveitamento de lógica.

### ✅ O que você aprenderá:
- O que são funções em C.
- Como declarar e definir funções.
- Como passar argumentos (parâmetros) e retornar valores.
- Diferença entre funções `void` e com retorno.
- Boas práticas de modularização.
- Exercícios práticos e um mini projeto com funções.

---

## 📖 Introdução às Funções

### 📌 O que é uma função?
Uma função é um **bloco de código reutilizável** que executa uma tarefa específica. Ela pode receber entradas (parâmetros) e pode (ou não) retornar um valor.

### 📌 Vantagens de usar funções:
- Organização e clareza do código.
- Evita repetição de código (reutilização).
- Facilita testes, manutenção e modularização.

---

## 🔧 Estrutura de uma Função
```c
// Declaração (protótipo)
tipo_de_retorno nome_funcao(tipo_parametro1, tipo_parametro2);

// Definição
tipo_de_retorno nome_funcao(tipo_parametro1, tipo_parametro2) {
    // corpo da função
    return valor; // se tiver retorno
}
```

---

## 🧱 Tipos de Funções com Exemplos e Explicações

### ✅ 1. Sem retorno, sem parâmetros
```c
#include <stdio.h>

void mensagem() {
    printf("Bem-vindo ao curso de C!\n");
}

int main() {
    mensagem(); // chama a função
    return 0;
}
```
**Explicação:**
- `void mensagem()` → Função **sem retorno** e **sem parâmetros**.
- A função apenas executa a ação de imprimir um texto.

---

### ✅ 2. Sem retorno, com parâmetros
```c
#include <stdio.h>

void exibir(int x) {
    printf("O valor recebido foi: %d\n", x);
}

int main() {
    exibir(10); // passa o valor 10 como argumento
    return 0;
}
```
**Explicação:**
- `void exibir(int x)` → Recebe um número inteiro e imprime.
- Útil para exibir valores formatados ou mensagens específicas.

---

### ✅ 3. Com retorno, sem parâmetros
```c
#include <stdio.h>

int gerarNumero() {
    return 42; // retorna sempre o mesmo valor
}

int main() {
    int n = gerarNumero();
    printf("Número gerado: %d\n", n);
    return 0;
}
```
**Explicação:**
- `int gerarNumero()` → Não recebe nada, mas **retorna um inteiro**.
- O retorno é capturado em `n` e impresso no `main()`.

---

### ✅ 4. Com retorno, com parâmetros
```c
#include <stdio.h>

float media(float a, float b) {
    return (a + b) / 2;
}

int main() {
    float m = media(7.5, 8.0);
    printf("Média: %.2f\n", m);
    return 0;
}
```
**Explicação:**
- `float media(float a, float b)` → Recebe dois `float` e retorna a média.
- Permite reutilização da lógica de cálculo da média.

---

## 📝 Exercícios para Desenvolver em Sala

### 1️⃣ Crie uma função `void mensagem()` que exiba "Bem-vindo ao curso de C!"
### 2️⃣ Crie uma função `int dobro(int n)` que receba um número inteiro e retorne o dobro.
### 3️⃣ Crie uma função `float media(float n1, float n2)` que retorne a média de duas notas.
### 4️⃣ Crie uma função `void tabuada(int n)` que exiba a tabuada do número de 1 a 10.

---

## 🎯 Desafio para Casa

### 📌 Sistema de Cadastro Modularizado
Desenvolva um programa em C com as seguintes funções:
- `void menu()` → exibe o menu principal com opções.
- `void cadastrarAluno()` → cadastra nome, idade e RM.
- `void exibirAluno()` → exibe os dados cadastrados.

📌 O programa deve conter:
- Um menu interativo com laço `do-while`.
- Uso correto de funções.
- Armazenamento de um único aluno (por enquanto).

---

## 📚 Recursos Adicionais
- 📖 Livro: "The C Programming Language" – Kernighan e Ritchie
- 🎥 Vídeo: [Funções em C - YouTube]([https://www.youtube.com/watch?v=Ta1hL9L4Oaw&pp=ygUYRnVuw6fDtWVzIGVtIEMgLSBZb3VUdWJl])
- 🌐 Documentação: [Funções em C - cppreference](https://en.cppreference.com/w/c/language/functions)

---

## 🔥 Próxima Aula: Vetores e Strings em C

**💡 Dúvidas? Comente no repositório ou pergunte no grupo de estudos!** 💬

