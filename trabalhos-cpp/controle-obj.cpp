/* Escreva um algoritmo que solicite ao usuário Nome, Idade, Sexo e três notas de N alunos em uma turma e ao final, apresente: 
1) total de alunos cadastrados
2) a media das idades dos alunos aprovados/reprovados da turma
3) gerar um relatório de alunos aprovados/reprovados na turma

*/

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <iomanip>
#include <cmath>

/*
Aluno
 └── vector<Matricula>
      ├── idMateria / nomeMateria
      ├── vector<float> notas
      ├── media
      └── aprovado

Materia
 └── vector<Aluno*>      ← ponteiros, não cópias
 └── vector<Avaliacao>
*/

class Avaliacao{
    private:
        static int proximoId;

        int id;
        float notaMax;
        float peso;
        std::string nome;
    public:
        Avaliacao(std::string nome, float notaMax, float peso)
        : id(proximoId), nome(nome), notaMax(notaMax), peso(peso) {
            this->nome[0] = std::toupper(this->nome[0]);
        }

        int getId() const {return id;}
        std::string getNome() const {return nome;}
        float getNotaMax() const {return notaMax;}
        float getPeso() const {return peso;}

        void imprimir() const{
            std::cout   << std::fixed << std::setprecision(2);

            std::cout   << "[" << id << "]" << nome << " | Nota max: " 
                        << notaMax << " | Peso: " << peso << "\n";
        }

};
int Avaliacao::proximoId = 1;

class Materia{
    private:
        static int proximoId;

        int id;
        std::string nome;
        float mediaAprovacao;
    public:
        Materia(){

        }
        int getId() const {return id;}
        std::string getNome() const {return nome;}
        float getMediaAprovacao() const { return mediaAprovacao; }
};
int Materia::proximoId = 1;

struct Matricula{
    int idMateria;
    std::string nomeMateria;
    std::vector<float> notas;
    float media;
    bool aprovado;
};

class Aluno{
    private:
        static int proximoId;

        int id;
        int idade;
        std::string nome;
        std::vector<Matricula> matriculas;
        char sexo;
        bool aprovado;

    public:
        Aluno(int idade, std::string nome, char sexo)
            : id(proximoId++), idade(idade), nome(nome), sexo(sexo) {
            this->nome[0] = std::toupper(this->nome[0]);
            this->sexo = std::toupper(this->sexo);
        }

        void adicionarMatricula(int idMateria, std::string nomeMateria){
            Matricula m;
            m.idMateria = idMateria;
            m.nomeMateria = nomeMateria;
            m.media = 0.0f;
            m.aprovado = false;
            matriculas.push_back(m);
        }

        void adicionarNota(int idMateria, float nota){
            for (Matricula& m : matriculas){ // for(tipo elemento : coleção) -> percorre cada item da coleção do inicio ao fim, sem a necessidade de índices.

            }
        }

        void calcularMedia(const std::vector<Avaliacao>& avaliacoes, const Materia& materia){
            if (notas.empty() or avaliacoes.empty()) return;    //Recebe o vetor de avaliações da              
            float somaPonderada = 0.0f;                         //Materia por referência, sem
            float somaPesos = 0.0f;                             //copiar e sem modificar

            for(int i = 0; i < notas.size() and i < avaliacoes.size(); i++){
                somaPonderada += notas[i] * avaliacoes[i].getPeso();
                somaPesos += avaliacoes[i].getPeso();
            }

            media = somaPonderada / somaPesos;
            aprovado = media >= materia.getMediaAprovacao();
        }

        int getId() const {return id;}
        int getIdade() const {return idade;}
        char getSexo() const {return sexo;}
        std::string getNome() const {return nome;}
        float getMedia() const {return media;}
        bool getAprovado() const {return aprovado;}

        void imprimir() const {
            std::cout   << std::fixed << std::setprecision(2);
            std::cout   << "[" << id << "]" << nome
                        << " | Idade: " << idade
                        << " | Sexo: " << sexo << "\n";
            std::cout   << "Matéria: [" << Materia.getId() << "] "
                        << Materia.getNome()
        }
};
int Aluno::proximoId = 1;

class Turma{
    private:
        static int proximoId;

        int id;
        int ano;
        std::string nome;
        std::vector<Aluno> alunos;
        std::vector<Materia> materias;

    public:
        Turma(){}    
};
int Turma::proximoId = 1;

void limpa(){
    system("clear");
}

int menu(){
    int opcao;
    limpa();
    printf("\n----- CONTROLE DE TURMA -----\n");
    printf("Escolha uma das opções abaixo:\n\n    1 - LISTAR TURMA\n    2 - ESTATISTICAS\n    3 - CADASTRO DE ATIVIDADE\n    4 - CADASTRO DE NOTAS\n    5 - CADASTRO DE ALUNO\n    6 - SAIR\n");
    printf("\nSua escolha: ");
    return scanf("%i", &opcao);
}

void cadastroAluno(){

}



int main(){

    menu();

    return 0;
}