//
// Created by Никита Сикалов on 23.11.2017.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 2009000999;

class WeightedGraph {
private:
    vector<vector<pair<int, int>>> neighbour;

    priority_queue<pair<int, int>> Queue;
    int size;
    vector<int> distance;
    vector<bool> used;
public:
    WeightedGraph(int N) {
        size = N;
        used.resize(N);
        distance.resize(N, INF);
        neighbour.resize(N, vector<pair<int, int>>());

    }

    void add_edge(int from, int to, int weight) {
        neighbour[from].push_back(pair<int, int>(to, weight));
        neighbour[to].push_back(pair<int, int>(from, weight));
    }

    vector<int> Decstra(int source) {
        distance[source] = 0;
        Queue.push(pair<int, int>(0, source));
        for (int i = 0; i < size; ++i) {
            if (Queue.empty()) { break; }
            int minv = Queue.top().second;
            Queue.pop();
            while (used[minv] && !Queue.empty()) {
                minv = Queue.top().second;
                Queue.pop();
            }
            if (used[minv]) { break; }
            used[minv] = true;
            for (auto u: neighbour[minv]) {
                if (!used[u.first] && distance[u.first] > distance[minv] + u.second) {
                    distance[u.first] = distance[minv] + u.second;
                    Queue.push(pair<int, int>(-distance[u.first], u.first));
                }
            }
        }
        return distance;
    }
};

int main() {
    int NUM;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> NUM;
    for (int i = 0; i < NUM; ++i) {
        int n, m;
        cin >> n >> m;
        WeightedGraph graph(n);
        for (int j = 0; j < m; ++j) {
            int from, to, weight;
            cin >> from >> to >> weight;
            graph.add_edge(from, to, weight);
        }
        int source;
        cin >> source;
        vector<int> ans = graph.Decstra(source);
        for (auto u : ans) {
            cout << u << ' ';
        }
        cout << '\n';
    }
    return 0;
}