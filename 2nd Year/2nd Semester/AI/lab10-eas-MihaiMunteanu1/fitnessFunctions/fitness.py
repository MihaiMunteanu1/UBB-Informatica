# high modularity -> dense connection between the nodes in the module, but rare otherwise

def modularity(communities, param):
    noNodes = param['noNodes']
    mat = param['mat']
    degrees = param['degrees']
    noEdges = param['noEdges']
    M = 2 * noEdges
    Q = 0.0
    for i in range(0, noNodes):
        for j in range(0, noNodes):
            if (communities[i] == communities[j]):
               Q += (mat[i][j] - degrees[i] * degrees[j] / M)
    return Q * 1 / M

##################################################################################

#numarul de muchii care unesc doua noduri din comunitati diferite
#cat mai putine cat mai bine

def new_fitness(communities_repres, net_param):
    mat = net_param['mat']
    noNodes = net_param['noNodes']
    communities = [int(round(c)) for c in communities_repres]

    if len(communities) != noNodes:
        return float('inf')

    #contor pentru muchiile care leaga noduri din comunitati diferite
    inter_edges = 0
    for i in range(noNodes):
        for j in range(i + 1, noNodes):
            if mat[i][j] == 1: # daca exista muchie
                if communities[i] != communities[j]: # daca sunt in comunitati diferite
                    inter_edges += 1
    return inter_edges

##################################################################################

def new_fitness2(communities_repres, net_param):

    mat = net_param['mat']
    noNodes = net_param['noNodes']

    communities = [int(round(c)) for c in communities_repres]

    if len(communities) != noNodes:
        return float(noNodes * noNodes)

    intra_edges = 0 # nr muchiilor dintre noduri din aceeasi comunitate
    inter_edges = 0 # altfel
    for i in range(noNodes):
        for j in range(i + 1, noNodes):
            if mat[i][j] == 1: # daca exista muchie
                if communities[i] == communities[j]: # daca sunt in aceeasi comunitate
                    intra_edges += 1
                else: # daca nu sunt in aceeasi comunitate
                    inter_edges += 1

# scopul este sa maximizam diferenta (intra_edges - inter_edges).
# mai mic e mai bun, inseamna comunitati bine delimitate
    return inter_edges - intra_edges