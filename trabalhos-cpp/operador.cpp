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


float Somar(float a, float b = 0){return a + b;}
float Subtrair(float a, float b = 0){return a - b;}
float Multiplicar(float a, float b = 1){return a * b;}
float Dividir(float a, float b = 1){return a / b;}
float Resto(float a, float b = 1){return fmod(a, b);}
float Potencia(float a, int b = 1){
    if(b < 1) return 1;
    return a * Potencia(a, b - 1);
}
float Fatorial(int a){
    if (a < 1) return 1;
    return a * Fatorial(a - 1);
}
float FatorialAditivo(int a){
    if (a < 1) return 0;
    return a + Fatorial(a - 1);
}
bool IsNotInt(float a){
    if(fmod(a, 1) == 0) return false;
    return true; 
}
int FloatToInt(float a){return a - fmod(a, 1);}

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
    float propA = 100 * ((Fatorial(realA) / FatorialAditivo(realA)) - 1);
    cout << "                 Proporção: A! é " << propA << "% maior que A?\n"; 

    if(IsNotInt(realB)){
        realB = FloatToInt(realB);
    }
    cout << "   Fatorial          (B!) : " << realB << "! " << " = " << Fatorial(realB) << "\n";
    cout << "   Fatorial Aditivo  (B?) : " << realB << "? " << " = " << FatorialAditivo(realB) << "\n";
    float propB = 100 * ((Fatorial(realB) / FatorialAditivo(realB)) - 1);
    cout << "                 Proporção: B! é " << propB << "% maior que B?\n"; 

    return 0;
}