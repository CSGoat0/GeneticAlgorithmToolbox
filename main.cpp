#include <iostream>
#include <random>
#include "core/Population.h"
#include "algorithms/Crossover.h"
#include "algorithms/Mutation.h"

int main() {
    std::mt19937 rng(42);

    // ==========================================
    // Test Order Crossover (OX)
    // ==========================================
    std::cout << "\nTesting Order Crossover..." << std::endl;
    std::vector<int> genes1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> genes2 = {8, 7, 6, 5, 4, 3, 2, 1};
    
    IntegerChromosome p1(genes1, 1, 8);
    IntegerChromosome p2(genes2, 1, 8);

    OrderCrossover ox;
    auto offspring = ox.crossover(p1, p2, rng);
    
    auto& child1 = dynamic_cast<IntegerChromosome&>(*offspring.first);
    std::cout << "Parent 1: ";
    for (int g : genes1) std::cout << g << " ";
    std::cout << "\nParent 2: ";
    for (int g : genes2) std::cout << g << " ";
    std::cout << "\nChild 1:  ";
    for (size_t i = 0; i < child1.getSize(); ++i) std::cout << child1.getGene(i) << " ";
    std::cout << std::endl;

    // ==========================================
    // Test Swap Mutation
    // ==========================================
    std::cout << "\nTesting Swap Mutation..." << std::endl;
    SwapMutation swapMut;
    std::cout << "Before Swap: ";
    for (size_t i = 0; i < child1.getSize(); ++i) std::cout << child1.getGene(i) << " ";
    std::cout << std::endl;
    
    // Note: Since mutation is probabilistic, we run it once and hope it swaps. 
    swapMut.mutate(child1, 0, 100, rng); 

    std::cout << "After Swap:  ";
    for (size_t i = 0; i < child1.getSize(); ++i) std::cout << child1.getGene(i) << " ";
    std::cout << std::endl;

    return 0;
}