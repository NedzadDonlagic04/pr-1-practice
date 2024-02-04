#include"./../includes/accumulator.hpp"

#include<iostream>

namespace acc {
    void Accumulator::setValue(const long long value) {
        this->value = value;
    }

    long long Accumulator::getValue() const {
        return this->value;
    }


    void Accumulator::printCurrentAccumulatorValue() const {
        std::cout<<"Accumulator: "<<this->getValue()<<std::endl;
    }
}