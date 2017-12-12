#include <iostream>
#include <vector>

const long long int MAX = (1 << 32);
const unsigned int N = (1 << 24);

using namespace std;

unsigned int a, b; // даны во входных данных
unsigned int cur = 0; // беззнаковое 32-битное число

unsigned int nextRand() {
  cur = cur * a + b; // вычисляется с переполнениями
  return cur >> 8; // число от 0 до 2^24-1.
}


int main()
{
    unsigned int m, q;
    cin >> m >> q >> a >> b;
    vector<long long int> array(N);
    vector<unsigned int> sums(N);
    unsigned int add, l ,r;
    for(int i = 0; i < m; i++){
        add = nextRand();
        l = nextRand();
        r = nextRand();
        if(l > r){
            swap(l, r);
        }
        array[l] += add;
        array[r + 1] -= add;
    }

    int cur_add_sum = 0;
    unsigned int temp_sum = 0;
    for(int i = 0; i < N; i++){
        cur_add_sum += array[i];
        if(cur_add_sum > MAX){
            cur_add_sum -= MAX;
        }
        temp_sum += cur_add_sum;
        sums[i] = temp_sum;
    }
    unsigned int res = 0;
    for(int i = 0; i < q; i++){
        l = nextRand();
        r = nextRand();
        if(l > r){
            swap(l, r);
        }
        if(l > 0){
            res += (sums[r] - sums[l - 1]);
        } else{
            res += (sums[r]);
        }
    }
    cout << res;
    return 0;
}
