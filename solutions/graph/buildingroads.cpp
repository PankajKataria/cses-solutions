#include <bits/stdc++.h>
using namespace std;

class _dsu {

    public:
        vector<int> p;
        int cc, n;

        _dsu (int _n) {
            cc = n = _n; p.resize(n, -1);
            for (int i = 0; i < n; i++) p[i] = i;
        }

        int getp(int u) {
            if (u == p[u]) return u;
            return (p[u] = getp(p[u]));
        }

        void join (int u, int v) {
            if ((u = getp(u)) == (v = getp(v))) return;
            if (u > v) swap(u, v); 
            p[v] = u; cc--;
        }

        vector<int> getccc () {
            for (int i = 0; i < n; i++) p[i] = getp(i);
            set<int> st {begin(p), end(p)};
            vector<int> temp{st.begin(), st.end()};
            return temp;
        }
};

int main () {
    // freopen("./input.txt", "r", stdin);

    int n, m; cin >> n >> m;
    int u, v; _dsu dsu(n);

    for (int i = 0; i < m; i++) {
        cin >> u; cin >> v;
        dsu.join(u-1, v-1);    
    }

    cout << dsu.cc - 1 << endl;
    vector <int> temp = dsu.getccc();

    for (int i = 1; i < temp.size(); i++) 
        printf("%d %d\n", temp[i-1] + 1, temp[i] + 1);

    return 0;
}