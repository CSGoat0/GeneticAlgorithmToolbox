#include "../../include/toolbox/GeneticAlgorithmToolbox.h"
#include <iostream>
#include <algorithm>

GeneticAlgorithmToolbox::GeneticAlgorithmToolbox(
    const GAConfig& config, std::unique_ptr<Selection> sel,
    std::unique_ptr<Crossover> cross, std::unique_ptr<Mutation> mut,
    std::unique_ptr<Replacement> repl, std::function<double(const Chromosome&)> fitFn,
    std::function<bool(const Chromosome&)> feasFn, Population&& initialPop
) : config(config), selectionAlgo(std::move(sel)), crossoverAlgo(std::move(cross)), 
    mutationAlgo(std::move(mut)), replacementAlgo(std::move(repl)),
    fitnessFn(fitFn), feasibilityFn(feasFn), population(std::move(initialPop)),
    rng(std::random_device{}()), 
    crossoverProb(config.crossoverProbability), 
    mutationProb(config.mutationProbability) {}

void GeneticAlgorithmToolbox::handleInfeasible(Chromosome& chromosome) {
    // Simple penalty: if infeasible, its fitness becomes 0.
    chromosome.setFitness(0.0);
}

std::unique_ptr<Chromosome> GeneticAlgorithmToolbox::run() {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);

    // 1. Evaluate initial population
    for (auto& ind : population.getIndividuals()) {
        if (feasibilityFn(*ind)) {
            ind->setFitness(fitnessFn(*ind));
        } else {
            handleInfeasible(*ind);
        }
    }

    // 2. Main GA Loop
    for (int gen = 0; gen < config.maxGenerations; ++gen) {
        
        // Step A: Selection
        // We need to select parents until we have enough to replace the population.
        // Assuming 2 parents make 2 children, we need popSize parents.
        size_t numParents = config.populationSize;
        // Ensure even number of parents for pairwise crossover
        if (numParents % 2 != 0) numParents++; 
        
        auto parents = selectionAlgo->select(population, numParents, rng);
        std::vector<std::unique_ptr<Chromosome>> offspring;

        // Step B: Crossover & Step C: Mutation
        for (size_t i = 0; i < parents.size(); i += 2) {
            // If we have an odd number of parents (shouldn't happen due to above check)
            if (i + 1 >= parents.size()) break;

            Chromosome* p1 = parents[i];
            Chromosome* p2 = parents[i+1];

            std::unique_ptr<Chromosome> c1, c2;

            // Check Crossover Probability
            if (probDist(rng) <= crossoverProb) {
                auto children = crossoverAlgo->crossover(*p1, *p2, rng);
                c1 = std::move(children.first);
                c2 = std::move(children.second);
            } else {
                // No crossover, just clone the parents
                c1 = p1->clone();
                c2 = p2->clone();
            }

            // Apply Mutation (The mutation algorithms themselves check the probability internally)
            mutationAlgo->mutate(*c1, gen, config.maxGenerations, mutationProb, rng);
            mutationAlgo->mutate(*c2, gen, config.maxGenerations, mutationProb, rng);

            // Step D: Evaluate Offspring
            if (feasibilityFn(*c1)) c1->setFitness(fitnessFn(*c1));
            else handleInfeasible(*c1);

            if (feasibilityFn(*c2)) c2->setFitness(fitnessFn(*c2));
            else handleInfeasible(*c2);

            // Add to offspring list
            offspring.push_back(std::move(c1));
            offspring.push_back(std::move(c2));
        }

        // Step E: Replacement
        replacementAlgo->replace(population, offspring);

        // Print progress every 20 generations
        if (gen % 20 == 0) {
            Chromosome* best = population.getBestIndividual();
            std::cout << "Gen " << gen << " | Best Fitness: " << best->getFitness() << std::endl;
        }
    }

    std::cout << "GA Finished." << std::endl;
    return population.getBestIndividual()->clone();
}