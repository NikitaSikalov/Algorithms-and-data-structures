//
// Created by Никита Сикалов on 06.12.2017.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefix_function(string &s){
    int N = s.size();
    vector<int> p(N);
    p[0] = 0;
    for (int i = 1; i < N; ++i) {
        int t = p[i - 1];
        while(t > 0 && s[t] != s[i]) {
            t = p[t - 1];
            //cout << t;
        }
        p[i] = (s[t] == s[i] ? t + 1 : 0);
    }
    return p;
}

int main(){
    string str;
    cin >> str;
    vector<int> ans = prefix_function(str);
    for (auto u : ans) {
        cout << u << ' ';
    }
    return 0;
}