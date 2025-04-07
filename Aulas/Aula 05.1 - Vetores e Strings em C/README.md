# 🚀 Aula 05.1: Vetores e Strings em C

## 📌 Objetivos da Aula
Nesta semana, você aprenderá os conceitos fundamentais para trabalhar com **coleções de dados** do mesmo tipo em C, utilizando **vetores** e **strings**.

### ✅ O que você aprenderá:
- O que são vetores (arrays) em C.
- Como declarar, inicializar e acessar vetores.
- Como percorrer vetores com laços.
- Como funcionam as strings em C.
- Como manipular strings com funções da biblioteca `<string.h>`.
- Exercícios práticos com vetores e strings.

---

## 📖 1. Vetores (Arrays)

### 📌 O que é um vetor?
Um vetor é uma **coleção de variáveis do mesmo tipo** armazenadas em posições contíguas da memória.

### 📌 Declaração de um vetor
```c
int numeros[5]; // vetor de 5 inteiros
```

### 📌 Inicialização
```c
int numeros[5] = {10, 20, 30, 40, 50};
```

### 📌 Acesso aos elementos
```c
printf("Primeiro número: %d\n", numeros[0]); // acessa o primeiro elemento
```

### 📌 Preenchimento com `for`
```c
for (int i = 0; i < 5; i++) {
    printf("Digite um número: ");
    scanf("%d", &numeros[i]);
}
```

---

## 📖 2. Strings em C

### 📌 O que é uma string?
Em C, uma string é um **vetor de caracteres** terminado com o caractere especial `\0` (nulo).

### 📌 Declaração e leitura
```c
char nome[20];
printf("Digite seu nome: ");
scanf("%s", nome); // lê até o primeiro espaço
```

### 📌 Leitura com espaços:
```c
fgets(nome, 20, stdin); // lê inclusive espaços
```

### 📌 Funções úteis da `<string.h>`:
```c
#include <string.h>

strlen(str);      // retorna o tamanho da string
strcpy(dest, src); // copia uma string para outra
strcmp(a, b);     // compara duas strings
strcat(a, b);     // concatena duas strings
```

---

## 📝 Exercícios para Desenvolver em Sala

### 1️⃣ Vetor de inteiros
Crie um programa que:
- Peça 5 números ao usuário e armazene em um vetor.
- Exiba os números na ordem inversa.

### 2️⃣ Média dos elementos
- Peça 4 notas e calcule a média usando vetor.

### 3️⃣ Nome com até 20 caracteres
- Leia um nome usando `fgets` e exiba letra por letra na vertical.

### 4️⃣ Comparação de nomes
- Peça dois nomes e diga se são iguais ou diferentes usando `strcmp`.

---

## 🎯 Desafio para Casa

### 📌 Cadastro de Nomes
Crie um programa que:
- Cadastre até 5 nomes de pessoas (com espaços).
- Após o cadastro, exiba todos os nomes cadastrados em ordem inversa.

📌 Dicas:
- Use um vetor de strings: `char nomes[5][50];`
- Use `fgets()` para ler os nomes.
- Use `for` para percorrer os índices de 4 até 0.

---

## 📚 Recursos Adicionais
- 📘 Livro: "Linguagem C - Completo e Descomplicado" – André Backes
- 🎥 Vídeo: [Vetores e Strings em C - Curso em Vídeo](https://www.youtube.com/watch?v=WxGBoY5iNXY)
- 🌐 Documentação: [Vetores e strings - cppreference](https://en.cppreference.com/w/c/string/byte)

---

## 🔥 Próxima Aula: Matrizes e manipulação de dados em tabelas

**💬 Em caso de dúvidas, consulte o professor ou monitor!**

