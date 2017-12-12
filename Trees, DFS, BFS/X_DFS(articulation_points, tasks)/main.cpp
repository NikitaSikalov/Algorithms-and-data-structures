#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Graph{
public:
    vector<vector<int> > gr;
    int timer, buildings;
    vector<int> fup;
    vector<int> tin;
    set<int> artic_points;

    Graph(int n, int m){
        timer = 0;
        buildings = n;
        for(int i = 0; i <= (n + m); i++){
            gr.push_back(vector<int>());
        }
        fup.resize(n + m + 1);
        tin.resize(n + m + 1);
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
            if(myGraph.fup[u] >= myGraph.tin[v] && p != -1 && v > myGraph.buildings){
                myGraph.artic_points.insert(v);
            }
            child_count++;
        }
    }
    if(p == -1 && child_count > 1 && v > myGraph.buildings){
        myGraph.artic_points.insert(v);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    Graph myGraph(n, m);
    for(int i = 1; i <= m; i++){
        int x, y, z;
        cin >> x >> y >> z;
        myGraph.gr[x].push_back(i + n);
        myGraph.gr[y].push_back(i + n);
        myGraph.gr[z].push_back(i + n);
        myGraph.gr[i + n].push_back(x);
        myGraph.gr[i + n].push_back(y);
        myGraph.gr[i + n].push_back(z);
    }
    for(int i = 1; i <= (n + m); i++){
        if(!myGraph.tin[i])
            find_artic_points(myGraph, i);
    }
    cout << myGraph.artic_points.size() << endl;
    for(auto it = myGraph.artic_points.begin(); it != myGraph.artic_points.end(); it++){
        cout << *it - n << ' ';
    }
    return 0;
}
