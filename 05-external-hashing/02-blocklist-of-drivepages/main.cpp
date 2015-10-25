#include <iostream>
#include "blocklist.h"

using std::cout;
using std::endl;

int main() {
    cout << "Compilation succeeded" << endl;

    // create the components of the BlockList
    Drive<DrivePage<int, int>> drive;
    DrivePage<int, int> drivePage;
    BlockIndex blockIndex = drive.write(drivePage);

    // create the BlockList
    BlockList<int, int> blockList(drive, blockIndex);

    // add some values to the BlockList
    for (int i = 0; i < 15; i++) {
        blockList.Add(i, i);
    }

    cout << blockList << endl;

    return 0;
}