import os

def LimpaTela():
    os.system('cls')

def Inicio():
    LimpaTela()
    print("""
          𝓕𝓲𝓷𝓪𝓷𝓬̧𝓪𝓼.𝓬𝓸𝓶

        Seu agente pessoal
    """)
    input('Pressione alguma tecla para continuar...')

def Escolha():
    LimpaTela()
    choice = str.lower(input(("""
    Nova Operação.
          Digite CREDITO para adicionar fundos;
          Digite DEBITO para subtrair fundos;
          Digite EXTRATO para imprimir o comprovante de todas as suas operações.
    
                       
    """)))
    match choice:
        case 'credito': 
            input('voce escolheu credito')
        case 'debito':
            input('voce escolheu debito')
        case 'extrato':
            input('voce escolheu extrato')
        case _:
            input('operacao inválida')


def Programa():
    LimpaTela()
    capital = int(input("Forneça o valor inicial de seu capital: "))
    index = 0
    complete = False
    maxOperacoes = 10
    while index < maxOperacoes or complete == False:
        Escolha()
        index += 1

def main():
    Inicio()
    Programa()

if __name__ == '__main__':
    main()

