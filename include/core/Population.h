#pragma once
#include "Chromosome.h"
#include <vector>
#include <memory>

class Population {
private:
    std::vector<std::unique_ptr<Chromosome>> individuals;

public:
    Population() = default;
    void addIndividual(std::unique_ptr<Chromosome> ind);
    void clear();
    size_t size() const;
    Chromosome* getBestIndividual() const;
    std::vector<std::unique_ptr<Chromosome>>& getIndividuals();
};