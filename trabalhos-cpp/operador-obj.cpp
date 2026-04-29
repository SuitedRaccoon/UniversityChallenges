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

//versão de código orientado a objetos

class OperadorBinario{
    private:
        //Atributos
        float realA, realB;
        int intB;

        //Métodos Auxiliares privados => "Método de Fachada"
        float PotenciaAux(float a, int b) const {
            if(b < 1) return 1;
            return a * PotenciaAux(a, b - 1);
        }

    public:
        //Construtor
        OperadorBinario(float a, float b) : realA(a), realB(b), intB(b - fmod(b, 1)){} // intB poderia ser truncado => intB((int)b)

        //Métodos
        float Somar() const {return realA + realB;}
        float Subtrair() const {return realA - realB;}
        float Multiplicar() const {return realA * realB;}
        float Dividir() const {return realA / realB;}
        float Resto() const {return fmod(realA, realB);}
        float Potencia() const {return PotenciaAux(realA, intB);}
        void Imprimir() const {
            cout << "\n--- OPERADORES BINARIOS DE "<< realA <<" e " << realB;
                if(intB != realB) cout << " (Ou seu menor valor inteiro mais próximo: " << intB << ")";
                cout << " ---\n";
            cout << "Soma                   : " << realA << " + " << realB << " = " << Somar() << "\n";
            cout << "Subtracao              : " << realA << " - " << realB << " = " << Subtrair() << "\n";
            cout << "Multiplicacao          : " << realA << " x " << realB << " = " << Multiplicar() << "\n";
            cout << "Divisao                : " << realA << " / " << realB << " = " << Dividir() << "\n";
            cout << "Resto da Divisao       : " << realA << " % " << realB << " = " << Resto() << "\n";
            cout << "Potencia               : " << realA << " ^ " << intB << " = " << Potencia() << "\n";
        }
};

class OperadorUnario{
    private:
        //Atributos
        float real;
        int inteiro;

        //Métodos de Fachada
        int FatorialAux(int a) const {
            if (a < 1) return 1;
            return a * FatorialAux(a - 1);
        }
        int FatorialAditivoAux(int a) const {
            if (a < 1) return 0;
            return a + FatorialAditivoAux(a - 1);
        }
    
    public:
        //Construtor
        OperadorUnario(float a) : real(a), inteiro(a - fmod(a, 1)){}

        //Métodos
        int Fatorial() const {return FatorialAux(inteiro);}
        int FatorialAditivo() const {return FatorialAditivoAux(inteiro);}
        float Sucessor() const {return real + 1;}
        float Oposto() const {return 0 - real;}
        void Imprimir() const {
            cout << "\n--- OPERADORES UNARIOS DE "<< real;
                if(inteiro != real) cout << " (Ou seu menor valor inteiro mais próximo: " << inteiro << ")";
                cout << " ---\n";
            cout << "   Sucessor            : " << real << " + 1 = " << Sucessor() << "\n";
            cout << "   Oposto              : 0 - " << real << " = " << Oposto() << "\n";
            cout << "   Fatorial            : " << inteiro << "! " << " = " << Fatorial() << "\n";
            cout << "   Fatorial Aditivo    : " << inteiro << "? " << " = " << FatorialAditivo() << "\n";
        }
};

int main(){

    float realA = 3, realB = 4;
    cout << "Insira um numero real:         A = ";
    cin >> realA;
    cout << "Insira mais um numero real:    B = ";
    cin >> realB;

    const OperadorBinario binario(realA, realB);
    const OperadorUnario unA(realA), unB(realB);

    binario.Imprimir();
    unA.Imprimir();
    unB.Imprimir();

    return 0;
}