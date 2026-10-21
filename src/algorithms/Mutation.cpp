#include "../../include/algorithms/Mutation.h"
#include <cmath>

// ==========================================
// --- Bit-Flip Mutation (Binary) ---
// ==========================================
void BitFlipMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    // We need the mutation probability. For simplicity, we assume 0.1 here, 
    // but normally this is passed from the GA Toolbox.
    double pm = 0.1; 
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    
    auto& binaryChromo = dynamic_cast<BinaryChromosome&>(chromosome);
    for (size_t i = 0; i < binaryChromo.getSize(); ++i) {
        if (dist(rng) <= pm) {
            binaryChromo.flipGene(i);
        }
    }
}

// ==========================================
// --- Uniform Float Mutation ---
// ==========================================
void UniformFloatMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    double pm = 0.1;
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_real_distribution<double> randDist(0.0, 1.0);
    
    auto& floatChromo = dynamic_cast<FloatChromosome&>(chromosome);
    
    for (size_t i = 0; i < floatChromo.getSize(); ++i) {
        if (probDist(rng) <= pm) {
            double x = floatChromo.getGene(i);
            auto bounds = floatChromo.getBounds(i);
            double LB = bounds.first;
            double UB = bounds.second;

            double deltaL = x - LB;
            double deltaU = UB - x;

            double delta = (randDist(rng) <= 0.5) ? deltaL : deltaU;
            double r2 = randDist(rng) * delta;

            double newX = (delta == deltaL) ? (x - r2) : (x + r2);
            floatChromo.setGene(i, newX);
        }
    }
}

// ==========================================
// --- Non-Uniform Float Mutation ---
// ==========================================
void NonUniformFloatMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    double pm = 0.1;
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_real_distribution<double> randDist(0.0, 1.0);
    
    auto& floatChromo = dynamic_cast<FloatChromosome&>(chromosome);
    
    for (size_t i = 0; i < floatChromo.getSize(); ++i) {
        if (probDist(rng) <= pm) {
            double x = floatChromo.getGene(i);
            auto bounds = floatChromo.getBounds(i);
            double LB = bounds.first;
            double UB = bounds.second;

            double deltaL = x - LB;
            double deltaU = UB - x;

            // Step C: Choose direction
            double y = (randDist(rng) <= 0.5) ? deltaL : deltaU;

            // Step D: Calculate Delta(t, y) from Lab 2
            double r = randDist(rng);
            double t = currentGen;
            double T = maxGen;
            
            // Formula: y * (1 - r ^ ((1 - t/T) ^ b))
            double exponent = std::pow((1.0 - (t / T)), bParam);
            double deltaT = y * (1.0 - std::pow(r, exponent));

            // Apply mutation
            double newX = (y == deltaL) ? (x - deltaT) : (x + deltaT);
            floatChromo.setGene(i, newX);
        }
    }
}

// ==========================================
// --- Swap Mutation (Integer/Permutation) ---
// ==========================================
void SwapMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    double pm = 0.1;
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    
    auto& intChromo = dynamic_cast<IntegerChromosome&>(chromosome);
    if (intChromo.getSize() < 2) return;

    if (probDist(rng) <= pm) {
        std::uniform_int_distribution<size_t> indexDist(0, intChromo.getSize() - 1);
        size_t idx1 = indexDist(rng);
        size_t idx2 = indexDist(rng);
        
        // Ensure they are different
        while (idx1 == idx2) {
            idx2 = indexDist(rng);
        }

        // Swap the genes
        int temp = intChromo.getGene(idx1);
        intChromo.setGene(idx1, intChromo.getGene(idx2));
        intChromo.setGene(idx2, temp);
    }
}