#ifndef ONE_ADDRESS_MACHINE_HPP
#define ONE_ADDRESS_MACHINE_HPP

#include"./accumulator.hpp"
#include"./utils.hpp"

namespace oam {
    struct Instruction {
        const std::size_t index {};
        const long long value {};

        Instruction(const std::size_t, const long long);
    };

    // % is where I imagine the number would go in this case
    // expect at least 2 instructions
    // the exit one has to be 1st
    constexpr char VALID_INSTRUCTIONS[][constants::BUFFER_SIZE] = {
        "EXIT",
        "LOAD IMMIDIATE %",
        "LOAD DIRECT %",
        "LOAD INDIRECT %",
    };

    constexpr std::size_t SHORTEST_INSTRUCTION_SIZE_LEN = utils::getShortestInstructionLen(VALID_INSTRUCTIONS, std::size(VALID_INSTRUCTIONS));

    struct OneAddressMachine {
        memory::Memory memory {};
        acc::Accumulator accumulator {};
        
        OneAddressMachine(const std::size_t);

        void startProcessingInstructions();

        [[nodiscard]] std::optional<Instruction> isValidInstruction(const char * const) const;
        [[nodiscard]] bool isInstructionFormSame(const char * const, const char * const) const;
    
        bool processInstruction(const Instruction &);

        bool loadImmediate(const memory::AddressType);
        bool loadDirect(const memory::AddressType);
        bool loadIndirect(memory::AddressType);
    };
}

#endif