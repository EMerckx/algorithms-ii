#ifndef HUFFMANCODING_DECODINGTREE_H
#define HUFFMANCODING_DECODINGTREE_H

#include <memory>

using std::unique_ptr;
using std::move;

class INode;

class Node;

class Leaf;

class DecodingTree : unique_ptr<INode> {
    using unique_ptr<INode>::unique_ptr;

    DecodingTree() { }

    ~DecodingTree() { }

    DecodingTree(DecodingTree &&decodingTree) : unique_ptr<INode>(move(decodingTree)) { }

    DecodingTree &operator=(DecodingTree &&decodingTree) {
        unique_ptr<INode>::operator=(decodingTree);
        return *this;
    }
};

class INode {
public:
    int occurrences;
    DecodingTree left, right;
};

class Node : INode {
public:

};

class Leaf : INode {
public:
    char character;
};

#endif //HUFFMANCODING_DECODINGTREE_H
