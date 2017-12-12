//
// Created by Никита Сикалов on 03.12.2017.
//
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <map>

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
                if (rest_network[v][u] > 0 && colors[u] != color) {
                    parent[u] = v;
                    colors[u] = color;
                    if (u == sink) { break; }
                    Queue.push(u);
                }
            }
            colors[v] = color;
        }
        int u = sink;
        if (colors[sink] != color) { return 0; }
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
        network.resize(N, vector<int>(N));
        parent.resize(N, -1);
        this->source = source;
        this->sink = sink;
        colors.resize(N);
        color = 1;
        mates.resize(N, vector<int>());
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

inline int valentnost(char element){
    if (element == 'H') {
        return 1;
    }
    if (element == 'O') {
        return 2;
    }
    if (element == 'N') {
        return 3;
    }
    return 4;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<char>> table(n, vector<char>(m));
    TransportNetwork network(n * m + 2, n * m, n * m + 1);
    int64_t out_stream = 0, in_stream = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char element;
            cin >> element;
            table[i][j] = element;
            if (element == '.') { continue; }
            if ((i + j) % 2 == 0) {
                network.add_edge(n * m, m * i + j, valentnost(element));
                out_stream += valentnost(element);
            } else {
                network.add_edge(m * i + j, n * m + 1, valentnost(element));
                in_stream += valentnost(element);
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < m; ++i) {
            if (table[k][i] == '.' || (k + i) % 2 == 1) { continue; }
            int cur = k * m + i;            //номер текущей вершны в графе
            int up = (k - 1) * m + i;       //номер соседа сверху
            int down = (k + 1) * m + i;     //номер соседа снизу
            int right = k * m + i + 1;      //номер соведа справа
            int left = k * m + i - 1;       //номер соседа слева
            if ((k - 1) >= 0 && table[k - 1][i] != '.'){
                network.add_edge(cur, up, 1);
            }
            if ((k + 1) < n && table[k + 1][i] != '.'){
                network.add_edge(cur, down, 1);
            }
            if ((i + 1) < m && table[k][i + 1] != '.'){
                network.add_edge(cur, right, 1);
            }
            if ((i - 1) >= 0 && table[k][i - 1] != '.'){
                network.add_edge(cur, left, 1);
            }
        }
    }
    int64_t stream = network.Admons_Karp();
    if (stream == in_stream && stream == out_stream && stream != 0){
        cout << "Valid";
    } else {
        cout << "Invalid";
    }
    return 0;
}