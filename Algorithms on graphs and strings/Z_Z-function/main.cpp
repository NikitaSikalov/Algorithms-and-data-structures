//
// Created by Никита Сикалов on 10.12.2017.
//
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void Z_function(vector<int> &Z, const string &str){
    Z[0] = str.size();
    int L = 0, R = 0;
    for (int i = 1; i < str.size(); ++i) {
        if (i > R) {
            Z[i] = 0;
        } else {
            Z[i] = min(Z[i - L], R - i + 1);
        }
        while (Z[i] + i < str.size() && str[i + Z[i]] == str[Z[i]]) {
            ++Z[i];
        }
        if (i + Z[i] - 1 > R) {
            R = i + Z[i] - 1;
            L = i;
        }
    }
}

vector<string> sub_prefixes(const string &str, const string &another_str){
    string new_str = str + '#' + another_str, cur;
    vector<int> Z(new_str.size());
    vector<string> ans;
    int cur_size = 0;
    Z_function(Z, new_str);
    for (int i = new_str.size() - 1; i > str.size() ; --i) {
        cur += new_str[i];
        if (cur.size() <= Z[i]) {
            reverse(cur.begin(), cur.end());
            ans.push_back(cur);
            cur_size += cur.size();
            cur.clear();
        }
    }
    if (cur_size < another_str.size()) {
        ans.clear();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(){
    string source, new_word;
    cin >> source >> new_word;
    vector<string> res = sub_prefixes(source, new_word);
    if (res.empty()) {
        cout << "Yes";
    } else {
        cout << "No" << '\n';
        for (const auto &u: res) {
            cout << u << ' ';
        }
    }
    return 0;
}