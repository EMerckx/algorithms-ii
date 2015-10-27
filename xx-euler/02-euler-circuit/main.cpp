#include <iostream>
#include "graaf.h"

using namespace std;

int main() {
    cout << "Compilation succeded" << endl << endl;

    Graaf<GERICHT> graaf;
    int knoop1 = graaf.voegKnoopToe();
    int knoop2 = graaf.voegKnoopToe();

    cout << graaf << endl << endl;

    graaf.voegVerbindingToe(knoop1, knoop1);
    graaf.voegVerbindingToe(knoop1, knoop2);
    graaf.voegVerbindingToe(knoop2, knoop1);
    graaf.voegVerbindingToe(knoop2, knoop2);

    cout << graaf << endl << endl;

    graaf.schrijfEuler(cout);

    return 0;
}