#include <iostream>
#include <vector>

const int MAX = 1e9;

using namespace std;

int log_2(int n){
    int ans = 1;
    while(n >= (1 << ans)){
        ans++;
    }
    return ans;
}

int RMQ(vector<vector<int>> &ST, int i, int j){
    int k = log_2(j - i + 1) - 1;
    return (min(ST[k][i], ST[k][j - (1 << k) + 1]));
}

int main()
{
    int n, m, a1;
    cin >> n >> m >> a1;
    vector<int> array;
    array.resize(n + 1);
    array[0] = MAX;
    array[1] = a1;
    for(int i = 2; i <= n; i++){
        array[i] = ((23 * array[i - 1]  + 21563) % 16714589);
    }

    vector<vector<int>> ST;
    ST.push_back(vector<int>(array));
    int k = log_2(n) - 1;
    for(int i = 1; (1 + (1 << i)) <= (n + 1); i++){
        ST.push_back(vector<int>());
        ST[i].push_back(MAX);
        for(int j = 1; (j + (1 << i)) <= (n + 1); j++){
            ST[i].push_back(min(ST[i - 1][j], ST[i - 1][j + (1 << (i - 1))]));
        }
    }

    int u, v, ans;
    cin >> u >> v;
    ans = RMQ(ST, min(u, v), max(u, v));
    for(int i = 2; i <= m; i++){
        u = (17 * u + 751 + ans + 2 * (i - 1)) % n + 1;
        v = (13 * v + 593 + ans + 5 * (i - 1)) % n + 1;
        ans = RMQ(ST, min(u, v), max(u, v));
    }
    cout << u << ' ' << v << ' ' << ans;
    return 0;
}
