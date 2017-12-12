#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

struct Node{
    int left;
    int right;
    int length;

    Node(): left(0), right(0), length(0) {};
};

vector<Node> init_tree(string& a){
    int k = 0;
    for(; (1 << k) < a.size(); k++);
    vector<Node> tree(((1 << (k + 1)) - 1), Node());
    for(int i = 0; i < a.size(); i++){
        if(a[i] == '('){
            tree[i + tree.size() / 2].left = 1;
        } else {
            tree[i + tree.size() / 2].right = 1;
        }
    }
    for(int i = tree.size() / 2 - 1; i >= 0; i--){
        Node L = tree[2 * i + 1];
        Node R = tree[2 * i + 2];
        tree[i].length = L.length + R.length + 2 * min(L.left, R.right);
        tree[i].left = L.left + R.left - min(L.left, R.right);
        tree[i].right = L.right + R.right - min(L.left, R.right);
    }
    return tree;
}

int get(int L, int R, vector<Node>& tree){
    L += (tree.size() / 2 - 1);
    R += (tree.size() / 2 - 1);
    Node ans_left, ans_right;
    while(L <= R){
        if(L % 2 == 0){
            ans_left.length += tree[L].length + 2 * min(ans_left.left, tree[L].right);
            ans_left.left -= min(ans_left.left, tree[L].right);
            ans_left.left += tree[L].left;
            L++;
        }
        if(R % 2 == 1){
            ans_right.length += tree[R].length + 2 * min(tree[R].left, ans_right.right);
            ans_right.right -= min(ans_right.right, tree[R].left);
            ans_right.right += tree[R].right;
            R--;
        }
        if(L > R){
            break;
        }
        L = (L - 1) / 2;
        R = (R - 1) / 2;
    }
    int ans = ans_left.length + ans_right.length + 2 * min(ans_left.left, ans_right.right);
    return ans;
}

int main()
{

    string a;
    cin >> a;
    vector<Node> segmets_tree = init_tree(a);
    int K;
    cin >> K;
    for(int i = 0; i < K; i++){
        int l, r;
        cin >> l >> r;
        cout << get(l, r, segmets_tree) << endl;
    }
    return 0;
}
