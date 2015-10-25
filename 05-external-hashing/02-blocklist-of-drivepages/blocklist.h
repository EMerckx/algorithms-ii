#ifndef BLOCKLIST_OF_DRIVEPAGES_BLOCKLIST_H
#define BLOCKLIST_OF_DRIVEPAGES_BLOCKLIST_H

#include <list>
#include <iostream>
#include <utility>
#include "drive.h"

using std::list;
using std::ostream;
using std::pair;

const int CAPACITY = 4;

template<class Key, class Data>
class DrivePage;

template<class Key, class Data>
class BlockList {
private:
    BlockIndex blockIndex;
    Drive<DrivePage<Key, Data>> *drive;

public:
    BlockList(Drive<DrivePage<Key, Data> > &drive) : drive(&drive) {
        DrivePage<Key, Data> drivePage;
        blockIndex = drive.write(drivePage);
    }

    BlockList(Drive<DrivePage<Key, Data> > &drive, BlockIndex blockIndex) : drive(&drive), blockIndex(blockIndex) { }

    void Add(Key key, Data data);

    // operator << to show the BlockList on screen
    friend ostream &operator<<(ostream &os, BlockList &blockList) {
        // if the Drive and the BlockIndex exist
        if (blockList.drive != 0 && blockList.blockIndex != 0) {
            // create a local DrivePage
            DrivePage<Key, Data> drivePage;
            // read the current DrivePage from the drive
            BlockIndex bi = blockList.blockIndex;

            while (bi != 0) {
                // read the the DrivePage
                blockList.drive->read(drivePage, bi);

                // write the DrivePage to the stream
                os << drivePage;

                // get the BlockIndex of the next DrivePage
                bi = drivePage.next_blockIndex;
            }
        }
        return os;
    }

    void write(ostream) const;
};

template<class Key, class Data>
class DrivePage : public list<pair<Key, Data> > {
public:
    BlockIndex next_blockIndex;

    DrivePage() : next_blockIndex(0) { }

    bool tryAdd(Key key, Data data);

    // operator << to show the DrivePage on screen
    friend ostream &operator<<(ostream &os, DrivePage &drivePage) {
        for (auto it = drivePage.begin(); it != drivePage.end(); it++) {
            os << "(" << it->first << "," << it->second << ") ";
        }
        os << "| ";
        return os;
    }
};

//---------------------------------------------------------------------------------------------------------------------

template<class Key, class Data>
void BlockList<Key, Data>::Add(Key key, Data data) {
    // if the Drive and the BlockIndex exist
    if (drive != 0 && blockIndex != 0) {
        // create a local DrivePage
        DrivePage<Key, Data> drivePage;
        // read the current DrivePage from the drive
        BlockIndex bi = this->blockIndex;
        drive->read(drivePage, bi);

        // while adding the key and data fails, read the next DrivePage
        // or create a new one if the next DrivePage doesn't exist
        while (!drivePage.tryAdd(key, data)) {
            // save the BlockIndex of the current DrivePage
            BlockIndex currentBlockIndex = bi;

            // get the BlockIndex of the next DrivePage
            bi = drivePage.next_blockIndex;
            if (bi == 0) {
                // create a new DrivePage
                DrivePage<Key, Data> newDrivePage;
                bi = drive->write(newDrivePage);

                // set the BlockIndex of the next DrivePage
                // and update it on the drive
                drivePage.next_blockIndex = bi;
                drive->rewrite(drivePage, currentBlockIndex);
            }
            drive->read(drivePage, bi);
        }

        // rewrite the DrivePage to finally add the Key and Data
        drive->rewrite(drivePage, bi);
    }
}


template<class Key, class Data>
bool DrivePage<Key, Data>::tryAdd(Key key, Data data) {
    if (this->size() < CAPACITY) {
        pair<Key, Data> p(key, data);
        this->push_back(p);
        return true;
    }
    else {
        return false;
    }
}


#endif //BLOCKLIST_OF_DRIVEPAGES_BLOCKLIST_H
