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
            //cout << t;
        }
        p[i] = (s[t] == s[i] ? t + 1 : 0);
    }
    return p;
}

int main(){
    string first, second, newStr;
    int n;
    cin >> n;
    n--;
    cin >> first >> second;
    string str1 = second + '1', str0 = second + '0';
    string newStr1 = first + '!' + str1 + str1, newStr0 = first + '0' + '!' + str0 + str0;
    vector<int> ans1 = prefix_function(newStr1);
    vector<int> ans0 = prefix_function(newStr0);
    bool flag1 = false, flag0 = false;
    //cout << newStr0 << '\n';
    //cout << newStr1 << '\n';
    for (auto u: ans0) {
        if (u == n) {
            flag0 = true;
            break;
        }
    }
    for (auto u: ans1) {
        if (u == n) {
            flag1 = true;
            break;
        }
    }
    if (flag1 && flag0) {
        cout << "Random";
    } else {
        if (flag1){
            cout << "Yes";
        } else {
            cout << "No";
        }
    }
    return 0;
}
