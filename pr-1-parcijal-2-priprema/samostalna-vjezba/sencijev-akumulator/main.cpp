/*
g++ main.cpp ./src/memory.cpp ./src/accumulator.cpp ./src/utils.cpp ./src/oneAddressMachine.cpp -o run
*/

#include<iostream>

#include"./includes/utils.hpp"
#include"./includes/oneAddressMachine.hpp"

int main() {
    std::size_t memorySize {};

    utils::handleSizeInput(memorySize);

    oam::OneAddressMachine oneAddressMachine(memorySize);
    utils::handleMemoryLinesInput(oneAddressMachine.memory); 

    oneAddressMachine.startProcessingInstructions();

    return 0;
}