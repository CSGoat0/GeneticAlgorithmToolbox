#pragma once
#include "../core/Chromosome.h"
#include <random>

class Mutation {
public:
    virtual ~Mutation() = default;
    virtual void mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) = 0;
};

class BitFlipMutation : public Mutation {
public:
    void mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) override;
};

class UniformFloatMutation : public Mutation {
public:
    void mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) override;
};

class NonUniformFloatMutation : public Mutation {
private:
    double bParam;
public:
    NonUniformFloatMutation(double b = 1.0) : bParam(b) {}
    void mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) override;
};

class SwapMutation : public Mutation {
public:
    void mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) override;
};