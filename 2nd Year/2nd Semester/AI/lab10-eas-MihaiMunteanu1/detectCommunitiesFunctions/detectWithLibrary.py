import time
import networkx as nx
from fitnessFunctions.fitness import modularity


def detect_communities_with_library(network, G=None):
    start_time = time.time()

    community_sets = list(nx.community.greedy_modularity_communities(G))

    num_nodes = network['noNodes']
    communities_list = [0] * num_nodes

    for community_id, nodes_in_community in enumerate(community_sets):
        for node in nodes_in_community:
            if 0 <= node < num_nodes:
                communities_list[node] = community_id

    fitness = modularity(communities_list, network)
    num_communities = len(set(communities_list))
    execution_time = time.time() - start_time

    result = {
        'communities': communities_list,
        'num_communities': num_communities,
        'execution_time': execution_time,
        'fitness': fitness
    }

    return result

