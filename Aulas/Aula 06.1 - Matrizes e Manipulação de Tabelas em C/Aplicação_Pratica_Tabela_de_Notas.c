#include <stdio.h>

int main()
{
    float notas[3][4];
    float soma, media;
    
    // i linhas
    for(int i = 0; i < 3; i++){
        printf("Digite as 4 notas do aluno %d: \n", i + 1);
        for(int j = 0; j < 4; j++){
            printf("Digite a nota %d: ", j + 1);
            scanf("%f", &notas[i][j]);
        }
        printf("\n");    
    }
    for(int i = 0; i < 3; i++){
        soma = 0;
        for(int j = 0; j < 4; j++){
            soma += notas[i][j];
        }
        media = soma/4;
        printf("A média do aluno %d é %.2f\n", i + 1, media);
    }
    return 0;
};
