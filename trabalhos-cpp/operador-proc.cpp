/*
    Escreva um algoritmo que solicite ao usuario dois numeros reais e apresente:
    1) a soma entre eles;
    2) a subtracao do primeiro pelo segundo;
    3) a multiplicacao entre eles;
    4) a divisao do primeiro pelo segundo;
    5) o resto da divisao do primeiro pelo segundo
    6) a exponencial do primeiro valor (base) pelo segundo (expoente) (usar o for)
    7) implementar recursividade no item 6 acima
*/

#include <iostream>
#include <cmath>
using namespace std;

//versão de código procedual

float Somar(float a, float b = 0);
float Subtrair(float a, float b = 0);
float Multiplicar(float a, float b = 1);
float Dividir(float a, float b = 1);
float Resto(float a, float b = 1);
float Potencia(float a, int b = 1);
float Fatorial(int a);
float FatorialAditivo(int a);
bool IsNotInt(float a);
int FloatToInt(float a);

int main(){
    float realA = 3, realB = 4;
    cout << "Insira um numero real:         A = ";
    cin >> realA;
    cout << "Insira mais um numero real:    B = ";
    cin >> realB;
    cout << "Soma               (A + B): " << realA << " + " << realB << " = " << Somar(realA, realB) << "\n";
    cout << "Subtracao          (A - B): " << realA << " - " << realB << " = " << Subtrair(realA, realB) << "\n";
    cout << "Multiplicacao      (A x B): " << realA << " x " << realB << " = " << Multiplicar(realA, realB) << "\n";
    cout << "Divisao            (A / B): " << realA << " / " << realB << " = " << Dividir(realA, realB) << "\n";
    cout << "Resto da Divisao   (A % B): " << realA << " % " << realB << " = " << Resto(realA, realB) << "\n";
    cout << "Potencia           (A ^ B): " << realA << " ^ " << realB << " = " << Potencia(realA, realB) << "\n";

    if(IsNotInt(realA)){
        realA = FloatToInt(realA);
    }
    cout << "   Fatorial          (A!) : " << realA << "! " << " = " << Fatorial(realA) << "\n";
    cout << "   Fatorial Aditivo  (A?) : " << realA << "? " << " = " << FatorialAditivo(realA) << "\n";
    cout << "         Proporção (A?/A!): " << realA << "?/" << realA << "! = " << FatorialAditivo(realA) / Fatorial(realA) << "\n"; 

    if(IsNotInt(realB)){
        realB = FloatToInt(realB);
    }
    cout << "   Fatorial          (B!) : " << realB << "! " << " = " << Fatorial(realB) << "\n";
    cout << "   Fatorial Aditivo  (B?) : " << realB << "? " << " = " << FatorialAditivo(realB) << "\n";
    cout << "         Proporção (B?/B!): " << realB << "?/" << realB << "! = " << FatorialAditivo(realB) / Fatorial(realB) << "\n"; 

    return 0;
}

float Somar(float a, float b){return a + b;}
float Subtrair(float a, float b){return a - b;}
float Multiplicar(float a, float b){return a * b;}
float Dividir(float a, float b){return a / b;}
float Resto(float a, float b){return fmod(a, b);}
float Potencia(float a, int b){
    if(b < 1) return 1;
    return a * Potencia(a, b - 1);
}
float Fatorial(int a){
    if (a < 1) return 1;
    return a * Fatorial(a - 1);
}
float FatorialAditivo(int a){
    if (a < 1) return 0;
    return a + FatorialAditivo(a - 1);
}
bool IsNotInt(float a){
    if(fmod(a, 1) == 0) return false;
    return true; 
}
int FloatToInt(float a){return a - fmod(a, 1);}
