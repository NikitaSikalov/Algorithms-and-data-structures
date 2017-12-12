#include <iostream>
#include <vector>

using namespace std;

int NOD(int x, int y){
    while(x != 0 && y != 0){
        if(x >= y){
            x %= y;
        } else {
            y %= x;
        }
    }
    if(x != 0){
        return x;
    } else {
        return y;
    }
}

vector<int> init_tree(vector<int>& a){
    int k = 0;
    for(; (1 << k) < a.size(); k++);
    vector<int> tree(((1 << (k + 1)) - 1), 0);
    for(int i = 0; i < a.size(); i++){
        tree[i + tree.size() / 2] = a[i];
    }
    for(int i = tree.size() / 2 - 1; i >= 0; i--){
        tree[i] = NOD(tree[2 * i + 1], tree[2 * i + 2]);
    }
    return tree;
}

int get(int L, int R, vector<int>& tree){
    L += (tree.size() / 2 - 1);
    R += (tree.size() / 2 - 1);
    int ans = tree[L];
    while(L <= R){
        if(L % 2 == 0){
            ans = NOD(ans, tree[L]);
            L++;
        }
        if(R % 2 == 1){
            ans = NOD(ans, tree[R]);
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
    vector<int> segmets_tree = init_tree(a);
    int K;
    cin >> K;
    for(int i = 0; i < K; i++){
        int l, r;
        cin >> l >> r;
        cout << get(l, r, segmets_tree) << endl;
    }
    return 0;
}
