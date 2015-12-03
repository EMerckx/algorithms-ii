#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <tuple>

using std::cout;
using std::greater;
using std::pair;
using std::priority_queue;
using std::string;
using std::vector;

int main() {

    // variables
    int alphabetSize = 254;
    string text = "sentence";

    // create a priority with smallest first (min heap)
    // std::priority_queue<int, std::vector<int>, std::greater<int> > my_min_heap;
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> amountPerCharacter;

    // fill the character frequency vector
    vector<int> charFrequency(alphabetSize, 0);
    for (int i = 0; i < text.size(); i++) {
        int charInt = (int) text[i];
        charFrequency[charInt]++;
    }

    // fill the priority queue
    for (int i = 0; i < charFrequency.size(); i++) {
        if (charFrequency[i] > 0) {
            char currentCharacter = (char) i;
            pair<int, char> amountPerChar(charFrequency[i], currentCharacter);
            amountPerCharacter.push(amountPerChar);
        }
    }

    while (!amountPerCharacter.empty()) {
        // get the pair
        pair<int, char> amountPerChar = amountPerCharacter.top();
        amountPerCharacter.pop();

        // write the pair to the screen
        cout << amountPerChar.first << "\t" << amountPerChar.second << "\n";
    }

    // create the decoding tree here
    // ...

    return 0;
}