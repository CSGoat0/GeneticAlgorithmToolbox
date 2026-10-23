#include <iostream>
#include <random>
#include "core/Population.h"
#include "builder/GeneticAlgorithmBuilder.h"
#include "algorithms/Selection.h"
#include "algorithms/Crossover.h"
#include "algorithms/Mutation.h"
#include "algorithms/Replacement.h"

int main() {
    std::cout << "---GA Toolbox Test: Maximize f(x) = x^2 ---" << std::endl;

    // 1. Setup GA Configuration
    GAConfig config;
    config.populationSize = 50;
    config.maxGenerations = 100;
    config.crossoverProbability = 0.8;
    config.mutationProbability = 0.2;

    GeneticAlgorithmBuilder builder;
    auto toolbox = builder
        .setConfig(config)
        
        // NEW: Injecting the Initialization logic here!
        .setInitializer([](int popSize) {
            Population pop;
            std::mt19937 initRng(42); // Fixed seed for initial pop
            for (int i = 0; i < popSize; ++i) {
                pop.addIndividual(std::make_unique<FloatChromosome>(1, -100.0, 100.0, initRng));
            }
            return pop;
        })
        
        .setSelection(std::make_unique<TournamentSelection>(3))
        .setCrossover(std::make_unique<MultiPointCrossover>())
        .setMutation(std::make_unique<NonUniformFloatMutation>(1.0))
        .setReplacement(std::make_unique<ElitistReplacement>())
        
        // INJECTING THE FITNESS FUNCTION
        .setFitnessFunction([](const Chromosome& c) {
            auto& fc = dynamic_cast<const FloatChromosome&>(c);
            return fc.getGene(0) * fc.getGene(0);
        })
        
        // INJECTING THE FEASIBILITY FUNCTION
        .setFeasibilityFunction([](const Chromosome& c) {
            return true; // No constraints
        })
        .build();

    // 4. Run the GA
    auto bestSolution = toolbox->run();

    // 5. Output Results
    auto& bestFloat = dynamic_cast<FloatChromosome&>(*bestSolution);
    std::cout << "\nBest x found: " << bestFloat.getGene(0) << std::endl;
    std::cout << "Fitness: " << bestSolution->getFitness() << std::endl;

    return 0;
}