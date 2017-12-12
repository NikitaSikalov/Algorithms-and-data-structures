#include <iostream>
#include <random>

using namespace std;

const int64_t INF_MIN = -1e12;

struct Treap {
    int prior;
    int64_t sum;
    int64_t data;
    int size;


    Treap *l, *r;
    Treap(int64_t data): data(data), prior(rand()), l(NULL), r(NULL), sum(data), size(1) {};
};

typedef Treap* Treap_ptr;

void print_treap(Treap_ptr root){
    if(root == NULL)
        return;
    print_treap(root->l);
    cout << root->data << ' ';
    print_treap(root->r);
}

void print(Treap_ptr root_1, Treap_ptr root_2){
    cout << "treap1: "; print_treap(root_1);
    cout << endl;
    cout << "treap2: "; print_treap(root_2);
    cout << endl;
}

int64_t sm(Treap_ptr root){
    if(root == NULL){
        return 0;
    }
    return root->sum;
}


int sz(Treap_ptr v){
    return (v == NULL) ?  0 : v->size;
}

void update(Treap_ptr root){
    if(root == NULL){
        return;
    }
    root->sum = sm(root->l) + sm(root->r) + root->data;
    root->size = sz(root->l) + sz(root->r) + 1;
}

int index_1(int i){
    return ((i + 2) / 2);
}

int index_2(int i){
    return ((i + 1) / 2);
}

void Split(Treap_ptr root, int x, Treap_ptr &L, Treap_ptr &R, int left = 1){
    if(root == NULL){
        L = NULL;
        R = NULL;
        return;
    }
    int key = left + sz(root->l);
    if(key <= x){
        L = root;
        Split(root->r, x, root->r, R, key + 1);
    } else {
        R = root;
        Split(root->l, x, L, root->l, left);
    }
    update(root);
}

Treap_ptr Merge(Treap_ptr L, Treap_ptr R) {
    if (L == NULL) {
        return R;
    } else if (R == NULL) {
        return L;
    }
    if (L->prior >= R->prior) {
        L->r = Merge(L->r, R);
        update(L);
        return L;
    } else {
        R->l = Merge(L, R->l);
        update(R);
        return R;
    }
}

void insert(Treap_ptr &root, int new_data, int x) {
    Treap_ptr new_v = new Treap(new_data);
    Treap_ptr tmp_l, tmp_r;
    Split(root, x - 1, tmp_l, tmp_r);
    root = Merge(tmp_l, Merge(new_v, tmp_r));
}

void Swap(Treap_ptr &root_1, Treap_ptr &root_2, int L, int R){
    Treap_ptr t1, t2, t3, t4;
    Split(root_1, index_1(R - 1), t1, t2);
    Split(t1, index_1(L) - 1, t3, t4);

    Treap_ptr v1, v2, v3, v4;
    Split(root_2, index_2(R - 1), v1, v2);
    Split(v1, index_2(L) - 1, v3, v4);
    root_1 = Merge(Merge(t3, v4), t2);
    root_2 = Merge(Merge(v3, t4), v2);
}

int64_t sum(Treap_ptr &root_1, Treap_ptr &root_2, int L, int R){
    int64_t ans = 0;
    Treap_ptr t1, t2, t3, t4;
    Split(root_1, index_1(R - 1), t1, t2);
    Split(t1, index_1(L) - 1, t3, t4);
    ans += sm(t4);

    Treap_ptr v1, v2, v3, v4;
    Split(root_2, index_2(R - 1), v1, v2);
    Split(v1, index_2(L) - 1, v3, v4);
    ans += sm(v4);

    root_1 = Merge(Merge(t3, t4), t2);
    root_2 = Merge(Merge(v3, v4), v2);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, count = 1;
    cin >> N >> M;
    while(N != 0 && M != 0){
        cout << "Swapper " << count << ':' << endl;
        count++;
        Treap_ptr root_2 = NULL, root_1 = NULL;
        for(int i = 1; i <= N; i++){
            int x;
            cin >> x;
            if(i % 2 == 1){
                insert(root_1, x, i);
            } else {
                insert(root_2, x, i);
            }
        }
        for(int i = 1; i <= M; i++){
            int comand, L, R;
            cin >> comand >> L >> R;
            if(comand == 1){
                Swap(root_1, root_2, L, R);
            }
            if(comand == 2){
                cout << sum(root_1, root_2, L, R) << endl;
            }
        }
        cout << endl;
        cin >> N >> M;
    }
    return 0;
}
