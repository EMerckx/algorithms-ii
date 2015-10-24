#ifndef BLOCKLIST_OF_DRIVEPAGES_DRIVE_H
#define BLOCKLIST_OF_DRIVEPAGES_DRIVE_H

#include <map>

using std::map;

typedef unsigned int BlockIndex;

template<class T>
class Drive : private map<BlockIndex, T> {
public:
    //write: add a T to the drive
    //returns the index
    BlockIndex write(const T &b) {
        ++indexCounter;
        //this-> is needed (for some compilers)
        // because the parametrisation can't be derived from the arguments
        this->operator[](indexCounter) = b;
        return indexCounter;
    }

    //deleteBlockIndex: delete the T at the BlockIndex on the drive
    void deleteBlockIndex(BlockIndex bi) {
        this->erase(bi);
    }

    //rewrite: rewrite the T at the BlockIndex to the drive
    void rewrite(const T &b, const BlockIndex bi) {
        this->operator[](bi) = b;
    }

    //read: read the T at the BlockIndex from the drive
    void read(T &b, const BlockIndex bi) {
        b = this->operator[](bi);
    }

    Drive() : map<BlockIndex, T>(), indexCounter(666) { };

private:
    BlockIndex indexCounter;

};

#endif //BLOCKLIST_OF_DRIVEPAGES_DRIVE_H
