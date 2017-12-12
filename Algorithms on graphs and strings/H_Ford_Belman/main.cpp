//
// Created by Никита Сикалов on 02.12.2017.
//

//http://informatics.mccme.ru/moodle/mod/statements/view3.php?chapterid=524#1

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int INF = 1e9 + 1e3;

class WeightedGraph{
private:
    struct Edge{
        pair<int, int> from, to;

        Edge(int from, int time_from, int to, int time_to){
            this->from = pair<int, int>(from, time_from);
            this->to = pair<int, int>(to, time_to);
        }
    };
    int size;
    vector<Edge> edges;

public:
    WeightedGraph(int N){
        size = N;
    }

    void add_edge(int from, int time_from, int to, int time_to){
        edges.push_back(Edge(from, time_from, to, time_to));
    }

    int Ford_Belman(int source, int finish){
        vector<int> arrive_time(size, INF);
        arrive_time[source] = 0;
        for (int i = 0; i < edges.size(); ++i) {
            for (auto e: edges) {
                if (arrive_time[e.to.first] > e.to.second && arrive_time[e.from.first] <= e.from.second) {
                    arrive_time[e.to.first] = e.to.second;
                }
            }
        }
        return  arrive_time[finish];
    }
};

int main(){
    int N, S, F, K;
    cin >> N >> S >> F >> K;
    WeightedGraph graph(N);
    for (int i = 0; i < K; ++i) {
        int from, time_from, to, time_to;
        cin >> from >> time_from >> to >> time_to;
        graph.add_edge(from - 1, time_from, to - 1, time_to);
    }
    cout << graph.Ford_Belman(S - 1, F - 1);
    return 0;
}