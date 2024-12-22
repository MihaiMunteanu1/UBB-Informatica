"""def consistent(subsecventa):
    for i in range(len(subsecventa) - 1):
        if subsecventa[i] >= subsecventa[i + 1]:
            return False
    return True"""
def consistent(subsecventa):
    for i in range(len(subsecventa)-1):
        for j in range(i+1,len(subsecventa)):
            if subsecventa[i]>subsecventa[j]:
                return False
            if subsecventa[i]==subsecventa[j]:
                return False
    for i in range(len(subsecventa) - 1):
        if subsecventa[i] >= subsecventa[i + 1]:
            return False
    return True
def solutie(subsecventa):
    return len(subsecventa) > 1

def solutieGasita(subsecventa):
    print(subsecventa)

"""def subsecventaIterativ(dim,lista_numere):
    x = [-1]
    while len(x) > 0:
        choosed = False
        while not choosed and x[-1] < dim - 1:
            x[-1] = x[-1] + 1
            choosed = consistent(x)
        if choosed:
            if solutie(x):
                solutieGasita(x)
            x.append(-1)
        else:
            x = x[:-1]"""

def subsecventaIterativ(lista):
    n = len(lista)
    result = []

    for i in range(2 ** n):

        subsecventa = [lista[j] for j in range(n) if (i >> j) & 1]

        verif_crescatoare = all(subsecventa[k] < subsecventa[k + 1] for k in range(len(subsecventa) - 1))

        if verif_crescatoare:
            result.append(subsecventa)

    return result[1:]
def subsecventaRecursiv(numere, subsecventa_curenta, index):
    subsecventa_curenta.append(0)
    for i in range(index, len(numere)):
        subsecventa_curenta[-1] = numere[i]
        if consistent(subsecventa_curenta):
            if solutie(subsecventa_curenta):
                solutieGasita(subsecventa_curenta)
            subsecventaRecursiv(numere, subsecventa_curenta, i + 1)
    subsecventa_curenta.pop()

dimensiune=5
lista_numere = [2,5,3,4,7]

print("Recursiv")
subsecventaRecursiv(lista_numere,[],0)

print("")

print("Iterativ:")
rezultat=subsecventaIterativ(lista_numere)
for lista in rezultat:
    print(lista)

