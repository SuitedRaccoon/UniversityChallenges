distancia = float(input("Digite a distância do percurso em km: "))
consumo = float(input("Digite o rendimento médio de seu carro em km/L: "))
preco = float(input("Digite o preço do litro de gasolina em R$: "))
gasto = round(distancia / consumo, 2)
custo = round(gasto * preco, 2)
print(f'Seu percurso precisará de {gasto} L, o que custará {custo} R$.')