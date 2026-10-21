#include "../../include/algorithms/Crossover.h"

std::pair<std::unique_ptr<Chromosome>, std::unique_ptr<Chromosome>> 
MultiPointCrossover::crossover(const Chromosome& parent1, const Chromosome& parent2, std::mt19937& rng) {
    // TODO: Clone parents. Select 1 or more random points. Swap genes between points.
    return {nullptr, nullptr};
}

std::pair<std::unique_ptr<Chromosome>, std::unique_ptr<Chromosome>> 
OrderCrossover::crossover(const Chromosome& parent1, const Chromosome& parent2, std::mt19937& rng) {
    // TODO: Implement Order Crossover (needed for CVRP). Copy a subset, fill the rest from the other parent.
    return {nullptr, nullptr};
}