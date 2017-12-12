#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int WHITE = 0, GREY = 1, BLACK = 2;

class Graph{
public:
    vector<vector<int> > gr;
    vector<int> colors;
    int start_circle;


    Graph(int n){
        for(int i = 0; i <= n; i++){
            gr.push_back(vector<int>());
        }
        colors.resize(n + 1);
        start_circle = 0;
    }
};

int dfs(Graph &myGraph, int v){
    myGraph.colors[v] = GREY;
    for(auto u: myGraph.gr[v]){
        if(myGraph.colors[u] == GREY){
            myGraph.start_circle = u;
            return ((v == u) ? -2 : u);
        }
        if(myGraph.colors[u] == WHITE){
            int t = dfs(myGraph, u);
            if(t > 0){
                if(v == t){
                    return -2;
                }
                return t;
            }
            if(t == -2)
                return t;
        }
    }
    myGraph.colors[v] = BLACK;
    return -1;
}

int main()
{
    int n;
    cin >> n;
    Graph myGraph(n);
    set<int> circles;
    for(int i = 1; i <= n; i++){
        int v;
        cin >> v    ;
        myGraph.gr[v].push_back(i);
    }
    for(int i = 1; i <= n; i++){
        if(myGraph.colors[i] == WHITE){
            dfs(myGraph, i);
            if(myGraph.start_circle != 0){
                circles.insert(myGraph.start_circle);
            }
        }
    }
    cout << circles.size();
    return 0;
}
