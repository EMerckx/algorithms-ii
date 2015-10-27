#ifndef BINARY_SEARCH_TREE_SEARCHTREE_H
#define BINARY_SEARCH_TREE_SEARCHTREE_H

#include <algorithm>
#include <iostream>
#include <memory>

using std::max;
using std::move;
using std::ostream;
using std::unique_ptr;

template<class Key, class Data>
class BinNode;

template<class Key, class Data>
class BinTree : public unique_ptr<BinNode<Key, Data> > {
public:
    using unique_ptr<BinNode<Key, Data>>::unique_ptr;

    BinTree() { }

    ~BinTree() { }

    BinTree(BinTree<Key, Data> &&binTree) : unique_ptr<BinNode<Key, Data>>(move(binTree)) { }

    BinTree<Key, Data> &operator=(BinTree<Key, Data> &&binTree) {
        unique_ptr<BinNode<Key, Data> >::operator=(binTree);
        return *this;
    }

    int depth() const {
        if (!*this) {
            return 0;
        }
        else {
            return max(this->get()->left.depth(), this->get()->right.depth()) + 1;
        }
    }

    void write(ostream &os) const;

    void write(ostream &os, BinNode<Key, Data> *binNode) const {
        if (binNode != 0) {
            os << *binNode;
        }
        else {
            "(,) ";
        }
    }

    void rotate(bool toLeft);

};

template<class Key, class Data>
class BinNode {
public:
    Key key;
    Data data;
    BinNode<Key, Data> *parent;
    BinTree<Key, Data> left, right;

    BinNode() : parent(0) { }

    BinNode(const Key &key, const Data &data) : key(key), data(data), parent(0) { }

    friend ostream &operator<<(ostream &os, BinNode<Key, Data> binNode){
        os << "(" << binNode.key << "," << binNode.data << ") ";
    }
};


#endif //BINARY_SEARCH_TREE_SEARCHTREE_H
