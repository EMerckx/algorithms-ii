#ifndef SPLAY_TREE_ADD_SPLAYTREE_H
#define SPLAY_TREE_ADD_SPLAYTREE_H

#include "zoekboom.h"

template<class Sleutel, class Data>
class SplayTree : public Zoekboom<Sleutel, Data> {
public:
    virtual void splay(Binboom<Sleutel, Data> *&plaats);

    void zoek(Sleutel &sl);

    virtual void voegtoe2(const Sleutel &sl, const Data &data);

    void schrijf2(ostream &os){
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
    std::cout << "hello0 \n";
    this->zoekplaats(sl, plaats, ouder);

    std::cout << "hello1 \n";
    splay(plaats);
}


template<class Sleutel, class Data>
void SplayTree<Sleutel, Data>::splay(Binboom<Sleutel, Data> *&plaats) {
    std::cout << "hello \n";
    Binboom<Sleutel, Data> *kind = plaats;
    // while the child c is not the root node
    if (kind->get() != this->deBinboom->ouder) {
        std::cout << "hello \n";
        bool naarLinks = (kind == &kind->get()->ouder->links) ? false : true;

        // ZIG: the parent of the child is the root node
        if (kind->get()->ouder == this->deBinboom.get()) {
            std::cout << "hello \n";
            this->deBinboom.roteer(naarLinks);
            std::cout << "hello 2 \n";
        }

    }


};

template<class Sleutel, class Data>
void SplayTree<Sleutel, Data>::voegtoe2(const Sleutel &sl, const Data &data) {
    std::cout << sl << std::endl;
    this->voegtoe(sl, data);
}

#endif //SPLAY_TREE_ADD_SPLAYTREE_H
