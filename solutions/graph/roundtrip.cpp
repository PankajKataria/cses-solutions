#include<bits/stdc++.h>
using namespace std;


int main () {
    // freopen("./input.txt", "r", stdin);

    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>());

    for (int  i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u; --v; 
        g[u].push_back(v); g[v].push_back(u);
    }

    vector<bool> visit(n, false);
    vector<int> p(n, -1);
    int ct = 0; int bcl = 0; int st, en;
    bool ctoken = true;

    function<void(int)> dfs = [&] (int u) {
        visit[u] = true; 
        for (int i = 0; i < g[u].size() && ctoken; i++) {
            int v = g[u][i];

            if (v == p[u]) continue;

            if (visit[v] == false) {
                p[v] = u; dfs(v);
            } else {
                ctoken = false;
                int cur = u; vector<int> path {v};
                while (cur != v) path.push_back(cur), cur = p[cur];
                path.push_back(v); reverse(begin(path), end(path));
                cout << path.size() << endl;
                for (auto x: path) cout << x + 1 << " "; cout << endl;
                return;
            }
        }
    };
    
    for (int i = 0; i < n && ctoken; i++) {
        if (visit[i] == false) {
            dfs(i);
        }
    }

    if (ctoken == true) cout << "IMPOSSIBLE" << endl;

    return 0;
}