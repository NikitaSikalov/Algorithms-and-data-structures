//
// Created by Никита Сикалов on 26.11.2017.
//
#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e9;

using namespace std;

class WeightedGraph{
private:
    struct Edge{
        int from, to, weight;

        Edge(int u, int v, int weight): from(u), to(v), weight(weight) {};
    };

    vector<Edge> edges;
    int size;
    mutable vector<int> distance, parent;
public:
    WeightedGraph(int n){
        size = n;
        distance.resize(n, INF);
        parent.resize(n, -1);
    }

    void add_edge(int u, int v, int cost){
        edges.push_back(Edge(u, v, cost));
    }

    vector<int> get_negative_circle(){
        distance.assign(size, 0);
        int v = -1;
        for (int i = 0; i < size; ++i) {
            v = -1;
            for (auto e: edges) {
                if (distance[e.from] < INF) {
                    if (distance[e.to] > distance[e.from] + e.weight && e.weight != 100000) {
                        distance[e.to] = max(-INF, distance[e.from] + e.weight);
                        parent[e.to] = e.from;
                        v = e.to;
                    }
                }
            }
        }
        vector<int> circle;
        if (v != -1) {
            for (int i = 0; i < size; ++i) {
                v = parent[v];
            }
            int start = v;
            circle.push_back(start);
            v = parent[v];
            while(v != start) {
                circle.push_back(v);
                v = parent[v];
            }
            circle.push_back(start);
            reverse(circle.begin(), circle.end());
        }
        return circle;
    }
};

int main(){
    int n;
    cin >> n;
    WeightedGraph graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cost;
            cin >> cost;
            graph.add_edge(i, j, cost);
        }
    }
    vector<int> ans = graph.get_negative_circle();
    if (ans.empty()) {
        cout << "NO";
    } else {
        cout << "YES" << endl;
        cout << ans.size() << endl;
        for (auto v: ans) {
            cout << v + 1 << ' ';
        }
    }
    return 0;
}