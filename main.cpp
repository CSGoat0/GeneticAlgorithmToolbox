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
    config.mutationProbability = 0.2; // High mutation for this simple problem

    // 2. Create Initial Population (Float Chromosome with 1 gene)
    std::mt19937 rng(42);
    Population initialPop;
    for (int i = 0; i < config.populationSize; ++i) {
        // 1 gene, bounds [-100, 100]
        initialPop.addIndividual(std::make_unique<FloatChromosome>(1, -100.0, 100.0, rng));
    }

    // 3. Configure Builder
    GeneticAlgorithmBuilder builder;
    auto toolbox = builder
        .setConfig(config)
        .setInitialPopulation(std::move(initialPop))
        .setSelection(std::make_unique<TournamentSelection>(3))
        .setCrossover(std::make_unique<MultiPointCrossover>())
        .setMutation(std::make_unique<NonUniformFloatMutation>(1.0))
        .setReplacement(std::make_unique<ElitistReplacement>())
        
        // INJECTING THE FITNESS FUNCTION
        .setFitnessFunction([](const Chromosome& c) {
            auto& fc = dynamic_cast<const FloatChromosome&>(c);
            double x = fc.getGene(0);
            return x * x; // Minimize negative, maximize positive
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
    double bestX = bestFloat.getGene(0);
    
    std::cout << "\n--- Final Result ---" << std::endl;
    std::cout << "Best x found: " << bestX << std::endl;
    std::cout << "Maximized Fitness f(x) = x^2: " << bestSolution->getFitness() << std::endl;
    
    if (bestX > 90.0 || bestX < -90.0) {
        std::cout << "SUCCESS! The GA converged to an extreme value." << std::endl;
    } else {
        std::cout << "GA did not converge well. Try tuning parameters." << std::endl;
    }

    return 0;
}