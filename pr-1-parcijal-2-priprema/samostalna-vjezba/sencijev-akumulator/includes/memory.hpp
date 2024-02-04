#ifndef MEMORY_HPP
#define MEMORY_HPP

#include<cstddef>
#include<memory>

namespace memory {
    using AddressType = unsigned int;

    struct Memory {
        std::size_t capacity {};
        std::size_t size {};

        std::unique_ptr<AddressType[]> memoryAddress {};
        std::unique_ptr<int[]> memoryValue {};

        std::size_t largetAddress {};
        std::size_t largestValue {};
        
        Memory() = default;
        Memory(const std::size_t);

        void resetMemory(const std::size_t);

        [[nodiscard]] std::ptrdiff_t doesAddressExist(const AddressType) const;
        [[nodiscard]] int getValueAtAddress(const AddressType) const;
        bool addAddressValue(const AddressType, const int);

        void sortAddresses();
        void printAddressValueTable() const;
    };
}

#endif