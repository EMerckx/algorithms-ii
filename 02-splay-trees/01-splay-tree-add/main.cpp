#include <iostream>
#include "zoekboom.h"

//using std::cout;
//using std::endl;

bool testDiepte();

bool testZoekData();

bool testVerwijder();

bool testVerwijder1();

bool testVerwijder2();

bool testVerwijder3();

bool testVerwijder4();

bool testVerwijder5();

bool testVerwijder6();

int main() {

    cout << "Test diepte gesorteerd toevoegen: " << testDiepte() << endl;

    cout << "Test zoek data: " << testZoekData() << endl;

    cout << "Test verwijder sleutel: " << testVerwijder() << endl;

    cout << "Test verwijder sleutel 1: " << testVerwijder1() << endl;

    cout << "Test verwijder sleutel 2: " << testVerwijder2() << endl;

    cout << "Test verwijder sleutel 3: " << testVerwijder3() << endl;

    cout << "Test verwijder sleutel 4: " << testVerwijder4() << endl;

    cout << "Test verwijder sleutel 5: " << testVerwijder5() << endl;

    cout << "Test verwijder sleutel 6: " << testVerwijder6() << endl;

    return 0;
}

// we gaan gesorteerd toevoegen, dus krijgen we eigenlijk een gelinkte lijst
// links = kleiner ; rechts = groter
// de diepte van de boom = het aantal elementen
bool testDiepte() {
    int aantal_elementen = 5;

    Zoekboom<int, int> b;

    for (int i = 0; i < aantal_elementen; i++) {
        b.voegtoe(i, i + 1);
    }

    int diepte = b.diepte();

    return aantal_elementen == diepte;
}

// we gaan gesorteerd toevoegen, dus krijgen we eigenlijk een gelinkte lijst
// links = kleiner ; rechts = groter
// de diepte van de boom = het aantal elementen
bool testZoekData() {
    int aantal_elementen = 5;

    Zoekboom<int, int> b;

    for (int i = 0; i < aantal_elementen; i++) {
        b.voegtoe(i, i + 1);
    }

    // sleutel i heeft als data i+1
    int te_zoeken_sleutel = 1;
    int te_zoeken_data = te_zoeken_sleutel + 1;

    int *gezocht = b.zoekdata(te_zoeken_sleutel);

    return *gezocht == te_zoeken_data;
}

// we gaan gesorteerd toevoegen, dus krijgen we eigenlijk een gelinkte lijst
// links = kleiner ; rechts = groter
// de diepte van de boom = het aantal elementen
bool testVerwijder() {
    int aantal_elementen = 5;

    Zoekboom<int, int> b;

    for (int i = 0; i < aantal_elementen; i++) {
        b.voegtoe(i, i + 1);
    }

    int diepte1 = b.diepte();

    b.verwijder(1);

    int diepte2 = b.diepte();

    return diepte1 == diepte2 + 1;
}

bool testVerwijder1() {
    // creer de boom
    Zoekboom<int, int> b;
    b.voegtoe(3, 3);
    b.voegtoe(1, 1);
    b.voegtoe(2, 2);

    //cout << b;

    b.verwijder(1);

    //cout << b;

    return b.diepte() == 2;
}

bool testVerwijder2() {
    // creer de boom
    Zoekboom<int, int> b;
    b.voegtoe(1, 1);
    b.voegtoe(3, 3);
    b.voegtoe(2, 2);

    cout << b;

    b.verwijder(1);

    cout << b;

    return b.diepte() == 2;
}

bool testVerwijder3() {
    // creer de boom
    Zoekboom<int, int> b;
    b.voegtoe(1, 1);
    b.voegtoe(3, 3);
    b.voegtoe(2, 2);

    cout << b;

    b.verwijder(3);

    cout << b;

    return b.diepte() == 2;
}

bool testVerwijder4() {
    // creer de boom
    Zoekboom<int, int> b;
    b.voegtoe(2, 2);
    b.voegtoe(1, 1);
    b.voegtoe(3, 3);

    cout << b;

    b.verwijder(2);

    cout << b;

    return b.diepte() == 2;
}

bool testVerwijder5() {
    // creer de boom
    Zoekboom<int, int> b;
    b.voegtoe(7, 7);
    b.voegtoe(4, 4);
    b.voegtoe(8, 8);
    b.voegtoe(2, 2);
    b.voegtoe(6, 6);
    b.voegtoe(1, 1);
    b.voegtoe(3, 3);

    cout << b;

    b.verwijder(7);

    cout << b;

    return b.diepte() == 4;
}

bool testVerwijder6() {
    // creer de boom
    Zoekboom<int, int> b;
    b.voegtoe(7, 7);
    b.voegtoe(4, 4);
    b.voegtoe(8, 8);
    b.voegtoe(2, 2);
    b.voegtoe(6, 6);
    b.voegtoe(1, 1);
    b.voegtoe(3, 3);
    b.voegtoe(5, 5);

    cout << b;

    b.verwijder(7);

    cout << b;

    return b.diepte() == 4;
}