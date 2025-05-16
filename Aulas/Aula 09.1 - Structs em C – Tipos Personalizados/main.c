#include <stdio.h>
#include <string.h>

struct Aluno{
    char nome[50];
    int idade;
    float notas[3];
    float media;
};

struct livros{
    char nome[50];
    int anoLancamento;
};

void exibirAluno(struct Aluno a) {
    printf("Nome: %s\n", a.nome);
    printf("Idade: %d\n", a.idade);
    float soma = 0;
    for(int i = 0; i < 3; i++){
        soma += a.notas[i];
    }
    a.media = soma/3;
    printf("Média: %.2f\n", a.media);
    
}

int main()
{   
    int qtdeAlunos;
    printf("Digite a quantidade de alunos: ");
    scanf("%d", &qtdeAlunos);
    struct Aluno turma[qtdeAlunos];
    for(int i = 0; i < qtdeAlunos; i++){
        printf("Aluno %d\n", i + 1);
        printf("Digite o nome: ");
        scanf("%s", turma[i].nome);
        printf("Digite a idade: ");
        scanf("%d", &turma[i].idade);
        for(int j = 0; j < 3; j++){
            printf("Digite a nota %d: ", j + 1);
            scanf("%f", &turma[i].notas[j]);
        }
        printf("\n");
    }
    for(int i = 0; i < qtdeAlunos; i++){
        exibirAluno(turma[i]);
        //if(turma[i].media >= 7){
            exibirAluno(turma[i]);
            //printf("Aluno %d\n", i + 1);
            //printf("%s\n", turma[i].nome);
            //printf("%d anos\n", turma[i].idade);
          //  printf("\n");
        //}
    }
    
   /* strcpy(a1.nome, "Erick");
   a1.idade = 12;
   a1.notas = 6;
   printf("O nome é: %s \n", a1.nome);
   printf("A idade é: %d \n", a1.idade);
   printf("A média do aluno é: %.2f \n", a1.notas);*/

    return 0;
}