#include "../../include/core/Population.h"
#include <algorithm>

void Population::addIndividual(std::unique_ptr<Chromosome> ind) {
    individuals.push_back(std::move(ind));
}
void Population::clear() { individuals.clear(); }
size_t Population::size() const { return individuals.size(); }

Chromosome* Population::getBestIndividual() const {
    if (individuals.empty()) return nullptr;
    Chromosome* best = individuals[0].get();
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