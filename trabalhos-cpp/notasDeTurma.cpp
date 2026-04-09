#include <stdio.h>

/*Escreva um algoritmo que solicite ao usuario Nome, Idade, Sexo e tres notas de N alunos em uma turma e ao final apresente:
    1) Total de alunos cadastrados
    2) A media das idades dos alunos aprovados/reprovados da turma
    3) Gerar um relatório de alunos aprovados/reprovados na turma

    Tarefas para 2 de Abril: 
        1) Implementar regras de negócio para validação dos dados;
*/

struct Aluno{
    char nome[30];
    int idade;
    char sexo;
    float notas[10];
    bool aprovado = false;
};

int main(){
    int qtdAlunos, qtdNotas, mediaAprovacao;
    
    struct Aluno Turma[100];
    
    printf("Informe a quantidade de alunos: ");
    scanf("%i", &qtdAlunos);

    printf("Informe a quantidade de notas: ");
    scanf("%i", &qtdNotas);

    do{
        printf("Informe a média de aprovação [min: 3 | max: 8]: ");
        scanf("%i", &mediaAprovacao);
    }while(mediaAprovacao < 3 or mediaAprovacao > 8);

    for (int i = 1; i <= qtdAlunos; i++){
        printf("Informe informe o nome do %iº Aluno: ", i);
        scanf("%s", &Turma[i].nome);
        Turma[i].notas[0] = 0;
        do{
            printf("Informe informe a idade de %s: [min: 16 | max: 99] ", Turma[i].nome);
            scanf("%i", &Turma[i].idade);
        }while(Turma[i].idade <= 16 or Turma[i].idade >= 99);

        do{
            printf("Informe informe o sexo de %s: ", Turma[i].nome);
            scanf("%s", &Turma[i].sexo);
        }while(Turma[i].sexo != 'M' and Turma[i].sexo != 'm' and Turma[i].sexo != 'F' and Turma[i].sexo != 'f');

        for (int n = 1; n <= qtdNotas; n++){
            do{
                printf("Informe informe a Nota #%i: [min: 0 | max: 10] ", n);
                scanf("%f", &Turma[i].notas[n]);
            }while(Turma[i].notas[n] < 0 or Turma[i].notas[n] > 10);

            Turma[i].notas[0] += Turma[i].notas[n];
            printf("nota: %0.2f |total: %0.2f \n",Turma[i].notas[n], Turma[i].notas[0]);
        }
        
        Turma[i].notas[0] = Turma[i].notas[0] / qtdNotas;
        printf("Media de %s: %0.2f \n", Turma[i].nome, Turma[i].notas[0]);

        if (Turma[i].notas[0] >= mediaAprovacao) Turma[i].aprovado = true;

    }    

    printf("\n RELATORIO DE APROVADOS\n");

    for(int i=1; i<= qtdAlunos; i++){
        if(Turma[i].aprovado) printf("\n Aluno #%i ----- Nome %s ----- Media %0.2f ----- Aprovado", i, Turma[i].nome, Turma[i].notas[0]);
        else printf("\n Aluno #%i ----- Nome %s ----- Media %0.2f ----- Reprovado", i, Turma[i].nome, Turma[i].notas[0]);
    }
    
    printf("\n\nFIM\n");

    return 0;
}