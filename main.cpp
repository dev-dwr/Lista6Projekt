#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>

int main() {

    //problem1
    std::vector<float> weights1 = {4, 1, 3, 2};
    std::vector<float> values1 = {5, 1, 4, 3};
    CKnapsackProblem problem1(5, weights1, values1);
    problem1.print();
    CGeneticAlgorithm genetic0(80, 0.6, 0.3, 10);
    genetic0.start(problem1);

    //problem2
    CKnapsackProblem problem2("../pliki/kanp1.txt");
    problem2.print();
    CGeneticAlgorithm genetic1(60, 0.3, 0.2, 10);
    genetic1.start(problem2);


    return 0;
}
