#include <bits/stdc++.h>
using namespace std;

int main () {
    // freopen("./input.txt", "r", stdin);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u; --v; 
        g[u].push_back(v); g[v].push_back(u);
    }

    vector<bool> visit(n, false);
    vector<int> p(n, -1);
    queue<int> q; q.push (0); visit[0] = true;
    
    int cd = 1;
    while (!q.empty()) {
        int sz = q.size(); cd++;
        while (sz--) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (visit[v] == false) {
                    if (v == (n-1)) {
                        cout << cd << endl;
                        vector<int> path {n};
                        int cur = u; while (cur != -1) path.push_back(cur + 1), cur = p[cur];
                        reverse(begin(path), end(path));
                        for (auto x: path) cout << x << " "; cout << endl;
                        return 0;
                    }

                    p[v] = u; visit[v] = true; q.push(v);
                }
            }
        }
    }

    cout << "IMPOSSIBLE" << endl;
    return 0;
}