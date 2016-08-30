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

int knuthMorrisPratt(string& text, string& pattern){
    // first get the prefix table
    vector<int> prefixtable;
    createPrefixTable(pattern, prefixtable);

    // iterate over the text with the prefix table
    // until the pattern is found 
    // or the end of the text is reached
    int i = 0;
    int j = 0;
    while(i < text.length() && j < pattern.length()){
        // if match, check next position
        // else check prefix table
        if(text[i] == pattern[j]){
            i++;
            j++;
        }
        else{
            if(j!=0){
                j = prefixtable[j - 1];
            }
            else {
                i++;
            }
        }
    }

    if(j == pattern.length()){
        return i - pattern.length();
    }
    else{
        return -1;
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
    cout << "\n\n";

    //---------------------------------------------------------------

    string text = "abcxabcdabcdabcy";

    cout << "text: " << text << "\n";

    int pos1 = knuthMorrisPratt(text, pattern);

    if(pos1 >= 0){
        cout << "      ";
        for(int i=0; i<pos1; i++){
            cout << " ";
        }
        cout << "^ \n";

        cout << "pos : " << pos1 << "\n";
    }
    else {
        cout << "pattern not in text! :( \n";
    }


}