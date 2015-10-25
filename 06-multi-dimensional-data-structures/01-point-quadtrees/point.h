#ifndef POINT_QUADTREES_POINT_H
#define POINT_QUADTREES_POINT_H

template<class X, class Y>
class Point {
public:
    X x;
    Y y;

    Point() { }

    Point(X x, Y y) : x(x), y(y) { }
};

#endif //POINT_QUADTREES_POINT_H
