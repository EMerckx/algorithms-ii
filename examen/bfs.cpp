// based on http://www.geeksforgeeks.org/ford-fulkerson-algorithm
//              -for-maximum-flow-problem/

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "graaf.h"

using std::cout;
using std::queue;
using std::string;
using std::vector;

template<RichtType RT,class Takdata>
bool bfs(GraafMetTakdata<RT, Takdata> g, 
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

            if(!visited[it->first] && !visited[t]){

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

int main(){
    
    GraafMetTakdata<GERICHT,int> g(5);
    g.voegVerbindingToe(0,1,9);
    g.voegVerbindingToe(1,2,3);
    g.voegVerbindingToe(2,3,4);
    g.voegVerbindingToe(1,3,7);
    cout << g << "\n";

    vector<int> parent;
    bfs(g, 0, 2, parent);
    
    return 0;
}