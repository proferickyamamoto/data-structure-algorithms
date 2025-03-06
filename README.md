# 🚀 Estruturas de Dados e Algoritmos em C

## 📌 Sobre o Curso
Este repositório contém o material do curso **Estruturas de Dados e Algoritmos em C**. Ele cobre desde os fundamentos da programação até estruturas avançadas.

## 📚 Conteúdo
- [Aulas](#slides-das-aulas)
- [Exercícios](#exercícios)
- [Projetos](#projetos)

## 📌 Online: Programação em C
 [Replit](https://replit.com/new) é uma plataforma online para desenvolvedores, independente de uma máquina local e suas configurações.

## 📌 Local: Configuração do VS Code para Programação em C
### 1️⃣ Instalar o VS Code
Se ainda não tem o Visual Studio Code, faça o download e instale a versão mais recente:

 [Baixar VS Code](https://code.visualstudio.com/)

---
### 2️⃣ Instalar um Compilador C (GCC)
O VS Code não compila C por conta própria, então precisamos instalar um compilador.

📌 Windows (Instalar o MinGW-w64)
1. Baixe o MinGW-w64:
   [MinGW-w64 Compiler]([https://winlibs.com/](https://winlibs.com/#download-release)) 

2. Instale a versão GCC (Instale a última versão).

3. Adicione o compilador ao PATH:

 - No Explorador de Arquivos, copie o caminho da pasta bin do MinGW (ex: C:\mingw-w64\bin).

 - No Windows, pesquise "Variáveis de Ambiente", clique em Editar as variáveis de ambiente do sistema.

 - Em Variáveis do sistema, selecione Path → Editar → Novo → Cole o caminho da pasta bin do MinGW.

 - Clique em OK e reinicie o computador.

### 📌 Verifique se a instalação foi bem-sucedida:

Abra o Prompt de Comando (cmd) e digite:
```bash
gcc --version
```
Se aparecer a versão do GCC, está tudo certo! ✅

### 📌 Linux (Ubuntu, Debian)
Abra o terminal e instale o GCC com:

```bash
sudo apt update
sudo apt install build-essential -y
```
Depois, verifique a instalação com:

```bash
gcc --version
```
### 📌 macOS
No terminal, instale o compilador usando:

```bash
xcode-select --install
```
---
### 3️⃣ Instalar Extensões do VS Code
Para melhorar a experiência de programação em C, instale estas extensões no VS Code:

🔹 C/C++ (by Microsoft) – Adiciona suporte a sintaxe e IntelliSense.

🔹 Code Runner – Permite executar códigos com um clique.

🔹 Better C++ Syntax – Melhora a coloração do código.

📌 Para instalar extensões:

No VS Code, clique em Extensões (Ctrl + Shift + X).
Pesquise o nome da extensão e clique em Instalar.

---
### 4️⃣ Criar um Projeto em C no VS Code
Abra o VS Code e crie uma pasta para seu projeto (C:\Projetos_C).
Crie um novo arquivo e nomeie como programa.c.
Escreva o código:
```c
#include <stdio.h>

int main() {
    printf("Olá, mundo!\n");
    return 0;
}
```
---
### 5️⃣ Configurar o Terminal para Compilar e Executar
📌 Para compilar e rodar o código no terminal integrado do VS Code:

Abra o terminal no VS Code (Ctrl + J).
Digite o comando de compilação:
```bash
gcc programa.c -o programa
Execute o programa com:
```
```bash
./programa   # Linux/macOS
programa.exe # Windows
```
---
### 6️⃣ Configurar Atalho para Compilar e Executar Automaticamente


### 📌 Para rodar o código com apenas um clique:

Vá para "Arquivo" → "Preferências" → "Configurações".
Pesquise por "Code Runner" e ative a opção "Run in Terminal".
Agora, basta pressionar Ctrl + Alt + N para executar o código.

### 📌 Caso precise configurar manualmente:

Vá até "Executar" → "Adicionar Configuração".
Selecione "C/C++: Executar o arquivo ativo" e edite o .vscode/tasks.json:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compilar e Executar",
            "type": "shell",
            "command": "gcc",
            "args": [
                "${file}",
                "-o",
                "${fileDirname}/programa",
                "&&",
                "${fileDirname}/programa"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```
Agora, sempre que quiser compilar e rodar, basta pressionar Ctrl + Shift + B! 🚀

### 🎯 Teste sua Configuração

📌 Para garantir que tudo está funcionando:

Escreva o código abaixo:
```c
#include <stdio.h>

int main() {
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);
    printf("Você digitou: %d\n", numero);
    return 0;
}
```

Compile e execute (Ctrl + Alt + N ou Ctrl + Shift + B).
Se o programa rodar corretamente, seu ambiente está pronto! ✅

---
### 🔥 Conclusão
Agora seu VS Code está totalmente configurado para programação em C! 🚀

---

### 📌 Resumo das etapas:

✅ Instalamos o compilador GCC.

✅ Instalamos extensões essenciais no VS Code.

✅ Criamos um primeiro programa e aprendemos a compilar.

✅ Configuramos atalhos para facilitar a execução.

Agora você pode começar a explorar e praticar a programação em C! 🏆

💡 Dúvidas? Comente no repositório ou me pergunte, nunca deixe para depois! 🎯
