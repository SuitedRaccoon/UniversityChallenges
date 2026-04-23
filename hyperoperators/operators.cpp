#include <stdio.h>
#include <stdlib.h>

unsigned int Successor(unsigned int a){
    return ++a;
}

unsigned int Addition(unsigned int a, unsigned int b = 0){
    unsigned int resultado = a;
    for(int i=0; i<b; ++i){
        resultado = Successor(resultado);
    }
    return resultado;
}

unsigned int Multiplication(unsigned int a, unsigned int b = 1){
    unsigned int resultado = 0;
    for(int i=0; i<b; ++i){
        resultado = Addition(resultado, a);
    }
    return resultado;
}

unsigned int Exponentiation(unsigned int a, unsigned int b = 0){
    unsigned int resultado = 1;
    for(int i=0; i<b; ++i){
        resultado = Multiplication(resultado, a);
    }
    return resultado;
}

unsigned int Tetration(unsigned int a, unsigned int b = 0){
    unsigned int resultado = a;
    for(int i=0; i<b; ++i){
        resultado = Exponentiation(resultado, a);
    }
    return resultado;
}

unsigned int Pentation(unsigned int a, unsigned int b = 0){
    unsigned int resultado = a;
    for(int i=0; i<b; ++i){
        resultado = Tetration(resultado, a);
    }
    return resultado;
}

void Imprime(unsigned int a, unsigned int b){
    printf("Imprimindo Hiperoperações dos valores %u e %u\n\n", a, b);
    printf("    succ:   %u  +  1  =  %u    %u  +  1  =  %u\n", a, Successor(a), b, Successor(b));
    printf("    add:    %u  +  0  =  %u    %u  +  %u  =  %u\n", a, Addition(a), a, b, Addition(a, b));
    printf("    mult:   %u  x  1  =  %u    %u  x  %u  =  %u\n", a, Multiplication(a), a, b, Multiplication(a, b));
    printf("    exp:    %u  ^  0  =  %u    %u  ^  %u  =  %u\n", a, Exponentiation(a), a, b, Exponentiation(a, b));
    printf("    tet:    %u ^ ^ 0  =  %u    %u ^ ^ %u  =  %u\n", a, Tetration(a), a, b, Tetration(a, b));
    printf("    pen:    %u ^^^ 0  =  %u    %u ^^^ %u  =  %u\n\n", a, Pentation(a), a, b, Pentation(a, b));
}

int main(){
    unsigned int a = 2, b = 1, resposta;
    bool continua;

    system("clear");
    printf("---- Bem vindo ao Hiperoperador! ----\n\n");

    do{
        Imprime(a,b);
        printf("\nDeseja hiperoperar com outros valores? (1 - SIM | 0 - NAO)  ");
        scanf("%i", &resposta);
        if(resposta != 0){
            continua = true;
            printf("\nEntre com um número inteiro:   ");
            scanf("%i", &a);
            printf("\n--- Hyperoperando sob o valor %u ---\n", a);
            printf("\nEntre com outro número inteiro:  ");
            scanf("%i", &b);
            printf("\n--- Hyperoperando o valor %u por %u ---\n", a, b);
        }
        else continua = false;
    }while(continua);
    printf("\n---- Até a próxima! ----\n\n");


    return 0;
}