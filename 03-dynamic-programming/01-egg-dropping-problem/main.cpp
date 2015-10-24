#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::max;
using std::vector;

void eggDrop(const int amountOfEggs, const int amountOfFloors);

void calculateMatrix(vector<vector<int> > &matrix, const int amountOfEggs, const int amountOfFloors);

void printMatrix(const vector<vector<int> > &matrix);


int main() {
    cout << "Compilation succeeded" << endl;

    int amountOfEggs = 10;
    int amountOfFloors = 20;

    eggDrop(amountOfEggs, amountOfFloors);

    return 0;
}

void eggDrop(const int amountOfEggs, const int amountOfFloors) {
    // init the matrix, rows = floors, cols = eggs
    // structure: matrix[floor][egg]
    vector<vector<int> > matrix(amountOfFloors + 1, vector<int>(amountOfEggs + 1, amountOfFloors + 100));

    calculateMatrix(matrix, amountOfEggs, amountOfFloors);

    printMatrix(matrix);
}

void calculateMatrix(vector<vector<int> > &matrix, const int amountOfEggs, const int amountOfFloors) {
    // if you have 0 eggs, you need 0 trials for i floors
    // if you have 1 egg, you need i trials for i floors
    for (int i = 0; i <= amountOfFloors; i++) {
        matrix[i][0] = 0;
        matrix[i][1] = i;
    }

    // if you have 0 floors, you need 0 trials for i eggs
    // if you have 1 floor, you only need 1 trial for i eggs
    for (int i = 0; i <= amountOfEggs; i++) {
        matrix[0][i] = 0;
        matrix[1][i] = 1;
    }

    // STILL SOME ERRORS !!!
    for (int i = 2; i <= amountOfFloors; i++) {
        for (int j = 2; j <= amountOfEggs; j++) {
            // for k eggs, less than or equal j eggs
            for (int k = 1; k <= j; k++) {
                // amount of drops = 1 drop + the maximum of drops of
                // either the amount of drops when the egg breaks -> one floor less and one egg less
                // either the amount of drops when the egg doesn't break -> one floor less and same amount of eggs
                int amountOfDrops = 1 + max(matrix[i - 1][k - 1], matrix[i - 1][k]);
                if (matrix[i][k] > amountOfDrops) {
                    matrix[i][k] = amountOfDrops;
                }
            }
        }
    }
}

void printMatrix(const vector<vector<int> > &matrix) {
    cout << "\t|\t";
    for (int j = 1; j <= matrix[1].size(); j++) {
        cout << j << "\t";
    }
    cout << endl;
    for (int i = 1; i <= matrix.size(); i++) {
        cout << "-----";
    }
    cout << endl;

    for (int i = 1; i <= matrix.size(); i++) {
        cout << i << "\t|\t";
        for (int j = 1; j <= matrix[1].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}