import os
from typing import List, Tuple

def LimpaTela() -> None:
    os.system('cls')

def Inicio() -> None:
    LimpaTela()
    print("""
           𝐏𝐢𝐳𝐳𝐚𝐫𝐢𝐚 𝐙𝐚𝐧𝐞𝐭𝐭𝐢

        Sabor direto da Itália
    """)
    input('\nPressione qualquer tecla para continuar...')

def DefineTamanho(tamanho) -> float: 
    fatorPequena = 1.00
    fatorMedia = 1.20
    fatorGrande = 1.50
    match tamanho:
        case 'p': return fatorPequena
        case 'm': return fatorMedia
        case 'g': return fatorGrande
        case _: return 0

def DefineSabor(sabor) -> float:
    precoCalabresa = 25.00
    precoFrango = 28.00
    precoMarguerita = 20.00
    precoQuatroQueijos = 30.00
    match sabor:
        case 'calabresa': return precoCalabresa
        case 'frango': return precoFrango
        case 'marguerita': return precoMarguerita
        case '4 queijos': return precoQuatroQueijos
        case _: return 0

def CalculaPreco(tamanho, sabor) -> float:
    fator = DefineTamanho(tamanho)
    preco = DefineSabor(sabor)
    valorTotalUnitario = preco * fator
    return valorTotalUnitario

def Quantidade() -> int:
    LimpaTela()
    repete = True
    while repete:
        quantidade = int(input('Digite quantas pizzas você deseja: '))
        if quantidade > 0 and quantidade <= 10:
            repete = False
            return quantidade
        else:
            print('Quantidade de pizzas inválida, por favor insira um valor válido! (mínimo de 1, máximo de 10)\n')

def EscolheTamanho() -> str:
    while True: #filtra entrada do usuário para não receber valores de tamanho diferentes dos possíveis
            try: 
                tamanho = str.lower(input('Digite o tamanho (P, M ou G): '))
                if tamanho not in ['p', 'm', 'g']:
                    raise ValueError("Tamanho inválido. Digite 'P', 'M' ou 'G'.\n")
                break
            except ValueError as e:
                print(e)
    return tamanho

def EscolheSabor() -> str:
    while True: #filtra entrada do usuário para não receber valores de sabores diferentes dos possíveis
        try:
            sabor = str.lower(input('Digite o sabor (Calabresa, Frango, Marguerita ou 4 Queijos): '))
            if sabor not in ['calabresa', 'frango', 'marguerita', '4 queijos']:
                raise ValueError("Sabor Inválido. Digite 'Calabresa', 'Frango', 'Marguerita' ou '4 Queijos'.\n")
            break
        except ValueError as e:
            print(e)
    return sabor

def Seletor() -> Tuple[str, str, float]:
    tamanho = EscolheTamanho()
    sabor = EscolheSabor()
    preco = CalculaPreco(tamanho, sabor)
    a = [sabor, tamanho, preco]
    return a

def MontaPizza() -> List[Tuple[str, str, float]]:
    index = 1
    quant = Quantidade()
    lista = []
    while index <= quant:
        print(f'Pizza #{index} de {quant}')
        a = Seletor()
        lista.append(a)
        index += 1
    return lista

def EscolheMudanca(lista) -> None:
    continuar = True
    while continuar:
        while True:
            try:
                index = int(input('\nDigite qual o número do item que deseja editar: '))
                if index < 1 or index > len(lista):
                    raise ValueError(f"Valor inválido. Por favor digite um número entre 1 e {len(lista)}")
                break
            except ValueError as e:
                print(e)
        index -= 1
        sabor = lista[index][0].capitalize()
        tamanho = lista[index][1].capitalize()
        indice = index + 1
        print(f"Você selecionou o item {indice}> {sabor} ({tamanho})")
        while True:
            try:
                escolha = int(input("\n Você deseja: 1 - Editar sabor  | 2 - Editar Tamanho  | 3 - Remover   "))
                if escolha not in [1, 2, 3]:
                    raise ValueError(f"Valor inválido. Por favor digite um número válido:  1 - Editar sabor  | 2 - Editar Tamanho  | 3 - Remover   ")
                break
            except ValueError as e:
                print(e)
        match escolha:
            case 1:
                lista[index][0] = EscolheSabor()
                print('Sabor de pizza alterado com sucesso!')
            case 2:
                lista[index][1] = EscolheTamanho()
                print('Tamanho de pizza alterado com sucesso!')
            case 3:
                del lista[index]
                print('Pizza removida com sucesso!')
            case _:
                print()
        MontaNota(lista)

def ContinuarEditando(lista) -> None:
    continuar = True
    while continuar:
        while True:
            try:
                escolha = str.lower(input("Deseja alterar mais algum item?  (S / N)   "))
                if escolha not in ['s', 'n']:
                    raise ValueError("Entrada inválida. Por favor digite 'S' para CONFIRMAR ou 'N' para NÃO CONFIRMAR\n")
                break
            except ValueError as e:
                print(e)
        if escolha == 'n':
            LimpaTela()
            valor = MontaNota(lista)
            FinalizaCompra(lista, valor)
            continuar = False
        else:
            EscolheMudanca(lista)

def EditarPedido(lista) -> None:
    MontaNota(lista)
    EscolheMudanca(lista)
    ContinuarEditando(lista)

def MontaNota(lista) -> float:
    LimpaTela()
    quant = len(lista)
    valorTotal = 0.00
    print("\nSua lista de pizzas:")
    index = 1
    for linha in range(quant):
        sabor = lista[linha][0].capitalize()
        tamanho = lista[linha][1].capitalize()
        preco = lista[linha][2]
        valorTotal += preco
        print(f'   {index}> {sabor} ({tamanho}) ----------- R${preco}')
        index += 1
    print(f'\nValor Total = R${valorTotal}\n')
    return valorTotal

def MetodoPagamento(valor) -> None:
    LimpaTela()
    print(f'Seu pedido se encontra no valor de R${valor}.')
    while True:
        try:
            metodo = str.lower(input('\nDigite o método de pagamento desejado. (PIX, Dinheiro, Cartão, Vale)   '))
            if metodo not in ['pix', 'dinheiro', 'cartao', 'cartão', 'vale']:
                raise ValueError("Entrada inválida. Por favor digite um dos métodos possíveis: (PIX, Dinheiro, Cartão, Vale)\n")
            break
        except ValueError as e:
            print(e)
    LimpaTela()
    match metodo:
        case 'pix': 
            input('Você selecionou pagamento por PIX. Pressione qualquer tecla para prosseguir...')
        case 'cartao' | 'cartão' | 'vale':
            print('Você selecionou pagamento com cartão.')
            PagamentoCartao()
        case 'dinheiro':
            print('Você selecionou pagamento em dinheiro.')
            PagamentoDinheiro(valor)
        case _:
            input('\nPressione qualquer tecla para retornar ao Menu Principal...')
    print('Compra concluída. Agora basta aguardar!')
    input('\nPressione qualquer tecla para retornar ao Menu Principal...')

def PagamentoDinheiro(valor) -> None:
    print(f'Seu pedido se encontra no valor de R${valor}.')
    while True:
        try:
            troco = str.lower(input('Você precisará de troco? (S / N)  '))
            if troco not in ['s', 'n']:
                raise ValueError("Entrada inválida. Por favor digite 'S' para SIM ou 'N' para NÃO\n")
            break
        except ValueError as e:
            print(e)

    if troco == 'n':
        print('Você selecionou que não precisa de troco.')
    else:
        while True:
            try:
                valor_para_troco = float(input('Digite para quanto será o troco necessário: R$'))
                if valor_para_troco < valor:
                    raise ValueError(f"Valor inválido. Por favor digite um valor maior que R${valor}")
                break
            except ValueError as e:
                print(e)
        valor_troco = valor_para_troco - valor
        print(f'Você receberá R${valor_troco} de troco.')

def PagamentoCartao(valor) -> None:
    print(f'Seu pedido se encontra no valor de R${valor}.')
    while True:
        try:
            card = str.lower(input('Selecione o tipo de cartão desejado: (Débito, Crédito, Vale)'))
            if card not in ['debito', 'débito', 'credito', 'crédito', 'vale']:
                raise ValueError("Entrada inválida. Por favor digite um dos métodos disponíveis: Débito, Crédito, Vale")
            break
        except ValueError as e:
            print(e)

def ConfirmaCompra() -> bool:
    confirmado = False
    while True:
        try:
            confirma = str.lower(input('Você deseja confirmar o pedido? (S / N)  '))
            if confirma not in ['s', 'n']:
                raise ValueError("Entrada inválida. Por favor digite 'S' para CONFIRMAR ou 'N' para NÃO CONFIRMAR\n")
            break
        except ValueError as e:
            print(e)
    if confirma == 's':
        confirmado = True
    return confirmado

def NaoConfirmaCompra(lista) -> None:
    print('Você escolheu não confirmar a compra.')
    while True:
        try:
            escolha = str.lower(input('\nDeseja editar ou cancelar o pedido? (E / C)  '))
            if escolha not in ['e', 'c']:
                raise ValueError("Entrada inválida. Por favor digite 'E' para EDITAR ou 'C' para CANCELAR\n")
            break
        except ValueError as e:
            print(e)
    if escolha == 'e':
        print('Você escolheu editar seu pedido')
        EditarPedido(lista)
    else:
        print('Compra Cancelada. :(')

def FinalizaCompra(lista, valor) -> None:
    if ConfirmaCompra():
        MetodoPagamento(valor)
    else:
        NaoConfirmaCompra(lista)
    input('\nPressione qualquer tecla para retornar ao Menu Principal...')

def main() -> None:
    Inicio()
    lista = MontaPizza()
    valor = MontaNota(lista)
    FinalizaCompra(lista, valor)
    
if __name__ == '__main__':
    main()


