#include <bits/stdc++.h>
#include "AlgebraicExpressionCalculator.h"

int main() {
    std::string str;
    std::cout << "Enter a valid algebraic expression: ";
    std::cin >> str;
    AlgebraicExpressionCalculator::AlgebraicExpressionCalculator calculator(str);
    std::cout << calculator.result();

    return 0;
}
