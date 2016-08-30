#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

void createPrefixTable(string pattern, vector<int>& v){
    // init vector
    v = vector<int>(pattern.length(), 0);

    // init i and j
    int i = 1;
    int j = 0;
    while(i<v.size()){
        if(pattern[i] == pattern[j]){
            v[i] = j + 1;
            j++;
            i++;
        }
        else{
            if(j > 0){
                j = v[j - 1];
            }
            else {
                v[i] = 0;
                i++;
                j = 0;
            }
        }
    }

}

int main(){
    // string = aabaabaaa
    // prefix = 010123452
    //string pattern = "aabaabaaa";
    string pattern = "abcdabd";

    vector<int> prefixtable;

    createPrefixTable(pattern, prefixtable);

    cout << "pattern: " << pattern << "\n";
    cout << "prefix : ";
    for(int i=0; i<prefixtable.size(); i++){
        cout << prefixtable[i];
    }
    cout << "\n";

}