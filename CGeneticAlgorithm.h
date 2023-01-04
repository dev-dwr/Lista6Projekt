#pragma once
#include <iostream>
#include <random>
#include "CIndividual.h"
#include "CKnapsackProblem.h"

class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(int ipopulationSize, float dcrossProbability, float dmutationProbability, int iiterationNumber);//
    ~CGeneticAlgorithm();

    CIndividual* start(CKnapsackProblem & CknapsackProblem);
private:
    std::vector<CIndividual*> individualVector;
    int populationSize;
    float mutationProb;
    int iterations;
    float crossProb;


    void swapIndividuals(std::vector<CIndividual *> childrenOfParents);
    void calculateSolution(CKnapsackProblem& cknapsackProblem);
    void crossPopulation();
    CIndividual* findBestIndividual();
    void makePopulation(int numOfProduct);
    void mutatePopulation();
};
