#include <bits/stdc++.h>
using namespace std;

void solve(string s, string p) {
    string nstr = p + '$' + s;
    int n = nstr.size();
    vector<int> z(n, 0);
    int x(0), y(0);

    for (int i = 1; i < n; i++) {
        z[i] = (i < y) ? min(z[i-x], y-i): 0;
        while((i+z[i]) < n && nstr[z[i]] == nstr[i+z[i]]) z[i]++;
        if (y < (i+z[i])) x = i, y = i + z[i];
    }

    int mele = *max_element(begin(z), end(z));
    int occ = count(begin(z), end(z), mele);
    
    if (mele == p.size()) cout << occ << endl;
    else cout << 0 << endl;
}

int main () {
    // freopen("./input.txt", "r", stdin);
    string s, p;
    cin >> s >> p;
    solve(s, p);
    return 0;
}