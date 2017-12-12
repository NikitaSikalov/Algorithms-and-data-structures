//
// Created by Никита Сикалов on 02.12.2017.
//
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

const int INF = 1e9;

class WeightedGraph{
private:
    vector<vector<pair<int, int>>> neighbour;
    vector<int> fires;
    vector<uint64_t> time_of_fire;
    int size;
public:
    WeightedGraph(int N){
        neighbour.resize(N);
        size = N;
        time_of_fire.resize(N);
    }

    void add_fire(int v){
        fires.push_back(v);
    }

    void add_edge(int from, int to, int weight){
        neighbour[from].push_back(pair<int, int>(to, weight));
        neighbour[to].push_back(pair<int, int>(from, weight));
    }

    void Decstra_fire(){
        vector<uint64_t> distance(size, -1);
        priority_queue<pair<uint64_t, int>> queue;
        vector<bool> used(size);
        for (auto u: fires) {
            distance[u] = 0;
            queue.push(pair<uint64_t, int>(0, u));
        }
        for (int i = 0; i < size; ++i) {
            if (queue.empty()) { break; }
            int v = queue.top().second;
            queue.pop();
            while (used[v] && !queue.empty()) {
                v = queue.top().second;
                queue.pop();
            }
            if (used[v]) { break; }
            used[v] = true;
            for (auto u: neighbour[v]) {
                if (!used[u.first] && (distance[u.first] > distance[v] + u.second || distance[u.first] == -1)) {
                    distance[u.first] = distance[v] + u.second;
                    queue.push(pair<uint64_t, int>(-distance[u.first], u.first));
                }
            }
        }
        time_of_fire = distance;
    }

    uint64_t Decstra_out(int source, int finish){
        this->Decstra_fire();
        vector<uint64_t> distance(size, -1);
        priority_queue<pair<uint64_t, int>> queue;
        vector<bool> used(size);
        distance[source] = 0;
        queue.push(pair<uint64_t, int>(0, source));
        for (int i = 0; i < size; ++i) {
            if (queue.empty()) { break; }
            int minv = queue.top().second;
            queue.pop();
            while (used[minv] && !queue.empty()) {
                minv = queue.top().second;
                queue.pop();
            }
            if (used[minv]) { break; }
            used[minv] = true;
            if (distance[minv] >= time_of_fire[minv] && time_of_fire[minv] != -1) {
                distance[minv] = -1;
                continue;
            }
            for (auto u: neighbour[minv]) {
                if (!used[u.first] && (distance[u.first] > distance[minv] + u.second || distance[u.first] == -1)) {
                    distance[u.first] = distance[minv] + u.second;
                    queue.push(make_pair(-distance[u.first], u.first));
                }
            }
        }
        return distance[finish];
    }
};

int main(){
    int N, M, K;
    cin >> N >> M >> K;
    WeightedGraph graph(N);
    for (int i = 0; i < K; ++i) {
        int v;
        cin >> v;
        graph.add_fire(v - 1);
    }
    for (int j = 0; j < M; ++j) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.add_edge(from - 1, to - 1, weight);
    }
    int S, F;
    cin >> S >> F;
    int64_t ans = graph.Decstra_out(S - 1, F - 1);
    cout << ans;
    return 0;
}
