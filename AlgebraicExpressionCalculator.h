//
// Created by LykorisR on 2022/10/15.
//

#ifndef BIGNUMBERCALCULATOR_ALGEBRAICEXPRESSIONCALCULATOR_H
#define BIGNUMBERCALCULATOR_ALGEBRAICEXPRESSIONCALCULATOR_H

#include <stack>
#include "BigNumber.h"

namespace AlgebraicExpressionCalculator {

    class AlgebraicExpressionCalculator {
    public:
        explicit AlgebraicExpressionCalculator(std::string &);

        BigNumber::BigNumber result();

    private:
        std::string algebraicExpression;
        std::stack<char> operatorStack;
        std::stack<BigNumber::BigNumber> numberStack;

        static int getOperatorIndex(char);

        static char getOperatorPriority(char, char);

        static BigNumber::BigNumber calculate(const BigNumber::BigNumber&, const BigNumber::BigNumber&, char);
    };

} // AlgebraicExpressionCalculator

#endif //BIGNUMBERCALCULATOR_ALGEBRAICEXPRESSIONCALCULATOR_H
