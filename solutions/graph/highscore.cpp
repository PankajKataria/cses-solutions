#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

int n, m;
vector<vector<pii>> g, gp, gr;


vector<ll> bf () {
    vector<ll> dist(n, INT_MIN); dist[0] = 0;
    for (int l = 0; l < (n-1); l++) {
        vector<ll> dist2 = dist;
        bool relaxed = false;
        for (int u = 0; u < n; u++) {
            for (auto& vp : g[u]) {
                int v = vp.first; int w = vp.second;
                long long nval = dist[u]*1ll + w;
                if (dist[u] != INT_MIN && nval > dist2[v]) {
                    dist2[v] = nval;
                    relaxed = true;
                }
            }
        }
                
        dist = dist2;
    }

    return dist;
}

int main () {
    // freopen("./input.txt", "r", stdin);
    cin >> n >> m; 

    unordered_map<int, ll> cw;
    unordered_map<int, bool> cvalid;
    vector<int> cycleLabel(n, -1), color(n, 0);
    vector<int> toposort;
    vector<bool> visit(n, false); 
    g.resize(n, vector<pii>());
    gr.resize(n, vector<pii>());
    gp.resize(n, vector<pii>());

    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        --u; --v;
        g[u].push_back({v, w}); 
        if (w > 0) gp[u].push_back({v, w}), gr[v].push_back({u, w});
    }

    function<void(int)> tsort = [&] (int u) {
        visit[u] = true;
        for (auto& vp: gp[u]) {
            int v = vp.first; int w = vp.second;
            if (visit[v] == false) tsort(v);
        }
        toposort.push_back(u);
    }; tsort(0);


    function<int(int, int, ll&)> scc = [&] (int u, int label, ll& csum) {
        int ret = 1;  cycleLabel[u] = label; color[u] = 1;
        for (auto& vp: gr[u]) {
            int v = vp.first; int w = vp.second;
            if (color[v] == 0 && visit[v] == true) csum += w, ret += scc(v, label, csum);
            else if (color[v] == 1) csum+=w;
        }

        color[u] = 2;
        return ret;
    };

    int ccl = 0;    
    for (int i = toposort.size()-1; i>=0; i--) {
        int u = toposort[i];
        if (color[u] == 0) {
            ll csum = 0;
            int clen = scc(u, ccl, csum);
            if (clen > 1) cvalid[ccl] = true;
            cw[ccl] = csum;
            ++ccl;
        }
    }

    // for (int i = 0; i < n; i++) cout << setw(3) << i + 1 << " "; cout << endl;
    // for (int i = 0; i < n; i++) cout << setw(3) << cycleLabel[i] << " "; cout << endl;
    // for (int i = 0; i < n; i++) cout << setw(3) << cw[cycleLabel[i]] << " "; cout << endl;

    visit.clear(); visit.resize(n, false);
    function<bool(int)> dfs3 = [&] (int u) {

        int ccl = cycleLabel[u];
        if (cvalid[ccl] && cw[ccl] > 0 && color[u] == 2) return true;
        
        
        visit[u] = true; bool ret = false;
        for (auto& vp : gr[u]) {
            int v = vp.first; int w = vp.second;
            if (visit[v] == false) {
                ret = ret || dfs3(v);
            }
        }

        return ret;
    };

    if (dfs3(n-1)) cout << -1 << endl;
    else {
        auto retv = bf();
        cout << retv[n-1] << endl;
    }

    return 0;
}