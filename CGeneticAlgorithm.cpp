#include <random>
#include "CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm(int ipopulationSize, float dcrossProbability,
                                     float dmutationProbability, int iiterationNumber) {
    iterations = iiterationNumber;
    mutationProb = dmutationProbability;
    crossProb = dcrossProbability;
    populationSize = ipopulationSize;
}

CGeneticAlgorithm::~CGeneticAlgorithm() {
    individualVector.clear();
}


void CGeneticAlgorithm::makePopulation(int numOfProduct) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(1, 10);

    for (int i = 0; i < populationSize; i++) {
        std::vector<int> geneticCode;
        for (int j = 0; j < numOfProduct; j++) {
            int random;
            if (dist(mt) > 5) {
                random = 0;
            } else {
                random = 1;
            }
            geneticCode.push_back(random);
        }
        individualVector.push_back(new CIndividual(geneticCode));
    }
}

CIndividual *CGeneticAlgorithm::findBestIndividual() {
    CIndividual *temporaryEl = individualVector.at(0);
    for (CIndividual *individual: individualVector) {
        if (individual->getQuality() > temporaryEl->getQuality()) {
            temporaryEl = individual;
        }
    }
    return temporaryEl;
}


void CGeneticAlgorithm::calculateSolution(CKnapsackProblem &problem) {
    problem.getSolution(individualVector);
}


void CGeneticAlgorithm::mutatePopulation() {
    for (int i = 0; i < populationSize; i++) {
        individualVector[i]->mutatePopu(mutationProb);
    }
}

void CGeneticAlgorithm::crossPopulation() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, populationSize - 1);
    std::uniform_real_distribution<double> probCross(0.0, 1.0);

    std::vector<CIndividual *> childrenOfParents;

    while (childrenOfParents.size() != populationSize) {
        int firstPerson = dist(mt);
        int secondPerson = dist(mt);
        while (firstPerson == secondPerson) {
            secondPerson = dist(mt);
        }
        std::vector<CIndividual *> crossedChildren;
        if (probCross(mt) < crossProb) {
            if (individualVector[firstPerson]->getQuality() < individualVector[secondPerson]->getQuality()) {
                crossedChildren = individualVector[secondPerson]->crossPopu(*individualVector[firstPerson]);
            } else {
                crossedChildren = individualVector[firstPerson]->crossPopu(*individualVector[secondPerson]);
            }
            childrenOfParents.push_back(crossedChildren.at(0));
            childrenOfParents.push_back(crossedChildren.at(1));
        }
    }
    swapIndividuals(childrenOfParents);
}

void CGeneticAlgorithm::swapIndividuals(std::vector<CIndividual *> childrenOfParents) {
    individualVector = childrenOfParents;
}

CIndividual *CGeneticAlgorithm::start(CKnapsackProblem &problem) {
    makePopulation(problem.getNumberOfElementsInBackpack());
    calculateSolution(problem);
    for (int i = 0; i < iterations; i++) {
        crossPopulation();
        mutatePopulation();
        calculateSolution(problem);
    }
    std::cout << "best individual is quality :" << std::endl;
    CIndividual *best = findBestIndividual();
    std::cout << best->getQuality() << std::endl;
    std::cout << "genotype:" << std::endl;
    best->printGenotype();

    return findBestIndividual();
}