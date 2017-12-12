#include <iostream>
#include <random>

using namespace std;

struct Treap{
    Treap *left, *right;
    int key, prior;
    long long int sum;

    Treap(int x): key(x), prior(rand()), left(NULL), right(NULL), sum(x) {};
};

typedef Treap* Treap_ptr;

long long int sm(Treap_ptr root){
    if(root == NULL){
        return 0;
    } else {
        return root->sum;
    }
}

void update(Treap_ptr root){
    if(root != NULL){
        root->sum = (sm(root->left) + sm(root->right) + root->key);
    }
}

Treap_ptr Merge(Treap_ptr L, Treap_ptr R){
    if(L == NULL){
        return R;
    }
    if(R == NULL){
        return L;
    }
    if(L->prior >= R->prior){
        L->right = Merge(L->right, R);
        update(L);
        return L;
    } else {
        R->left = Merge(L, R->left);
        update(R);
        return R;
    }
}

void Split(Treap_ptr root, Treap_ptr &L, Treap_ptr &R, int key){
    if(root == NULL){
        L = NULL;
        R = NULL;
        return;
    }
    if(root->key <= key){
        Split(root->right, root->right, R, key);
        L = root;
    } else {
        Split(root->left, L, root->left, key);
        R = root;
    }
    update(root);
}

bool find(Treap_ptr root, int x){
    if(root == NULL){
        return false;
    }
    if(root->key == x){
        return true;
    }
    if(root->key < x){
        return find(root->right, x);
    } else {
        return find(root->left, x);
    }
}

void insert(Treap_ptr &root, int x){
    if(!find(root, x)){
        Treap_ptr new_vertex = new Treap(x);
        Treap_ptr l, r;
        Split(root, l, r, x);
        root = Merge(Merge(l, new_vertex), r);
    }
}

void print(Treap_ptr root){
    if(root == NULL){
        return;
    }
    print(root->left);
    cout << root->key << ' ';
    print(root->right);
}

long long int sum_tree(Treap_ptr &root, int x, int y){
    Treap_ptr t1, t2, t3, t4;
    Split(root, t1, t2, y);
    Split(t1, t3, t4, x - 1);
    long long int res = sm(t4);
    root = Merge(t3, Merge(t4, t2));
    return res;

}

int main()
{
    Treap_ptr root = NULL;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    char comand;
    long long int n, ans;
    cin >> n;
    bool prev_sum = false;
    for(int i = 0; i < n; i++){
        cin >> comand;
        if(comand == '+'){
            long long int x;
            cin >> x;
            if(prev_sum){
                x = (ans + x) % (1000000000);
            }
            insert(root, x);
            prev_sum = false;
        }
        if(comand == '?'){
            int x, y;
            cin >> x >> y;
            ans = sum_tree(root, x, y);
            prev_sum = true;
            cout << ans << endl;
        }
    }
    return 0;
}
