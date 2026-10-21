#include "../../include/core/Chromosome.h"
#include <algorithm>
#include <stdexcept>

// ==========================================
// --- BinaryChromosome ---
// ==========================================
BinaryChromosome::BinaryChromosome(size_t size, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 1);
    for (size_t i = 0; i < size; ++i) genes.push_back(dist(rng));
}

BinaryChromosome::BinaryChromosome(const std::vector<bool>& g) : genes(g) {}

double BinaryChromosome::getFitness() const { return fitness; }
void BinaryChromosome::setFitness(double f) { fitness = f; }
size_t BinaryChromosome::getSize() const { return genes.size(); }
std::unique_ptr<Chromosome> BinaryChromosome::clone() const { 
    return std::make_unique<BinaryChromosome>(*this); 
}

void BinaryChromosome::swapGenes(Chromosome& other, size_t start, size_t end) {
    auto& o = dynamic_cast<BinaryChromosome&>(other);
    for (size_t i = start; i <= end; ++i) {
        // Manual swap due to vector<bool> proxy issue
        bool temp = genes[i];
        genes[i] = o.genes[i];
        o.genes[i] = temp;
    }
}

bool BinaryChromosome::getGene(size_t i) const { return genes[i]; }
void BinaryChromosome::setGene(size_t i, bool v) { genes[i] = v; }
void BinaryChromosome::flipGene(size_t i) { genes[i] = !genes[i]; }


// ==========================================
// --- IntegerChromosome ---
// ==========================================
IntegerChromosome::IntegerChromosome(size_t size, int minVal, int maxVal, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    for (size_t i = 0; i < size; ++i) {
        genes.push_back(dist(rng));
        bounds.push_back({minVal, maxVal});
    }
}

IntegerChromosome::IntegerChromosome(const std::vector<int>& g, int minVal, int maxVal) : genes(g) {
    for (size_t i = 0; i < g.size(); ++i) bounds.push_back({minVal, maxVal});
}

double IntegerChromosome::getFitness() const { return fitness; }
void IntegerChromosome::setFitness(double f) { fitness = f; }
size_t IntegerChromosome::getSize() const { return genes.size(); }
std::unique_ptr<Chromosome> IntegerChromosome::clone() const { 
    return std::make_unique<IntegerChromosome>(*this); 
}

void IntegerChromosome::swapGenes(Chromosome& other, size_t start, size_t end) {
    auto& o = dynamic_cast<IntegerChromosome&>(other);
    for (size_t i = start; i <= end; ++i) {
        std::swap(genes[i], o.genes[i]);
    }
}

int IntegerChromosome::getGene(size_t i) const { return genes[i]; }
void IntegerChromosome::setGene(size_t i, int v) { genes[i] = v; }
std::pair<int, int> IntegerChromosome::getBounds(size_t i) const { return bounds[i]; }


// ==========================================
// --- FloatChromosome ---
// ==========================================
FloatChromosome::FloatChromosome(size_t size, double minVal, double maxVal, std::mt19937& rng) {
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    for (size_t i = 0; i < size; ++i) {
        genes.push_back(dist(rng));
        bounds.push_back({minVal, maxVal});
    }
}

FloatChromosome::FloatChromosome(const std::vector<double>& g, double minVal, double maxVal) : genes(g) {
    for (size_t i = 0; i < g.size(); ++i) bounds.push_back({minVal, maxVal});
}

double FloatChromosome::getFitness() const { return fitness; }
void FloatChromosome::setFitness(double f) { fitness = f; }
size_t FloatChromosome::getSize() const { return genes.size(); }
std::unique_ptr<Chromosome> FloatChromosome::clone() const { 
    return std::make_unique<FloatChromosome>(*this); 
}

void FloatChromosome::swapGenes(Chromosome& other, size_t start, size_t end) {
    auto& o = dynamic_cast<FloatChromosome&>(other);
    for (size_t i = start; i <= end; ++i) {
        std::swap(genes[i], o.genes[i]);
    }
}

double FloatChromosome::getGene(size_t i) const { return genes[i]; }
void FloatChromosome::setGene(size_t i, double v) { genes[i] = v; }
std::pair<double, double> FloatChromosome::getBounds(size_t i) const { return bounds[i]; }