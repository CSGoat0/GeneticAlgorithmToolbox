#pragma once

struct GAConfig {
    int populationSize = 100;
    int maxGenerations = 500;
    double crossoverProbability = 0.8;
    double mutationProbability = 0.01;
};