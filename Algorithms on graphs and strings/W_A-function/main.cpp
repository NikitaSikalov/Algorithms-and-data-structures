//
// Created by Никита Сикалов on 09.12.2017.
//

//http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=1042#1

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void Z_function(vector<int> &Z, const string &numbers){
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

vector<int> mirror_substrings(const string &str){
    string rev_subsequence = str;
    reverse(rev_subsequence.begin(), rev_subsequence.end());
    string new_subsequence = str + '#' + rev_subsequence;
    vector<int> Z(new_subsequence.size()), ans(str.size());
    Z_function(Z, new_subsequence);
    for (int i = str.size() + 1, k = 0; i < new_subsequence.size(); ++i, ++k) {
        ans[k] = Z[i];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(){
    int N;
    cin >> N;
    string str;
    cin >> str;
    vector<int> res = mirror_substrings(str);
    for (auto u: res) {
        cout << u << ' ';
    }
    return 0;
}