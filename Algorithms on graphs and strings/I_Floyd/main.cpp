//
// Created by Никита Сикалов on 26.11.2017.
//
#include <iostream>
#include <vector>

using namespace std;

class WeightedGraph{
private:
    int size;
    vector<vector<int>> graph;
    vector<vector<int>> distance;
public:
    WeightedGraph(int n){
        graph.resize(n, vector<int>(n));
        distance.resize(n, vector<int>(n));
        size = n;
    }

    void add_edge(int from, int to, int cost){
        graph[from][to] = cost;
    }

    int Floyd(int source, int to){
        distance = graph;
        for (int k = 0; k < size; ++k) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if ((distance[i][j] == -1 || distance[i][j] > distance[i][k] + distance[k][j]) && distance[i][k] != -1 && distance[k][j] != -1){
                        distance[i][j] = distance[i][k] + distance[k][j];
                    }
                }
            }
        }
        return distance[source][to];
    }
};

int main(){
    int N, s, t;
    cin >> N >> s >> t;
    WeightedGraph graph(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int cost;
            cin >> cost;
            graph.add_edge(i, j, cost);
        }
    }
    cout << graph.Floyd(s - 1, t - 1);
    return 0;
}