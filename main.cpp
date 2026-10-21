#include <iostream>
#include <random>
#include "core/Population.h"
#include "algorithms/Selection.h"
#include "algorithms/Replacement.h"

int main() {
    std::cout << "--- Phase 2 Checkpoint ---" << std::endl;
    std::mt19937 rng(42);

    // Create a population
    Population pop;
    for (int i = 0; i < 10; ++i) {
        pop.addIndividual(std::make_unique<FloatChromosome>(3, -10.0, 10.0, rng));
    }

    // Assign fake fitnesses (0 to 9)
    auto& inds = pop.getIndividuals();
    for (int i = 0; i < 10; ++i) {
        inds[i]->setFitness(i * 10.0); // Fitnesses: 0, 10, 20... 90
    }

    // ==========================================
    // Test Selection
    // ==========================================
    std::cout << "\nTesting Tournament Selection (size 3)..." << std::endl;
    TournamentSelection tournament(3);
    auto parents = tournament.select(pop, 5, rng);
    
    for (auto* p : parents) {
        std::cout << "Selected Parent Fitness: " << p->getFitness() << std::endl;
    }
    // Notice how the selected fitnesses are usually 70 or 80, because tournament favors the best.

    // ==========================================
    // Test Replacement
    // ==========================================
    std::cout << "\nTesting Elitist Replacement..." << std::endl;
    
    // Create 10 bad offspring (fitness = 5.0)
    std::vector<std::unique_ptr<Chromosome>> offspring;
    for (int i = 0; i < 10; ++i) {
        auto child = std::make_unique<FloatChromosome>(3, -10.0, 10.0, rng);
        child->setFitness(5.0); 
        offspring.push_back(std::move(child));
    }

    ElitistReplacement elitist;
    elitist.replace(pop, offspring);

    // The best individual from before was 90.0. It should survive because of elitism!
    std::cout << "New Best Fitness after Elitist Replacement: " 
              << pop.getBestIndividual()->getFitness() << std::endl;
    std::cout << "Population size after replacement: " << pop.size() << std::endl;

    return 0;
}