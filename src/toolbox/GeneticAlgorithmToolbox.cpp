#include "../../include/toolbox/GeneticAlgorithmToolbox.h"
#include <iostream>

GeneticAlgorithmToolbox::GeneticAlgorithmToolbox(
    const GAConfig& config, std::unique_ptr<Selection> sel,
    std::unique_ptr<Crossover> cross, std::unique_ptr<Mutation> mut,
    std::unique_ptr<Replacement> repl, std::function<double(const Chromosome&)> fitFn,
    std::function<bool(const Chromosome&)> feasFn, Population&& initialPop
) : config(config), selectionAlgo(std::move(sel)), crossoverAlgo(std::move(cross)), 
    mutationAlgo(std::move(mut)), replacementAlgo(std::move(repl)),
    fitnessFn(fitFn), feasibilityFn(feasFn), population(std::move(initialPop)),
    rng(std::random_device{}()) {}

void GeneticAlgorithmToolbox::handleInfeasible(Chromosome& chromosome) {
    // TODO: Implement penalty logic. E.g., chromosome.setFitness(0.0);
}

std::unique_ptr<Chromosome> GeneticAlgorithmToolbox::run() {
    // 1. Evaluate Initial Population
    for (auto& ind : population.getIndividuals()) {
        ind->setFitness(fitnessFn(*ind));
    }

    for (int gen = 0; gen < config.maxGenerations; ++gen) {
        // TODO: Implement the GA Loop
        // Step 1: Selection -> get parents
        // Step 2: Crossover -> create offspring (check probability Pc)
        // Step 3: Mutation -> mutate offspring (check probability Pm)
        // Step 4: Evaluate offspring fitness (and feasibility)
        // Step 5: Replacement -> replace current pop with offspring
        
        if (gen % 50 == 0) {
            std::cout << "Gen " << gen << " | Best Fitness: " 
                      << population.getBestIndividual()->getFitness() << std::endl;
        }
    }
    
    return population.getBestIndividual()->clone();
}