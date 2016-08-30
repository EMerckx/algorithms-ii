// Thanks to Robin W.

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using std::cout;
using std::map;
using std::stack;
using std::string;
using std::vector;

// initializes the women
// adds the names of the women and their priority list of men
void initWomen(map<string, vector<string> >& women){
    women["annelien"]={"steven","toby","marouane","axel","dries","thibaut","kevin","vincent","eden"};
    women["ellen"]=   {"thibaut","dries","toby","eden","axel","kevin","marouane","steven","vincent"};
    women["julie"]=   {"kevin","eden","marouane","toby","vincent","axel","thibaut","dries","steven"};
    women["tatiana"]= {"axel","eden","dries","vincent","marouane","thibaut","toby","kevin","steven"};
    women["virginie"]={"eden","marouane","toby","axel","thibaut","steven","vincent","dries","kevin"};
    women["laura"]=   {"dries","eden","kevin","vincent","axel","thibaut","steven","toby","marouane"};
    women["cilou"]=   {"thibaut","marouane","dries","vincent","steven","eden","axel","kevin","toby"};
    women["laurence"]={"steven","kevin","eden","vincent","toby","dries","marouane","thibaut","axel"};
    women["zeynep"]=  {"marouane","axel","toby","kevin","thibaut","eden","vincent","steven","dries"};
}

// initializes the men
// adds the names of the men and their priority list of women
void initMen(map<string, vector<string> >& men){
    men["dries"] =   {"tatiana","virginie","laurence","ellen","laura","annelien","cilou","julie","zeynep"};
    men["kevin"] =   {"annelien","ellen","julie","cilou","virginie","zeynep","tatiana","laurence","laura"};
    men["steven"] =  {"tatiana","cilou","laurence","annelien","laura","ellen","julie","zeynep","virginie"};
    men["thibaut"] = {"laura","julie","zeynep","annelien","cilou","laurence","tatiana","ellen","virginie"};
    men["vincent"] = {"julie","annelien","laura","laurence","zeynep","virginie","ellen","cilou","tatiana"};
    men["eden"] =    {"ellen","laurence","cilou","zeynep","laura","annelien","julie","virginie","tatiana"};
    men["toby"] =    {"julie","virginie","tatiana","laurence","ellen","zeynep","laura","annelien","cilou"};
    men["axel"] =    {"cilou","ellen","tatiana","virginie","julie","laurence","zeynep","laura","annelien"};
    men["marouane"]= {"zeynep","tatiana","laura","ellen","virginie","julie","cilou","laurence","annelien"};
}

// gets the priority as an int, from the priority list
int getPriority(vector<string>& priorityList, string & name){
    int i = 0;
    while(i<priorityList.size() && priorityList[i]!=name){
        i++;
    }
    return i;
}

//-------------------------------------------------------------------

int main(){

    // get all the men
    map<string, vector<string> > men;
    initMen(men);

    // get all the women
    map<string, vector<string> > women;
    initWomen(women);

    // initialize the singles
    stack<string> singles;
    for(auto it = men.begin(); it != men.end(); it++){
        singles.push(it->first);
    }

    // ALGORITHM: Gale-Shapley
    // here we are going to match each man to a woman
    // but for sake of looking up, we use the woman as key
    //map<string, string> couplesManWoman;
    map<string, string> couplesWomanMan;
    while(!singles.empty()){
        // get the current man
        string currentMan = singles.top();
        singles.pop();

        // loop every woman in the priority list
        // until a woman is found
        int i = 0;
        bool foundWoman = false;
        while(i<men[currentMan].size() && !foundWoman){

            // get the woman from the priority list
            string woman = men[currentMan][i];

            // if the woman hasn't found a man yet, 
            // create a couple
            if(couplesWomanMan.find(woman) == couplesWomanMan.end()){
                //couplesManWoman[currentMan] = woman;
                couplesWomanMan[woman] = currentMan;
                foundWoman = true;
            }
            else if (getPriority(women[woman], currentMan) < 
                getPriority(women[woman], couplesWomanMan[woman])){
                // push the rejected man back to the singles stack
                singles.push(couplesWomanMan[woman]);
                // replace the old man with the current man
                couplesWomanMan[woman] = currentMan;
                foundWoman = true;
            }

            i++;
        }
    }

    // show output
    for(auto it = couplesWomanMan.begin(); it != couplesWomanMan.end(); it++){
        cout << it->second << " married to " << it->first << "\n";
    }

    return 0;
}