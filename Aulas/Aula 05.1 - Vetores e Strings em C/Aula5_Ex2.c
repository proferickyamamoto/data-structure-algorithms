#include <stdio.h>

int main()
{
    float notas[4][10][3];
    float soma;
    for(int i = 0; i < 4; i++){
        printf("Digite sua nota %d:", i+1);
        scanf("%f", &notas[i]);
        soma += notas[i];
    }
    float media = soma/4;
    //float media = (notas[0] + notas[1] + notas[2] + notas[3])/4;
    printf("A nota do aluno é %.2f", media);

    return 0;
}
