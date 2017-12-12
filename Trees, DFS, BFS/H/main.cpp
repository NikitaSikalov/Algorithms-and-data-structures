#include <iostream>
#include <vector>

using namespace std;

void update(vector<vector<long long int> >& t, int x, int y, int delta){
    for(int i = x; i < t.size(); i = (i | (i + 1)))
            for(int j = y; j < t[i].size(); j = (j | (j + 1)))
                t[i][j] += delta;
}

long long int sum(vector<vector<long long int> >& t, int x, int y){
    long long int res = 0;
    for(int i = x; i >= 0; i = ((i & (i + 1)) - 1))
        for(int j = y; j >= 0; j = ((j & (j + 1)) - 1))
            res += t[i][j];
    return res;
}

int main()
{
    int X, Y;
    cin >> X >> Y;
    vector<vector<long long int> > t;
    for(int i = 0; i < X; i++){
        t.push_back(vector<long long int>(Y));
    }

    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        char com;
        cin >> com;
        if(com == '1'){
            int X, Y, A;
            cin >> X >> Y >> A;
            update(t, X - 1, Y - 1, A);
        }
        if(com == '2'){
            int L, B, R, T;
            cin >> L >> B >> R >> T;
            cout << (sum(t, R - 1, T - 1) - sum(t, R - 1, B - 2) - sum(t, L - 2, T - 1) + sum(t, L - 2, B - 2)) << endl;
        }
    }
    return 0;
}
