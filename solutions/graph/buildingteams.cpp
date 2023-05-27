#include<bits/stdc++.h>
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

    vector<int> color(n, -1); 

    auto bfs = [&] (int start) {
        color[start] = 0;
        queue<int> q; q.push(start);
        while (!q.empty()) {
            int sz = q.size(); 
            while (sz--) {
                int u = q.front(); q.pop();
                int cc = color[u]; int nc = 1 - cc;
                for (int v: g[u]) {
                    if (color[v] == -1) { 
                        color[v] = nc; q.push(v);
                    } else if (color[v] == color[u]) return false;
                }
            }
        }

        return true;
    };

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (bfs(i) == false) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) cout << color[i] + 1 << " "; cout << endl;
    return 0;
}