#include "shiftand.h"

using std::cout;

int main() {

    uint needleLength = 8;
    uchar needle[] = {'a', 'n', 'n', 'o', 'u', 'n', 'c', 'e'};
    ShiftAnd tmp(needle, needleLength);

    uchar haystack[] = {'a', 'n', 'n', 'u', 'a', 'l', '-', 'a', 'n', 'n', 'o', 'u', 'n', 'c', 'e', 'a', 'n', 'n', 'o',
                        'u', 'n', 'c', 'e', 'a', 'n', 'n', 'o', 'u', 'n', 'c', 'e', 'a', 'n', 'n', 'o', 'u', 'n', 'c',
                        'e'};
    queue<const uchar *> myq = tmp.search(haystack, 39);


    while (!myq.empty()) {
        const uchar *current = myq.front();
        myq.pop();
        for (int i = 0; i < needleLength; i++) {
            cout << *current;
            current++;
        }
        cout << "\n";
    }

    return 0;
}