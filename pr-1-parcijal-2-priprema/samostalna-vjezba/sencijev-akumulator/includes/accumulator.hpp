#ifndef ACCUMULATOR_HPP 
#define ACCUMULATOR_HPP

namespace acc {
    struct Accumulator {
        long long value {};

        Accumulator() = default; 

        void setValue(const long long);
        long long getValue() const; 

        void printCurrentAccumulatorValue() const;
    };
}

#endif