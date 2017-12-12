#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph{
private:
    vector<vector<int> > gr, rew_gr;
    int timer;
    mutable vector<int> tout, colors;
    mutable vector<bool> used;
    int size;
    mutable int color;

    void dfs(const int v) const{
        this->used[v] = true;
        for(auto u : this->gr[v]){
            if(!this->used[u]){
                dfs(u);
            }
        }
        this->tout.push_back(v);
    }

    void rew_dfs(const int v, const int color) const{
        this->colors[v] = color;
        for(auto u : this->rew_gr[v]){
            if(!this->colors[u]){
                rew_dfs(u, color);
            }
        }
    }

public:

    Graph(const int n){
        timer = 0;
        for(int i = 0; i <= n; i++){
            gr.push_back(vector<int>());
            rew_gr.push_back(vector<int>());
        }
        colors.resize(n + 1);
        used.resize(n + 1);
        size = n;
        color = 1;
    }

    void add_edge(const int u, const int v){
        this->gr[v].push_back(u);
        this->rew_gr[u].push_back(v);
    }

    vector<int> Kosarau() const{
        for(int i = 1; i <= this->size; i++){
            if(!this->used[i]){
                dfs(i);
            }
        }
        reverse(this->tout.begin(), this->tout.end());
        for(auto v: this->tout){
            if(!this->colors[v]){
                rew_dfs(v, (this->color)++);
            }
        }
        return this->colors;
    }
};


int main()
{
    int n, m;
    cin >> n >> m;
    Graph myGraph(n);
    for(int i = 1; i <= m; i++){
        int v, u;
        cin >> v >> u;
        myGraph.add_edge(u, v);
    }
    vector<int> components = myGraph.Kosarau();
    int quantity = *(max_element(components.begin(), components.end()));
    cout << quantity << endl;
    for(int i = 1; i <= n; i++){
        cout << components[i] << ' ';
    }
    return 0;
}
