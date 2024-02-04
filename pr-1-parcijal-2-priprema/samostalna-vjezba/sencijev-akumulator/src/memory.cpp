#include"./../includes/memory.hpp"
#include"./../includes/utils.hpp"

#include<iostream>
#include<cmath>
#include<cstring>

namespace memory {
    Memory::Memory(const std::size_t capacity) 
        :   capacity(capacity), 
            size(0), 
            largetAddress(0),
            largestValue(0),
            memoryAddress(std::make_unique<AddressType[]>(capacity)),
            memoryValue(std::make_unique<int[]>(capacity))
    {}

    void Memory::resetMemory(const std::size_t capacity) {
        this->capacity = capacity;
        this->size = 0;

        this->largetAddress = 0;
        this->largestValue = 0;

        this->memoryAddress.reset(new AddressType[capacity]);
        this->memoryValue.reset(new int[capacity]);
    }
        
    std::ptrdiff_t Memory::doesAddressExist(const AddressType address) const {
        std::ptrdiff_t start = 0;
        std::ptrdiff_t middle {};
        std::ptrdiff_t end = this->size - 1;

        while (start <= end) {
            middle = start + (end - start) / 2;

            if (this->memoryAddress[middle] == address) {
                return this->memoryAddress[middle];
            } else if (this->memoryAddress[middle] < address) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        return -1;
    }

    bool Memory::addAddressValue(const AddressType address, const int value) {
        if (this->size == this->capacity) {
            return false;
        } else if (this->doesAddressExist(address) != -1) {
            return false;
        }

        this->memoryAddress[this->size] = address;
        this->memoryValue[this->size] = value;

        if (this->size == 0) {
            this->largestValue = utils::getDigitCount(value);
            this->largetAddress = utils::getDigitCount(address);
        } else {
            this->largestValue = std::max(utils::getDigitCount(value), this->largestValue);
            this->largetAddress = std::max(utils::getDigitCount(address), this->largetAddress);

            this->sortAddresses();
        }

        this->size++;

        return true;
    }
    
    void Memory::sortAddresses() {
        std::size_t i = this->size;

        while (i >= 1 && this->memoryAddress[i] < this->memoryAddress[i - 1]) {
            std::swap(this->memoryAddress[i], this->memoryAddress[i - 1]);
            std::swap(this->memoryValue[i], this->memoryValue[i - 1]);

            i--;
        }
    }
    
    void Memory::printAddressValueTable() const {
        const char *addressText { "Address" };
        const char *valueText { "Value" };

        std::size_t maxWidth = std::max(strlen(valueText), strlen(addressText));
        maxWidth = std::max(maxWidth, this->largetAddress);
        maxWidth = std::max(maxWidth, this->largestValue);

        utils::drawLineBorder(maxWidth);
        utils::printFormatedMemoryLine(addressText, valueText, maxWidth);   
        utils::drawLineBorder(maxWidth);

        for (std::size_t i = 0; i < this->size; i++) {
            utils::printFormatedMemoryLine(this->memoryAddress[i], this->memoryValue[i], maxWidth);   
        }

        utils::drawLineBorder(maxWidth);
    }

    int Memory::getValueAtAddress(const AddressType address) const {
        std::ptrdiff_t start = 0;
        std::ptrdiff_t middle {};
        std::ptrdiff_t end = this->size - 1;

        while (start <= end) {
            middle = start + (end - start) / 2;

            if (this->memoryAddress[middle] == address) {
                return this->memoryValue[middle];
            } else if (this->memoryAddress[middle] < address) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        return 0;
    }
}