#ifndef SPLAY_TREE_ADD_ZOEKBOOM_H
#define SPLAY_TREE_ADD_ZOEKBOOM_H

/**********************************************************************


   beschrijving: Deze code bevat fouten !!!!!!!!!!!!!!!!
   en C++11-features

***************************************************************************/
#include <cstdlib>
#include <iostream>
#include <queue>

using std::ostream;
using std::cout;
using std::endl;

// compiler kent unique_ptr niet dus voegen we hem toe
#include <memory>

using std::unique_ptr;
using std::move;

// compile kent max niet, dus voegen we hem toe
#include <algorithm>

using std::max;


/**********************************************************************

   Klasse: Binboom met Binknoop: binaire boom

   beschrijving: Domme klasse om de gegevens van een boom te bevatten
                 Omdat ze enkel in een wrapper wordt gebruikt, heeft ze
                 alles publiek staan. Ze mag dan ook nooit buiten een
                 wrapper gebruikt worden!

***************************************************************************/

template<class Sleutel, class Data>
class Binknoop;

template<class Sleutel, class Data>
class Binboom : public unique_ptr<Binknoop<Sleutel, Data>> {
public:
    using unique_ptr<Binknoop<Sleutel, Data>>::unique_ptr;

    Binboom<Sleutel, Data>() { }

    ~Binboom<Sleutel, Data>() { }

    Binboom<Sleutel, Data>(Binboom<Sleutel, Data> &&b) : unique_ptr<Binknoop<Sleutel, Data>>(move(b)) {
        cout << "\tje maakt gebruik van een move constructor" << endl;
    }

    Binboom<Sleutel, Data> &operator=(Binboom<Sleutel, Data> &&b) {
        cout << "\tje maakt gebruik van een move operator" << endl;
        unique_ptr<Binknoop<Sleutel, Data>>::operator=(move(b));
        return *this;
    }

    int diepte() const {
        if (!*this)
            return 0;
        else
            // hier haakjes toegevoegd, van *this naar (*this)
            return max((*this)->links.diepte(), (*this)->rechts.diepte()) + 1;
    };

    void schrijf(ostream &) const;

    void schrijf(ostream &os, Binknoop<Sleutel, Data> *kn) const {
        if (kn != 0)
            os << "(" << kn->sl << "," << kn->data << ")";
        else
            os << "(,)";
    }

    void roteer(bool links);
};

template<class Sleutel, class Data>
class Binknoop {
public:
    Sleutel sl;
    Data data;
    Binknoop<Sleutel, Data> *ouder;
    Binboom<Sleutel, Data> links, rechts;

    Binknoop() : ouder(0) { }

    Binknoop(const Sleutel &_sl, const Data &_data) : ouder(0), sl(_sl), data(_data) { }
};

/**********************************************************************

   klasse: Zoekboom

   beschrijving: Dit is een wrapper voor een Binboom,
                 die ervoor zorgt dat de sleutels in de Binboom
                 op volgorde staan

***************************************************************************/

template<class Sleutel, class Data>
class Zoekboom {
public:
    virtual void voegtoe(const Sleutel &, const Data &);

    void voegtoe(Binboom<Sleutel, Data> &knoop, const Sleutel &sl, const Data &data);

//volgende functie doet niets als er geen knoop is met het gegeven Sleutel
    virtual void verwijder(const Sleutel &);

//geef pointer naar data horend bij een sleutel
    virtual Data *zoekdata(const Sleutel &);

    int diepte() const { return deBinboom.diepte(); };

    friend ostream &operator<<(ostream &os, Zoekboom<Sleutel, Data> &b) {
        b.deBinboom.schrijf(os);
        return os;
    };
protected:
//zoekplaats: geeft adres van boom waaraan knoop hangt, of zou moeten hangen
//en adres van de ouder.
    virtual void zoekplaats(const Sleutel &, Binboom<Sleutel, Data> *&, Binknoop<Sleutel, Data> *&);

//De binaire boom die de data bevat
    Binboom<Sleutel, Data> deBinboom;

//geeft de voorganger. Veronderstelt dat de linkerboom onder de knoop niet leeg is
    Binboom<Sleutel, Data> *ondervoorganger(Binknoop<Sleutel, Data> *);

};

template<class Sleutel, class Data>
void Binboom<Sleutel, Data>::roteer(bool links) {
    Binboom<Sleutel, Data> op;
    if (links) {
        op = move((*this)->rechts);
        (*this)->rechts = move(op->links);
        if ((*this)->rechts != nullptr)
            (*this)->rechts->ouder = (*this).get();

        (*this)->ouder = (*this)->links->ouder;
        //(*this)->links->ouder = (*this).get();

        op->links = move(*this);
        op->links->ouder = op.get();
    }
    else {
        op = move((*this)->links);
        (*this)->links = move(op->rechts);
        if ((*this)->links != nullptr)
            (*this)->links->ouder = (*this).get();

        (*this)->ouder = (*this)->rechts->ouder;
        //(*this)->links->ouder = (*this).get();

        op->rechts = move(*this);
        op->rechts->ouder = op.get();
    }
    *this = move(op);
    (*this)->ouder = 0;
}


template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::zoekplaats(const Sleutel &sl, Binboom<Sleutel, Data> *&plaats,
                                         Binknoop<Sleutel, Data> *&ouder) {
    plaats = &deBinboom;
    ouder = 0;
    while (*plaats != 0 && (*plaats)->sl != sl) {
        ouder = plaats->get();
        if (sl < (*plaats)->sl)
            plaats = &((*plaats)->links);
        else
            plaats = &((*plaats)->rechts);
    }
}

template<class Sleutel, class Data>
Data *Zoekboom<Sleutel, Data>::zoekdata(const Sleutel &sl) {
    Binboom<Sleutel, Data> *plaats;
    Binknoop<Sleutel, Data> *ouder;
    zoekplaats(sl, plaats, ouder);
    if (plaats == 0)
        return 0;
    else return &((*plaats)->data);
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::voegtoe(const Sleutel &sl, const Data &data) {
    if (deBinboom == 0) {
        unique_ptr<Binknoop<Sleutel, Data>> nieuw = unique_ptr<Binknoop<Sleutel, Data>>(
                new Binknoop<Sleutel, Data>(sl, data));
        deBinboom = move(nieuw);
        deBinboom->ouder = 0;
    }
    else
        voegtoe(deBinboom, sl, data);
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::voegtoe(Binboom<Sleutel, Data> &knoop, const Sleutel &sl, const Data &data) {
    Binboom<Sleutel, Data> *kind;
    if (sl < knoop->sl)
        kind = &(knoop->links);
    else
        kind = &(knoop->rechts);
    if (*kind == 0) {
        (*kind) = move((unique_ptr<Binknoop<Sleutel, Data>>) new Binknoop<Sleutel, Data>(sl, data));
        (*kind)->ouder = knoop.get();
    }
    else
        voegtoe(*kind, sl, data);
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::verwijder(const Sleutel &sl) {
    //throw "verwijder nog niet aangepast aan C++11: extra oefening";

    Binboom<Sleutel, Data> *plaats;
    Binknoop<Sleutel, Data> *ouder;
    zoekplaats(sl, plaats, ouder);
    Binknoop<Sleutel, Data> *weg = plaats->get();
    if (plaats->get() != 0) {
        cout << "\tplaats->get() != 0" << endl;

        if (weg->links.get() == 0) {
            cout << "\tweg->links.get() == 0" << endl;
            (*plaats) = move(weg->rechts);
            if (plaats->get() != 0) {
                cout << "\tplaats->get() != 0" << endl;
                plaats->get()->ouder = ouder;
            }
        }
        else if (weg->rechts.get() == 0) {
            cout << "\tweg->rechts.get() == 0" << endl;
            (*plaats) = move(weg->links);
            if (plaats->get() != 0) {
                cout << "\tplaats->get() != 0" << endl;
                plaats->get()->ouder = ouder;
            }
        }
        else {
            //vervangen door voorganger
            Binboom<Sleutel, Data> *voorlink = ondervoorganger(weg);
            Binboom<Sleutel, Data> *hulp = move(voorlink);

            cout << "voorlink: ";
            voorlink->schrijf(cout);
            cout << endl;
            cout << "hulp: ";
            hulp->schrijf(cout);
            cout << endl;

            if (voorlink != &(weg->links)) {
                if (voorlink->get()->links != 0) {
                    Binboom<Sleutel, Data> hulp = move(voorlink->get()->links);
                    Binknoop<Sleutel, Data> *ouder = voorlink->get()->ouder;

                    // de ouder moet je mee kopieren
                    voorlink->get()->ouder = plaats->get()->ouder;
                    // move het linkse en rechtse kind van de te verwijderen knoop naar de voorganger
                    voorlink->get()->links = move(plaats->get()->links);
                    voorlink->get()->rechts = move(plaats->get()->rechts);
                    // de ouder moet je mee kopieren
                    voorlink->get()->links->ouder = voorlink->get();
                    voorlink->get()->rechts->ouder = voorlink->get();

                    // dan vervangen we de te verwijderen knoop door de voorganger
                    (*plaats) = move(*voorlink);

                    hulp->ouder = ouder;
                    ouder->rechts = move(hulp);
                }
                else {
                    // de ouder moet je mee kopieren
                    voorlink->get()->ouder = plaats->get()->ouder;
                    // move het linkse en rechtse kind van de te verwijderen knoop naar de voorganger
                    voorlink->get()->links = move(plaats->get()->links);
                    voorlink->get()->rechts = move(plaats->get()->rechts);
                    // de ouder moet je mee kopieren
                    voorlink->get()->links->ouder = voorlink->get();
                    voorlink->get()->rechts->ouder = voorlink->get();

                    // dan vervangen we de te verwijderen knoop door de voorganger
                    (*plaats) = move(*voorlink);
                }
            }
            else {
                // de ouder moet je mee kopieren
                voorlink->get()->ouder = plaats->get()->ouder;
                // move het rechtse kind van de te verwijderen knoop naar de voorganger
                voorlink->get()->rechts = move(plaats->get()->rechts);
                // de ouder moet je mee kopieren
                voorlink->get()->rechts->ouder = voorlink->get();

                // dan vervangen we de te verwijderen knoop door de voorganger
                (*plaats) = move(*voorlink);
            }
        }
    }
}

template<class Sleutel, class Data>
Binboom<Sleutel, Data> *Zoekboom<Sleutel, Data>::ondervoorganger(Binknoop<Sleutel, Data> *kn) {
    Binboom<Sleutel, Data> *onder = &(kn->links);
    while (onder->get()->rechts.get() != 0)
        onder = &(onder->get()->rechts);
    return onder;
}


template<class Sleutel, class Data>
void Binboom<Sleutel, Data>::schrijf(ostream &os) const {
    if (*this != 0) {
        Binknoop<Sleutel, Data> *loper = this->get();
        std::queue<Binknoop<Sleutel, Data> *, std::deque<Binknoop<Sleutel, Data> *> > q;
        q.push(loper);
        while (!q.empty()) {
            Binknoop<Sleutel, Data> *nu = q.front();
            schrijf(os, nu);
            os << " links: ";
            schrijf(os, nu->links.get());
            os << " rechts: ";
            schrijf(os, nu->rechts.get());
            os << " ouder: ";
            schrijf(os, nu->ouder);
            os << std::endl;
            if (nu->links != 0)
                q.push(nu->links.get());
            if (nu->rechts != 0)
                q.push(nu->rechts.get());
            q.pop();
        }
    }
    else {
        os << " XX ";
    }
}

#endif //SPLAY_TREE_ADD_ZOEKBOOM_H_H
