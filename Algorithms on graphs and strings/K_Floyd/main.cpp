//
// Created by Никита Сикалов on 26.11.2017.
//
#include <iostream>
#include <vector>
#include <map>
#include <utility>

const int INF = 1e9 + 1e3 + 1;

using namespace std;

class WeightedGraph{
private:
    int size, counter;
    vector<vector<int>> graph, distance, next;
    map<pair<int, int>, int> flight;
public:
    WeightedGraph(int n){
        size = n;
        graph.resize(n, vector<int>(n, INF));
        for (int i = 0; i < size; ++i) {
            graph[i][i] = 0;
        }
        distance.resize(n, vector<int>(n));
        next.resize(n, vector<int>(n));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                next[i][j] = j;
            }
        }
        counter = 1;
    }

    void add_edge(int from, int to, int cost){
        if (graph[from][to] == INF || graph[from][to] < cost) {
            graph[from][to] = cost;
            flight[pair<int, int>(from, to)] = counter;
        }
        counter++;
    }

    vector<int> Floyd(vector<pair<int, int>> &route){
        distance = graph;
        for (int k = 0; k < size; ++k) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if ((distance[i][j] == INF || distance[i][j] < distance[i][k] + distance[k][j]) && distance[i][k] != INF && distance[k][j] != INF) {
                        distance[i][j] = min(INF - 1, distance[i][k] + distance[k][j]);
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int t = 0; t < size; ++t) {
                    if (distance[i][t] != INF && distance[t][t] > 0 && distance[t][j] != INF && i != j) {
                        distance[i][j] = -INF;
                    }
                }
            }
        }
        for (int i = 0; i < size; ++i) {
            distance[i][i] = (distance[i][i] > 0) ? -INF: 0;
        }
        vector<int> path, sequence;
        for (auto p: route) {
            if (distance[p.first][p.second] == -INF) {
                sequence.clear();
                return sequence;
            }
            get_path_2(p.first, p.second, path);
            path.pop_back();
        }
        path.push_back(route.rbegin()->second);
        for (int i = 0; i < path.size() - 1; ++i) {
            sequence.push_back(flight[pair<int, int>(path[i], path[i + 1])]);
        }
        return sequence;
    }

    void get_path_2(int i, int j, vector<int>& path){
        int c = i;
        while(c != j){
            path.push_back(c);
            c = next[c][j];
        }
        path.push_back(j);
    }
};

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    WeightedGraph graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, cost;
        cin >> from >> to >> cost;
        graph.add_edge(from - 1, to - 1, cost);
    }
    vector<pair<int, int>> route;
    int v, u;
    bool flag = true;
    cin >> v;
    for (int j = 1; j < k; ++j) {
        cin >> u;
        if (v != u) {
            flag = false;
        }
        route.push_back(pair<int, int>(v - 1, u - 1));
        v = u;
    }
    vector<int> ans = graph.Floyd(route);
    if (ans.empty() && !flag) {
        cout << "infinitely kind";
    } else {
        cout << ans.size() << endl;
        for (auto u: ans) {
            cout << u << ' ';
        }
    }
    return 0;
}