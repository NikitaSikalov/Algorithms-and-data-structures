//
// Created by Никита Сикалов on 26.11.2017.
//
#include <iostream>
#include <vector>

const int INF = 1e9;

using namespace std;

class WeightedGraph{
private:
    struct Edge{
        int from, to, weight;

        Edge(int u, int v, int weight): from(u), to(v), weight(weight) {};
    };

    int size;
    vector<Edge> edges;
    vector<vector<int>> distance;
public:
    WeightedGraph(int n){
        distance.resize(n, vector<int>(n, INF));
        size = n;
    }

    void add_edge(int from, int to, int cost){
        edges.push_back(Edge(from, to, cost));
    }

    int Ford_Belman(int source, int to, int quantity){
        distance[source][0] = 0;
        quantity = min(quantity, size - 1);
        for (int i = 1; i <= quantity; ++i) {
            for (int j = 0; j < size; ++j) {
                distance[j][i] = distance[j][i - 1];
            }
            for (auto e: edges) {
                if (distance[e.from][i - 1] < INF) {
                    distance[e.to][i] = min(distance[e.to][i], distance[e.from][i - 1] + e.weight);
                }
            }
        }
        return distance[to][quantity];
    }
};

int main(){
    int N, M, K, S, F;
    cin >> N >> M >> K >> S >> F;
    WeightedGraph graph(N);
    for (int i = 0; i < M; ++i) {
        int from, to, cost;
        cin >> from >> to >> cost;
        graph.add_edge(from - 1, to - 1, cost);
    }
    int ans = graph.Ford_Belman(S - 1, F - 1, K);
    cout << (ans == INF ? -1 : ans);
    return 0;
}