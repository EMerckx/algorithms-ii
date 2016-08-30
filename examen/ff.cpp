// based on http://www.geeksforgeeks.org/ford-fulkerson-algorithm
//              -for-maximum-flow-problem/

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

template<RichtType RT,class Takdata>
bool bfs(GraafMetTakdata<RT, Takdata>& g, 
    int s, int t, vector<int>& parent){
    // reset the parent vector
    parent = vector<int>(g.aantalKnopen(), 0);
    // create the visited vertices vector
    vector<bool> visited(g.aantalKnopen(), false);
    // init queue
    queue<int> q;

    // insert the source
    q.push(s);
    visited[s] = true;

    while(!q.empty()){
        // get the next vertex
        int vertex = q.front();
        q.pop();

        for(auto it = g[vertex].begin(); it != g[vertex].end(); it++){

            if(!visited[it->first] && !visited[t] &&
                g.geefTakdata(vertex, it->first) &&
                *g.geefTakdata(vertex, it->first)){

                cout << vertex << " to " << it->first << "\n";
                q.push(it->first);
                parent[it->first] = vertex;
                visited[it->first] = true; 
            }
        }
    }

    // if we did reach the sink, return true
    return visited[t];
}

template<RichtType RT,class Takdata>
Takdata fordFulkerson(GraafMetTakdata<RT, Takdata>& g, int s, int t){

    //Takdata maxFlow = 0;

    // init residual network
    GraafMetTakdata<GERICHT,Takdata> rg(g.aantalKnopen());
    for(int i=0; i<g.aantalKnopen(); i++){
        for(auto it=g[i].begin(); it != g[i].end(); it++){
            rg.voegVerbindingToe(i, it->first, 
                *g.geefTakdata(i, it->first));
        }
    }

    // init parent vector
    vector<int> parent;
    // init max flow parameter
    Takdata maxFlow = 0;

    // while an augmenting path exists, increase flow
    while(bfs(rg, s, t, parent)){

        // starting from the sink, going to the source
        // find via the parent, the edge with the lowest capacity
        Takdata pathFlow = INT_MAX;
        int v = t;
        while(v != s){
            // replace the current path flow, if the capacity
            // of the current edge is smaller
            pathFlow = min(pathFlow, *rg.geefTakdata(parent[v],v));

            // replace v with its parent
            v = parent[v];
        }

        // add the current flow of the path, to the max flow
        maxFlow += pathFlow;

        // update the residual network
        // this by decreasing the capacity of each edge
        // (that the augmenting path contained)
        v = t;
        while(v != s){
            // get the capacity of the forward and backward edges
            Takdata capacityForw = *rg.geefTakdata(parent[v],v);
            Takdata capacityBackw = 0;
            if(rg.geefTakdata(v,parent[v])){
                capacityBackw = *rg.geefTakdata(v,parent[v]);
            }
            
            // now change the capacities
            rg.wijzigTakdata(parent[v],v, capacityForw - pathFlow);
            rg.wijzigTakdata(v,parent[v], capacityBackw + pathFlow);

            // replace v with its parent
            v = parent[v];
        }
    }

    return maxFlow;

}

template<RichtType RT,class Takdata>
void GraafMetTakdata<RT,Takdata>::wijzigTakdata(int van, int naar, const Takdata& td){
    if(this->geefTakdata(van,naar)){
        int taknummer=this->verbindingsnummer(van,naar);
        if (taknummer!=-1){
            takdatavector[taknummer]=td;
        }   
    }
    else{
        this->voegVerbindingToe(van, naar, td);
    }
}

int main(){
    
    GraafMetTakdata<GERICHT,int> g(5);
    g.voegVerbindingToe(0,1,21);
    g.voegVerbindingToe(1,2,12);
    g.voegVerbindingToe(2,3,4);
    g.voegVerbindingToe(1,3,7);
    cout << g << "\n";

    vector<int> parent;
    bfs(g, 0, 2, parent);

    cout << "\n\n";

    int flow = fordFulkerson(g, 0,3);

    cout << "max flow: " << flow << "\n";
    
    return 0;
}