#pragma once
#include <iostream>
#include <vector>
#include "CIndividual.h"

class CKnapsackProblem {
public:
    CKnapsackProblem(float capacity, const std::vector<float>& weights, const std::vector<float>& values);
    CKnapsackProblem(const std::string& filePath);

    CKnapsackProblem(float capacity, std::vector<float> weights, const std::vector<double> &values);

    ~CKnapsackProblem();
    void print();
    void printElement(int offset);

    int getNumberOfElementsInBackpack();
    void getSolution(std::vector<CIndividual*> individuals);
private:
    float capacityKnap;
    std::vector<float> weightsVector;
    std::vector<float> valuesVector;

    std::vector<float> stringLineOfNumberToVector(std::string& stringToConvert);
};
