//
// Created by Никита Сикалов on 01.12.2017.
//
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

const int NUM = 1001000;
const int INF = 1e9;
const int MAX = 1000000;

class WeightedGrapgh{
private:
    vector<vector<pair<int, int>>> neibghour;
    int lift_in, lift_out, up, down;
public:
    WeightedGrapgh(int U, int D, int I, int J){
        neibghour.resize(NUM, vector<pair<int, int>>());
        up = U;
        down = D;
        lift_in = I;
        lift_out = J;
    }

    void add_edge(int lift, int floor){
        neibghour[lift].push_back(pair<int, int>(floor, lift_out));
        neibghour[floor].push_back(pair<int, int>(lift, lift_in));
    }

    int Decstra(int source, int finish){
        vector<int> distance(NUM, INF);
        distance[source] = 0;
        priority_queue<pair<int, int>> queue;
        queue.push(pair<int, int>(0, source));
        vector<bool> used(NUM);
        while (!used[finish]) {
            int v = queue.top().second;
            queue.pop();
            while (used[v] && !queue.empty()) {
                v = queue.top().second;
                queue.pop();
            }
            used[v] = true;
            if(v != 0 && v < MAX && !used[v - 1] && distance[v - 1] > distance[v] + down) {
                distance[v - 1] = distance[v] + down;
                queue.push(pair<int, int>(-distance[v - 1], v - 1));
            }
            if(!used[v + 1] && v < MAX && distance[v + 1] > distance[v] + up) {
                distance[v + 1] = distance[v] + up;
                queue.push(pair<int, int>(-distance[v + 1], v + 1));
            }
            for (auto u: neibghour[v]) {
                if (!used[u.first] && distance[u.first] > distance[v] + u.second) {
                    distance[u.first] = distance[v] + u.second;
                    queue.push(pair<int, int>(-distance[u.first], u.first));
                }
            }
        }
        return distance[finish];
    };
};

int main(){
    int N, U, D, I, J, L;
    cin >> N >> U >> D >> I >> J >> L;
    WeightedGrapgh graph(U, D, I, J);
    for (int i = 0; i < L; ++i) {
        int K, u;
        cin >> K;
        for (int j = 0; j < K; ++j) {
            cin >> u;
            graph.add_edge(i + 1000000, u - 1);
        }
    }
    cout << graph.Decstra(0, N - 1);
    return 0;
}