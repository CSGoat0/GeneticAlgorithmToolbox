#pragma once
#include "../core/GAConfig.h"
#include "../core/Population.h"
#include "../algorithms/Selection.h"
#include "../algorithms/Crossover.h"
#include "../algorithms/Mutation.h"
#include "../algorithms/Replacement.h"
#include "../toolbox/GeneticAlgorithmToolbox.h"
#include <functional>

class GeneticAlgorithmBuilder {
private:
    GAConfig config;
    std::unique_ptr<Selection> selectionAlgo;
    std::unique_ptr<Crossover> crossoverAlgo;
    std::unique_ptr<Mutation> mutationAlgo;
    std::unique_ptr<Replacement> replacementAlgo;
    
    std::function<double(const Chromosome&)> fitnessFn;
    std::function<bool(const Chromosome&)> feasibilityFn;
    
    std::function<Population(int popSize)> initFunction; 
    Population initialPopulation;

public:
    GeneticAlgorithmBuilder& setConfig(const GAConfig& c);
    GeneticAlgorithmBuilder& setSelection(std::unique_ptr<Selection> algo);
    GeneticAlgorithmBuilder& setCrossover(std::unique_ptr<Crossover> algo);
    GeneticAlgorithmBuilder& setMutation(std::unique_ptr<Mutation> algo);
    GeneticAlgorithmBuilder& setReplacement(std::unique_ptr<Replacement> algo);
    GeneticAlgorithmBuilder& setFitnessFunction(std::function<double(const Chromosome&)> fn);
    GeneticAlgorithmBuilder& setFeasibilityFunction(std::function<bool(const Chromosome&)> fn);
    
    GeneticAlgorithmBuilder& setInitializer(std::function<Population(int)> initFn);
    
    // Kept for manual population setting
    GeneticAlgorithmBuilder& setInitialPopulation(Population&& pop);

    std::unique_ptr<GeneticAlgorithmToolbox> build();
};