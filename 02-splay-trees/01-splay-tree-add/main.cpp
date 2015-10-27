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

    splayTree.schrijf2(cout);

    int tezoeken = 2;

    splayTree.zoek(tezoeken);

    splayTree.schrijf2(cout);

    /*b.verwijder(1);

    cout << b;*/

    return 0;
}