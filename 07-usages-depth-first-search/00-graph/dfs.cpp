#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include "graph.h"

using std::cout;
using std::vector;

template<RichtType RT>
void depthfirstsearch(Graaf<RT>& g){
    vector<bool> seen(g.aantalKnopen(), false);
    for(int i=0; i<g.aantalKnopen(); i++){
        depthfirstsearch(g, seen, i);

        cout << "\n";
    }
}


template<RichtType RT>
void depthfirstsearch(Graaf<RT>& g, vector<bool>& seen, int vertex){
    if(! seen[vertex]){
        seen[vertex] = true;

        cout << vertex << " ";

        for (auto it=g[vertex].begin(); it!=g[vertex].end(); it++){
            depthfirstsearch(g, seen, it->first);
        }
    }
}

int main() {

    // create graph
    int amount = 7;
    Graaf<GERICHT> g(amount);

    // add edges
    g.voegVerbindingToe(0,1);
    g.voegVerbindingToe(0,3);
    g.voegVerbindingToe(1,0);
    g.voegVerbindingToe(1,2);
    g.voegVerbindingToe(2,1);
    g.voegVerbindingToe(2,3);
    g.voegVerbindingToe(3,0);
    g.voegVerbindingToe(3,2);
    g.voegVerbindingToe(4,2);
    g.voegVerbindingToe(4,5);
    g.voegVerbindingToe(4,6);
    g.voegVerbindingToe(5,4);
    g.voegVerbindingToe(5,6);
    g.voegVerbindingToe(6,4);
    g.voegVerbindingToe(6,5);

    cout << g << "\n";

    // use depth first search

    cout << "DFS: \n";
    depthfirstsearch(g);
    
    return 0;
}
