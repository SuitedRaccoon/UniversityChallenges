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

/*
    class Mae{
        protected:
            tipo atributo = valor;                          => protected funciona de forma parecida com private, mas deixa as filhas acessarem diretamente!
        public:
            virtual tipo ClasseBaseGenerica() const = 0;    => não implementada propositalmente para a filha implementar!
    };                                                      => virtual -> significa que este método será sobrescrito pelas classes filhas

    class Filha : public Mae{
        private:
            tipo outroAtributo = valor;
        public:
            tipo ClasseBaseGenerica() const override{       => override == "estou sobrescrevendo"
                |> implementação
            }
    };

    Visibilidade| Mesma Classe  | Classes Filhas| Fora da Classe| 
    public      | true          | true          | true          |              
    protected   | true          | true          | false         |              
    private     | true          | false         | false         |              

*/


// Classe Mãe
class Operador{ 
    protected:
        //Atributos base
        float real;
        int inteiro;
    public:
        //Construtor
        Operador(float a) : real(a), inteiro((int) a){}

        //Classe que será herdada pelas filhas
        virtual void Imprimir() const = 0;
};

// Classe Filha
class Unario : public Operador{
    private:
        //Atributos declarados na classe mãe!
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
        Unario(float a) : Operador(a) {}

        //Métodos
        int Fatorial() const {return FatorialAux(inteiro);}
        int FatorialAditivo() const {return FatorialAditivoAux(inteiro);}
        float Sucessor() const {return real + 1;}
        float Oposto() const {return 0 - real;}
        void Imprimir() const override {
            cout << "\n--- OPERADORES UNARIOS DE "<< real;
                if(inteiro != real) cout << " (Ou seu menor valor inteiro mais próximo: " << inteiro << ")";
                cout << " ---\n";
            cout << "   Sucessor            : " << real << " + 1 = " << Sucessor() << "\n";
            cout << "   Oposto              : 0 - " << real << " = " << Oposto() << "\n";
            cout << "   Fatorial            : " << inteiro << "! " << " = " << Fatorial() << "\n";
            cout << "   Fatorial Aditivo    : " << inteiro << "? " << " = " << FatorialAditivo() << "\n";
        }
};

class Binario : public Operador{
    private:
        //Atributos
        float realB;
        int intB;

        //Métodos Auxiliares privados => "Método de Fachada"
        float PotenciaAux(float a, int b) const {
            if(b < 1) return 1;
            return a * PotenciaAux(a, b - 1);
        }

    public:
        //Construtor
        Binario(float a, float b) : Operador(a), realB(b), intB((int) b){} // intB poderia ser truncado => intB((int)b)

        //Métodos
        float Somar() const {return real + realB;}
        float Subtrair() const {return real - realB;}
        float Multiplicar() const {return real * realB;}
        float Dividir() const {return real / realB;}
        float Resto() const {return fmod(real, realB);}
        float Potencia() const {return PotenciaAux(real, intB);}
        void Imprimir() const override {
            cout << "\n--- OPERADORES BINARIOS DE "<< real <<" e " << realB;
                if(intB != realB) cout << " (Ou seu menor valor inteiro mais próximo: " << intB << ")";
                cout << " ---\n";
            cout << "   Soma                   : " << real << " + " << realB << " = " << Somar() << "\n";
            cout << "   Subtracao              : " << real << " - " << realB << " = " << Subtrair() << "\n";
            cout << "   Multiplicacao          : " << real << " x " << realB << " = " << Multiplicar() << "\n";
            cout << "   Divisao                : " << real << " / " << realB << " = " << Dividir() << "\n";
            cout << "   Resto da Divisao       : " << real << " % " << realB << " = " << Resto() << "\n";
            cout << "   Potencia               : " << real << " ^ " << intB << " = " << Potencia() << "\n";
        }
};

int main(){

    float realA = 3, realB = 4;
    cout << "Insira um numero real:         A = ";
    cin >> realA;
    cout << "Insira mais um numero real:    B = ";
    cin >> realB;

    const Binario binario(realA, realB);
    const Unario unA(realA), unB(realB);

    const Operador* operadores[] = {&binario, &unA, &unB};
    for(auto operador : operadores) operador->Imprimir();

    return 0;
}