//
// Created by LykorisR on 2022/10/15.
//

#ifndef BIGNUMBERCALCULATOR_BIGNUMBER_H
#define BIGNUMBERCALCULATOR_BIGNUMBER_H

#include <string>
#include "iostream"
#include "vector"
#include "sstream"
#include <deque>

namespace BigNumber {
    class BigNumber {
    protected:
        std::vector<char> integerDigits;
        std::vector<char> decimalDigits;
        bool isPositive = true;

    public:
        explicit BigNumber();

        explicit BigNumber(long long);

        explicit BigNumber(int);

        explicit BigNumber(const std::string &);

        explicit BigNumber(double);

        // 运算符重载

        // 赋值运算符
        BigNumber &operator=(const BigNumber &);

        // 取负运算符
        friend BigNumber operator-(const BigNumber &);

        // 自增自减运算符
        BigNumber &operator++();

        BigNumber &operator--();

        const BigNumber operator++(int number);

        const BigNumber operator--(int number);

        // 加减
        friend BigNumber operator+(const BigNumber &, const BigNumber &);

        friend BigNumber operator-(const BigNumber &, const BigNumber &);

        friend BigNumber &operator+=(BigNumber &, const BigNumber &);

        friend BigNumber &operator-=(BigNumber &, const BigNumber &);

        // 乘除
        friend BigNumber operator*(const BigNumber &, const BigNumber &);

        friend BigNumber operator/(const BigNumber &, const BigNumber &);

        friend BigNumber &operator*=(BigNumber &, const BigNumber &);

        friend BigNumber &operator/=(BigNumber &, const BigNumber &);

        // 取余数
        friend BigNumber operator%(const BigNumber &, const BigNumber &);

        friend BigNumber &operator%=(BigNumber &, const BigNumber &);

        // 逻辑比较
        friend bool operator==(const BigNumber &, const BigNumber &);

        friend bool operator!=(const BigNumber &, const BigNumber &);

        friend bool operator>(const BigNumber &, const BigNumber &);

        friend bool operator<(const BigNumber &, const BigNumber &);

        friend bool operator>=(const BigNumber &, const BigNumber &);

        friend bool operator<=(const BigNumber &, const BigNumber &);


        // 输出输入
        friend std::ostream &operator<<(std::ostream &, const BigNumber &);

        friend std::istream &operator>>(std::istream &, BigNumber &);


    private:
        friend BigNumber abs(const BigNumber &);

        void trim();

    };

} // AlgebraicExpressionCalculator

#endif //BIGNUMBERCALCULATOR_BIGNUMBER_H
