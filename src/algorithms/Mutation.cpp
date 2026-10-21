#include "../../include/algorithms/Mutation.h"

void BitFlipMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    // TODO: Iterate genes, if rand() < Pm, flipGene
}

void UniformFloatMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    // TODO: Implement Lab 2 Uniform Mutation
}

void NonUniformFloatMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    // TODO: Implement Lab 2 Non-Uniform Mutation using bParam
}

void SwapMutation::mutate(Chromosome& chromosome, int currentGen, int maxGen, std::mt19937& rng) {
    // TODO: Select two random indices and swap them
}