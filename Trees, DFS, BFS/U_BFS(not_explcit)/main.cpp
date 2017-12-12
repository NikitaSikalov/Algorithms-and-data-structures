#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <queue>

using namespace std;

pair<int, int> up(vector<vector<int>> &track, pair<int, int> v){
   int y_wall = v.second - 1;
   while(y_wall >= 0 && track[v.first][y_wall] == 0){
        y_wall--;
   }
    int new_y = y_wall + (v.second - y_wall + 1) / 2;
    return make_pair(v.first, new_y);
}

pair<int, int> down(vector<vector<int>> &track, pair<int, int> v){
    int y_wall = v.second + 1;
    while(y_wall < track[0].size() && track[v.first][y_wall] == 0){
        y_wall++;
    }
    int new_y = y_wall - (y_wall - v.second + 1) / 2;
    return make_pair(v.first, new_y);
}

pair<int, int> right(vector<vector<int>> &track, pair<int, int> v){
   int x_wall = v.first + 1;
   while(x_wall < track.size() && track[x_wall][v.second] == 0){
        x_wall++;
   }
    int new_x = x_wall - (x_wall - v.first + 1) / 2;
    return make_pair(new_x, v.second);
}

pair<int, int> left(vector<vector<int>> &track, pair<int, int> v){
   int x_wall = v.first - 1;
   while(x_wall >= 0 && track[x_wall][v.second] == 0){
        x_wall--;
   }
    int new_x = x_wall + (v.first - x_wall + 1) / 2;
    return make_pair(new_x, v.second);
}

map<pair<int, int>, int>  BFS(vector<vector<int>> &track, pair<int, int> start){
    queue<pair<int, int>> Q;
    Q.push(start);
    map<pair<int, int>, int> tin;
    tin[start] = 1;
    while(!Q.empty()){
        pair<int, int> cur = Q.front();
        //cout << cur.first << ' ' << cur.second << ' ' << Q.size() << endl;
        Q.pop();
        pair<int, int> up_cur = up(track, cur), down_cur = down(track, cur);
        pair<int, int> right_cur = right(track, cur), left_cur = left(track, cur);
        if(up_cur != cur && tin[up_cur] == 0){
            tin[up_cur] = tin[cur] + 1;
            Q.push(up_cur);
        }
        if(down_cur != cur && tin[down_cur] == 0){
            tin[down_cur] = tin[cur] + 1;
            Q.push(down_cur);
        }
        if(right_cur != cur && tin[right_cur] == 0){
            tin[right_cur] = tin[cur] + 1;
            Q.push(right_cur);
        }
        if(left_cur != cur && tin[left_cur] == 0){
            tin[left_cur] = tin[cur] + 1;
            Q.push(left_cur);
        }
    }
    return tin;
}

int main()
{
    vector<vector<int>> track;
    int n, m;
    cin >> n >> m;
    pair<int, int> start, finish;
    for(int i = 0; i < n; i++){
        track.push_back(vector<int>(m));
        for(int j = 0; j < m; j++){
            char field;
            cin >> field;
            if(field == '#'){
                track[i][j] = 1;
            }
            if(field == 'S'){
                start = make_pair(i, j);
            }
            if(field == 'T'){
                finish = make_pair(i, j);
            }
        }
    }
    map<pair<int, int>, int> ans;
    ans = BFS(track, start);
    //cout << 1;
    cout << ans[finish] - 1;
    return 0;
}
