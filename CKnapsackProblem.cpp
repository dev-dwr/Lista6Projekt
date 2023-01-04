#include <fstream>
#include <sstream>
#include "CKnapsackProblem.h"
#include "CIndividual.h"

CKnapsackProblem::~CKnapsackProblem() {
    weightsVector.clear();
    valuesVector.clear();
}

CKnapsackProblem::CKnapsackProblem(float capacity, const std::vector<float> &weights,
                                   const std::vector<float> &values) {
    if (capacity < 0) {
        std::cout << "Negative capacity! error" << std::endl;
        return;
    }

    if (weights.empty() || values.empty()) {
        std::cout << "weight or value vector is empty! error!" << std::endl;
        return;
    }

    if (weights.size() != values.size()) {
        std::cout << "weights size and value size of vector needs to be the same! error!" << std::endl;
        return;
    }

    capacityKnap = capacity;
    weightsVector = weights;
    valuesVector = values;
}

CKnapsackProblem::CKnapsackProblem(const std::string &path) {
    std::ifstream file(path);

    float cap;
    std::vector<float> weightsTab;
    std::vector<float> valuesTab;
    std::string word;
    int line = 0;

    while (file >> word) {
        switch (line) {
            case 1:
                cap = std::stof(word);
                line++;
                break;
            case 3:
                valuesTab = stringLineOfNumberToVector(word);
                line++;
                break;
            case 5:
                weightsTab = stringLineOfNumberToVector(word);
                line++;
                break;
            default:
                line++;
        }
    }
    file.close();
    weightsVector = weightsTab;
    valuesVector = valuesTab;
    capacityKnap = cap;

}

void CKnapsackProblem::getSolution(std::vector<CIndividual*> individuals) {
    for(CIndividual* individual : individuals){
        individual->calculateFitnessAndQuality(weightsVector, capacityKnap, valuesVector);
    }
}

void CKnapsackProblem::print() {
    std::cout << "Problem plecakowy:\nLp.\tV.\tW." << std::endl;
    for (int i = 0; i < valuesVector.size(); i++) {
        printElement(i);
    }
}

void CKnapsackProblem::printElement(int offset) {
    if (offset >= 0 && offset < valuesVector.size()) {
        std::cout << (offset + 1) << ".\t" << valuesVector[offset] << "\t" << weightsVector[offset] << std::endl;
    }
}

int CKnapsackProblem::getNumberOfElementsInBackpack() {
    return valuesVector.size();
}

std::vector<float> CKnapsackProblem::stringLineOfNumberToVector(std::string &stringOfNumber) {
    std::vector<float> vec;
    size_t pos = 0;
    std::string token;
    while ((pos = stringOfNumber.find(',')) != std::string::npos) {
        token = stringOfNumber.substr(0, pos);
        vec.push_back(std::stof(token));
        stringOfNumber.erase(0, pos + 1);
    }
    vec.push_back(std::stof(stringOfNumber));
    return vec;
}