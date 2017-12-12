#include <iostream>
#include <vector>

using namespace std;

const int WHITE = 0, GREY = 1, BLACK = 2;

class Graph{
public:
    vector<vector<int> > gr;
    int timer;
    vector<int> color, discovery, tin;
    vector<int> circle;
    bool exist_circle;

    Graph(int n){
        timer = 0;
        for(int i = 0; i <= n; i++){
            gr.push_back(vector<int>());
        }
        color.resize(n + 1);
        tin.resize(n + 1);
        discovery.push_back(0);
        exist_circle = false;
    }
};

int dfs(Graph &myGraph, int v){
    myGraph.color[v] = GREY;
    for(auto u: myGraph.gr[v]){
        if(myGraph.color[u] == GREY){
            myGraph.circle.push_back(v);
            return ((v == u) ? -2: u);
        }
        if(myGraph.color[u] == WHITE){
            int v_start = dfs(myGraph, u);
            if(v_start > 0){
                myGraph.circle.push_back(v);
                if(v_start == v)
                    return -2;
                return v_start;
            }
            if(v_start == -2){
                return -2;
            }
        }
    }
    myGraph.color[v] = BLACK;
    return -1;
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
    }
    for(int i = 1; i <= n; i++){
        if(!myGraph.circle.size())
            dfs(myGraph, i);
    }
    if(myGraph.circle.size()){
        cout << "YES" << endl;
        for(auto it = myGraph.circle.rbegin(); it != myGraph.circle.rend(); it++){
            cout << *it << ' ';
        }
    } else {
        cout << "NO";
    }
    return 0;
}
