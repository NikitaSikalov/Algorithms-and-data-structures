#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Graph{
public:
    vector<vector<int> > gr;
    int timer;
    vector<int> fup;
    vector<int> tin;
    set<int> artic_points;

    Graph(int n){
        timer = 0;
        for(int i = 0; i <= n; i++){
            gr.push_back(vector<int>());
        }
        fup.resize(n + 1);
        tin.resize(n + 1);
    }
};

void find_artic_points(Graph &myGraph, int v, int p = -1){
    myGraph.fup[v] = myGraph.tin[v] = ++myGraph.timer;
    int child_count = 0;
    for(auto u : myGraph.gr[v]){
        if(u == p){
            continue;
        }
        if(myGraph.tin[u]){
            myGraph.fup[v] = min(myGraph.fup[v], myGraph.tin[u]);
        } else {
            find_artic_points(myGraph, u, v);
            myGraph.fup[v] = min(myGraph.fup[v], myGraph.fup[u]);
            if(myGraph.fup[u] >= myGraph.tin[v] && p != -1){
                myGraph.artic_points.insert(v);
            }
            child_count++;
        }
    }
    if(p == -1 && child_count > 1){
        myGraph.artic_points.insert(v);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    Graph myGraph(n);
    for(int i = 1; i <= m; i++){
        int v, u;
        cin >> v >> u;
        myGraph.gr[v].push_back(u);
        myGraph.gr[u].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        if(!myGraph.tin[i])
            find_artic_points(myGraph, i);
    }
    cout << myGraph.artic_points.size() << endl;
    for(auto it = myGraph.artic_points.begin(); it != myGraph.artic_points.end(); it++){
        cout << *it << endl;
    }
    return 0;
}
