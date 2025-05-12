# 🚀 Semana 09.1: Structs em C – Tipos Personalizados

## 📌 Objetivos da Aula

Nesta semana, vamos aprender a criar nossos próprios tipos de dados em C utilizando **structs**, permitindo representar entidades do mundo real (como alunos, produtos, livros, etc.) com múltiplos atributos.

### ✅ O que você aprenderá:

* O que é uma `struct` e por que usá-la.
* Como declarar, inicializar e acessar membros.
* Como passar structs para funções (por valor e por referência).
* Como utilizar structs com ponteiros e arrays.
* Aplicações práticas e exercícios.

---

## 📖 1. O que é uma `struct`?

Uma `struct` (estrutura) é uma coleção de variáveis de diferentes tipos agrupadas sob um mesmo nome.

### 📌 Exemplo básico:

```c
struct Aluno {
    char nome[50];
    int idade;
    float nota;
};
```

### 📌 Como declarar e usar:

```c
struct Aluno a1;
strcpy(a1.nome, "Maria");
a1.idade = 20;
a1.nota = 8.5;
```

---

## 🔄 2. Passagem de Struct para Função

### 📌 Por valor (faz uma cópia):

```c
void exibirAluno(struct Aluno a) {
    printf("Nome: %s\n", a.nome);
    printf("Idade: %d\n", a.idade);
    printf("Nota: %.2f\n", a.nota);
}
```

### 📌 Por referência (usa ponteiro):

```c
void atualizarNota(struct Aluno *a) {
    a->nota += 0.5;
}
```

---

## 🧠 3. Vetor de Structs

### 📌 Exemplo:

```c
struct Aluno turma[3];

for (int i = 0; i < 3; i++) {
    printf("Digite o nome: ");
    scanf("%s", turma[i].nome);
    printf("Digite a idade: ");
    scanf("%d", &turma[i].idade);
    printf("Digite a nota: ");
    scanf("%f", &turma[i].nota);
}
```

---

## 📝 Exercícios para Desenvolver em Sala

### 1️⃣ Criar e exibir dados de um aluno

* Criar uma `struct Aluno` com nome, idade e nota.
* Ler os dados do usuário e exibir na tela.

### 2️⃣ Função que recebe struct como parâmetro

* Criar função `void imprimirAluno(struct Aluno a)` para exibir os dados.

### 3️⃣ Função que atualiza struct via ponteiro

* Criar função `void atualizarNota(struct Aluno *a)` que adiciona 0.5 na nota.

### 4️⃣ Vetor de 5 alunos

* Criar vetor de alunos.
* Ler os dados e exibir os alunos com nota >= 7.

---

## 🎯 Desafio para Casa

### 📌 Cadastro de Livros

* Criar uma `struct Livro` com: título, autor, ano.
* Permitir cadastro de 5 livros.
* Criar função para buscar livro por título (usar `strcmp`).
* Criar função para exibir livros publicados após 2010.

---

## 📚 Recursos Adicionais

* 📘 Livro: "C Completo e Total" – Herbert Schildt
* 🎥 Vídeo: [Structs em C - Curso em Vídeo](https://www.youtube.com/watch?v=CXz9yZbXWco)
* 🌐 Documentação: [Structs em C - cppreference](https://en.cppreference.com/w/c/language/struct)

---

## 🔥 Próxima Aula: Ordenação e Busca com Structs

**💬 Dúvidas? Comente no repositório ou fale com o professor ou monitor!**
