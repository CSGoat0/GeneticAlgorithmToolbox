#pragma once
#include "../core/Population.h"
#include <vector>
#include <memory>

class Replacement {
public:
    virtual ~Replacement() = default;
    virtual void replace(Population& currentPop, std::vector<std::unique_ptr<Chromosome>>& offspring) = 0;
};

class GenerationalReplacement : public Replacement {
public:
    void replace(Population& currentPop, std::vector<std::unique_ptr<Chromosome>>& offspring) override;
};

class ElitistReplacement : public Replacement {
public:
    void replace(Population& currentPop, std::vector<std::unique_ptr<Chromosome>>& offspring) override;
};