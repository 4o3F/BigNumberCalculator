//
// Created by LykorisR on 2022/10/15.
//

#include "AlgebraicExpressionCalculator.h"

namespace AlgebraicExpressionCalculator {
    AlgebraicExpressionCalculator::AlgebraicExpressionCalculator(std::string &input) {
        input.push_back('@');
        algebraicExpression = input;
    }

    BigNumber::BigNumber AlgebraicExpressionCalculator::result() {
        operatorStack.push('@');
        int counter = 0;
        int index = 0;
        char character = algebraicExpression[index];

        bool firstNumberNegative = false;
        std::string numberStr = "";
        if (character == '-') {
            firstNumberNegative = true;
//            BigNumber::BigNumber number("-1");
//            numberStack.push(number);
            numberStr = "-";
            counter++;
            index++;
            character = algebraicExpression[index];
        }


        while (character != '@' || operatorStack.top() != '@') {
            if (std::isdigit(character) || character == '.') {
                if (counter != 0) {
//                    BigNumber::BigNumber number;
//                    number = numberStack.top();
//                    numberStack.pop();
//                    if (firstNumberNegative) {
//                        number *= BigNumber::BigNumber(character - '0');
//                        firstNumberNegative = false;
//                    } else {
//                        number *= BigNumber::BigNumber(10);
//                        number += BigNumber::BigNumber(character - '0');
//                    }
                    if (!numberStack.empty()) {
                        numberStack.pop();
                    }
                    numberStr.push_back(character);
                    BigNumber::BigNumber number(numberStr);
                    numberStack.push(number);
                } else {
                    numberStr.push_back(character);
                    BigNumber::BigNumber number(character - '0');
                    numberStack.push(number);
                    counter++;
                }
                index++;
                character = algebraicExpression[index];
            } else {
                counter = 0;
                numberStr = "";
                switch (getOperatorPriority(operatorStack.top(), character)) {
                    case '<':
                        operatorStack.push(character);
                        index++;
                        character = algebraicExpression[index];
                        break;
                    case '=':
                        operatorStack.pop();
                        index++;
                        character = algebraicExpression[index];
                        break;
                    case '>':
                        char operatorChar = operatorStack.top();
                        operatorStack.pop();
                        BigNumber::BigNumber numberA = numberStack.top();
                        numberStack.pop();
                        BigNumber::BigNumber numberB = numberStack.top();
                        numberStack.pop();

                        BigNumber::BigNumber number;
                        number = calculate(numberA, numberB, operatorChar);
                        numberStack.push(number);
                }
            }
        }
        return numberStack.top();
    }

    int AlgebraicExpressionCalculator::getOperatorIndex(char operatorChar) {
        int index = 0;
        switch (operatorChar) {
            case '+':
                index = 0;
                break;
            case '-':
                index = 1;
                break;
            case '*':
                index = 2;
                break;
            case '/':
                index = 3;
                break;
            case '%':
                index = 4;
                break;
            case '(':
                index = 5;
                break;
            case ')':
                index = 6;
                break;
            case '@':
                index = 7;
                break;
            default:
                break;
        }
        return index;
    }

    char AlgebraicExpressionCalculator::getOperatorPriority(char operatorA, char operatorB) {

        const char priority[8][8] =
                {
                        {'>', '>', '<', '<', '<', '<', '>', '>'},
                        {'>', '>', '<', '<', '<', '<', '>', '>'},
                        {'>', '>', '>', '>', '>', '<', '>', '>'},
                        {'>', '>', '>', '>', '>', '<', '>', '>'},
                        {'>', '>', '>', '>', '>', '<', '>', '>'},
                        {'<', '<', '<', '<', '<', '<', '=', '0'},
                        {'>', '>', '>', '>', '>', '0', '>', '>'},
                        {'<', '<', '<', '<', '<', '<', '0', '='},
                };
        int indexA = getOperatorIndex(operatorA);
        int indexB = getOperatorIndex(operatorB);

        return priority[indexA][indexB];
    }

    BigNumber::BigNumber
    AlgebraicExpressionCalculator::calculate(const BigNumber::BigNumber &numberA, const BigNumber::BigNumber &numberB,
                                             char operatorChar) {
        BigNumber::BigNumber result;
        switch (operatorChar) {
            case '+':
                result = numberB + numberA;
                break;
            case '-':
                result = numberB - numberA;
                break;
            case '*':
                result = numberB * numberA;
                break;
            case '/':
                result = numberB / numberA;
                break;
            case '%':
                result = numberB % numberA;
                break;
            default:
                break;
        }
        return result;
    }
} // AlgebraicExpressionCalculator