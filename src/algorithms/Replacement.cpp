#include "../../include/algorithms/Replacement.h"

void GenerationalReplacement::replace(Population& currentPop, std::vector<std::unique_ptr<Chromosome>>& offspring) {
    // TODO: Clear current population, move all offspring into it
}

void ElitistReplacement::replace(Population& currentPop, std::vector<std::unique_ptr<Chromosome>>& offspring) {
    // TODO: Keep the top N best individuals from currentPop, fill the rest with offspring
}