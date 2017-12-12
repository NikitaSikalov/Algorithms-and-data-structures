//
// Created by Никита Сикалов on 22.11.2017.
//

#include <iostream>
#include <vector>

const int INF = 1e9;

using namespace std;

class TransportNetwork{
private:
    vector<vector<int>> network;
    vector<vector<int>> rest_network;
    int size, color;
    int source, sink;
    vector<int> colors;

    int dfs(int v, int p = -1, int min = INF){
        if (v == sink) {
            rest_network[p][v] -= min;
            rest_network[v][p] += min;
            return min;
        } else {
            colors[v] = color;
            for (int u = 1; u <= size; ++u){
                if (rest_network[v][u] > 0 && colors[u] != color) {
                    int res;
                    if (res = dfs(u, v, std::min(min, rest_network[v][u]))){
                        if (p != -1) {
                            rest_network[p][v] -= res;
                            rest_network[v][p] += res;
                        }
                        return res;
                    }
                }
            }
            return 0;
        }
    }
public:
    TransportNetwork(int N, int source, int sink){
        size = N;
        network.resize(N + 1, vector<int>(N + 1));
        this->source = source;
        this->sink = sink;
        colors.resize(N + 1);
        color = 1;
    }

    void add_edge(int u, int v, int stream){
        network[u][v] += stream;
    }

    int Ford_Fulkerson(){
        int maxStream = 0, res;
        rest_network = network;
        while (res = dfs(source)) {
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
    cout << network.Ford_Fulkerson();
    return 0;
}