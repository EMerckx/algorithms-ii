#ifndef SPLAY_TREE_ADD_SPLAYTREE_H
#define SPLAY_TREE_ADD_SPLAYTREE_H

#include "zoekboom.h"

template<class Sleutel, class Data>
class SplayTree : public Zoekboom<Sleutel, Data> {
public:
    virtual void splay(Binboom<Sleutel, Data> *&plaats);

    void zoek(Sleutel &sl);

    virtual void voegtoe2(const Sleutel &sl, const Data &data);

    void schrijf(ostream &os) {
        this->deBinboom.schrijf(os);
    }

    /*friend ostream &operator<<(ostream &os, SplayTree<Sleutel, Data> &splayTree) {
        splayTree.deBinboom.schrijf(os);
        return os;
    }*/
};

template<class Sleutel, class Data>
void SplayTree<Sleutel, Data>::zoek(Sleutel &sl) {
    Binboom<Sleutel, Data> *plaats;
    Binknoop<Sleutel, Data> *ouder;
    this->zoekplaats(sl, plaats, ouder);

    splay(plaats);
}


template<class Sleutel, class Data>
void SplayTree<Sleutel, Data>::splay(Binboom<Sleutel, Data> *&plaats) {
    Binboom<Sleutel, Data> *kind = plaats;
    // while the child c is not the root node
    while (kind->get()->ouder != 0) {

        this->schrijf(std::cout);

        bool isKindLinks = (kind == &kind->get()->ouder->links) ? true : false;

        // ZIG: the parent of the child is the root node
        if (kind->get()->ouder == this->deBinboom.get()) {
            std::cout << "1. kind->get()->ouder == this->deBinboom.get() \n";
            std::cout << "\t is het kind links ? " << isKindLinks << "\n";
            this->deBinboom.roteer(!isKindLinks);

            kind = &this->deBinboom;
        }
        // ZIG-ZAG: the child has a grand parent
        //          the parent is a left child of the grand parent
        //          the child is a right child of the parent
        else if (kind->get()->ouder->ouder != 0) {
            std::cout << "2. kind->get()->ouder == this->deBinboom.get() \n";
            Binboom<Sleutel, Data> *ouder;
            bool isParentLinks;
            if (kind->get()->ouder == kind->get()->ouder->ouder->links.get()) {
                std::cout << "2.1. kind->get()->ouder == kind->get()->ouder->ouder->links.get() \n";
                isParentLinks = true;
                ouder = &kind->get()->ouder->ouder->links;
            }
            else {
                std::cout << "2.2. kind->get()->ouder == kind->get()->ouder->ouder->rechts.get() \n";
                isParentLinks = false;
                ouder = &kind->get()->ouder->ouder->rechts;
            }
            // rotate
            ouder->roteer(!isKindLinks);
            kind = ouder;
        }
    }


};

template<class Sleutel, class Data>
void SplayTree<Sleutel, Data>::voegtoe2(const Sleutel &sl, const Data &data) {
    //std::cout << sl << std::endl;
    this->voegtoe(sl, data);
}

#endif //SPLAY_TREE_ADD_SPLAYTREE_H
