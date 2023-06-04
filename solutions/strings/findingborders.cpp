#include<bits/stdc++.h>
using namespace std;

void kmp (string str){
    int n = str.size();
    vector<int> lcsp(n, 0);
    for (int i = 1; i < n; i++){
        int idx = lcsp[i-1];
        while(idx > 0 && str[idx] != str[i]) idx = lcsp[idx-1];
        lcsp[i] = (idx == 0) ? (str[i] == str[0]) : idx+1;
    }


    int start = n-1; vector<int> ret;
    while (lcsp[start] > 0) ret.push_back(lcsp[start]), start = lcsp[start] - 1;

    reverse(ret.begin(), ret.end());
    for(auto x: ret) cout << x << " "; cout << endl;
}

int main () {
    // freopen("./input.txt", "r", stdin);
    string str; cin >> str;
    kmp(str);

    return 0;
}