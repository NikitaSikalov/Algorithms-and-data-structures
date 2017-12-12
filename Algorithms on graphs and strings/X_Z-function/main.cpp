//
// Created by Никита Сикалов on 06.12.2017.
//
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Z_function(const string &str, vector<int> &ans){
    ans[0] = str.size();
    int L = 0, R = 0 ; //Z - блок
    for (int i = 1; i < str.size(); ++i) {
        if(i > R) {
            ans[i] = 0;
        } else {
            ans[i] = min(ans[i - L], R - i + 1);
        }
        while(i + ans[i] < str.size() && str[i + ans[i]] == str[ans[i]]) {
            ++ans[i];
        }
        if (i + ans[i] - 1 > R) {
            L = i;
            R = i + ans[i] - 1;
        }
    }
}

int main(){
    string str;
    cin >> str;
    vector<int> ans(str.size());
    Z_function(str, ans);
    for (auto u: ans){
        cout << u << ' ';
    }
    return 0;
}