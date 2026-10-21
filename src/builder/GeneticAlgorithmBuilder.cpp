#include "../../include/builder/GeneticAlgorithmBuilder.h"

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setConfig(const GAConfig& c) { config = c; return *this; }
GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setSelection(std::unique_ptr<Selection> algo) { selectionAlgo = std::move(algo); return *this; }
GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setCrossover(std::unique_ptr<Crossover> algo) { crossoverAlgo = std::move(algo); return *this; }
GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setMutation(std::unique_ptr<Mutation> algo) { mutationAlgo = std::move(algo); return *this; }
GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setReplacement(std::unique_ptr<Replacement> algo) { replacementAlgo = std::move(algo); return *this; }
GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setFitnessFunction(std::function<double(const Chromosome&)> fn) { fitnessFn = fn; return *this; }
GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setFeasibilityFunction(std::function<bool(const Chromosome&)> fn) { feasibilityFn = fn; return *this; }
GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::setInitialPopulation(Population&& pop) { initialPopulation = std::move(pop); return *this; }

std::unique_ptr<GeneticAlgorithmToolbox> GeneticAlgorithmBuilder::build() {
    return std::make_unique<GeneticAlgorithmToolbox>(
        config, std::move(selectionAlgo), std::move(crossoverAlgo), 
        std::move(mutationAlgo), std::move(replacementAlgo), 
        fitnessFn, feasibilityFn, std::move(initialPopulation)
    );
}