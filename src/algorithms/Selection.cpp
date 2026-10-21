#include "../../include/algorithms/Selection.h"
#include <numeric>

std::vector<Chromosome*> RouletteWheelSelection::select(Population& pop, size_t numParents, std::mt19937& rng) {
    // TODO: Implement Roulette Wheel. (Calculate total fitness, generate random thresholds, select parents)
    return {};
}

std::vector<Chromosome*> TournamentSelection::select(Population& pop, size_t numParents, std::mt19937& rng) {
    // TODO: Implement Tournament. (Randomly pick k individuals, pick the best one. Repeat numParents times).
    return {};
}