//
// Created by Никита Сикалов on 06.12.2017.
//
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> prefix_function(string &s){
    int N = s.size();
    vector<int> p(N);
    p[0] = 0;
    for (int i = 1; i < N; ++i) {
        int t = p[i - 1];
        while(t > 0 && s[t] != s[i]) {
            t = p[t - 1];
        }
        p[i] = (s[t] == s[i] ? t + 1 : 0);
    }
    return p;
}

int main() {
    string str, subStr;
    cin >> str >> subStr;
    int n = subStr.size();
    string newStr = subStr + '!' + str;
    vector<int> prefix = prefix_function(newStr);
    for (int i = 0; i < prefix.size(); i++) {
        if (prefix[i] == n) {
            cout << i - 2 * n << ' ';
        }
    }
    return 0;
}
