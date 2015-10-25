#ifndef POINT_QUADTREES_POINTQUADTREE_H
#define POINT_QUADTREES_POINTQUADTREE_H

#include <memory>
#include "point.h"

using std::unique_ptr;
using std::move;

template<class X, class Y, class Data>
class PointQuadNode;

template<class X, class Y, class Data>
class PointQuadTree : unique_ptr<PointQuadNode<X, Y, Data> > {
public:
    using unique_ptr<PointQuadNode<X, Y, Data> >::unique_ptr;

    PointQuadTree() { }

    ~PointQuadTree() { }

    PointQuadTree<X, Y, Data>(PointQuadTree<X, Y, Data> &&pointQuadTree)
            : unique_ptr<PointQuadNode<X, Y, Data> >(move(pointQuadTree)) { }

    PointQuadTree<X, Y, Data> &operator=(PointQuadTree<X, Y, Data> &&pointQuadTree) {
        unique_ptr<PointQuadNode<X, Y, Data> >::operator=(move(pointQuadTree));
        return *this;
    }

    PointQuadTree<X, Y, Data> *search(X x, Y y);

    void add(X x, Y y, Data data);
};

template<class X, class Y, class Data>
class PointQuadNode {
public:
    X x;
    Y y;
    Data data;

    // [ SW , NW , SE , NE ]
    PointQuadNode<X, Y, Data> children[4];

    PointQuadNode() {
        for(int i=0; i<4; i++){
            PointQuadTree<X, Y, Data> pointQuadTree;
            children[i] = move(pointQuadTree);
        }
    }

    PointQuadNode(X x, Y y, Data data) {
        this->x = x;
        this->y = y;
        this->data = data;

        for(int i=0; i<4; i++){
            PointQuadTree<X, Y, Data> pointQuadTree;
            children[i] = move(pointQuadTree);
        }
    }

    void setChild(PointQuadTree<X, Y, Data> &&pointQuadTree);

    PointQuadTree<X, Y, Data> *getChild(X x, Y y);

private:
    PointQuadTree<X, Y, Data> *getSouthWestChild();

    PointQuadTree<X, Y, Data> *getNorthWestChild();

    PointQuadTree<X, Y, Data> *getSouthEastChild();

    PointQuadTree<X, Y, Data> *getNorthEastChild();

    void setSouthWestChild(PointQuadTree<X, Y, Data> &&pointQuadTree);

    void setNorthWestChild(PointQuadTree<X, Y, Data> &&pointQuadTree);

    void setSouthEastChild(PointQuadTree<X, Y, Data> &&pointQuadTree);

    void setNorthEastChild(PointQuadTree<X, Y, Data> &&pointQuadTree);
};

//---------------------------------------------------------------------------------------------------------------------

template<class X, class Y, class Data>
PointQuadTree<X, Y, Data> *PointQuadTree<X, Y, Data>::search(X x, Y y) {
    PointQuadTree<X, Y, Data> *pointQuadTree = this;
    // while the PointQuadTree exists and the x and y are not equal
    // then the searched PointQuadTree is not found
    while (pointQuadTree->get() != 0 && pointQuadTree->get()->x != x && pointQuadTree->get()->y != y) {
        // get the next PointQuadTree
        pointQuadTree = pointQuadTree->get()->getChild(x, y);
    }

    return pointQuadTree;
}

template<class X, class Y, class Data>
void PointQuadTree<X, Y, Data>::add(X x, Y y, Data data) {
    PointQuadTree<X, Y, Data> *pointQuadTree = this->search(x, y);
    if (pointQuadTree->get() != 0) {
        pointQuadTree->get()->setChild(pointQuadTree);
    }
    else {
        PointQuadTree<X, Y, Data> newPointQuadTree(x, y, data);
        (*pointQuadTree) = move(newPointQuadTree);
    }
}

//---------------------------------------------------------------------------------------------------------------------

template<class X, class Y, class Data>
PointQuadTree<X, Y, Data> *PointQuadNode<X, Y, Data>::getChild(X x, Y y) {
    if (x < this->x) {
        if (y < this->y) {
            return getSouthWestChild();
        }
        else {
            return getSouthEastChild();
        }
    }
    else {
        if (y < this->y) {
            return getNorthWestChild();
        }
        else {
            return getNorthEastChild();
        }
    }
}

template<class X, class Y, class Data>
void PointQuadNode<X, Y, Data>::setChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
    if ((*pointQuadTree)->get()->x < this->x) {
        if ((*pointQuadTree)->get()->y < this->y) {
            setSouthWestChild(pointQuadTree);
        }
        else {
            setSouthEastChild(pointQuadTree);
        }
    }
    else {
        if ((*pointQuadTree)->get()->y < this->y) {
            setNorthWestChild(pointQuadTree);
        }
        else {
            setNorthEastChild(pointQuadTree);
        }
    }
}

template<class X, class Y, class Data>
PointQuadTree<X, Y, Data> *PointQuadNode<X, Y, Data>::getSouthWestChild() {
    return &children[0];
}

template<class X, class Y, class Data>
PointQuadTree<X, Y, Data> *PointQuadNode<X, Y, Data>::getNorthWestChild() {
    return &children[1];
}

template<class X, class Y, class Data>
PointQuadTree<X, Y, Data> *PointQuadNode<X, Y, Data>::getSouthEastChild() {
    return &children[2];
}

template<class X, class Y, class Data>
PointQuadTree<X, Y, Data> *PointQuadNode<X, Y, Data>::getNorthEastChild() {
    return &children[3];
}

template<class X, class Y, class Data>
void PointQuadNode<X, Y, Data>::setSouthWestChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
    children[0] = move(pointQuadTree);
}

template<class X, class Y, class Data>
void PointQuadNode<X, Y, Data>::setNorthWestChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
    children[1] = move(pointQuadTree);
}

template<class X, class Y, class Data>
void PointQuadNode<X, Y, Data>::setSouthEastChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
    children[2] = move(pointQuadTree);
}

template<class X, class Y, class Data>
void PointQuadNode<X, Y, Data>::setNorthEastChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
    children[3] = move(pointQuadTree);
}

#endif //POINT_QUADTREES_POINTQUADTREE_H
