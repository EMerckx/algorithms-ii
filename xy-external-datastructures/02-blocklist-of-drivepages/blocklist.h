#ifndef BLOCKLIST_OF_DRIVEPAGES_BLOCKLIST_H
#define BLOCKLIST_OF_DRIVEPAGES_BLOCKLIST_H

#include <list>
#include <tuple>
#include <map>
#include "drive.h"

using std::list;
using std::map;
using std::pair;

template<class Key, class Data>
class DrivePage;

template<class Key, class Data>
class BlockList {
public:
    BlockList(Drive<DrivePage<Key, Data> > &drive, BlockIndex blockIndex) : drive(&drive), blockIndex(blockIndex) { }

private:
    BlockIndex blockIndex;
    Drive<DrivePage<Key, Data>> *drive;
};

const int CAPACITY = 4;

template<class Key, class Data>
class DrivePage : public map<Key, Data> {
public:
    BlockIndex next_blockIndex;

    DrivePage() : next_blockIndex(-1) { }
};


#endif //BLOCKLIST_OF_DRIVEPAGES_BLOCKLIST_H
