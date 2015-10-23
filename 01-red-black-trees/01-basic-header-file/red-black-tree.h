#ifndef BASIC_HEADER_FILE_RED_BLACK_TREE_H
#define BASIC_HEADER_FILE_RED_BLACK_TREE_H

#include <memory>
#include <iostream>

using std::unique_ptr;
using std::ostream;
using std::endl;

template<class Key, class Data>
class RedBlackNode;

template<class Key, class Data>
class RedBlackTree : unique_ptr<RedBlackNode<Key, Data> > {
public:
    using unique_ptr<RedBlackNode<Key, Data> >::unique_ptr;

    RedBlackTree<Key, Data>() { };

    ~RedBlackTree<Key, Data>() { };

    RedBlackTree<Key, Data>(RedBlackTree<Key, Data> &&redBlackTree)
            : unique_ptr<RedBlackNode<Key, Data> >(move(redBlackTree)) { }

    RedBlackTree<Key, Data> &operator=(RedBlackTree<Key, Data> &&redBlackTree) {
        unique_ptr<RedBlackNode<Key, Data> >::operator=(move(redBlackTree));
        return *this;
    }

    friend ostream &operator<<(ostream &os, const RedBlackTree<Key, Data> &redBlackTree) {
        redBlackTree.write(os);
        return os;
    }

private:
    // we will write the tree in PREORDER
    void write(ostream &os) const;
};

template<class Key, class Data>
class RedBlackNode {
public:
    Key key;
    Data data;
    // isBlack = true  -> the node is black
    // isBlack = false -> the node is red
    bool isBlack;

    RedBlackTree<Key, Data> left, right;

    RedBlackNode() { }

    RedBlackNode(const Key key, const Data data, const bool isBlack) : key(key), data(data), isBlack(isBlack) { }
};

template<class Key, class Data>
void RedBlackTree<Key, Data>::write(ostream &os) const {
    if (this.get()) {
        os << "Key = " << this->get()->key << " | Data = " << this->get()->data << endl;
        this->get()->left.write(os);
        this->get()->right.write(os);
    }
}

#endif //BASIC_HEADER_FILE_RED_BLACK_TREE_H
