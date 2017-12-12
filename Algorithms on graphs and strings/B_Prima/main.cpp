//
// Created by Никита Сикалов on 25.11.2017.
//
#include <iostream>
#include <vector>

using namespace std;

class WeightedGraph {
private:
    vector<vector<int>> graph;
    vector<bool> used;
    vector<int> distance, parent, children;
    int size;
public:
    WeightedGraph(int N) {
        size = N;
        distance.resize(N);
        used.resize(N);
        graph.resize(N, vector<int>(N));
    }

    void add_edge(int v, int u, int weight) {
        graph[v][u] = weight;
    }

    int Prima(int source = 0) {
        used[0] = true;
        used[source] = true;
        distance = graph[source];
        int ans = 0;
        for (int i = 0; i < size; ++i) {
            int minv = -1;
            for (int j = 0; j < size; ++j) {
                if (!used[j] && (minv == -1 || distance[minv] > distance[j])){
                    minv = j;
                }
            }
            if (minv == -1) { break;}
            used[minv] = true;
            ans += distance[minv];
            for (int k = 0; k < size; ++k) {
                if (distance[k] > graph[minv][k]) {
                    distance[k] = graph[minv][k];
                }
            }
        }
        return ans;
    }
};

int main() {
    int n;
    cin >> n;
    WeightedGraph graph(n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;
            cin >> weight;
            graph.add_edge(i, j, weight);
        }
    }
   // cout << graph.Prima(0);
    for (int k = 0; k < n; ++k) {
        int coast;
        cin >> coast;
        graph.add_edge(n, k, coast);
        graph.add_edge(k, n, coast);
    }
    //cout << graph.Prima(0) << ' ';
    cout << graph.Prima();
    return 0;
}