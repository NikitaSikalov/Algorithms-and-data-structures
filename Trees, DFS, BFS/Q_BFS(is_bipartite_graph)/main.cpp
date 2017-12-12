#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph{
public:
    vector<vector<int> > gr;
    vector<int> colors;
    vector<bool> used;
    bool is_bipartite;

    Graph(int n){
        for(int i = 0; i <= n; i++){
            gr.push_back(vector<int>());
        }
        colors.resize(n + 1, -1);
        used.resize(n + 1);
        is_bipartite = true;
    }
};

void BFS(Graph &graph, int v){
    queue<int> Q;
    graph.colors[v] = 0;
    Q.push(v);
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        for(auto u: graph.gr[v]){
            if(!graph.used[u]){
                graph.colors[u] = (graph.colors[v] + 1) % 2;
                Q.push(u);
            } else {
                if(graph.colors[u] == graph.colors[v]){
                    graph.is_bipartite = false;
                    return;
                }
            }
        }
        graph.used[v] = true;
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
        if(!myGraph.used[i]){
            BFS(myGraph, i);
        }
    }
    if(myGraph.is_bipartite){
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
