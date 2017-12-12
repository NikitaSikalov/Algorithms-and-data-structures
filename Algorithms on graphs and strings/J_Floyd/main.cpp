//
// Created by Никита Сикалов on 26.11.2017.
//
#include <iostream>
#include <vector>

using namespace std;

class DirectedGraph{
private:
    int size;
    vector<vector<bool>> graph;
    vector<vector<bool>> distance;
public:
    DirectedGraph(int n){
        size = n;
        graph.resize(n, vector<bool>(n));
        distance.resize(n, vector<bool>(n));
    }

    void add_edge(int from, int to, bool exist){
        graph[from][to] = exist;
    }

    vector<vector<bool>> Floyd(){
        distance = graph;
        for (int k = 0; k < size; ++k) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if (distance[i][j] == false && distance[i][k] == true && distance[k][j] == true) {
                        distance[i][j] = true;
                    }
                }
            }
        }
        return distance;
    }
};

int main(){
    int N;
    cin >> N;
    DirectedGraph graph(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            bool edge;
            cin >> edge;
            graph.add_edge(i, j, edge);
        }
    }
    vector<vector<bool>> new_graph = graph.Floyd();
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            cout << new_graph[k][i] << ' ';
        }
        cout << endl;
    }
    return 0;
}