//
// Created by Никита Сикалов on 25.11.2017.
//
#include <iostream>
#include <vector>

using namespace std;

class DSU {
private:
    vector<int> tree, size, weight, rank;
public:
    DSU(int n){
        tree.resize(n);
        rank.resize(n);
        weight.resize(n);
        for (int i = 0; i < n; ++i) {
            tree[i] = i;
        }
    }

    int find_set(int v){
        if (v == tree[v]) {
            return v;
        }
        return tree[v] = find_set(tree[v]);
    }

    void union_set(int a, int b, int w){
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                swap(a, b);
            }
            if (rank[a] == rank[b]) {
                ++rank[a];
            }
            tree[b] = a;
            weight[a] += weight[b];
        }
        weight[a] += w;
    }

    int weight_set(int a){
        a = find_set(a);
        return weight[a];
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    DSU graph(n);
    for (int i = 0; i < m; ++i) {
        int com;
        cin >> com;
        if (com == 1) {
            int u, v, weight;
            cin >> u >> v >> weight;
            graph.union_set(u - 1, v - 1, weight);
        }
        if (com == 2) {
            int u;
            cin >> u;
            cout << graph.weight_set(u - 1) << '\n';
        }
    }
    return 0;
}