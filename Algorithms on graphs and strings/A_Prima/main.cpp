//
// Created by Никита Сикалов on 25.11.2017.
//
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <cstdlib>

using namespace std;

double dist(pair<int, int> point1, pair<int, int> point2) {
    double delta_x = (point1.first - point2.first) * (point1.first - point2.first);
    double delta_y = (point1.second - point2.second) * (point1.second - point2.second);
    return sqrt(delta_x + delta_y);
}

class WeightedGraph{
private:
    int size;
    mutable vector<bool> used;
    mutable vector<double> distance;
    vector<pair<int, int>> points;
public:
    WeightedGraph(int N) {
        size = N;
        distance.resize(N);
        used.resize(N);
    }

    void add_edge(int x, int y){
        points.push_back(pair<int, int>(x, y));
    }

    double Prima(int source = 0) const {
        double ans = 0;
        used[source] = true;
        for (int l = 0; l < size; ++l) {
            distance[l] = dist(points[source], points[l]);
        }
        for (int i = 0; i < size; ++i) {
            int minv = -1;
            for (int j = 0; j < size; ++j) {
                if (!used[j] && (minv == -1 || distance[minv] > distance[j])) {
                    minv = j;
                }
            }
            if (minv == -1) { break; }
            used[minv] = true;
            ans += distance[minv];
            for (int k = 0; k < size; ++k) {
                double weight = dist(points[minv], points[k]);
                if (distance[k] > weight) {
                    distance[k] = weight;
                }
            }
        }
        return ans;
    }

};

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> points;
    WeightedGraph graph(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        graph.add_edge(x, y);
    }
    printf("%.10f", graph.Prima());
    return 0;
}


