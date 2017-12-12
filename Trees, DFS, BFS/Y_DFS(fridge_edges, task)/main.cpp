#include <iostream>
#include <vector>
#include <set>
#include<utility>

using namespace std;

vector<int> tin, fup;
int timer = 0;
vector<pair<int, int>> bridges;
vector<int> colors, components;
vector<set<int>> neighb_br;

const int WHITE = 0, GREY = 1, BLACK = 2;

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
        bridges.push_back(make_pair(v, p));
        neighb_br[p].insert(v);
        neighb_br[v].insert(p);
    }
}

void dfs(vector<vector<int> > &graph, int v, int key){
    colors[v] = GREY;
    components[v] = key;
    for(auto u: graph[v]){
        if(colors[u] == WHITE && neighb_br[v].find(u) == neighb_br[v].end()){
            dfs(graph, u, key);
        }
    }
    colors[v] = BLACK;
}

int main()
{
    int n, m;
    cin >> n >> m;
    tin.resize(n + 1);
    fup.resize(n + 1);
    colors.resize(n + 1);
    neighb_br.resize(n + 1, set<int>());
    components.resize(n + 1);
    vector<vector<int> > graph(n + 1, vector<int>());

    for(int i = 1; i <= m; i++){
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        if(!tin[i]){
            find_bridges(graph, i);
        }
    }
    int key = 1;
    for(int i = 1; i <= n; i++){
        if(colors[i] == WHITE){
            dfs(graph, i, key);
        }
        key++;
    }

    int count_leaves = 0;
    vector<vector<int>> sub_graph(n + 1, vector<int>());
    for(auto u: bridges){
        sub_graph[components[u.first]].push_back(components[u.second]);
        sub_graph[components[u.second]].push_back(components[u.first]);
    }
    for(int i = 1; i <= n; i++){
        if(sub_graph[i].size() == 1){
            count_leaves++;
        }
    }
    cout << (count_leaves + 1) / 2;
    return 0;
}
