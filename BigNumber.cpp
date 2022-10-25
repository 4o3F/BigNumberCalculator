//
// Created by LykorisR on 2022/10/15.
//

#include "BigNumber.h"

#define ACCURACY 1000

namespace BigNumber {
    // DONE
    BigNumber::BigNumber() {
        isPositive = true;
        integerDigits.push_back(0);
        decimalDigits.push_back(0);
    }

    // DONE
    BigNumber::BigNumber(long long number) {
        if (number >= 0) {
            isPositive = true;
        } else {
            isPositive = false;
            number *= (-1);
        }
        do {
            integerDigits.push_back((char) (number % 10));
            number /= 10;
        } while (number != 0);

        decimalDigits.push_back(0);
    }

    // DONE
    BigNumber::BigNumber(int number) {
        if (number >= 0) {
            isPositive = true;
        } else {
            isPositive = false;
            number *= (-1);
        }
        do {
            integerDigits.push_back((char) (number % 10));
            number /= 10;
        } while (number != 0);

        decimalDigits.push_back(0);
    }

    // DONE
    BigNumber::BigNumber(const std::string &numberStr) {
        bool type = numberStr.find('.') != std::string::npos;
        isPositive = true;
        for (auto iter = numberStr.crbegin(); iter < numberStr.crend(); iter++) {
            char ch = (*iter);
            if (ch == '.') {
                type = false;
                iter++;
            }
            if (iter == numberStr.rend() - 1) {
                if (ch == '+') {
                    break;
                }
                if (ch == '-') {
                    isPositive = false;
                    break;
                }
            }
            if (type) {
                decimalDigits.push_back((char) ((*iter) - '0'));
            } else {
                integerDigits.push_back((char) ((*iter) - '0'));
            }
        }
    }

    // DONE
    BigNumber::BigNumber(double number) {
        *this = BigNumber(std::to_string(number));
    }

    // DONE
    BigNumber &BigNumber::operator=(const BigNumber &) = default;

    // DONE
    BigNumber operator-(const BigNumber &number) {
        BigNumber returnNumber(number);
        returnNumber.isPositive = !returnNumber.isPositive;
        return returnNumber;
    }

    // DONE
    BigNumber &BigNumber::operator++() {
        if (!(*this).decimalDigits.empty() || !(*this).decimalDigits.empty()) {
            throw std::range_error("This operation can only apply to integer");
        }
        BigNumber number = *this;
        number += BigNumber(1);
        integerDigits = number.integerDigits;
        isPositive = number.isPositive;
        return *this;
    }

    // DONE
    BigNumber &BigNumber::operator--() {
        if (!(*this).decimalDigits.empty() || !(*this).decimalDigits.empty()) {
            throw std::range_error("This operation can only apply to integer");
        }
        BigNumber number = *this;
        number -= BigNumber(1);
        integerDigits = number.integerDigits;
        isPositive = number.isPositive;
        return *this;
    }

    // DONE
    const BigNumber BigNumber::operator++(int) {
        BigNumber bigNumber = *this;
        ++(*this);
        return bigNumber;
    }

    // DONE
    const BigNumber BigNumber::operator--(int) {
        BigNumber bigNumber = *this;
        --(*this);
        return bigNumber;
    }

    // DONE
    BigNumber operator+(const BigNumber &numberA, const BigNumber &numberB) {
        BigNumber tempNumber(numberA);
        tempNumber += numberB;
        return tempNumber;
    }

    // DONE
    BigNumber operator-(const BigNumber &numberA, const BigNumber &numberB) {
        BigNumber tempNumber(numberA);
        tempNumber -= numberB;
        return tempNumber;
    }

    // DONE
    BigNumber &operator+=(BigNumber &numberA, const BigNumber &numberB) {
        if (numberA.isPositive == numberB.isPositive) {
            std::vector<char>::iterator iter1;
            std::vector<char>::const_iterator iter2, it;

            //先处理小数部分
            int numberA_decimal_size = static_cast<int>(numberA.decimalDigits.size());
            int numberB_decimal_size = static_cast<int>(numberB.decimalDigits.size());
            char carry = 0;
            if (numberA_decimal_size < numberB_decimal_size) {
                iter1 = numberA.decimalDigits.begin();
                iter2 = numberB.decimalDigits.begin();
                iter2 = iter2 - (numberA_decimal_size - numberB_decimal_size);

                while (iter1 != numberA.decimalDigits.end() && iter2 != numberB.decimalDigits.end()) {
                    *iter1 = static_cast<char>((*iter1) + (*iter2) + carry);
                    carry = static_cast<char>((*iter1) > 9);
                    *iter1 = static_cast<char>((*iter1) % 10);
                    iter1++;
                    iter2++;
                }

                it = numberB.decimalDigits.begin();
                iter2 = numberB.decimalDigits.end();
                iter2 = iter2 - numberA_decimal_size - 1;
                while (iter2 != it) {
                    numberA.decimalDigits.insert(numberA.decimalDigits.begin(), *iter2);
                    iter2--;
                }
                numberA.decimalDigits.insert(numberA.decimalDigits.begin(), *iter2);
            } else if (numberA_decimal_size > numberB_decimal_size) {
                iter1 = numberA.decimalDigits.begin();
                iter1 = iter1 + (numberA_decimal_size - numberB_decimal_size);
                iter2 = numberB.decimalDigits.begin();

                while (iter1 != numberA.decimalDigits.end() && iter2 != numberB.decimalDigits.end()) {
                    *iter1 = static_cast<char>((*iter1) + (*iter2) + carry);
                    carry = static_cast<char>((*iter1) > 9);
                    *iter1 = static_cast<char>((*iter1) % 10);
                    iter1++;
                    iter2++;
                }
            } else {
                iter1 = numberA.decimalDigits.begin();
                iter2 = numberB.decimalDigits.begin();
                while (iter1 != numberA.decimalDigits.end() && iter2 != numberB.decimalDigits.end()) {
                    *iter1 = static_cast<char>((*iter1) + (*iter2) + carry);
                    carry = static_cast<char>((*iter1) > 9);
                    *iter1 = static_cast<char>((*iter1) % 10);
                    iter1++;
                    iter2++;
                }
            }

            iter1 = numberA.integerDigits.begin();
            iter2 = numberB.integerDigits.begin();

            while (iter1 != numberA.integerDigits.end() && iter2 != numberB.integerDigits.end()) {
                *iter1 = static_cast<char>((*iter1) + (*iter2) + carry);
                carry = static_cast<char>((*iter1) > 9);
                *iter1 = static_cast<char>((*iter1) % 10);
                iter1++;
                iter2++;
            }
            while (iter1 != numberA.integerDigits.end()) {
                *iter1 = static_cast<char>((*iter1) + carry);
                carry = static_cast<char>((*iter1) > 9);
                *iter1 = static_cast<char>((*iter1) % 10);
                iter1++;
            }
            while (iter2 != numberB.integerDigits.end()) {
                char val = static_cast<char>((*iter2) + carry);
                carry = static_cast<char>(val > 9);
                val %= 10;
                numberA.integerDigits.push_back(val);
                iter2++;
            }
            if (carry != 0) {
                numberA.integerDigits.push_back(carry);
            }
            numberA.trim();
            return numberA;
        } else {
            if (numberA.isPositive) {
                BigNumber temp(-numberB);
                return numberA -= temp;
            } else {
                BigNumber temp(-numberA);
                return numberA = numberB - temp;
            }
        }
    }

    // DONE
    BigNumber &operator-=(BigNumber &numberA, const BigNumber &numberB) {
        if (numberA.isPositive == numberB.isPositive) {
            if (numberA.isPositive) {
                if (numberA < numberB) {
                    BigNumber temp(numberB - numberA);
                    numberA = -temp;
                    numberA.trim();
                    return numberA;
                }
            } else {
                if (-numberA > -numberB)
                    return numberA = -((-numberA) - (-numberB));
                else
                    return numberA = (-numberB) - (-numberA);
            }

            char borrow = 0;
            int numberA_decimal_size = static_cast<int>(numberA.decimalDigits.size());
            int numberB_decimal_size = static_cast<int>(numberB.decimalDigits.size());
            auto it1 = numberA.decimalDigits.begin();
            auto it2 = numberB.decimalDigits.begin();

            if (numberA_decimal_size > numberB_decimal_size) {
                numberA_decimal_size -= numberB_decimal_size;
                it1 = it1 + numberA_decimal_size;
            } else {
                int number = numberB_decimal_size - numberA_decimal_size;
                while (number != 0) {
                    numberA.decimalDigits.insert(numberA.decimalDigits.begin(), 0);
                    number--;
                }
                it1 = numberA.decimalDigits.begin();
                it2 = numberB.decimalDigits.begin();
            }
            while ((it1 != numberA.decimalDigits.end()) && (it2 != numberB.decimalDigits.end())) {
                (*it1) = static_cast<char>((*it1) - (*it2) - borrow);
                borrow = 0;
                if ((*it1) < 0) {
                    borrow = 1;
                    (*it1) += 10;
                }
                it1++;
                it2++;
            }
            auto iter1 = numberA.integerDigits.begin();
            auto iter2 = numberB.integerDigits.begin();

            while (iter1 != numberA.integerDigits.end() && iter2 != numberB.integerDigits.end()) {
                (*iter1) = static_cast<char>((*iter1) - (*iter2) - borrow);
                borrow = 0;
                if ((*iter1) < 0) {
                    borrow = 1;
                    (*iter1) += 10;
                }
                iter1++;
                iter2++;
            }
            while (iter1 != numberA.integerDigits.end()) {
                (*iter1) = static_cast<char>((*iter1) - borrow);
                borrow = 0;
                if ((*iter1) < 0) {
                    borrow = 1;
                    (*iter1) += 10;
                } else
                    break;
                iter1++;
            }
            numberA.trim();
            return numberA;
        } else {
            if (numberA > BigNumber(0)) {
                BigNumber temp(-numberB);
                return numberA += temp;
            } else {
                BigNumber temp(-numberA);
                return numberA = -(numberB + temp);
            }
        }
    }

    // DONE
    BigNumber operator*(const BigNumber &numberA, const BigNumber &numberB) {
        BigNumber tempNumber(numberA);
        tempNumber *= numberB;
        return tempNumber;
    }

    // DONE
    BigNumber operator/(const BigNumber &numberA, const BigNumber &numberB) {
        BigNumber tempNumber(numberA);
        tempNumber /= numberB;
        return tempNumber;
    }

    // DONE
    BigNumber &operator*=(BigNumber &numberA, const BigNumber &numberB) {
        BigNumber result(0);
        if (numberA == BigNumber(0) || numberB == BigNumber(0))
            result = BigNumber(0);
        else {
            int size = 0;
            std::vector<char> temp_numberA(numberA.integerDigits.begin(), numberA.integerDigits.end());
            if (numberA.decimalDigits.size() != 1 ||
                (numberA.decimalDigits.size() == 1 && (*numberA.decimalDigits.begin()) != 0)) {
                temp_numberA.insert(temp_numberA.begin(), numberA.decimalDigits.begin(), numberA.decimalDigits.end());
                size += static_cast<int>(numberA.decimalDigits.size());
            }

            std::vector<char> temp_numberB(numberB.integerDigits.begin(), numberB.integerDigits.end());
            if (numberB.decimalDigits.size() != 1 ||
                (numberB.decimalDigits.size() == 1 && (*numberB.decimalDigits.begin()) != 0)) {
                temp_numberB.insert(temp_numberB.begin(), numberB.decimalDigits.begin(), numberB.decimalDigits.end());
                size += static_cast<int>(numberB.decimalDigits.size());
            }

            auto iter2 = temp_numberB.begin();
            while (iter2 != temp_numberB.end()) {
                if (*iter2 != 0) {
                    std::deque<char> temp(temp_numberA.begin(), temp_numberA.end());
                    char carry = 0;
                    auto iter1 = temp.begin();
                    while (iter1 != temp.end()) {
                        (*iter1) *= (*iter2);
                        (*iter1) += carry;
                        carry = (*iter1) / 10;
                        (*iter1) %= 10;
                        iter1++;
                    }
                    if (carry != 0) {
                        temp.push_back(carry);
                    }
                    int num_of_zeros = iter2 - temp_numberB.begin();
                    while (num_of_zeros--)
                        temp.push_front(0);
                    BigNumber temp2;
                    temp2.integerDigits.clear();
                    temp2.integerDigits.insert(temp2.integerDigits.end(), temp.begin(), temp.end());
                    temp2.trim();
                    result = result + temp2;
                }
                iter2++;
            }
            result.isPositive = ((numberA.isPositive && numberB.isPositive) ||
                                 (!numberA.isPositive && !numberB.isPositive));

            if (size != 0) {
                if (size >= result.integerDigits.size()) {
                    int n = size - result.integerDigits.size();
                    for (int i = 0; i <= n; i++)
                        result.integerDigits.insert(result.integerDigits.end(), 0);
                }
                result.decimalDigits.clear();
                result.decimalDigits.insert(result.decimalDigits.begin(), result.integerDigits.begin(),
                                            result.integerDigits.begin() + size);
                result.integerDigits.erase(result.integerDigits.begin(), result.integerDigits.begin() + size);
            }
        }
        numberA = result;
        numberA.trim();
        return numberA;
    }

    // DONE
    BigNumber &operator/=(BigNumber &numberA, const BigNumber &numberB) {
        if (numberB == BigNumber(0))
            throw std::out_of_range("Division by 0");
        if (numberA == BigNumber(0))
            return numberA;
        if (numberA == numberB)
            return (numberA = BigNumber(1));

        BigNumber temp_numberA = numberA;
        BigNumber temp_numberB = numberB;

        temp_numberA.isPositive = true;
        temp_numberB.isPositive = true;

        int Integer_Size = 0;
        if ((temp_numberB.decimalDigits.size() == 1) && (*(temp_numberB.decimalDigits.begin()) == 0)) {
        } else {
            int t = temp_numberB.decimalDigits.size();
            while (t--) {
                temp_numberA = temp_numberA * BigNumber(10);
                temp_numberB = temp_numberB * BigNumber(10);
            }
        }
        if (temp_numberA < temp_numberB) {
            while (temp_numberA < temp_numberB) {
                temp_numberA *= BigNumber(10);
                Integer_Size--;
            }
        } else {
            while (temp_numberA > temp_numberB) {
                temp_numberA.decimalDigits.push_back(*temp_numberA.integerDigits.begin());
                temp_numberA.integerDigits.erase(temp_numberA.integerDigits.begin());
                Integer_Size++;
            }
        }

        int k = ACCURACY;
        BigNumber quotient(0);

        while (k--) {
            if (temp_numberA < temp_numberB) {
                temp_numberA = temp_numberA * BigNumber(10);
                quotient = quotient * BigNumber(10);
            } else {
                int i;
                BigNumber compare;
                for (i = 1; i <= 10; i++) {
                    BigNumber BF(i);
                    compare = temp_numberB * BF;
                    if (compare > temp_numberA)
                        break;
                }
                compare -= temp_numberB;
                temp_numberA -= compare;
                BigNumber index(i - 1);
                quotient = quotient + index;
            }
        }

        if (Integer_Size < 0) {
            std::vector<char> temp(quotient.integerDigits.begin(), quotient.integerDigits.end());
            quotient.integerDigits.clear();
            quotient.integerDigits.push_back(0);

            quotient.decimalDigits.clear();
            int count_zero = -Integer_Size;
            while (--count_zero) {
                quotient.decimalDigits.insert(quotient.decimalDigits.begin(), 0);
            }
            quotient.decimalDigits.insert(quotient.decimalDigits.begin(), temp.begin(), temp.end());
        } else {
            if (quotient.integerDigits.size() > Integer_Size) {
                std::vector<char> temp(quotient.integerDigits.begin(), quotient.integerDigits.end());

                quotient.integerDigits.clear();

                quotient.integerDigits.assign(temp.end() - Integer_Size, temp.end());

                quotient.decimalDigits.clear();

                quotient.decimalDigits.insert(quotient.decimalDigits.begin(), temp.begin(), temp.end() - Integer_Size);
            } else {
                int t = Integer_Size - quotient.integerDigits.size();
                while (t--) {
                    quotient = quotient * BigNumber(10);
                }
            }
        }
        quotient.isPositive = ((numberA.isPositive && numberB.isPositive) ||
                               (!numberA.isPositive && !numberB.isPositive));
        numberA = quotient;
        numberA.trim();
        return numberA;

    }

    // DONE
    BigNumber operator%(const BigNumber &numberA, const BigNumber &numberB) {
        BigNumber tempNumber;
        tempNumber = numberA;
        tempNumber %= numberB;
        return tempNumber;
    }

    // DONE
    BigNumber &operator%=(BigNumber &numberA, const BigNumber &numberB) {
        if (!(((numberA.decimalDigits.size() == 1 && numberA.decimalDigits.at(0) == 0) ||
               numberA.decimalDigits.empty()) &&
              ((numberB.decimalDigits.size() == 1 && numberB.decimalDigits.at(0) == 0) ||
               numberB.decimalDigits.empty()))) {
            throw std::range_error("Mod can only be apply to integer");
        }

        if (numberB.integerDigits.size() == 1 && numberB.integerDigits[0] == 0) {
            throw std::range_error("Division By 0");
        }
        if (abs(numberA) < abs(numberB)) {
            numberA = BigNumber();
            return numberA;
        }

        if (numberA == numberB) {
            numberA = BigNumber(1);
            return numberA;
        }
        BigNumber tempNumber = numberA / numberB;
        tempNumber.decimalDigits.clear();
        numberA = numberA - (tempNumber) * numberB;
        return numberA;

    }

    // DONE
    bool operator==(const BigNumber &numberA, const BigNumber &numberB) {
        if (numberA.isPositive != numberB.isPositive)
            return false;
        if (numberA.integerDigits.size() != numberB.integerDigits.size())
            return false;
        if (numberA.decimalDigits.size() != numberB.decimalDigits.size())
            return false;

        auto iter1 = numberA.decimalDigits.begin();
        auto iter2 = numberB.decimalDigits.begin();
        while (iter1 != numberA.decimalDigits.end()) {
            if (*iter1 != *iter2)
                return false;
            iter1++;
            iter2++;
        }

        iter1 = numberA.integerDigits.begin();
        iter2 = numberB.integerDigits.begin();
        while (iter1 != numberA.integerDigits.end()) {
            if (*iter1 != *iter2)
                return false;
            iter1++;
            iter2++;
        }
        return true;
    }

    // DONE
    bool operator!=(const BigNumber &numberA, const BigNumber &numberB) {
        return !(numberA == numberB);
    }

    // DONE
    bool operator>(const BigNumber &numberA, const BigNumber &numberB) {
        return !(numberA <= numberB);
    }

    // DONE
    bool operator<(const BigNumber &numberA, const BigNumber &numberB) {
        bool sign;
        if (numberA.isPositive != numberB.isPositive) {
            sign = !numberA.isPositive;
            return sign;
        } else {
            if (numberA.integerDigits.size() != numberB.integerDigits.size()) {
                if (numberA.isPositive) {
                    sign = numberA.integerDigits.size() < numberB.integerDigits.size();
                    return sign;
                } else {
                    sign = numberA.integerDigits.size() > numberB.integerDigits.size();
                    return sign;
                }
            }
            auto iter1 = numberA.integerDigits.rbegin();
            auto iter2 = numberB.integerDigits.rbegin();
            while (iter1 != numberA.integerDigits.rend()) {
                if (numberA.isPositive && *iter1 < *iter2)
                    return true;
                if (numberA.isPositive && *iter1 > *iter2)
                    return false;
                if (!numberA.isPositive && *iter1 > *iter2)
                    return true;
                if (!numberA.isPositive && *iter1 < *iter2)
                    return false;
                iter1++;
                iter2++;
            }

            auto it1 = numberA.decimalDigits.rbegin();
            auto it2 = numberB.decimalDigits.rbegin();
            while (it1 != numberA.decimalDigits.rend() && it2 != numberB.decimalDigits.rend()) {
                if (numberA.isPositive && *it1 < *it2)
                    return true;
                if (numberA.isPositive && *it1 > *it2)
                    return false;
                if (!numberA.isPositive && *it1 > *it2)
                    return true;
                if (!numberA.isPositive && *it1 < *it2)
                    return false;
                it1++;
                it2++;
            }
            return (numberA.isPositive && it2 != numberB.decimalDigits.rend()) ||
                   (!numberA.isPositive && it1 != numberA.decimalDigits.rend());
        }
    }

    // DONE
    bool operator>=(const BigNumber &numberA, const BigNumber &numberB) {
        return (numberA > numberB || numberA == numberB);
    }

    // DONE
    bool operator<=(const BigNumber &numberA, const BigNumber &numberB) {
        return (numberA < numberB || numberA == numberB);
    }

    // DONE
    std::ostream &operator<<(std::ostream &out, const BigNumber &number) {
        if (!number.isPositive) {
            out << "-";
        }
        for (auto iter = number.integerDigits.rbegin(); iter != number.integerDigits.rend(); iter++) {
            out << (char) ((*iter) + '0');
        }
        if (!(number.decimalDigits.size() == 1 && number.decimalDigits.at(0) == 0)) {
            out << '.';
            for (auto iter = number.decimalDigits.rbegin(); iter != number.decimalDigits.rend(); iter++) {
                out << (char) ((*iter) + '0');
            }
        }
        return out;
    }

    // DONE
    std::istream &operator>>(std::istream &in, BigNumber &number) {
        std::string numberStr;
        in >> numberStr;
        number = BigNumber(numberStr);
        return in;
    }

    // DONE
    BigNumber abs(const BigNumber &number) {
        BigNumber result;
        result.decimalDigits = number.decimalDigits;
        result.integerDigits = number.integerDigits;
        return result;
    }

    // DONE
    void BigNumber::trim() {
        auto iter = integerDigits.rbegin();

        while (!integerDigits.empty() && (*iter) == 0) {
            integerDigits.pop_back();
            iter = integerDigits.rbegin();
        }

        if (integerDigits.size() == 0 && decimalDigits.size() == 0) {
            isPositive = true;
        }

        if (integerDigits.size() == 0) {
            integerDigits.push_back(0);
        }

        auto it = decimalDigits.begin();

        while (!decimalDigits.empty() && (*it) == 0) {
            it = decimalDigits.erase(it);
        }

        if (decimalDigits.size() == 0) {
            decimalDigits.push_back(0);
        }
    }


} // AlgebraicExpressionCalculator