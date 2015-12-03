#ifndef SHIFT_AND_SHIFTAND_H
#define SHIFT_AND_SHIFTAND_H

#include "BitPattern.h"
#include <queue>

using std::queue;

typedef unsigned char uchar;

class ShiftAnd {
public:

    ShiftAnd(const uchar *needle, uint needleLength) {
        this->needleLength = needleLength;

        // set the found array
        bool found[needleLength];
        for (int i = 0; i < needleLength; i++) {
            found[i] = false;
        }

        // set a 1 bit on each place the same character appears
        for (int i = 0; i < needleLength; i++) {

            // if not found
            if (!found[i]) {

                // get the current char
                uchar current = needle[i];

                // set the bit in the BitPattern
                BitPattern bp = BitPattern::onebit(needleLength - i - 1);

                for (int j = i; j < needleLength; j++) {
                    // if the we found the current char again
                    // set the bit on that place to 1
                    if (needle[j] == current) {
                        found[j] = true;
                        BitPattern tmp = BitPattern::onebit(needleLength - j - 1);
                        bp |= tmp;
                    }
                }
                int curr = (int) current;
                charPattern[curr] = bp;

                // debug
                // std::cout << current << "\t" << curr << "\t" << bp << "\n";
            }
        }
    }

    const queue<const uchar *> search(const uchar *haystack, uint haystackLength) const {
        BitPattern bp = BitPattern::onebit(needleLength - 1);
        int foundIndex = 0;
        queue<const uchar *> result;

        for (int i = 0; i < haystackLength; i++) {
            BitPattern found = charPattern[(int) haystack[i]];

            if (found.andOperator(bp)) {

                // debug
                //std::cout << haystack[i] << "\t" << bp << "\n";

                if (bp.andOperator(BitPattern::onebit(0))) {

                    // debug
                    //std::cout << "found the whole word at index " << foundIndex << "\n";

                    result.push(&haystack[foundIndex]);
                    foundIndex = i + 1;
                }

                bp &= found;
                bp = bp.shiftLeft(1);
                bp |= BitPattern::onebit(needleLength - 1);
            }
            else {
                bp = BitPattern::onebit(needleLength - 1);
                foundIndex = i + 1;
            }
        }

        return result;
    }

private:
    BitPattern charPattern[256];
    uint needleLength;
};

#endif //SHIFT_AND_SHIFTAND_H
