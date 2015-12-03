#ifndef SHIFT_AND_WITH_FILE_BITPATTERN_H
#define SHIFT_AND_WITH_FILE_BITPATTERN_H

#include <iostream>

using std::ostream;

typedef unsigned int uint;
const int patroonlengte = sizeof(uint) * 8;

class BitPattern {
public:
    uint bits;

    BitPattern(uint u = 0) : bits(u) { };

//AND-operator
    const BitPattern operator&(const BitPattern &b) const {
        return BitPattern(bits & b.bits);
    }

    //OR-operator
    const BitPattern operator|(const BitPattern &b) const {
        return BitPattern(bits | b.bits);
    }

    //AND-=-operator
    const BitPattern &operator&=(const BitPattern &b) {
        bits &= b.bits;
        return *this;
    }

    //OR-=-operator
    const BitPattern &operator|=(const BitPattern &b) {
        bits |= b.bits;
        return *this;
    }

    //logic operators
    bool andOperator(const BitPattern &b) const {
        return (bits & b.bits) != 0;
    }

    bool orOperator(const BitPattern &b) const {
        return (bits | b.bits) != 0;
    }

    //attention: shiftoperations don't move anything is movement >= patternlength
    const BitPattern shiftLeft(uint movement) const {
        return BitPattern(bits << movement);
    }

    const BitPattern shiftRight(uint movement) const {
        return BitPattern(bits >> movement);
    }

    //not secured: u must be smaller than the patternlength
    static BitPattern onebit(uint u) {
        return BitPattern(uint(1) << (patroonlengte - 1 - u));
    }

    friend ostream &operator<<(ostream &os, const BitPattern &b) {
        for (int i = 0; i < patroonlengte; i++) {
            os << b.andOperator(onebit(i));
        }
        return os;
    }
};

#endif //SHIFT_AND_WITH_FILE_BITPATTERN_H
