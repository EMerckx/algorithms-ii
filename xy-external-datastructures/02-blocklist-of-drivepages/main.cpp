#include <iostream>
#include "blocklist.h"

using namespace std;

int main() {
    cout << "Compilation succeeded" << endl;

    Drive<DrivePage<int, int>> drive;
    DrivePage<int, int> drivePage;
    BlockIndex blockIndex = drive.write(drivePage);

    BlockList<int, int> blockList(drive, blockIndex);
    return 0;
}