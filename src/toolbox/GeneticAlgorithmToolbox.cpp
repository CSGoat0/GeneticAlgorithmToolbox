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
    mutationProb(config.mutationProbability) 
{
    // Safety check: If initial population size doesn't match config, warn the user.
    if (population.size() != config.populationSize) {
        std::cerr << "Warning: Initial population size (" << population.size() 
                  << ") does not match GAConfig.populationSize (" << config.populationSize << ").\n";
    }
}

void GeneticAlgorithmToolbox::handleInfeasible(Chromosome& chromosome) {
    // 1. Death Penalty: Set fitness to 0 so it is not selected.
    // 2. We also reset the genes to something valid if possible (optional, problem-specific).
    // For the general toolbox, we just apply the penalty.
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

            // Apply Mutation (Passing the probability from config)
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

        // Enforce population size constraint
        while (population.size() < config.populationSize) {
            Chromosome* best = population.getBestIndividual();
            if (best) {
                population.addIndividual(best->clone());
            } else {
                break;
            }
        }

        // Logging
        if (gen % 20 == 0) {
            Chromosome* best = population.getBestIndividual();
            if (best) {
                std::cout << "Gen " << gen 
                          << " | Best Fitness: " << best->getFitness() 
                          << " | Avg Fitness: " << population.getAverageFitness() 
                          << std::endl;
            }
        }
    }

    std::cout << "GA Finished." << std::endl;
    
    // Check for nullptr before cloning
    Chromosome* best = population.getBestIndividual();
    if (best == nullptr) {
        std::cerr << "Error: GA finished with an empty population!" << std::endl;
        return nullptr;
    }
    
    return best->clone();
}