/*
	Name: TRIAGIUM
	Copyright: 
	Author: Gustavo Zanetti Saud & Livya Carneiro Trindade
	Date: 18/05/24 14:01
	Description: Programa criado para auxiliar no processo de triagem em um ambiente hospitalar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //biblioteca responsável por auxiliar com variáveis booleanas.

//CONSTANTES GLOBAIS
#define MAXIMO 250 //Número Máximo de caracteres para nome do paciente e observações.
#define DIA_HOJE 19     // 
#define MES_HOJE 5      // Data do dia atual, para fins de se calcular a idade do paciente.
#define ANO_HOJE 2024   //

//VARIÁVEIS GLOBAIS
int corPulseira = 3; //após o sistema dar uma pulseira, ele pode acompanhar caso a situação se agrave e aumentar esse índice.
bool temPulseira = false;               // variáveis booleanas responsáveis por acompanhar as respostas
bool temAVC = false;                    // do paciente e interpretar quais dos sintomas mais graves ele
bool temDor = false;                    // possui.
int indiceDor = 0;                      // indiceDor é um inteiro responsável por receber o valor que o
bool temDificuldadeRespirar = false;    // paciente menciona ao ser requisitado no questionário, caso
bool temConvulsao = false;           // reporte estar com dor.
char infoAdicional[MAXIMO]; //string responsável por receber as observações adicionais reportadas pelo paciente durante a triagem.

//constructo que irá conter todas as informações sobre o paciente:
struct Paciente{ 
    int nascDia, nascMes, nascAno; // data de nascimento;
    char nome[MAXIMO];  // nome completo;
    int pressaoSistolica, pressaoDiastolica, saturacao, batimento;  // sinais vitais;
    double temperatura;                                             //
};

//função responsável por limpar o buffer stdin antes de se utilizar uma função fgets.
void clear_stdin(void) { 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//função responsável por calcular a idade do paciente com base na data de nascimento fornecida.
int CalculaIdade(int dia, int mes, int ano){ 
    int difAno = ANO_HOJE - ano;
    int difMenos = difAno - 1;
    if(mes < MES_HOJE){
        return difAno;
    }
    if(mes > MES_HOJE){
        return difMenos;
    }

    int difDias = dia - DIA_HOJE;
    if(difDias >= 0){
        return difAno;
    }
    if(difDias < 0){
        return difMenos;
    }
    return 0;
}

//função responsável por alterar a cor da pulseira do paciente para sempre a de maior prioridade, conforme suas respostas apresentam uma nova situação.
void Pulseira(int cor){
    if(cor <= corPulseira){
        corPulseira = cor;
    }
} 

//função responsável por imprimir a pulseira que está sendo indicada pelo programa.
void ImprimePulseira(){
    switch(corPulseira){
        case 0: printf("\n---- EMERGENCIA - PULSEIRA VERMELHA ----\n\n\n\n");
            break;
        case 1: printf("\n---- MUITA URGENCIA - PULSEIRA LARANJA ----\n\n\n\n");
            break;        
        case 2: printf("\n---- URGENCIA - PULSEIRA AMARELA ----\n\n\n\n");
            break;
        case 3: printf("\n---- POUCO URGENTE - PULSEIRA VERDE ----\n\n\n\n");
            break;
        }
}

//função responsável por separadamente definir o status do paciente como um caso de extrema emergência.
int AVC(){
    int resultado;
    printf("\nPaciente se queixa de DOR FORTE NO PEITO ou apresenta SINAIS DE AVC? (1-sim / 2-nao) \n");
    scanf("%d", &resultado);
    if(resultado == 1 ){
        Pulseira(0);
        temAVC = true;
        return 1;
    } 
    return 0;
}

//função responsável por guiar o questionário ao paciente sobre seus sintomas e usar essas informações para definir o status do paciente e sua pulseira de acordo.
int Sintomas(){
    void Pulseira(int cor);

    //checa primeiramente se o paciente tem sinais de AVC, e se tiver, já sai da função.
    if(AVC() == 1){
        return 0;
    }

    //identificando e avaliando a dor do paciente.
    int resultado;
    printf("\nO paciente reporta dor? (1-sim/ 2-nao): \n");
    scanf("%d", &resultado);
    if(resultado == 1){
        temDor = true;
        printf("De qual intensidade?\nQuase sem dor 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 Dor insuportavel\n");
        scanf("%d", &indiceDor);
        if(indiceDor >= 8){
            Pulseira(2);
        }
    }

    //identificando se o paciente possui sintomas de problemas respiratórios.
    printf("\nO paciente apresenta dificuldade para respirar? (1-sim / 2-nao): \n");
    scanf("%d", &resultado);
    if (resultado == 1) {
       temDificuldadeRespirar = true;
       Pulseira(1);
    } 

    //indentificando se o paciente possui sintomas de dano cerebral.
    printf("\nO paciente tem alteracoes na visao ou na audicao ou reporta crises convulsivas epilepticas? (1-sim/ 2-nao): \n" );
    scanf("%d", &resultado);
    if (resultado == 1 ) {
        temConvulsao = true;
        Pulseira(2);
    }

    //espaço destinado a observações obtidas ao longo da entrevista com o paciente.
    clear_stdin();
    printf("\nObservacoes ou queixas adicionais:\n");
    fgets(infoAdicional, sizeof(infoAdicional), stdin);

    return 0;
}

//função responsável por avaliar os Sinais Vitais do paciente, e indicar suas pulseiras de acordo.
int SinaisVitais(int pressaoSistolica, int saturacao, int batimento, double temperatura){
    //avaliação da Temperatura Corporal do Paciente.
    if(temperatura >= 37.6 && temperatura < 39.6){
        printf("----- FEBRE BAIXA \n");
        Pulseira(2);
    } else if(temperatura >= 39.6){
        printf("***** FEBRE ALTA\n ");
        Pulseira(1);
    } else {
        printf("..... TEMPERATURA ESTAVEL \n");
        Pulseira(3);
    }
    
    //avaliação da Pressão Arterial do Paciente.
    if(pressaoSistolica >= 140 && pressaoSistolica < 160){
        printf("----- PRESSAO ARTERIAL ACIMA DA MEDIA\n");
        Pulseira(2);
    } else if(pressaoSistolica >= 160 && pressaoSistolica < 180){
        printf("----- PRESSAO ARTERIAL ALTA URGENTE\n");
        Pulseira(1);
    } else if(pressaoSistolica >= 180){
        printf("***** CRISE HIPERTENSIVA EMERGENCIAL\n");
        Pulseira(0);
    } else {
        printf("..... PRESSAO ARTERIAL ESTAVEL\n");
        Pulseira(3);
    }
    
    //avaliação da Saturação de O2 no sangue do Paciente.
    if(saturacao <= 90){
        printf("***** SATURACAO BAIXA EMERGENCIAL\n ");
        Pulseira(0);
    } else {
        printf("..... SATURACAO ESTAVEL\n");
        Pulseira(3);
    }
    
    //avaliação da frequência cardiaca do paciente.
    if(batimento >= 130 && batimento < 170){
        printf("----- TAQUICARDIA\n");
        Pulseira(1);
    } else if(batimento >= 170){
        printf("***** TAQUICARDIA EMERGENCIAL\n");
        Pulseira(0);
    } else {
        printf("..... FREQUENCIA CARDIACA ESTAVEL\n");
        Pulseira(3);
    }
    return 0;
}

//função responsável por imprimir na tela o resumo da sessão de triagem, com informações sobre o paciente, seus sinais vitais, seus sintomas e observações entradas pelo profissional de saúde responsável.
void Resumo(char nome[MAXIMO], int nascDia, int nascMes, int nascAno, double temperatura, int saturacao, int batimento, int pressaoSistolica, int pressaoDiastolica, char infoAdicional[MAXIMO]){
    printf("\n\n%s%d anos de vida\n",nome, CalculaIdade(nascDia, nascMes, nascAno));
    printf("\nTemperatura corporal: %.1f C\nSaturacao: %d SpO2\nBatimento Cardiaco: %d BPM\nPressao Arterial: %d X %d mmHg\n\n", temperatura, saturacao, batimento, pressaoSistolica, pressaoDiastolica);
    SinaisVitais(pressaoSistolica, saturacao, batimento, temperatura);
    if(temAVC){
        printf("\n***** DORES NO PEITO / SINAIS DE AVC\n");
    }
    if(temDor){
        printf("\n***** DOR DE NIVEL %d\n", indiceDor);
    }
    if(temDificuldadeRespirar){
        printf("\n***** DIFICULDADE DE RESPIRAR\n");
    }
    if(temConvulsao){
        printf("\n***** SINTOMAS DE DANO CEREBRAL\n");
    }
    printf("\nObservacoes: %s\n\n", infoAdicional);
    ImprimePulseira();
}

//função principal do programa.
int main(){
    //declaração de todas as funções usadas diretamente dentro da main().
    int Sintomas();
    void Resumo(char nome[MAXIMO], int nascDia, int nascMes, int nascAno, double temperatura, int saturacao, int batimento, int pressaoSistolica, int pressaoDiastolica, char infoAdicional[MAXIMO]);
    
    struct Paciente pac; //chamada do constructo Paciente, recebendo o nome de "pac".
    
    int continuar = 1;
    while(continuar){
        system("cls"); //função para limpar a tela do cmd toda vez que o programa se inicia.

        //cabeçalho de boas vindas.
        printf("\n\n==========================================================\n===== Bem Vindo a Plataforma de Triagem Automatizada =====\n==========================================================\n");
        printf("\nPressione ENTER para continuar...");
        clear_stdin();

        //entrada de nome e data de nascimento do paciente.
        printf("\n\n====== CADASTRO DE PACIENTE =======\n\n");
        printf("Digite o nome do paciente: ");
        fgets(pac.nome, sizeof(pac.nome), stdin);
        printf("Digite o ano de nascimento do paciente no formato DD/MM/AAAA: ");
        scanf("%d/%d/%d", &pac.nascDia, &pac.nascMes, &pac.nascAno);

        //entrada de sinais vitais do paciente.
        printf("\n\n===== COLETA DE SINAIS VITAIS =====\n\n");
        printf("Temperatura (Celcius): ");
        scanf("%lf", &pac.temperatura);
        printf("Saturacao (SpO2): ");
        scanf("%d", &pac.saturacao);
        printf("Batimento Cariaco (BPM): ");
        scanf("%d", &pac.batimento);
        printf("PA Sistolica (mmHg): ");
        scanf("%d", &pac.pressaoSistolica);
        printf("PA Diastolica (mmHg): ");
        scanf("%d", &pac.pressaoDiastolica);

        //entrada de respostas do paciente com relação à seus sintomas.
        printf("\n\n======= TRIAGEM DE SINTOMAS =======\n\n");
        Sintomas();
        
        //impressão do sumário de todas as informações obtidas, assim como qual a pulseira é adequada para o pa,ciente em questão.
        Resumo(pac.nome, pac.nascDia, pac.nascMes, pac.nascAno, pac.temperatura, pac.saturacao, pac.batimento, pac.pressaoSistolica, pac.pressaoDiastolica, infoAdicional);

        printf("\n\nSe deseja fechar o programa ENTRE 0...\nSe deseja iniciar um novo paciente ENTRE qualquer numero...\n");
        scanf("%d", &continuar);
    }
    
    return 0;
}

