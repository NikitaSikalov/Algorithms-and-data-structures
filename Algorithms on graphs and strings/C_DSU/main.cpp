//
// Created by Никита Сикалов on 25.11.2017.
//
#include <iostream>
#include <vector>

using namespace std;

class DSU {
private:
    vector<int> tree, size;
public:
    DSU(int n){
        tree.resize(n);
        size.resize(n);
        for (int i = 0; i < n; ++i) {
            tree[i] = i;
            size[i] = 1;
        }
    }

    void make_set(int v){
        tree[v] = v;
        size[v] = 1;
    }

    int find_set(int v){
        if (v == tree[v]) {
            return v;
        }
        return find_set(tree[v]);
    }

    void union_set(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) {
                swap(a, b);
            }
            tree[b] = a;
            size[a] += size[b];
        }
    }
};

struct Query{
    int type;
    int v, u;

    Query(int t, int v, int u): type(t), v(v), u(u) {};
};

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    DSU graph(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
    }
    vector<Query> queries;
    for (int j = 0; j < k; ++j) {
        string comand;
        cin >> comand;
        int u, v;
        cin >> u >> v;
        if (comand == "ask") {
            queries.push_back(Query(1, v - 1, u - 1));
        }
        if (comand == "cut") {
            queries.push_back(Query(2, v - 1, u - 1));
        }
    }
    vector<string> ans;
    for (auto it = queries.rbegin(); it != queries.rend(); it++){
        if (it->type == 1) {
            if (graph.find_set(it->u) == graph.find_set(it->v)) {
                ans.push_back("YES");
            } else {
                ans.push_back("NO");
            }
        } else {
            graph.union_set(it->u, it->v);
        }
    }
   for (auto it = ans.rbegin(); it != ans.rend(); it++) {
       cout << *it << endl;
   }
    return 0;
}