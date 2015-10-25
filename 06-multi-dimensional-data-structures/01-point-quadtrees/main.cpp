#include <iostream>
#include "pointquadtree.h"

using std::cout;
using std::endl;

int main() {
    cout << "Compilation succeeded" << endl;

    PointQuadTree<int, int, char> pointQuadTree;

    pointQuadTree.add(1,1,'a');

    return 0;
}