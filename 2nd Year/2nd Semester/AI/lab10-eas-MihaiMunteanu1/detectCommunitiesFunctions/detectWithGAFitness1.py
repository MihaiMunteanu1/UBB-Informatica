import time

from GA import GA
from fitnessFunctions.fitness import new_fitness, modularity


def detect_communities_with_ga_fitness1(network, pop_size=100, num_generations=100, pc=0.8, pm=0.1):
    start_time = time.time()

    n = network['noNodes']
    max_communities = min(int(n**0.5) + 1, n)

    problem_param = {
        'noDim': n,
        'min': 0,
        'max': max_communities - 1,  # max possible community id
        'function': lambda communities: new_fitness(communities, network),
        'noBits': 8
    }

    ga_param = {
        'popSize': pop_size,
        'noGen': num_generations,
        'pc': pc,
        'pm': pm
    }

    ga = GA(ga_param, problem_param)
    ga.initialisation()
    ga.evaluation()

    best_fitnesses = []
    avg_fitnesses = []
    generations = []

    best_fitness = ga.bestChromosome().fitness
    best_fitnesses.append(best_fitness)


    avg_fitness = sum(c.fitness for c in ga.population) / pop_size
    avg_fitnesses.append(avg_fitness)
    generations.append(0)

    for g in range(num_generations):
        ga.oneGenerationElitism()

        best_fitness = ga.bestChromosome().fitness
        best_fitnesses.append(best_fitness)


        avg_fitness = sum(c.fitness for c in ga.population) / pop_size
        avg_fitnesses.append(avg_fitness)
        generations.append(g+1)

        if g % 10 == 0:
            print(f"Generation {g}: Best fitness = {best_fitness:.4f}")

    best_solution = [round(val) for val in ga.bestChromosome().repres]
    final_fitness = ga.bestChromosome().fitness

    unique_communities = set(best_solution)
    community_map = {old_id: new_id for new_id, old_id in enumerate(unique_communities)}
    normalized_communities = [community_map[comm] for comm in best_solution]

    return {
        'communities': normalized_communities,
        'fitness': final_fitness,
        'num_communities': len(unique_communities),
        'execution_time': time.time() - start_time,
    }