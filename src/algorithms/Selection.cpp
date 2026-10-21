#include "../../include/algorithms/Selection.h"
#include <numeric>
#include <stdexcept>

// ==========================================
// --- Roulette Wheel Selection ---
// ==========================================
std::vector<Chromosome*> RouletteWheelSelection::select(Population& pop, size_t numParents, std::mt19937& rng) {
    std::vector<Chromosome*> parents;
    auto& individuals = pop.getIndividuals();
    
    if (individuals.empty()) return parents;

    // 1. Calculate total fitness of the population
    double totalFitness = 0.0;
    for (const auto& ind : individuals) {
        totalFitness += ind->getFitness();
    }

    // 2. Generate random thresholds and select parents
    std::uniform_real_distribution<double> dist(0.0, totalFitness);
    
    for (size_t i = 0; i < numParents; ++i) {
        double spin = dist(rng); // Spin the roulette wheel
        double currentSum = 0.0;
        
        // Find the individual whose cumulative fitness exceeds the spin
        for (const auto& ind : individuals) {
            currentSum += ind->getFitness();
            if (currentSum >= spin) {
                parents.push_back(ind.get());
                break;
            }
        }
    }
    return parents;
}

// ==========================================
// --- Tournament Selection ---
// ==========================================
std::vector<Chromosome*> TournamentSelection::select(Population& pop, size_t numParents, std::mt19937& rng) {
    std::vector<Chromosome*> parents;
    auto& individuals = pop.getIndividuals();
    
    if (individuals.empty()) return parents;
    if (individuals.size() < tournamentSize) {
        throw std::runtime_error("Population is smaller than tournament size!");
    }

    std::uniform_int_distribution<size_t> dist(0, individuals.size() - 1);

    for (size_t i = 0; i < numParents; ++i) {
        // 1. Pick 'k' random individuals (the tournament)
        std::vector<Chromosome*> contestants;
        for (int j = 0; j < tournamentSize; ++j) {
            contestants.push_back(individuals[dist(rng)].get());
        }

        // 2. Find the best one among the contestants
        Chromosome* winner = contestants[0];
        for (size_t j = 1; j < contestants.size(); ++j) {
            if (contestants[j]->getFitness() > winner->getFitness()) {
                winner = contestants[j];
            }
        }
        parents.push_back(winner);
    }
    return parents;
}