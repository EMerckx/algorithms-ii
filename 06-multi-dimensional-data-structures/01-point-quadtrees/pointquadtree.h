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

    PointQuadTree<X, Y,Data>(PointQuadTree<X,Y,Data> && pointQuadTree)
            : unique_ptr<PointQuadNode<X,Y, Data> >(move(pointQuadTree)){ }

    PointQuadTree<X, Y, Data>&operator= (PointQuadTree<X,Y, Data> && pointQuadTree){
        unique_ptr<PointQuadNode<X,Y,Data> >::operator=(move(pointQuadTree));
        return *this;
    };
};

template<class X, class Y, class Data>
class PointQuadNode {
public:
    X x;
    Y y;
    Data data;

    // [ SW , NW , SE , NE ]
    PointQuadNode<X, Y, Data> children[4];

    PointQuadNode() { }

    void setChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
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

    PointQuadTree<X, Y, Data> *getSouthWestChild() {
        return &children[0];
    }

    PointQuadTree<X, Y, Data> *getNorthWestChild() {
        return &children[1];
    }

    PointQuadTree<X, Y, Data> *getSouthEastChild() {
        return &children[2];
    }

    PointQuadTree<X, Y, Data> *getNorthEastChild() {
        return &children[3];
    }

    void setSouthWestChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
        children[0] = move(pointQuadTree);
    }

    void setNorthWestChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
        children[1] = move(pointQuadTree);
    }

    void setSouthEastChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
        children[2] = move(pointQuadTree);
    }

    void setNorthEastChild(PointQuadTree<X, Y, Data> &&pointQuadTree) {
        children[3] = move(pointQuadTree);
    }
};

#endif //POINT_QUADTREES_POINTQUADTREE_H
