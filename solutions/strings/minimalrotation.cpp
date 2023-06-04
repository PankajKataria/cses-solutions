#include<bits/stdc++.h>
using namespace std;

string mr (string str) {
    string nstr = str + str;
    int n = nstr.size(); int ans(0);
    for (int i(0); i < (n/2);) {
        ans = i; int k(i), j(i+1);
        for (; j<n && (nstr[k] <= nstr[j]); j++) {
            if (nstr[k] < nstr[j]) k = i;
            else k++;
        }

        for(; i<=k; i+=(j-k)) {}
    }

    return nstr.substr(ans, n/2);
}


int main () {
    string str; cin >> str;
    cout << mr(str) << endl;
    return 0;
}