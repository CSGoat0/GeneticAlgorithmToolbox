#include "../../include/algorithms/Mutation.h"
#include <cmath>

void BitFlipMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, double mutationProb, std::mt19937& rng) {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    auto& binaryChromo = dynamic_cast<BinaryChromosome&>(chromosome);
    
    for (size_t i = 0; i < binaryChromo.getSize(); ++i) {
        if (dist(rng) <= mutationProb) { // USE PASSED PROBABILITY
            binaryChromo.flipGene(i);
        }
    }
}

void UniformFloatMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, double mutationProb, std::mt19937& rng) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_real_distribution<double> randDist(0.0, 1.0);
    auto& floatChromo = dynamic_cast<FloatChromosome&>(chromosome);
    
    for (size_t i = 0; i < floatChromo.getSize(); ++i) {
        if (probDist(rng) <= mutationProb) { // USE PASSED PROBABILITY
            double x = floatChromo.getGene(i);
            auto bounds = floatChromo.getBounds(i);
            double LB = bounds.first, UB = bounds.second;

            double deltaL = x - LB;
            double deltaU = UB - x;

            double delta = (randDist(rng) <= 0.5) ? deltaL : deltaU;
            double r2 = randDist(rng) * delta;

            double newX = (delta == deltaL) ? (x - r2) : (x + r2);
            floatChromo.setGene(i, newX);
        }
    }
}

void NonUniformFloatMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, double mutationProb, std::mt19937& rng) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_real_distribution<double> randDist(0.0, 1.0);
    auto& floatChromo = dynamic_cast<FloatChromosome&>(chromosome);
    
    for (size_t i = 0; i < floatChromo.getSize(); ++i) {
        if (probDist(rng) <= mutationProb) { // USE PASSED PROBABILITY
            double x = floatChromo.getGene(i);
            auto bounds = floatChromo.getBounds(i);
            double LB = bounds.first, UB = bounds.second;

            double deltaL = x - LB;
            double deltaU = UB - x;
            double y = (randDist(rng) <= 0.5) ? deltaL : deltaU;

            double r = randDist(rng);
            double t = currentGen;
            double T = maxGen;
            
            double exponent = std::pow((1.0 - (t / T)), bParam);
            double deltaT = y * (1.0 - std::pow(r, exponent));

            double newX = (y == deltaL) ? (x - deltaT) : (x + deltaT);
            floatChromo.setGene(i, newX);
        }
    }
}

void SwapMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, double mutationProb, std::mt19937& rng) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    auto& intChromo = dynamic_cast<IntegerChromosome&>(chromosome);
    if (intChromo.getSize() < 2) return;

    if (probDist(rng) <= mutationProb) { // USE PASSED PROBABILITY
        std::uniform_int_distribution<size_t> indexDist(0, intChromo.getSize() - 1);
        size_t idx1 = indexDist(rng);
        size_t idx2 = indexDist(rng);
        
        while (idx1 == idx2) idx2 = indexDist(rng);

        int temp = intChromo.getGene(idx1);
        intChromo.setGene(idx1, intChromo.getGene(idx2));
        intChromo.setGene(idx2, temp);
    }
}