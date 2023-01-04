#include "CIndividual.h"
#include <random>


CIndividual::CIndividual(std::vector<int> genotype) {
    quality = 0;
    geneticCode = genotype;
}

CIndividual::~CIndividual() {
    geneticCode.clear();
}

float CIndividual::getQuality() {
    return quality;
}

std::vector<int> CIndividual::getGeneticCode() {
    return geneticCode;
}

std::vector<int> CIndividual::mutatePopu(float mutationProb) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    int size = geneticCode.size();
    for (int i = 0; i < size; i++) {
        if (dist(mt) < mutationProb) {
            if (geneticCode.at(i) == 1) {
                geneticCode[i] = 0;
            } else {
                geneticCode[i] = 1;
            }
        }
    }
    return geneticCode;
}

void CIndividual::calculateFitnessAndQuality(std::vector<float> weights, float capacity, std::vector<float> values) {
    float valueSum = 0;
    float weightSum = 0;
    int size = geneticCode.size();
    for (int i = 0; i < size; i++) {
        if (geneticCode[i] == 1) {
            valueSum += values[i];
            weightSum += weights[i];
        }
    }
    if (!(weightSum > capacity)){
        quality = valueSum;
    }else{
        quality = 0;
    }
}

std::vector<CIndividual *> CIndividual::crossPopu(CIndividual &diffIndi) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, geneticCode.size()-1);
    int splitPlace = dist(mt);
    int size = geneticCode.size();
    std::vector<int> geneticCodeAfterCrossing;
    std::vector<int> geneticCodeAfterCrossing2;

    for (int i = 0; i < size; i++) {
        if (i < splitPlace) {
            geneticCodeAfterCrossing.push_back(diffIndi.geneticCode[i]);
            geneticCodeAfterCrossing2.push_back(geneticCode[i]);
        } else {
            geneticCodeAfterCrossing.push_back(geneticCode[i]);
            geneticCodeAfterCrossing2.push_back(diffIndi.geneticCode[i]);
        }
    }
    std::vector<CIndividual *> result;
    result.push_back(new CIndividual(geneticCodeAfterCrossing2));
    result.push_back(new CIndividual(geneticCodeAfterCrossing));
    return result;
}

void CIndividual::printGenotype() {
    for(int i = 0; i < geneticCode.size(); i ++){
        std::cout << geneticCode[i] << std::endl;
    }
}

