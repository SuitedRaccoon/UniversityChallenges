# trabalhos-cpp

Implementações em C++ de um sistema de controle acadêmico, desenvolvidas em duas abordagens distintas para fins comparativos.

---

## Arquivos

### `controle-obj.cpp` — Paradigma Orientado a Objetos
Implementação utilizando os recursos modernos de C++, com foco em organização por classes, encapsulamento e interação entre objetos.

**Bibliotecas utilizadas:**
- `<iostream>` — entrada e saída via `std::cin` e `std::cout`
- `<vector>` — listas dinâmicas
- `<string>` — strings modernas
- `<numeric>` — `std::accumulate` para soma de vetores
- `<iomanip>` — formatação de casas decimais com `std::setprecision`
- `<cmath>` — `std::round` para arredondamento

**Classes implementadas:**

| Classe | Responsabilidade |
|---|---|
| `Avaliacao` | Define nome, nota máxima e peso de cada avaliação |
| `Matricula` | Struct auxiliar que vincula um aluno a uma matéria com suas notas |
| `Aluno` | Armazena dados pessoais e um vetor de matrículas |
| `Materia` | Gerencia avaliações e alunos matriculados, lança notas |
| `Turma` | Agrega alunos e matérias, orquestra matrículas e lançamentos |

**Conceitos aplicados:**
- Encapsulamento com `private` / `public`
- IDs auto incrementáveis com membros `static`
- Médias ponderadas por avaliação com peso configurável
- Média de aprovação editável por matéria
- Ponteiros (`Aluno*`) para evitar cópias e garantir que alterações reflitam no objeto original
- Sobrecarga de métodos e `const` em getters e métodos de leitura

---

### `controle-proc.cpp` — Paradigma Procedural
Implementação do mesmo sistema utilizando C com estilo procedural, sem orientação a objetos nem `iostream`.

**Bibliotecas utilizadas:**
- `<stdio.h>` — `printf` e `scanf` para entrada e saída
- `<string.h>` — manipulação de strings com `strcpy`, `strlen`, etc.

**Estruturas implementadas:**

| Struct | Responsabilidade |
|---|---|
| `Avaliacao` | Dados de cada avaliação |
| `Aluno` | Dados pessoais e vetor de notas |
| `Materia` | Dados da matéria e seus alunos |
| `Turma` | Agrupamento de alunos e matérias |

**Conceitos aplicados:**
- `struct` sem métodos — dados e funções separados
- Funções globais para cada operação (`adicionarAluno`, `lancarNota`, `calcularMedia`, etc.)
- Gerenciamento manual de arrays com tamanho fixo
- `printf` com format specifiers (`%d`, `%f`, `%s`) para saída formatada

---

## Comparativo entre as abordagens

| Aspecto | `controle-obj.cpp` | `controle-proc.cpp` |
|---|---|---|
| Paradigma | Orientado a Objetos | Procedural |
| E/S | `iostream` (`cout`, `cin`) | `stdio.h` (`printf`, `scanf`) |
| Agrupamento | Dados + métodos na classe | Dados em `struct`, lógica em funções globais |
| Strings | `std::string` | `char[]` |
| Listas | `std::vector` (dinâmico) | Arrays de tamanho fixo |
| Type safety | Automático (templates) | Manual (format specifiers) |
| Extensibilidade | Alta — sobrecarga, herança | Baixa — funções isoladas |

---

## Como compilar

```bash
# Orientado a objetos
g++ -std=c++17 controle-obj.cpp -o controle-obj

# Procedural
gcc controle-proc.cpp -o controle-proc
```
