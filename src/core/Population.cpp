#include "../../include/core/Population.h"

void Population::addIndividual(std::unique_ptr<Chromosome> ind) {
    individuals.push_back(std::move(ind));
}

void Population::clear() { 
    individuals.clear(); 
}

size_t Population::size() const { 
    return individuals.size(); 
}

Chromosome* Population::getBestIndividual() const {
    if (individuals.empty()) return nullptr;
    
    // Start by assuming the first individual is the best
    Chromosome* best = individuals[0].get();
    
    // Iterate through the rest to find the one with the highest fitness
    for (const auto& ind : individuals) {
        if (ind->getFitness() > best->getFitness()) {
            best = ind.get();
        }
    }
    return best;
}

std::vector<std::unique_ptr<Chromosome>>& Population::getIndividuals() {
    return individuals;
}