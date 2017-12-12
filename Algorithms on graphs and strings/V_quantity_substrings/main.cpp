//
// Created by Никита Сикалов on 09.12.2017.
//

//https://www.e-olymp.com/ru/submissions/3808589

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void Z_function(vector<int> &Z, const string &str){
    Z[0] = str.size();
    int L, R = 0;
    for (int i =  1; i < str.size(); ++i) {
        if (i > R) {
            Z[i] = 0;
        } else {
            Z[i] = min(Z[i - L], R - i + 1);
        }
        while (Z[i] + i < str.size() && str[Z[i]] == str[i + Z[i]]) {
            ++Z[i];
        }
        if (i + Z[i] - 1 > R) {
            R = i + Z[i] - 1;
            L = i;
        }
    }
}

int quantity_of_substrings(const string &str){
    string temp;
    int ans = 0;
    vector<int> Z(str.size());
    for (auto symbol: str) {
        temp += symbol;
        reverse(temp.begin(), temp.end());
        Z_function(Z, temp);
        ans += temp.size() - *max_element(Z.begin() + 1, Z.end());
        reverse(temp.begin(), temp.end());
    }
    return ans;
}

int main(){
    string str;
    cin >> str;
    cout << quantity_of_substrings(str);
    return 0;
}