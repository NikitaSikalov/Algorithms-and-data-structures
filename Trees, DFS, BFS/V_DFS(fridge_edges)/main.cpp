#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

vector<int> tin, fup;
int timer = 0;
set<int> answer;
map<pair<int, int>, int> edges;
map<pair<int, int>, int> multy_edges;

void find_bridges(vector<vector<int> > &graph, int v, int p = -1){
    tin[v] = ++timer;
    fup[v] = tin[v];
    for(auto u: graph[v]){
        if(u == p){
            continue;
        }
        if(tin[u]){
            fup[v] = min(fup[v], tin[u]);
        } else {
            find_bridges(graph, u, v);
            fup[v] = min(fup[v], fup[u]);
        }
    }
    if(p != -1 && fup[v] > tin[p]){
        if(edges[make_pair(p, v)] != -1)
            answer.insert(edges[make_pair(p, v)]);
    }
}

bool operator==(pair<int, int> p1, pair<int, int> p2){
    if(p1.first == p2.first && p1.second == p2.second || p1.first == p2.second && p1.second == p2.first)
        return true;
    else
        return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    tin.resize(n + 1);
    fup.resize(n + 1);
    vector<vector<int> > graph;
    for(int i = 0; i <= n; i++){
        graph.push_back(vector<int>());
    }
    for(int i = 1; i <= m; i++){
        int v, u;
        cin >> v >> u;
        if(edges[make_pair(v, u)] == 0)
            edges[make_pair(v, u)] = i;
        else {
           edges[make_pair(v, u)] = -1;
        }
        if(edges[make_pair(u, v)] == 0){
            edges[make_pair(u, v)] = i;
        } else {
            edges[make_pair(u, v)] = -1;
        }
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        if(!tin[i]){
            find_bridges(graph, i);
        }
    }
    cout << answer.size() << endl;
    for(auto it = answer.begin(); it != answer.end(); it++){
        cout << *it << endl;
    }
    return 0;
}
