#include <iostream>
#include <vector>

using namespace std;

vector<int64_t> init_tree(vector<int>& a){
    int k = 0;
    for(; (1 << k) < a.size(); k++);
    vector<int64_t> tree(((1 << (k + 1)) - 1), 0);
    for(int i = 0; i < a.size(); i++){
        tree[i + tree.size() / 2] = a[i];
    }
    return tree;
}

void update(int L, int R, vector<int64_t>& tree, int add){
    L += (tree.size() / 2 - 1);
    R += (tree.size() / 2 - 1);
    //int ans = tree[L];
    while(L <= R){
        if(L % 2 == 0){
            //ans = NOD(ans, tree[L]);
            tree[L] += add;
            L++;
        }
        if(R % 2 == 1){
            //ans = NOD(ans, tree[R]);
            tree[R] += add;
            R--;
        }
        if(L > R){
            break;
        }
        L = (L - 1) / 2;
        R = (R - 1) / 2;
    }
}

int64_t get(int index, vector<int64_t>& tree, vector<int>& a){
    int64_t ans = 0;
    int i = index + tree.size() / 2;
    while(i != 0){
        ans += tree[i];
        i = (i - 1) / 2;
    }
    ans += tree[0];
    return ans;

}

int main()
{
    int n = 4;
    std::vector<std::vector<std::vector<int>>> vec(4, std::vector<std::vector<int>>(4, std::vector<int>(4)));

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; i++){
        cin >> a[i];
    }
    vector<int64_t> segmets_tree = init_tree(a);
    int K;
    cin >> K;
    for(int i = 0; i < K; i++){
        char comand;
        cin >> comand;
        if(comand == 'g'){
            int index;
            cin >> index;
            cout << get(index - 1, segmets_tree, a) << endl;
        }
        if(comand == 'a'){
            int l, r, add;
            cin >> l >> r >> add;
            update(l, r, segmets_tree, add);
        }
    }
    return 0;
}
