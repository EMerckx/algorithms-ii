#ifndef DRIVE_DRIVE_H
#define DRIVE_DRIVE_H

#include <map>

using std::map;

typedef unsigned int blockIndex;

template<class T>
class Drive : private map<blockIndex, T> {
public:
    //write: add a T to the drive
    //returns the index
    blockIndex write(const T &b) {
        ++indexCounter;
        //this-> is needed (for some compilers)
        // because the parametrisation can't be derived from the arguments
        this->operator[](indexCounter) = b;
        return indexCounter;
    }

    //deleteBlockIndex: delete the T at the blockIndex on the drive
    void deleteBlockIndex(blockIndex bi) {
        this->erase(bi);
    }

    //rewrite: rewrite the T at the blockIndex to the drive
    void rewrite(const T &b, const blockIndex bi) {
        this->operator[](bi) = b;
    }

    //read: read the T at the blockIndex from the drive
    void read(T &b, const blockIndex bi) {
        b = this->operator[](bi);
    }

    Drive() : map<blockIndex, T>(), indexCounter(666) { };

private:
    blockIndex indexCounter;

};

#endif //DRIVE_DRIVE_H
