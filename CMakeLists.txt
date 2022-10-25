cmake_minimum_required(VERSION 3.24)
project(BigNumberCalculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(BigNumberCalculator main.cpp AlgebraicExpressionCalculator.cpp AlgebraicExpressionCalculator.h BigNumber.cpp BigNumber.h)
#add_executable(BigNumberCalculator main.cpp BigNumber.cpp BigNumber.h)