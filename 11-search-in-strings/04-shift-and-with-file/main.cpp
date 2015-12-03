#include "shiftand.h"
#include <fstream>
#include <vector>

using std::cout;
using std::ifstream;
using std::vector;

int main() {

    // init the needle and ShiftAnd instance
    uint needleLength = 8;
    uchar needle[] = {'A', 'b', 'd', 'a', 'l', 'l', 'a', 'h'};
    ShiftAnd shiftAnd(needle, needleLength);

    // read from the file
    ifstream input;
    input.open("res/koran.txt");
    vector<uchar> myvect;
    uchar character = input.get();
    while (!input.fail()) {
        myvect.push_back(character);
        character = input.get();
    }

    // init the haystack
    uchar *haystack = &myvect[0];
    int haystackLength = myvect.size();
    queue<const uchar *> myq = shiftAnd.search(haystack, haystackLength);

    // show the found items
    int amount = 0;
    while (!myq.empty()) {
        const uchar *current = myq.front();
        myq.pop();
        for (int i = 0; i < needleLength; i++) {
            cout << *current;
            current++;
        }
        cout << "\n";

        amount++;
    }

    cout << "Amount of items found: " << amount << "\n";

    return 0;
}