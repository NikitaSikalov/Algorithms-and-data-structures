//
// Created by Никита Сикалов on 25.11.2017.
//
#include <iostream>
#include <vector>

const int INF = 30000;

using namespace std;

class WeightedGraph{
private:
    struct Edge{
        int from, to, weight;

        Edge(int u, int v, int weight): from(u), to(v), weight(weight) {};
    };
    vector<Edge> edges;
    vector<int> distance;
    int size;
public:
    WeightedGraph(int n){
        size = n;
        distance.resize(n, INF);
    }

    void add_edge(int u, int v, int weight){
        edges.push_back(Edge(u, v, weight));
    }


    vector<int> Ford_Belman(int source){
        distance[source] = 0;
        for (int i = 1; i < size; ++i) {
            for (auto e: edges) {
                if (distance[e.from] < INF) {
                    distance[e.to] = min(distance[e.to], distance[e.from] + e.weight);
                }
            }
        }
        return distance;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    WeightedGraph graph(n);
    for (int i = 0; i < m; ++i) {
        int v, u, cost;
        cin >> v >> u >> cost;
        graph.add_edge(v - 1, u - 1, cost);
    }
    vector<int> ans = graph.Ford_Belman(0);
    for (auto u: ans) {
        cout << u << ' ';
    }
    return 0;
}