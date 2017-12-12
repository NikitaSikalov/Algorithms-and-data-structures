//
// Created by Никита Сикалов on 22.11.2017.
//

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

const int INF = 1e9;

using namespace std;

class TransportNetwork{
private:
    vector<vector<int>> network;
    vector<vector<int>> rest_network;
    vector<vector<int>> mates;
    int size, color;
    int source, sink;
    vector<int> colors;
    vector<int> parent;

    int bfs(int source){
        queue<int> Queue;
        Queue.push(source);
        int min = INF;
        while (!Queue.empty()) {
            int v = Queue.front();
            Queue.pop();
            for (auto u: mates[v]) {
                if (rest_network[v][u] != 0 && colors[u] != color) {
                    parent[u] = v;
                    if (u == sink) { break; }
                    colors[u] = color;
                    Queue.push(u);
                }
            }
            colors[v] = color;
        }
        int u = sink;
        while (u != source) {
            min = std::min(rest_network[parent[u]][u], min);
            u = parent[u];
        }
        u = sink;
        while (u != source) {
            rest_network[parent[u]][u] -= min;
            rest_network[u][parent[u]] += min;
            u = parent[u];
        }
        return min;
    }
    
public:
    TransportNetwork(int N, int source, int sink){
        size = N;
        network.resize(N + 1, vector<int>(N + 1));
        parent.resize(N + 1);
        this->source = source;
        this->sink = sink;
        colors.resize(N + 1);
        color = 1;
        mates.resize(N + 1, vector<int>());
    }

    void add_edge(int u, int v, int stream){
        network[u][v] = stream;
        mates[u].push_back(v);
        mates[v].push_back(u);
    }

    int64_t Admons_Karp(){
        int64_t maxStream = 0, res;
        rest_network = network;
        while (res = bfs(source)) {
            maxStream += res;
            color++;
        }
        return maxStream;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    TransportNetwork network(n, 1, n);
    for (int i = 1; i <= m; ++i) {
        int v, u, stream;
        cin >> v >> u >> stream;
        network.add_edge(v, u, stream);
    }
    cout << network.Admons_Karp();
    return 0;
}