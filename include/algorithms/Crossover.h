#pragma once
#include "../core/Chromosome.h"
#include <memory>
#include <utility>
#include <random>

class Crossover {
public:
    virtual ~Crossover() = default;
    virtual std::pair<std::unique_ptr<Chromosome>, std::unique_ptr<Chromosome>> 
    crossover(const Chromosome& parent1, const Chromosome& parent2, std::mt19937& rng) = 0;
};

class MultiPointCrossover : public Crossover {
public:
    std::pair<std::unique_ptr<Chromosome>, std::unique_ptr<Chromosome>> 
    crossover(const Chromosome& parent1, const Chromosome& parent2, std::mt19937& rng) override;
};

class OrderCrossover : public Crossover {
public:
    std::pair<std::unique_ptr<Chromosome>, std::unique_ptr<Chromosome>> 
    crossover(const Chromosome& parent1, const Chromosome& parent2, std::mt19937& rng) override;
};