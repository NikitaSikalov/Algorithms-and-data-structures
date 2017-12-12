//
// Created by Никита Сикалов on 09.12.2017.
//

//http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=112567#1

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void Z_function(vector<int> &Z, const vector<int> &numbers){
    Z[0] = numbers.size();
    int L = 0, R = 0;
    for (int i = 1; i < numbers.size(); ++i) {
        if (i > R) {
            Z[i] = 0;
        } else {
            Z[i] = min(Z[i - L], R - i + 1);
        }
        while (Z[i] + i < numbers.size() && numbers[Z[i] + i] == numbers[Z[i]]) {
            ++Z[i];
        }
        if (i + Z[i] - 1 > R) {
            R = i + Z[i] - 1;
            L = i;
        }
    }
}

vector<int> mirror_substrings(const vector<int> &numbers){
    vector<int> rev_subsequence(numbers.size());
    reverse_copy(numbers.begin(), numbers.end(), rev_subsequence.begin());
    vector<int> new_subsequence(numbers.size() * 2 + 1);
    auto it = copy(numbers.begin(), numbers.end(), new_subsequence.begin());
    new_subsequence[numbers.size()] = -1;
    copy(rev_subsequence.begin(), rev_subsequence.end(), it + 1);
    vector<int> Z(new_subsequence.size()), ans;
    Z_function(Z, new_subsequence);
    for (int i = numbers.size() + 1; i < new_subsequence.size(); ++i) {
        if (Z[i] % 2 == 0 && Z[i] == new_subsequence.size() - i) {
            ans.push_back(numbers.size() - Z[i] / 2);
        }
    }
    return ans;
}

int main(){
    int N, M;
    cin >> N >> M;
    vector<int> numbers(N);
    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
    }
    vector<int> res = mirror_substrings(numbers);
    for (auto u: res) {
        cout << u << ' ';
    }
    cout << N;
    return 0;
}