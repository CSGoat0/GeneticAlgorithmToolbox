#include "../../include/algorithms/Replacement.h"
#include <algorithm>

// ==========================================
// --- Generational Replacement ---
// ==========================================
void GenerationalReplacement::replace(Population& currentPop, std::vector<std::unique_ptr<Chromosome>>& offspring) {
    // 1. Clear the current population completely
    currentPop.clear();
    
    // 2. Move the offspring into the current population
    for (auto& child : offspring) {
        currentPop.addIndividual(std::move(child));
    }
}

// ==========================================
// --- Elitist Replacement ---
// ==========================================
void ElitistReplacement::replace(Population& currentPop, std::vector<std::unique_ptr<Chromosome>>& offspring) {
    auto& individuals = currentPop.getIndividuals();
    size_t popSize = individuals.size();
    size_t offspringSize = offspring.size();
    
    // 1. Determine how many elites to keep (e.g., top 10% of the population)
    size_t numElites = popSize / 10; 
    if (numElites == 0 && popSize > 0) numElites = 1; // Keep at least 1 elite

    // 2. Sort the current population by fitness in descending order
    std::sort(individuals.begin(), individuals.end(), 
        [](const std::unique_ptr<Chromosome>& a, const std::unique_ptr<Chromosome>& b) {
            return a->getFitness() > b->getFitness();
        });

    // 3. Create a new pool to hold the next generation
    std::vector<std::unique_ptr<Chromosome>> nextGeneration;

    // 4. Keep the elites
    for (size_t i = 0; i < numElites && i < popSize; ++i) {
        nextGeneration.push_back(std::move(individuals[i]));
    }

    // 5. Fill the rest with offspring
    for (size_t i = 0; i < offspringSize && nextGeneration.size() < popSize; ++i) {
        nextGeneration.push_back(std::move(offspring[i]));
    }

    // 6. If there's still empty space (e.g., not enough offspring), fill with remaining old individuals
    for (size_t i = numElites; i < popSize && nextGeneration.size() < popSize; ++i) {
        nextGeneration.push_back(std::move(individuals[i]));
    }

    // 7. Replace the old population with the new one
    currentPop.clear();
    for (auto& ind : nextGeneration) {
        currentPop.addIndividual(std::move(ind));
    }
}