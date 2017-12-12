#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

struct Treap{
    int data, key, prior;
    Treap *left, *right, *prev;

    Treap(int i, int key, int prior): data(i), key(key), prior(prior), left(NULL), right(NULL), prev(NULL) {};
};

struct vectors{
    vector<int> prev, left, right;

    vectors(int n){
        prev.resize(n);
        left.resize(n);
        right.resize(n);
    }
};

typedef Treap* Treap_ptr;


Treap_ptr insert(Treap_ptr &root, Treap_ptr right, pair<int, pair<int, int>> v){
    Treap_ptr new_vertex = new Treap(v.second.second, v.first, v.second.first);
    if(right == NULL){
        root = new_vertex;
        return root;
    }
    Treap_ptr cur = right;
    Treap_ptr right_son = cur->right;
    while(cur != NULL && cur->prior > new_vertex->prior){
        right_son = cur;
        cur = cur->prev;
    }
    if(cur != NULL){
        cur->right = new_vertex;
        new_vertex->prev = cur;
        new_vertex->left = right_son;
        if(right_son != NULL){
            right_son->prev = new_vertex;
        }
        return new_vertex;
    } else {
        root = new_vertex;
        new_vertex->left = right_son;
        right_son->prev = new_vertex;
        return new_vertex;
    }
}

void print_treap(Treap_ptr root, vectors &ans){
    if(root == NULL){
        return;
    }
    if(root->left != NULL){
        ans.prev[root->left->data] = root->data;
        ans.left[root->data] = root->left->data;
    }
    if(root->right != NULL){
        ans.prev[root->right->data] = root->data;
        ans.right[root->data] = root->right->data;
    }
    print_treap(root->left, ans);
    print_treap(root->right, ans);
}


typedef pair<int, pair<int, int>> my_pair;

int main()
{
    Treap_ptr root = NULL;
    int n;
    cin >> n;
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>> Q;
    for(int i = 1; i <= n; i++){
        int x, y;
        cin >> x >> y;
        Q.push(make_pair(x, make_pair(y, i)));
    }
    Treap_ptr right = NULL;
    while(!Q.empty()){
        auto v = Q.top();
        Q.pop();
        right = insert(root, right, v);
    }
    vectors ans(n + 1);
    print_treap(root, ans);
    cout << "YES" << endl;
    for(int i = 1; i <= n; i++){
        cout << ans.prev[i] << ' ' << ans.left[i] << ' ' << ans.right[i] << endl;
    }
    return 0;
}
