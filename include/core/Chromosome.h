#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <random>

class Chromosome {
protected:
    double fitness = 0.0;

public:
    virtual ~Chromosome() = default;

    virtual double getFitness() const = 0;
    virtual void setFitness(double f) = 0;
    virtual size_t getSize() const = 0;
    
    virtual std::unique_ptr<Chromosome> clone() const = 0;
    
    // Used by generic crossovers to swap chunks of genes
    virtual void swapGenes(Chromosome& other, size_t startIdx, size_t endIdx) = 0;
};

class BinaryChromosome : public Chromosome {
private:
    std::vector<bool> genes;
public:
    BinaryChromosome(size_t size, std::mt19937& rng);
    BinaryChromosome(const std::vector<bool>& genes);
    ~BinaryChromosome() override = default;

    double getFitness() const override;
    void setFitness(double f) override;
    size_t getSize() const override;
    std::unique_ptr<Chromosome> clone() const override;
    void swapGenes(Chromosome& other, size_t startIdx, size_t endIdx) override;
    
    bool getGene(size_t index) const;
    void setGene(size_t index, bool value);
    void flipGene(size_t index);
};

class IntegerChromosome : public Chromosome {
private:
    std::vector<int> genes;
    std::vector<std::pair<int, int>> bounds;
public:
    IntegerChromosome(size_t size, int minVal, int maxVal, std::mt19937& rng);
    IntegerChromosome(const std::vector<int>& genes, int minVal, int maxVal);
    ~IntegerChromosome() override = default;

    double getFitness() const override;
    void setFitness(double f) override;
    size_t getSize() const override;
    std::unique_ptr<Chromosome> clone() const override;
    void swapGenes(Chromosome& other, size_t startIdx, size_t endIdx) override;
    
    int getGene(size_t index) const;
    void setGene(size_t index, int value);
    std::pair<int, int> getBounds(size_t index) const;
};

class FloatChromosome : public Chromosome {
private:
    std::vector<double> genes;
    std::vector<std::pair<double, double>> bounds;
public:
    FloatChromosome(size_t size, double minVal, double maxVal, std::mt19937& rng);
    FloatChromosome(const std::vector<double>& genes, double minVal, double maxVal);
    ~FloatChromosome() override = default;

    double getFitness() const override;
    void setFitness(double f) override;
    size_t getSize() const override;
    std::unique_ptr<Chromosome> clone() const override;
    void swapGenes(Chromosome& other, size_t startIdx, size_t endIdx) override;
    
    double getGene(size_t index) const;
    void setGene(size_t index, double value);
    std::pair<double, double> getBounds(size_t index) const;
};