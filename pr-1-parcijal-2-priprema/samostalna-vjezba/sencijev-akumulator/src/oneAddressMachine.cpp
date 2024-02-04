#include"./../includes/oneAddressMachine.hpp"
#include"./../includes/constants.hpp"

#include<iostream>
#include<cstring>
#include<charconv>

namespace oam {
    OneAddressMachine::OneAddressMachine(const std::size_t capacity) {
        this->memory.resetMemory(capacity);
    }

    void OneAddressMachine::startProcessingInstructions() {
        char instruction[constants::BUFFER_SIZE] {}; 

        utils::clearTerminalANSI();
        utils::clearBuffer();
        while(1) {
            this->memory.printAddressValueTable();

            std::cin.getline(instruction, constants::BUFFER_SIZE);

            utils::clearTerminalANSI();
            
            auto instructionData = this->isValidInstruction(instruction);
            
            if (instructionData) {
                // EXIT
                if (instructionData.value().index == 0) {
                    break;
                }

                bool didInstructionFail { this->processInstruction(instructionData.value()) };

                if (!didInstructionFail) {
                    std::cout<<"Instruction fail\n";
                } else {
                    this->accumulator.printCurrentAccumulatorValue();
                }
            } else {
                std::cout<<"Invalid instruction\n";
            }

        }
    }

    bool OneAddressMachine::isInstructionFormSame(const char * const instruction, const char * const VALID_INSTRUCTION) const {
        for (std::size_t i = 0; i < strlen(instruction) && VALID_INSTRUCTION[i] != '%'; i++) {
            if (instruction[i] != VALID_INSTRUCTION[i]) {
                return false;
            }
        }
        
        return true;
    }

    std::optional<Instruction> OneAddressMachine::isValidInstruction(const char * const instruction) const {
        if (strcmp(instruction, VALID_INSTRUCTIONS[0]) == 0) {
            return Instruction(0, 0);
        } else if (utils::strlen(instruction) < SHORTEST_INSTRUCTION_SIZE_LEN) {
            return std::nullopt;
        }
    
        bool instrValidationFlag {};

        for (std::size_t i = 1; i < std::size(VALID_INSTRUCTIONS); i++) {
            instrValidationFlag = this->isInstructionFormSame(instruction, VALID_INSTRUCTIONS[i]);

            if (instrValidationFlag) {
                std::unique_ptr<char []> potentialNumber = utils::substr(instruction, strlen(VALID_INSTRUCTIONS[i]) - 1, strlen(instruction));
                
                memory::AddressType num {};

                auto [ptr, ec] = std::from_chars(potentialNumber.get(), potentialNumber.get() + strlen(potentialNumber.get()), num);

                // Used for debugging
                /* std::cout<<potentialNumber.get()<<std::endl;
                std::cout<<num<<std::endl;
                std::cout<<ptr<<std::endl; */

                if (ec == std::errc() && strlen(ptr) == 0) {
                    return Instruction(i, num);
                } else {
                    return std::nullopt;
                }
            }
        }

        return std::nullopt;
    }

    bool OneAddressMachine::loadImmediate(const memory::AddressType value) {
        this->accumulator.setValue(value);

        return true; 
    }
    
    bool OneAddressMachine::loadDirect(const memory::AddressType address) {
        if (this->memory.doesAddressExist(address) == -1) {
            this->accumulator.setValue(0);
            return false;
        }

        this->accumulator.setValue(this->memory.getValueAtAddress(address));

        return true;
    }
        
    bool OneAddressMachine::loadIndirect(memory::AddressType address) {
        if (this->memory.doesAddressExist(address) == -1) {
            this->accumulator.setValue(0);
            return false;
        }

        address = this->memory.getValueAtAddress(address);

        if (this->memory.doesAddressExist(address) == -1) {
            this->accumulator.setValue(0);
            return false;
        }

        this->accumulator.setValue(this->memory.getValueAtAddress(address));

        return true;
    }

    bool OneAddressMachine::processInstruction(const Instruction &instruction) {
        if (instruction.index == 1) {
            return this->loadImmediate(instruction.value);
        } else if (instruction.index == 2) {
            return this->loadDirect(instruction.value);
        } else {
            return this->loadIndirect(instruction.value);
        }
    }

    Instruction::Instruction(const std::size_t index, const long long value)
        : index(index), value(value) {}
}