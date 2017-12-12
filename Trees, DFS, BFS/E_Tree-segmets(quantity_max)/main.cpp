#include <iostream>
#include <vector>
#include <utility>

const int MIN_default = -(1e9);

using namespace std;

vector<pair<int, int>> init_tree(vector<int>& a){
    int k = 0;
    for(; (1 << k) < a.size(); k++);
    vector<pair<int, int>> tree(((1 << (k + 1)) - 1), make_pair(MIN_default, 1));
    for(int i = 0; i < a.size(); i++){
        tree[i + tree.size() / 2].first = a[i];
        tree[i + tree.size() / 2].second = 1;
    }
    for(int i = tree.size() / 2 - 1; i >= 0; i--){
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
        if(tree[2 * i + 1].first == tree[2 * i + 2].first)
            tree[i].second = tree[2 * i + 1].second + tree[2 * i + 2].second;
    }
    return tree;
}

pair<int, int> get(int L, int R, vector<pair<int, int>>& tree){
    L += (tree.size() / 2 - 1);
    R += (tree.size() / 2 - 1);
    pair<int, int> ans = make_pair(MIN_default, 1);
    while(L <= R){
        if(L % 2 == 0){
            if(ans.first == tree[L].first){
                ans.second += tree[L].second;
            } else {
                ans = max(ans, tree[L]);
            }
            L++;
        }
        if(R % 2 == 1){
            if(ans.first == tree[R].first){
                ans.second += tree[R].second;
            } else {
                ans = max(ans, tree[R]);
            }
            R--;
        }
        if(L > R){
            break;
        }
        L = (L - 1) / 2;
        R = (R - 1) / 2;
    }
    return ans;
}

int main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; i++){
        cin >> a[i];
    }
    vector<pair<int, int>> segmets_tree = init_tree(a);
    int K;
    cin >> K;
    for(int i = 0; i < K; i++){
        int l, r;
        cin >> l >> r;
        pair<int, int> ans = get(l, r, segmets_tree);
        cout << ans.first << ' ' << ans.second << endl;
    }
    return 0;
}
