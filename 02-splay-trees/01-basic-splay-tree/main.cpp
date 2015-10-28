#include <iostream>
#include "splaytree.h"

bool testZigLeft();

bool testZigZagLeft();

bool testZigZigLeft();

bool testZigRight();

bool testZigZagRight();

bool testZigZigRight();

int main() {

    cout << "TEST ZIG LEFT" << endl;
    testZigLeft();
    cout << endl;

    cout << "TEST ZIG-ZAG LEFT" << endl;
    testZigZagLeft();
    cout << endl;

    cout << "TEST ZIG-ZIG LEFT" << endl;
    testZigZigLeft();
    cout << endl;

    cout << "TEST ZIG RIGHT" << endl;
    testZigRight();
    cout << endl;

    cout << "TEST ZIG-ZAG RIGHT" << endl;
    testZigZagRight();
    cout << endl;

    cout << "TEST ZIG-ZIG RIGHT" << endl;
    testZigZigRight();
    cout << endl;

    return 0;
}

bool testZigLeft() {
    SplayTree<int, int> splayTree;

    splayTree.voegtoe(4, 4);
    splayTree.voegtoe(2, 2);
    splayTree.voegtoe(5, 5);
    splayTree.voegtoe(1, 1);
    splayTree.voegtoe(3, 3);

    int tezoeken = 2;

    splayTree.zoek(tezoeken);

    splayTree.schrijf(cout);

}

bool testZigZagLeft() {
    SplayTree<int, int> splayTree;

    splayTree.voegtoe(4, 4);
    splayTree.voegtoe(2, 2);
    splayTree.voegtoe(5, 5);
    splayTree.voegtoe(1, 1);
    splayTree.voegtoe(3, 3);

    int tezoeken = 3;

    splayTree.zoek(tezoeken);

    splayTree.schrijf(cout);

}

bool testZigZigLeft() {
    SplayTree<int, int> splayTree;

    splayTree.voegtoe(4, 4);
    splayTree.voegtoe(2, 2);
    splayTree.voegtoe(5, 5);
    splayTree.voegtoe(1, 1);
    splayTree.voegtoe(3, 3);

    int tezoeken = 1;

    splayTree.zoek(tezoeken);

    splayTree.schrijf(cout);

}

bool testZigRight() {
    SplayTree<int, int> splayTree;

    splayTree.voegtoe(2, 2);
    splayTree.voegtoe(1, 1);
    splayTree.voegtoe(4, 4);
    splayTree.voegtoe(3, 3);
    splayTree.voegtoe(5, 5);

    int tezoeken = 4;

    splayTree.zoek(tezoeken);

    splayTree.schrijf(cout);
}

bool testZigZagRight() {
    SplayTree<int, int> splayTree;

    splayTree.voegtoe(2, 2);
    splayTree.voegtoe(1, 1);
    splayTree.voegtoe(4, 4);
    splayTree.voegtoe(3, 3);
    splayTree.voegtoe(5, 5);

    int tezoeken = 3;

    splayTree.zoek(tezoeken);

    splayTree.schrijf(cout);
}

bool testZigZigRight() {
    SplayTree<int, int> splayTree;

    splayTree.voegtoe(2, 2);
    splayTree.voegtoe(1, 1);
    splayTree.voegtoe(4, 4);
    splayTree.voegtoe(3, 3);
    splayTree.voegtoe(5, 5);

    int tezoeken = 5;

    splayTree.zoek(tezoeken);

    splayTree.schrijf(cout);
}