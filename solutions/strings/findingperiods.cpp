#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

void zalgo(string str){
    int n = str.size();
    vi z(n, 0);    
    for (int i(1), x(0), y(0); i < n; i++) {
        if (i < y) z[i] = min(z[i-x], y-i);
        while((i+z[i]) < n && str[z[i]] == str[i+z[i]]) z[i]++;
        if (y < (i+z[i])) x = i, y = i + z[i];
    }

    // for (auto x: str) printf("%3c ", x); cout << endl;
    // for (auto v: z) printf("%3d ", v); cout << endl;
    for (int i = 0; i < n; i++) if ((i+z[i]) == n) cout << i << " "; cout << n << endl;
}

int main () {
    string str; cin >> str;
    zalgo(str);
    return 0;
}