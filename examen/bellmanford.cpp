#include <algorithm>
#include <iostream>
#include <limits.h>
#include <queue>
#include <string>
#include <vector>
#include "graaf.h"

using std::cout;
using std::min;
using std::queue;
using std::string;
using std::vector;

template<RichtType RT, class Takdata>
void bellmanFord(GraafMetTakdata<RT, Takdata>& g, int s){

    // init the distance vector
    vector<Takdata> distances(g.aantalKnopen(),0);

    // STEP 1
    // Initialize distances from source to 
    // all other vertices as INFINITE
    for(int i=0; i<g.aantalKnopen(); i++){
        distances[i] = INT_MAX;
    }
    distances[s] = 0;

    // STEP 2 
    // Relax all edges |V| - 1 times. A simple shortest path
    // from src to any other vertex can have at-most |V| - 1 edges
    queue<int> q;
    q.push(s);
    int iter = 0;

    while(!q.empty() && iter < 2 * g.aantalKnopen()){

        int vertex = q.front();
        q.pop();

        for(auto it = g[vertex].begin(); it!=g[vertex].end(); it++){

            // calculate the distance to the vertex along this path
            Takdata dist = 
                distances[vertex] + *g.geefTakdata(vertex, it->first);

            if(dist < distances[it->first]){

                cout << "edge " << vertex << " to " << it->first 
                    << " with distance " << dist << "\n";

                q.push(it->first);
                distances[it->first] = dist;
            }
        }

        iter++;
    }

    cout << "\namount of iterations: " << iter << "\n";

    for(int i=0; i<distances.size(); i++){
        cout << distances[i] << " ";
    }
    cout << "\n";
}



int main(){
    
    GraafMetTakdata<GERICHT,int> g(5);
    g.voegVerbindingToe(0,1,21);
    g.voegVerbindingToe(1,2,12);
    g.voegVerbindingToe(2,3,4);
    g.voegVerbindingToe(1,3,7);
    g.voegVerbindingToe(3,4,1);
    g.voegVerbindingToe(0,4,-1);
    g.voegVerbindingToe(4,3,2);
    g.voegVerbindingToe(3,2,5);
    //g.voegVerbindingToe(2,1,2);
    cout << g << "\n\n\n";

    bellmanFord(g, 0);
}