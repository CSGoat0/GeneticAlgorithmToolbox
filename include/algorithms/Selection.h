#pragma once
#include "../core/Population.h"
#include <vector>

class Selection {
public:
    virtual ~Selection() = default;
    virtual std::vector<Chromosome*> select(Population& pop, size_t numParents, std::mt19937& rng) = 0;
};

class RouletteWheelSelection : public Selection {
public:
    std::vector<Chromosome*> select(Population& pop, size_t numParents, std::mt19937& rng) override;
};

class TournamentSelection : public Selection {
private:
    int tournamentSize;
public:
    TournamentSelection(int size = 3) : tournamentSize(size) {}
    std::vector<Chromosome*> select(Population& pop, size_t numParents, std::mt19937& rng) override;
};