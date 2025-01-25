#ifndef ITFDATA_H
#define ITFDATA_H

#include <string>
#include <stdint.h>

struct itfData {
    std::string itName; // Default initializes to an empty string
    uint32_t itfType;   // Default initializes to 0

    // Constructors
    itfData() : itName(""), itfType(0) {} // Default constructor
    itfData(const std::string& name, uint32_t type) : itName(name), itfType(type) {} // Parameterized constructor
};

#endif 
