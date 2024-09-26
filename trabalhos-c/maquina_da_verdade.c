#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
// Tamanho máximo da expressão
#define MAXIMO 100 
// Máximo de variáveis suportadas
#define VARIAVEIS_MAXIMO 10 

// Função responsavel pelo "Não" - '~'.
int InversorNao(int p) {
    return !p;
}

// Função responsável pelo "E" - '^'.
int E(int p,int q){
    return p && q;
}

// Função responsável pelo "Ou" - 'v', ou como usado neste programa '|'.
int Ou(int p,int q){
    return p || q;
}

// Função responsável pela "Operação Condicional" - '->', ou como usado neste programa, '>'.
int Condicional(int p, int q){
    if(p == 1 && q == 0){
        return 0;
    } else {
        return 1;
    }
}

// Função responsável pela "Operação Condicional Dupla" - '<->', ou como usado neste programa, '<'.
int DuplaCondicional(int p, int q){
    if((p == 1 && q == 1) || (p == 0 && q == 0)){
        return 1;
    } else {
        return 0;
    }
}

// Definindo a Ordem de Precedência. Se o operador for um '~', ele será contabilizado antes dos demais.
int precedencia(char op) {
    if (op == '>' || op == '<') {
        return 1;
    } else if (op == '|') {
        return 2;
    } else if (op == '^') {
        return 3;
    } else if (op == '~') {
        return 4; // maior precedência para a negação unária
    }
    return 0;
}

// Função que passará para o programa a instrução do que fazer no caso de cada operador encontrado na expressão.
int AplicaOperador(int a, int b, char operador){
    switch(operador){
        case '^': return E(a, b);
        case '|': return Ou(a, b);
        case '>': return Condicional(a, b);
        case '<': return DuplaCondicional(a, b);
    }
    return 0;
}

// Pela grande precedência, e por afetar apenas um valor, aplicamos o NÃO separadamente.
int AplicaOperadorNao(int a, char operador) {
    if (operador == '~') {
        return InversorNao(a);
    }
    return 0;
}

// Função que realiza o algoritmo "Shutting Yard" de Dijkstra.
void ShuttingYard(char* expressao, char* saida){
    //indices para os vetores string da pilha e da saída.
    int i, k = 0;   
    //vetor da pilha, com tamanho máximo pré-definido.     
    char pilha[MAXIMO];
    //define o índice do topo da pilha. 
    int topo = -1;      
    //corre por todos os índices da string da expressão.
    for(i=0; expressao[i]; ++i){
        //isalpha checa se o valor do índice pertence ao conjunto de letras do Alfabeto.
        if(isalpha(expressao[i])){          
            //caso pertença, ele o adiciona no índice k da pilha, e a avança em 1.
            saida[k++] = expressao[i];      
        } else if(expressao[i] == '('){
            //caso não pertença e for um '(', o empilha.
            pilha[++topo] = expressao[i];   
        } else if(expressao[i] == ')'){
            //caso não pertença e for um ')', desempilha até encontrar um '('.     
            while(topo != -1 && pilha[topo] != '('){
                saida[k++] = pilha[topo--]; 
            }
            //ao fim, remove o '(' da pilha.
            topo--;                         
        } else if(expressao[i] == '~') {
            //empilha a negação.
            pilha[++topo] = expressao[i];
        } else {                            
            while(topo != -1 && precedencia(pilha[topo]) >= precedencia(expressao[i])){
                //caso não pertença ao alfabeto e não sejam os '(' e ')', os identifica e desempilha os de maior precedência.
                saida[k++] = pilha[topo--]; 
            }
            //posiciona os restantes no topo da pilha.
            pilha[++topo] = expressao[i];   
        }
    }
    //desempilha os demais caracteres.
    while(topo != -1){                      
        saida[k++] = pilha[topo--];
    }
    //finaliza a string da saída.
    saida[k] = '\0';                        
}

// Função que avalia a operação de saída.
int AvaliaSaida(char* exp, int* valores) {
    int i;
    int pilha[MAXIMO];
    int topo = -1;

    for (i = 0; exp[i]; ++i) {
        if (isalnum(exp[i])) {
            pilha[++topo] = valores[exp[i] - 'p'];
        } else if (exp[i] == '~') {
            int val = pilha[topo--];
            pilha[++topo] = AplicaOperadorNao(val, exp[i]);
        } else {
            int val1 = pilha[topo--];
            int val2 = pilha[topo--];
            pilha[++topo] = AplicaOperador(val2, val1, exp[i]);
        }
    }
    return pilha[topo];
}

// Função que percorre a expressão de entrada e indentifica todas as variáveis presentes.
void findVariables(char* exp, char* variables, int* varCount) {
    int found[26] = {0};
    *varCount = 0;

    for (int i = 0; exp[i]; ++i) {
        if (isalpha(exp[i]) && !found[exp[i] - 'p']) {
            found[exp[i] - 'p'] = 1;
            variables[(*varCount)++] = exp[i];
        }
    }
}

// Função para imprimir a tabela da verdade com base na expressão de entrada.
void ImprimeTabela(char* entrada, char* variaveis, int contaVariaveis){
    //descobre quantas linhas a tabela deverá ter.
    int linhas = pow(2, contaVariaveis);
    //definimos a variável de nossa saída.
    char saida[MAXIMO];

    //chamamos nosso algoritmo para fazer a notação polonesa reversa.
    ShuttingYard(entrada, saida);

    //imprime o cabeçalho, mostrando todas as variáveis utilizadas e por ultimo a expressão de entrada.
    printf("\nSUA TABELA DA VERDADE:\n");
    printf("----------------------\n");
    for (int i = 0; i < contaVariaveis; ++i){
        printf("%c  ", variaveis[i]);
    }
    printf("%s\n", entrada);

    //imprime as linhas da tabela, contendo todos os valores possíveis das váriaveis e o resultado final.
    for(int i = 0; i < linhas; ++i){
        int valores[VARIAVEIS_MAXIMO] = {0};
        for(int j = 0; j < contaVariaveis; ++j){
            valores[j] = (i >> (contaVariaveis - j - 1)) & 1;
            printf("%d  ", valores[j]);
        }
        int resultado = AvaliaSaida(saida, valores);
        printf("%d\n", resultado);
    }
}

//Função principal que rodará todas as funções acima para e que irá gerar nosso programa executável!
int main(){
    //declaramos todas as funções que serão utilizadas diretamente pela main().
    void findVariables(char* exp, char* variables, int* varCount),
        ImprimeTabela(char* entrada, char* variaveis, int contaVariaveis);

    //e todas as variáveis que serão utilizadas diretamente por tais funções.
    char entrada[MAXIMO];
    char variaveis[VARIAVEIS_MAXIMO];
    int contaVariaveis;
    
    printf("\n\n****** BEM VINDO! ******\n\n ");

    //laço de repetição para o usuário não ter que reabrir o programa toda vez que desejar criar uma tabela.
    bool continuar = true;
    while(continuar){
        //comando inicial para indicar ao usuário que pode entrar com uma expressão.
        printf("\nDigite uma expressao logica: ");
        scanf("%s", entrada);

        //chamamos as funções que declaramos previamente, onde todo o corpo do programa será executado dentro da main().
        findVariables(entrada, variaveis, &contaVariaveis);
        ImprimeTabela(entrada, variaveis, contaVariaveis);

        
        //para fins didáticos, aqui serão impressas a expressão de entrada do usuário e a expressão de saída após aplicar a Notação Polonesa Reversa pelo método Shutting Yard.
        char saida[MAXIMO];
        ShuttingYard(entrada, saida);
        printf("\nEsta foi sua Entrada: %s\n", entrada);
        printf("Esta foi a Saida em RPN: %s\n", saida);
        
        
        //requerimento ao usuário para o programa saber se deve continuar ou se deve terminar a execução
        printf("\n\nEntre '0' para sair.\nEntre qualquer outro valor para iniciar uma nova tabela.\n");
        int escolha;
        scanf("%d", &escolha);
        if(escolha == 0){
            return continuar = false;
        }
    }

    //comando para a main() retornar o valor 0 e indicar para o sistema que o programa terminou a execução.
    return 0;
}