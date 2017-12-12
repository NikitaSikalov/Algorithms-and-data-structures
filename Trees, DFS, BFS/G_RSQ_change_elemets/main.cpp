#include <iostream>
#include <vector>

using namespace std;

void update(vector<long long int>& tree, int k, int delta){
    while(k < tree.size()){
        tree[k] += delta;
        k = (k | (k + 1));
    }
}

long long int sum(vector<long long int>& tree, int k){
    long long int res = 0;
    while(k >= 0){
        res += tree[k];
        k = ((k & (k + 1)) - 1);
    }
    return res;
}

int main()
{
    int N;
    cin >> N;
    vector<int> a;
    vector<long long int> ans;
    for(int i = 0; i < N; ++i){
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    vector<long long int> tree(a.size(), 0);
    for(int i = 0; i < N; ++i){
        update(tree, i, a[i]);
    }
    cin >> N;
    for(int i = 0; i < N; ++i){
        char com;
        cin >> com;
        if(com == 's'){
            int x, y;
            cin >> x >> y;
            ans.push_back(sum(tree, y - 1) - sum(tree, x - 2));
        }
        if(com == 'u'){
            int x, val;
            cin >> x >> val;
            update(tree, x - 1, val - a[x - 1]);
            a[x - 1] = val;
        }
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << ' ';
    }
    return 0;
}
