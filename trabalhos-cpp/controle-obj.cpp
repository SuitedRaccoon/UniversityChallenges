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

 Turma
 ├── vector<Aluno>     ← objetos reais, Turma é dona
 └── vector<Materia>   ← objetos reais, Turma é dona
      └── vector<Aluno*>  ← ponteiros para os alunos da Turma
*/
struct Matricula{
    int idMateria;
    std::string nomeMateria;
    std::vector<float> notas;
    float media;
    bool aprovado;
};

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

            std::cout   << "[" << id << "] " << nome << " | Nota max: " 
                        << notaMax << " | Peso: " << peso << "\n";
        }

};
int Avaliacao::proximoId = 1;

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
                if (m.idMateria == idMateria){
                    m.notas.push_back(nota);
                    return;
                }
            }
            std::cout << "Materia com o ID [" << idMateria << "] não encontrada.\n";
        }

        void calcularMedia(int idMateria, const std::vector<Avaliacao>& avaliacoes, float mediaAprovacao){  //Recebe o vetor de avaliações da
            for (Matricula& m : matriculas){                                                                //Materia por referência, sem
                if (m.idMateria == idMateria){                                                              //copiar e sem modificar
                    if(m.notas.empty() or avaliacoes.empty()) return;

                    float somaPonderada = 0.0f;
                    float somaPesos = 0.0f;

                    for (int i = 0; i < m.notas.size() and i < avaliacoes.size(); i++){
                        somaPonderada += m.notas[i] * avaliacoes[i].getPeso();
                        somaPesos += avaliacoes[i].getPeso();
                    }
                    m.media = somaPonderada / somaPesos;
                    m.aprovado = m.media >= mediaAprovacao;
                    return;
                }
            }
        }

        // Getters
        int getId() const {return id;}
        int getIdade() const {return idade;}
        char getSexo() const {return sexo;}
        std::string getNome() const {return nome;}
        const std::vector<Matricula>& getMatriculas() const {return matriculas;}

        void imprimir() const {
            std::cout   << std::fixed << std::setprecision(2);
            std::cout   << "[" << id << "] " << nome
                        << " | Idade: " << idade
                        << " | Sexo: " << sexo << "\n";

            for (const Matricula& m : matriculas){    
                std::cout   << "Materia: [" << m.idMateria << "] "
                            << m.nomeMateria << " | Notas: ";
                for (float n : m.notas) std::cout << n << " ";
                std::cout   << "| Media: " << m.media
                            << " | " << (m.aprovado ? "Aprovado" : "Reprovado") << "\n";
            }
        }
};
int Aluno::proximoId = 1;

class Materia{
    private:
        static int proximoId;

        int id;
        std::string nome;
        float mediaAprovacao;
        std::vector<Aluno*> alunos; // Ponteiros -> Não copia a variável!
        std::vector<Avaliacao> avaliacoes;

    public:
        //Construtor
        Materia(std::string nome, float mediaAprovacao = 5.0f) : id(proximoId++), nome(nome), mediaAprovacao(mediaAprovacao) {
            this->nome[0] = std::toupper(this->nome[0]);
        }

        //Avaliações
        void adicionarAvaliacao(Avaliacao avaliacao){
            avaliacoes.push_back(avaliacao);
        }

        //Alunos
        void adicionarAluno(Aluno* aluno){
            alunos.push_back(aluno);
            aluno->adicionarMatricula(id, nome); // registra a matricula no aluno
        }

        Aluno* buscarAluno(int idAluno){
            for (Aluno* a : alunos){
                if (a->getId() == idAluno) return a;
            }
            return nullptr;
        }

        //Notas
        void lancarNota(int idAluno, float nota){
            Aluno* aluno = buscarAluno(idAluno);

            if (!aluno){
                std::cout << "Aluno de ID [" << idAluno << "] não encontrado \n";
                return;
            }

            aluno->adicionarNota(id, nota);
            aluno->calcularMedia(id, avaliacoes, mediaAprovacao);
        }

        //Getters
        int getId() const {return id;}
        std::string getNome() const {return nome;}
        float getMediaAprovacao() const { return mediaAprovacao; }

        const std::vector<Avaliacao>& getAvaliacoes() const {return avaliacoes;}

        //Utilitários
        void imprimir() const{
            std::cout   << std::fixed << std::setprecision(2);
            std::cout   << "\n--- Matéria: [" << id << "] "<< nome
                        << " | Aprovacao: " << mediaAprovacao << " ---\n";
            
            std::cout << "Avaliacoes:\n";
            for (const Avaliacao& av : avaliacoes) av.imprimir();

            std::cout << "Alunos:\n";
            for (const Aluno* a : alunos) a->imprimir();
        }
};
int Materia::proximoId = 1;

class Turma{
    private:
        static int proximoId;

        int id;
        int ano;
        std::string nome;
        std::vector<Aluno> alunos;
        std::vector<Materia> materias;

    public:
        //Construtor
        Turma(std::string nome, int ano) : id(proximoId++), nome(nome), ano(ano){
            this->nome[0] = std::toupper(this->nome[0]);
        }   
        
        //Alunos
        void adicionarAluno(Aluno aluno){
            alunos.push_back(aluno);
        }

        Aluno* buscarAluno(int idAluno){
            for (Aluno& a : alunos){
                if(a.getId() == idAluno) return &a;
            }
            return nullptr;
        }
        
        //Matérias
        void adicionarMateria(Materia materia){
            materias.push_back(materia);
        }

        Materia* buscarMateria(int idMateria){
            for (Materia& m : materias){
                if (m.getId() == idMateria) return &m;
            }
            return nullptr;
        }

        //Matrícula
        void matricularAluno(int idAluno, int idMateria){
            Aluno* aluno = buscarAluno(idAluno);
            Materia* materia = buscarMateria(idMateria);

            if (!aluno){
                std::cout << "Aluno com ID [" << idAluno << "] não encontrado.\n";
                return;
            }
            if (!materia){
                std::cout << "Matéria com ID [" << idMateria << "] não encontrada.\n";
                return;
            }

            materia->adicionarAluno(aluno);
            std::cout   << aluno->getNome() << " matriculado em "
                        << materia->getNome() << ".\n";
        }

        void lancarNota(int idAluno, int idMateria, float nota){
            Materia* materia = buscarMateria(idMateria);

            if (!materia){
                std::cout << "Matéria com ID [" << idMateria << "] não encontrada.\n";
                return;
            }

            materia->lancarNota(idAluno, nota);
        }

        //Getters
        int getId() const {return id;}
        std::string getNome() const {return nome;}
        int getAno() const {return ano;}

        //Utilitários
        void imprimir() const {
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "\n╔══════════════════════════════╗\n";
            std::cout <<   "  Turma: " << nome << " | Ano: " << ano
                    <<   " | ID: "   << id   << "\n";
            std::cout << "╚══════════════════════════════╝\n";

            std::cout << "\n── Alunos (" << alunos.size() << ") ──\n";
            for (const Aluno& a : alunos) a.imprimir();

            std::cout << "\n── Matérias (" << materias.size() << ") ──\n";
            for (const Materia& m : materias) m.imprimir();
        }
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

/* EXEMPLO DE USO!
int main() {
    limpa();
    Turma turma("3A", 2024);

    // Adiciona alunos na turma
    turma.adicionarAluno(Aluno(20, "carlos", 'M'));
    turma.adicionarAluno(Aluno(22, "ana",    'F'));
    turma.adicionarAluno(Aluno(19, "bruno",  'M'));

    // Cria e adiciona matérias
    Materia mat("matemática");
    mat.adicionarAvaliacao(Avaliacao("prova 1",    10.0f, 0.4f));
    mat.adicionarAvaliacao(Avaliacao("prova 2",    10.0f, 0.4f));
    mat.adicionarAvaliacao(Avaliacao("trabalho",   10.0f, 0.2f));
    turma.adicionarMateria(mat);

    // Matricula alunos nas matérias
    turma.matricularAluno(1, 1);
    turma.matricularAluno(2, 1);
    turma.matricularAluno(3, 1);

    // Lança notas
    turma.lancarNota(1, 1, 7.5f);
    turma.lancarNota(1, 1, 8.0f);
    turma.lancarNota(1, 1, 9.0f);

    turma.lancarNota(2, 1, 5.0f);
    turma.lancarNota(2, 1, 6.0f);
    turma.lancarNota(2, 1, 7.0f);

    turma.lancarNota(3, 1, 4.0f);
    turma.lancarNota(3, 1, 3.5f);
    turma.lancarNota(3, 1, 5.0f);

    turma.imprimir();
}
*/

int main(){
    return 0;
}