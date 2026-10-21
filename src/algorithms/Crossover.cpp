#include "../../include/algorithms/Crossover.h"
#include <algorithm>
#include <unordered_set>

// ==========================================
// --- Multi-Point Crossover ---
// ==========================================
std::pair<std::unique_ptr<Chromosome>, std::unique_ptr<Chromosome>> 
MultiPointCrossover::crossover(const Chromosome& parent1, const Chromosome& parent2, std::mt19937& rng) {
    // 1. Clone the parents to create the offspring
    auto child1 = parent1.clone();
    auto child2 = parent2.clone();
    
    size_t size = parent1.getSize();
    if (size < 2) return {std::move(child1), std::move(child2)}; // Can't crossover if size is 0 or 1

    // 2. Generate 1 or 2 random crossover points
    std::uniform_int_distribution<size_t> dist(1, size - 1);
    size_t point1 = dist(rng);
    size_t point2 = dist(rng);
    
    // Ensure point1 is always smaller than point2
    if (point1 > point2) std::swap(point1, point2);

    // 3. Swap the genes between the points
    // Note: We use the swapGenes method we implemented in Phase 1!
    child1->swapGenes(*child2, point1, point2 - 1);

    return {std::move(child1), std::move(child2)};
}

// ==========================================
// --- Order Crossover (OX) ---
// ==========================================
std::pair<std::unique_ptr<Chromosome>, std::unique_ptr<Chromosome>> 
OrderCrossover::crossover(const Chromosome& parent1, const Chromosome& parent2, std::mt19937& rng) {
    size_t size = parent1.getSize();
    if (size < 2) return {parent1.clone(), parent2.clone()};

    auto& p1 = dynamic_cast<const IntegerChromosome&>(parent1);
    auto& p2 = dynamic_cast<const IntegerChromosome&>(parent2);

    std::uniform_int_distribution<size_t> dist(0, size - 1);
    size_t cut1 = dist(rng);
    size_t cut2 = dist(rng);
    if (cut1 > cut2) std::swap(cut1, cut2);

    std::vector<int> child1Genes(size, -1);
    std::vector<int> child2Genes(size, -1);

    std::unordered_set<int> usedInChild1;
    std::unordered_set<int> usedInChild2;

    // 1. Copy the segment from Parent 1 to Child 1, and Parent 2 to Child 2
    for (size_t i = cut1; i <= cut2; ++i) {
        child1Genes[i] = p1.getGene(i);
        usedInChild1.insert(child1Genes[i]);

        child2Genes[i] = p2.getGene(i);
        usedInChild2.insert(child2Genes[i]);
    }

    // 2. Fill the rest of Child 1 with Parent 2's genes in order
    size_t c1Index = (cut2 + 1) % size;
    for (size_t i = 1; i <= size; ++i) { // Iterate through the whole parent
        int gene = p2.getGene((cut2 + i) % size); // Start reading after cut2
        if (usedInChild1.find(gene) == usedInChild1.end()) {
            child1Genes[c1Index] = gene;
            c1Index = (c1Index + 1) % size;
            usedInChild1.insert(gene); // Mark as used so we don't duplicate
        }
    }

    // 3. Fill the rest of Child 2 with Parent 1's genes in order
    size_t c2Index = (cut2 + 1) % size;
    for (size_t i = 1; i <= size; ++i) {
        int gene = p1.getGene((cut2 + i) % size);
        if (usedInChild2.find(gene) == usedInChild2.end()) {
            child2Genes[c2Index] = gene;
            c2Index = (c2Index + 1) % size;
            usedInChild2.insert(gene);
        }
    }

    auto child1 = std::make_unique<IntegerChromosome>(child1Genes, p1.getBounds(0).first, p1.getBounds(0).second);
    auto child2 = std::make_unique<IntegerChromosome>(child2Genes, p2.getBounds(0).first, p2.getBounds(0).second);

    return {std::move(child1), std::move(child2)};
}