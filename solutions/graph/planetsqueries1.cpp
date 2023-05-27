#include <bits/stdc++.h>
using namespace std;
int table[200000][32];

class stable {
    public:
        int n, k;
        stable(int _n, int _k, vector<int>& p) {
            n = _n;
            for (int i = 0; i <n; i++) table[i+1][0] = p[i];

            for (int j = 1; j < 32; j++) {
                for (int i = 1; i <= n; i++) {
                    table[i][j] = table[table[i][j-1]][j-1];
                }
            }
        }

        int getp (int u, int dist) {
            if (dist == 0) return u;
            int cur = u; int LOG = log2(dist);
            for (int i = LOG; i>=0; i--) if ((1<<i)&dist) cur = table[cur][i];
            return cur;
        } 
};

int main () {
    int n, q; vector<int> p;
    cin >> n >> q; p.resize(n, 0);
    for (int i = 0; i<n; i++) scanf("%d", &p[i]);
    stable st(n, 32, p);

    while (q--) {
        int u, d;
        scanf ("%d %d", &u, &d);
        cout << st.getp(u, d) << endl;
    }

    return 0;
}