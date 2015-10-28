#include <iostream>
#include "splaytree.h"

int main() {

    SplayTree<int, int> splayTree;

    splayTree.voegtoe2(4, 4);
    splayTree.voegtoe2(2, 2);
    splayTree.voegtoe2(5, 5);
    splayTree.voegtoe2(1, 1);
    splayTree.voegtoe2(3, 3);

    //cout << splayTree;

    splayTree.schrijf(cout);

    int tezoeken = 3;

    splayTree.zoek(tezoeken);

    splayTree.schrijf(cout);

    /*b.verwijder(1);

    cout << b;*/

    return 0;
}