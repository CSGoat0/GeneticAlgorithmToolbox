#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include "CVRP.h"
#include "ExampleInstance.h"
#include "../include/builder/GeneticAlgorithmBuilder.h"

using namespace std;

vector<int> genesOf(const Chromosome& c) {
    const auto& ic = dynamic_cast<const IntegerChromosome&>(c);
    vector<int> genes(ic.getSize());
    for (size_t i = 0; i < genes.size(); i++) genes[i] = ic.getGene(i);
    return genes;
}

void printSolution(const CVRP& problem, const Routes& routes) {
    int totalDistance = 0, totalLoad = 0;
    for (size_t v = 0; v < routes.size(); v++) {
        cout << "Route for vehicle " << v << ":\n 0 Load(0) -> ";
        int load = 0;
        for (int c : routes[v]) {
            cout << " " << c << " Load(" << load << ") -> ";
            load += problem.demand[c];
        }
        cout << " 0 Load(" << load << ")\n";
        int d = problem.routeCost(routes[v]);
        cout << "Distance of the route: " << d << "m\nLoad of the route: " << load << "\n\n";
        totalDistance += d;
        totalLoad += load;
    }
    cout << "Total distance of all routes: " << totalDistance << "m\n";
    cout << "Total load of all routes: " << totalLoad << "\n";
}

int main() {
    CVRP problem = makeGoogleExample();
    int n = problem.numCustomers();

    GAConfig config;
    config.populationSize = 500;
    config.maxGenerations = 1000;
    config.crossoverProbability = 0.9;

    mt19937 rng(random_device{}());
    Population population;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    for (int i = 0; i < config.populationSize; i++) {
        shuffle(perm.begin(), perm.end(), rng);
        population.addIndividual(make_unique<IntegerChromosome>(perm, 1, n));
    }

    auto fitnessFn = [&problem](const Chromosome& c) {
        return 1.0 / problem.totalCost(problem.decode(genesOf(c)));
    };

    auto feasibilityFn = [&problem](const Chromosome& c) {
        vector<int> genes = genesOf(c);
        return problem.isValidPermutation(genes) && problem.isFeasible(problem.decode(genes));
    };

    GeneticAlgorithmBuilder builder;
    auto toolbox = builder
        .setConfig(config)
        .setInitialPopulation(move(population))
        .setSelection(make_unique<TournamentSelection>(3))
        .setCrossover(make_unique<OrderCrossover>())
        .setMutation(make_unique<SwapMutation>())
        .setReplacement(make_unique<ElitistReplacement>())
        .setFitnessFunction(fitnessFn)
        .setFeasibilityFunction(feasibilityFn)
        .build();

    auto best = toolbox->run();

    vector<int> genes = genesOf(*best);
    Routes routes = problem.decode(genes);
    if (!problem.isValidPermutation(genes) || !problem.isFeasible(routes)) {
        cout << "No feasible solution found\n";
        return 1;
    }
    cout << "Objective: " << problem.totalCost(routes) << "\n";
    printSolution(problem, routes);
    return 0;
}
