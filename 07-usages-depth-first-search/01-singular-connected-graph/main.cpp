#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <queue>
#include <utility>
#include "graph.h"

using std::cout;
using std::pair;
using std::priority_queue;
using std::vector;

//-------------------------------------------------------------------

template<RichtType RT>
void depthfirstsearch1(Graaf<RT>& g, priority_queue<pair<int, int> >& q){
    vector<bool> seen(g.aantalKnopen(), false);

    int level = 0;
    for(int i=0; i<g.aantalKnopen(); i++){
        depthfirstsearch1(g, seen, i, q, level);

        // debug
        //cout << "\n";
    }
}

template<RichtType RT>
void depthfirstsearch1(Graaf<RT>& g, vector<bool>& seen, int vertex, 
    priority_queue<pair<int, int> >& q, int& level){
    if(! seen[vertex]){
        seen[vertex] = true;

        // debug
        //cout << vertex << " ";

        for (auto it=g[vertex].begin(); it!=g[vertex].end(); it++){
            depthfirstsearch1(g, seen, it->first, q, level);
        }

        q.push(pair<int, int>(level, vertex));
        level++;
    }
}

//-------------------------------------------------------------------

template<RichtType RT>
void depthfirstsearch2(Graaf<RT>& g, priority_queue<pair<int, int> >& q){
    vector<bool> seen(g.aantalKnopen(), false);

    while(!q.empty()){
        pair<int, int> p = q.top();
        q.pop();

        depthfirstsearch2(g, seen, p.second);

        cout << "\n";
    }
}

template<RichtType RT>
void depthfirstsearch2(Graaf<RT>& g, vector<bool>& seen, int vertex){
    if(! seen[vertex]){
        seen[vertex] = true;

        cout << vertex << " ";

        for (auto it=g[vertex].begin(); it!=g[vertex].end(); it++){
            depthfirstsearch2(g, seen, it->first);
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
    g.voegVerbindingToe(2,4);
    g.voegVerbindingToe(3,0);
    g.voegVerbindingToe(3,2);
    g.voegVerbindingToe(4,5);
    g.voegVerbindingToe(4,6);
    g.voegVerbindingToe(5,4);
    g.voegVerbindingToe(5,6);
    g.voegVerbindingToe(6,4);
    g.voegVerbindingToe(6,5);

    std::cout << g << "\n";

    cout << "\n-------------------------\n";

    // STEP 1
    // create the reversed graph
    Graaf<GERICHT> reversed(g.aantalKnopen());

    // add each reversed edge
    // loop every vertex number
    for(int i=0; i<g.aantalKnopen(); i++){
        // loop every edge per vertex
        for(auto it=g[i].begin(); it!=g[i].end(); it++){
            // add the reversed edge to the reversed graph
            reversed.voegVerbindingToe(it->first, i);
        }
    }

    cout << reversed << "\n";

    // STEP 2
    // use depth first search with post order numeration
    // we store the vertices and their level in a priority queue
    priority_queue<pair<int, int> > q;
    depthfirstsearch1(reversed, q);

    // debug: review the priority queue
    /*cout << "PRIORITY QUEUE: \n";
    while(!q.empty()){
        pair<int, int> p = q.top();
        q.pop();

        cout << p.first << " " << p.second << "\n";
    }

    cout << "\n";*/

    // STEP 3
    // use depth first search on the original graph
    // to find the strongly connected components
    // and this by using the order of the priority queue
    cout << "STRONGLY CONNECTED COMPONENTS: \n";
    depthfirstsearch2(g, q);
    
    return 0;
}
