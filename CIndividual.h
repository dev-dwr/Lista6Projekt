#pragma once

#include <iostream>
#include <vector>
#include <random>


class CIndividual {
public:
    CIndividual(std::vector<int> genotype);

    ~CIndividual();

    std::vector<CIndividual *> crossPopu(CIndividual &diffIndi);

    std::vector<int> mutatePopu(float mutationProb);

    void printGenotype();

    void calculateFitnessAndQuality(std::vector<float> weights, float capacity, std::vector<float> values);

    std::vector<int> getGeneticCode();

    float getQuality();

private:
    float quality;
    std::vector<int> geneticCode;

};
