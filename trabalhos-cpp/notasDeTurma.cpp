/* Escreva um algoritmo que solicite ao usuário Nome, Idade, Sexo e três notas de N alunos em uma turma e ao final, apresente: 
1) total de alunos cadastrados
2) a media das idades dos alunos aprovados/reprovados da turma
3) gerar um relatório de alunos aprovados/reprovados na turma

Tarefas para semana que vem 02/04
1) Implementar regras de negócio para validação dos dados
	1.1) qtdProva 1 a 10 -
	1.2) Idade: 17 a 115 -
	1.3) Notas 0 a 10
*/

#include <stdio.h>


struct Aluno{
    char nome[30];
    int idade;
    char sexo;
    float notas[10];
    bool aprovado = false;
};

int main(){
    int qtdAlunos, qtdNotas, mediaAprovacao, masc = 0, fem = 0, aprovM = 0, aprovF = 0, aprovados;
    float media = 0, mediaTurma, mediaAprovados, notasM = 0, notasF = 0, notasMAprov = 0, notasFAprov = 0;
        
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
        Turma[i].notas[0] = media;
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

            media += Turma[i].notas[n];
            printf("nota #%i: %0.2f |total: %0.2f \n", n, Turma[i].notas[n], media);
        }
        
        media = media / qtdNotas;
        printf("Media de %s: %0.2f \n", Turma[i].nome, media);

        if(media >= mediaAprovacao) Turma[i].aprovado = true;

        if(Turma[i].sexo == 'M' or 'm'){
            masc++;
            notasM += media;
            if(Turma[i].aprovado){
                aprovM++;
                notasMAprov += media;
            }
        }else{
            fem++;
            notasF += media;
            if(Turma[i].aprovado){
                aprovF++;
                notasFAprov += media;
            }
        }
    }

    aprovados = aprovM + aprovF;
    mediaTurma = (notasM + notasF) / qtdAlunos;
    mediaAprovados = (notasMAprov + notasFAprov) / aprovados;

    printf("\n RELATORIO FINAL\n");

    printf("\n QUANTIDADE TOTAL DE ALUNOS: %i", qtdAlunos);
    printf("\n SEXO: MASCULINO %i | FEMININO %i", masc, fem);
    printf("\n MEDIA DE APROVACAO: %0.2f | MEDIA DA TURMA: %0.2f",mediaAprovacao, mediaTurma);
    printf("\n TOTAL DE APROVADOS: %i, isto é %0.2f%% da turma | MEDIA DOS APROVADOS: %0.2f", aprovados, 100 * aprovados / qtdAlunos, mediaAprovados);
    printf("\n MEDIA MASCULINA: %0.2f | MEDIA FEMININA: %0.2f", notasM / masc, notasF / fem);
    printf("\n MEDIA MASCULINA APROVADOS: %0.2f | MEDIA FEMININA APROVADOS: %0.2f", notasMAprov / aprovM, notasFAprov / aprovF);

    printf("\n LISTA FINAL\n");

    for(int i=1; i<= qtdAlunos; i++){
        if(Turma[i].aprovado) printf("\n Aluno #%i ----- Nome %s ----- Media %0.2f ----- Aprovado", i, Turma[i].nome, media);
        else printf("\n Aluno #%i ----- Nome %s ----- Media %0.2f ----- Reprovado", i, Turma[i].nome, media);
    }
    
    printf("\n\nFIM\n");

    return 0;
}