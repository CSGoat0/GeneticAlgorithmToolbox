#include <iostream>
#include <random>
#include "core/Population.h"

int main() {
    std::cout << "--- Phase 1 Checkpoint ---" << std::endl;

    // 1. Setup random generator
    std::mt19937 rng(42); // Fixed seed for reproducible results

    // 2. Create a population
    Population pop;

    // 3. Add 5 FloatChromosomes (size 3, bounds -10 to 10)
    for (int i = 0; i < 5; ++i) {
        pop.addIndividual(std::make_unique<FloatChromosome>(3, -10.0, 10.0, rng));
    }

    std::cout << "Population size: " << pop.size() << std::endl;

    // 4. Assign some fake fitness scores
    // Let's give the 3rd chromosome (index 2) the highest fitness
    auto& individuals = pop.getIndividuals();
    individuals[0]->setFitness(15.5);
    individuals[1]->setFitness(42.0);
    individuals[2]->setFitness(99.9); // This should be the winner!
    individuals[3]->setFitness(10.0);
    individuals[4]->setFitness(5.5);

    // 5. Test getBestIndividual()
    Chromosome* best = pop.getBestIndividual();
    
    if (best != nullptr) {
        std::cout << "Best Fitness found: " << best->getFitness() << std::endl;
        
        // Let's verify it's the right one by casting it and checking a gene
        auto& floatBest = dynamic_cast<FloatChromosome&>(*best);
        std::cout << "Best Chromosome Gene 0: " << floatBest.getGene(0) << std::endl;
    } else {
        std::cout << "Population is empty!" << std::endl;
    }

    // 6. Test cloning
    std::cout << "\nTesting clone()..." << std::endl;
    auto clonedBest = best->clone();
    std::cout << "Cloned best fitness: " << clonedBest->getFitness() << std::endl;

    return 0;
}