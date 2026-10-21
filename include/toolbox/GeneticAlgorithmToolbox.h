#pragma once
#include "../core/GAConfig.h"
#include "../core/Population.h"
#include "../algorithms/Selection.h"
#include "../algorithms/Crossover.h"
#include "../algorithms/Mutation.h"
#include "../algorithms/Replacement.h"
#include <functional>
#include <random>

class GeneticAlgorithmToolbox {
private:
    GAConfig config;
    std::unique_ptr<Selection> selectionAlgo;
    std::unique_ptr<Crossover> crossoverAlgo;
    std::unique_ptr<Mutation> mutationAlgo;
    std::unique_ptr<Replacement> replacementAlgo;
    
    std::function<double(const Chromosome&)> fitnessFn;
    std::function<bool(const Chromosome&)> feasibilityFn;
    Population population;
    
    std::mt19937 rng;
    
    double crossoverProb;
    double mutationProb;

    void handleInfeasible(Chromosome& chromosome);

public:
    GeneticAlgorithmToolbox(
        const GAConfig& config, std::unique_ptr<Selection> sel,
        std::unique_ptr<Crossover> cross, std::unique_ptr<Mutation> mut,
        std::unique_ptr<Replacement> repl, std::function<double(const Chromosome&)> fitFn,
        std::function<bool(const Chromosome&)> feasFn, Population&& initialPop
    );

    std::unique_ptr<Chromosome> run();
};