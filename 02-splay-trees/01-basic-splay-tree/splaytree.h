#ifndef BASIC_SPLAY_TREE_SPLAYTREE_H
#define BASIC_SPLAY_TREE_SPLAYTREE_H

#include "zoekboom.h"

template<class Sleutel, class Data>
class SplayTree : public Zoekboom<Sleutel, Data> {
public:
    void zoek(Sleutel &sl);

    virtual void voegtoe(const Sleutel &sl, const Data &data);

    void schrijf(ostream &os) {
        this->deBinboom.schrijf(os);
    }

private:
    virtual void splay(Binboom<Sleutel, Data> *&plaats);
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

        bool isKindLinks = (kind == &kind->get()->ouder->links) ? true : false;

        // ZIG: the parent of the child is the root node
        if (kind->get()->ouder == this->deBinboom.get()) {
            this->deBinboom.roteer(!isKindLinks);

            kind = &this->deBinboom;
        }
            // ZIG-ZAG: the child has a grand parent
            //          the parent is a left child of the grand parent
            //          the child is a right child of the parent
            // ZIG-ZIG: the child has a grand parent
            //          the parent is a left child of the grand parent
            //          the child is a left child of the parent
        else if (kind->get()->ouder->ouder != 0) {
            Binboom<Sleutel, Data> *ouder;
            bool isParentLinks;
            if (kind->get()->ouder == kind->get()->ouder->ouder->links.get()) {
                isParentLinks = true;
                ouder = &kind->get()->ouder->ouder->links;
            }
            else {
                isParentLinks = false;
                ouder = &kind->get()->ouder->ouder->rechts;
            }

            // If child is a right child: ZIG ZAG
            // Else, the child is a left child: ZIG ZIG
            if ((isParentLinks && !isKindLinks) || (!isParentLinks && isKindLinks)) {
                // rotate
                ouder->roteer(!isKindLinks);
                kind = ouder;
            }
            else {
                if (ouder->get()->ouder->ouder == 0) {
                    this->deBinboom.roteer(!isParentLinks);
                }
                else {
                    if (ouder->get()->ouder == ouder->get()->ouder->ouder->links.get()) {
                        ouder->get()->ouder->ouder->links.roteer(false);
                    }
                    else {
                        ouder->get()->ouder->ouder->rechts.roteer(true);
                    }
                }
            }
        }
    }


};

template<class Sleutel, class Data>
void SplayTree<Sleutel, Data>::voegtoe(const Sleutel &sl, const Data &data) {
    Zoekboom<Sleutel, Data>::voegtoe(sl, data);
}


#endif //BASIC_SPLAY_TREE_SPLAYTREE_H
