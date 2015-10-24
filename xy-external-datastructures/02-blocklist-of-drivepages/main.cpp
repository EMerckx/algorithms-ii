#include <iostream>
#include "blocklist.h"

using namespace std;

int main() {
    cout << "Compilation succeeded" << endl;

    Drive<DrivePage<int, int>> drive;
    DrivePage<int, int> drivePage;
    //error: use of deleted function 'DrivePage<int, int>& DrivePage<int, int>::operator=(const DrivePage<int, int>&)
    //when: this->operator[](indexCounter) = b;
    //need to solve this
    //BlockIndex blockIndex = drive.write(drivePage);

    /*BlockList<int, int> blockList(drive, blockIndex);*/
    return 0;
}