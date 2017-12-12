#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph{
public:
    vector<vector<int> > gr;
    int timer;
    vector<int> tin, colors;
    vector<bool> used;
    int size, color;

    Graph(int n){
        timer = 0;
        for(int i = 0; i <= n; i++){
            gr.push_back(vector<int>());
        }
        colors.resize(n + 1);
        tin.resize(n + 1);
        size = n;
        color = 1;
    }
};

const int WHITE = 0, GREY = 1, BLACK = 2;

vector<int> BFS(Graph &myGraph, int n, int x, int y){
    queue<int> Q;
    vector<vector<int> > prev;
    for(int i = 0; i <= n; i++){
        prev.push_back(vector<int>());
    }
    Q.push(x);
    while(Q.size() != 0){
        int v = Q.front();
        Q.pop();
        for(auto u: myGraph.gr[v]){
            if(myGraph.colors[u] == WHITE){
                myGraph.colors[u] = GREY;
                myGraph.tin[u] = myGraph.tin[v] + 1;
                prev[u].push_back(v);
                Q.push(u);
            }
            if(u == y)
                break;
        }
        myGraph.colors[v] = BLACK;
    }
    vector<int> res;
    int cur = y;
    while(cur != x){
        res.push_back(cur);
        int i = 0;
        for(; i < prev[cur].size(); i++){
             int v = prev[cur][i];
             if(myGraph.tin[v] + 1 == myGraph.tin[cur]){
                cur = v;
                break;
             }
        }
        if(i == prev[cur].size())
            break;
    }
    res.push_back(cur);
    return res;
}

int main()
{
    int n, m, a, b;
    cin >> n >> m;
    cin >> a >> b;
    Graph myGraph(n);
        for(int i = 1; i <= m; i++){
        int v, u;
        cin >> v >> u;
        myGraph.gr[v].push_back(u);
        myGraph.gr[u].push_back(v);
    }
    vector<int> ans = BFS(myGraph, n, a, b);
    if(a == b){
        cout << 0 << endl;
        cout << a;
    } else {
        if(ans[ans.size() - 1] != a){
            cout << -1;
        } else {
            cout << ans.size() - 1 << endl;
            for(int i = ans.size() - 1; i >= 0; i--){
                cout << ans[i] << ' ';
            }
        }
    }
    return 0;
}
