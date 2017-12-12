//
// Created by Никита Сикалов on 02.12.2017.
//
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

class DSU{
private:
    vector<int> tree;
    vector<int> rank;
public:
    DSU(int N){
        tree.resize(N);
        for (int i = 0; i < N; ++i) {
            tree[i] = i;
        }
        rank.resize(N);
    }

    int find_set(int a){
        if (a == tree[a]) {
            return a;
        }
        return a = find_set(tree[a]);
    }

    void union_set(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if (a == b){
            return;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        tree[b] = a;
        if (rank[a] == rank[b]){
            rank[a]++;
        }
    }
};

class WeightedGraph{
private:
    struct Edge{
    public:
        int from, to, weight, type, num;

    public:
        Edge(int from, int to, int weight, int type, int num = 0): from(from), to(to), weight(weight), type(type), num(num) {};
        // type = 1 - w_i, u_i, v_i
        // type = 2 - b_i, x_i, y_i
    };

    struct my_comp{
        bool operator()(const Edge &e1, const Edge &e2){
            return (e1.weight > e2.weight || (e1.weight == e2.weight && e1.type > e2.type));
        }
    };


    vector<vector<pair<int, int>>> neighbour;
    vector<Edge> edges;
    vector<int> refills;
    priority_queue<Edge, vector<Edge>, my_comp> queries;
    int size, quantity_queries;
public:

    WeightedGraph(int N){
        neighbour.resize(N);
        size = N;
        quantity_queries = 0;
    }

    void add_refill(int v){
        refills.push_back(v);
    }

    void add_edge(int from, int to, int weight){
        neighbour[from].push_back(pair<int, int>(to, weight));
        neighbour[to].push_back(pair<int, int>(from, weight));
        edges.push_back(Edge(from, to, weight, 1));
    }

    void add_query(int from, int to, int weight, int type, int k = 0){
        queries.push(Edge(from, to, weight, type, k));
        quantity_queries += type - 1;
    }

    void Decstra_condensation(){
       vector<int> distance(size, -1);
       priority_queue<pair<int, int>> q;
       vector<int> colors(size, -1);
       vector<bool> used(size);
       for (auto u: refills) {
           distance[u] = 0;
           colors[u] = u;
           q.push(pair<int, int>(0, u));
       }
       for (int i = 0; i < size; ++i) {
           if (q.empty()) { break; }
           int minv = q.top().second;
           q.pop();
           while (used[minv] && !q.empty()) {
               minv = q.top().second;
               q.pop();
           }
           if (used[minv]) { break; }
           used[minv] = true;
           for (auto u: neighbour[minv]) {
               if (!used[u.first] && (distance[u.first] > distance[minv] + u.second || distance[u.first] == -1)) {
                   colors[u.first] = colors[minv];
                   distance[u.first] = distance[minv] + u.second;
                   q.push(pair<int, int>(-distance[u.first], u.first));
               }
           }
       }
       for (auto e: edges) {
           if (colors[e.from] != colors[e.to] && colors[e.from] != -1 && colors[e.to] != -1) {
               int ref_1 = colors[e.from];
               int ref_2 = colors[e.to];
               this->add_query(ref_1, ref_2, e.weight + distance[e.from] + distance[e.to], 1);
           }
       }

   }

    vector<bool> answer_queries(){
        DSU dsu(size);
        vector<bool> ans(quantity_queries);
        while (!queries.empty()){
            Edge query = queries.top();
            queries.pop();
            if (query.type == 1) {
                dsu.union_set(query.from, query.to);
            }
            if (query.type == 2) {
             ans[query.num] = (dsu.find_set(query.from) == dsu.find_set(query.to));
            }
        }
        return ans;
    }
};

int main(){
    int n, s, m;
    cin >> n >> s >> m;
    WeightedGraph graph(n);
    for (int i = 0; i < s; ++i) {
        int v;
        cin >> v;
        graph.add_refill(v - 1);
    }
    for (int j = 0; j < m; ++j) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.add_edge(from - 1, to - 1, weight);
    }
    int q;
    cin >> q;
    for (int k = 0; k < q; ++k) {
        int b, x, y;
        cin >> x >> y >> b;
        graph.add_query(x - 1, y - 1, b, 2, k);
    }
    graph.Decstra_condensation();
    vector<bool> res = graph.answer_queries();
    for (auto a: res){
        if (a){
            cout << "TAK" << '\n';
        } else {
            cout << "NIE" << '\n';
        }
    }
    return 0;
}
