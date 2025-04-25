# 🚀 Aula 07.1: Ponteiros e Endereçamento de Memória em C

## 📌 Objetivos da Aula
Nesta semana, vamos entender como o C lida com a memória e como os **ponteiros** nos permitem acessar e manipular diretamente os endereços de variáveis.

### ✅ O que você aprenderá:
- O que são ponteiros e como declará-los.
- Como obter e utilizar o endereço de uma variável com `&`.
- Como acessar e modificar o valor apontado com `*`.
- Relação entre ponteiros e vetores.
- Exercícios práticos com ponteiros.

---

## 📖 1. O que são Ponteiros?
Ponteiros são **variáveis que armazenam endereços de memória**.

### 📌 Declaração de ponteiro
```c
int *ptr;
```

### 📌 Atribuição com `&` (endereço de memória)
```c
int x = 10;
ptr = &x; // ptr aponta para x
```

### 📌 Acesso ao conteúdo com `*`
```c
printf("Valor de x: %d\n", *ptr); // acessa o conteúdo de x
```

### 📌 Modificando o valor por meio do ponteiro
```c
*ptr = 20; // altera o valor de x para 20
```

---

## 🔍 2. Ilustração simples de ponteiro
```c
int a = 5;
int *p = &a;

printf("Endereço de a: %p\n", &a);
printf("Valor de p: %p\n", p);
printf("Conteúdo apontado por p: %d\n", *p);
```

---

## 🔁 3. Ponteiros e Vetores
Em C, o nome de um vetor é um ponteiro para seu primeiro elemento.
```c
int v[3] = {10, 20, 30};
int *p = v; // equivalente a &v[0]

printf("%d\n", *(p + 1)); // imprime 20
```

---

## 📝 Exercícios para Desenvolver em Sala

### 1️⃣ Manipulação com ponteiros
- Declare uma variável `int x` e um ponteiro `int *p`.
- Use o ponteiro para alterar o valor de `x` para 100.

### 2️⃣ Soma de dois números com ponteiros
- Crie duas variáveis `a` e `b`.
- Use ponteiros para somar os dois valores e mostrar o resultado.

### 3️⃣ Troca de valores com ponteiros
- Crie uma função `void trocar(int *a, int *b)` que troque os valores entre duas variáveis usando ponteiros.

---

## 🎯 Desafio para Casa

### 📌 Calculadora com Ponteiros
- Crie um programa que:
  - Solicite dois números ao usuário.
  - Receba dois ponteiros (`int *a`, `int *b`)
  - Tenha funções para somar, subtrair, multiplicar e dividir usando ponteiros.

📌 Exemplo:
```c
void somar(int *a, int *b) {
    printf("Soma: %d\n", *a + *b);
}
```

---

## 📚 Recursos Adicionais
- 📘 Livro: "C Completo e Total" – Herbert Schildt
- 🎥 Vídeo: [Ponteiros em C - Curso em Vídeo](https://www.youtube.com/watch?v=2V7V6sH1EZs)
- 🌐 Documentação: [Pointers - cppreference](https://en.cppreference.com/w/c/language/pointer)

---

# 🎮 Projeto em Sala – Jogo da Troca: Ponteiros em Ação

## 🎯 Objetivo
Desenvolver um jogo interativo que utilize **ponteiros** para manipular diretamente variáveis na memória. O foco é aplicar de forma prática e divertida os conceitos aprendidos na aula.

---

## 🧠 Habilidades Desenvolvidas
- Declaração e uso de ponteiros (`int *ptr`)
- Passagem de parâmetros por referência
- Manipulação de valores e endereços de memória
- Estrutura de controle com `switch` e `do-while`
- Criação de um menu interativo

---

## 📝 Regras do Projeto
Você deverá implementar um programa em C que simule um **jogo de troca de pontos entre dois jogadores**, utilizando funções que manipulam valores por meio de **ponteiros**.

### 🧩 Funcionalidades obrigatórias:
- Trocar valores entre jogadores
- Somar os pontos
- Exibir o vencedor
- Alterar valor de um jogador manualmente
- Exibir os endereços de memória dos jogadores
- Sair do programa

---

## 🧭 Menu Interativo
```
--- JOGO DA TROCA: PONTEIROS EM AÇÃO ---
1. Trocar pontos entre jogadores
2. Somar os pontos
3. Ver quem está vencendo
4. Alterar valor de um jogador
5. Mostrar endereços de memória
6. Sair
```

---

## 🛠️ Funções obrigatórias
```c
void exibirMenu();
void trocar(int *a, int *b);
void somar(int *a, int *b);
void mostrarVencedor(int *a, int *b);
void alterarValor(int *alvo);
void mostrarEnderecos(int *a, int *b);
```

---

## ✅ Exemplo de uso
```c
int jogador1 = 10, jogador2 = 20;
trocar(&jogador1, &jogador2);
somar(&jogador1, &jogador2);
alterarValor(&jogador1);
```

---

## 📎 Entrega
- Envie o arquivo `.c` com o nome `jogo_troca_nome.c` no **Teams** até o final da aula.
- O programa deve compilar e rodar corretamente.
- Comente seu código para facilitar a leitura.

---

## 🧮 Avaliação
| Critério                         | Pontos |
|---------------------------------|--------|
| Uso correto de ponteiros        | 3,0    |
| Funções implementadas corretamente | 3,0 |
| Menu interativo funcional       | 2,0    |
| Organização e comentários       | 2,0    |
| **Total**                       | **10** |

---


**🚀 Boa sorte! Divirta-se codando e domine os ponteiros!**
**💬 Dúvidas? Comente no repositório ou fale com o professor!**

