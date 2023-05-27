#include <bits/stdc++.h> 
using namespace std;
int n;
vector<int> succ, p2, cycle, indeg, root, dist;
vector<vector<int>> g, gr;
unordered_map<int, int> clen;
int table[200000][32];

int flca(int u, int v) {
    if (dist[u] < dist[v]) swap(u, v);

    int diff = dist[u] - dist[v];
    if (diff > 0) {
        for (int i = log2(diff); i>=0; i--) {
            if (diff&(1<<i)) u = table[u][i];
        }
    }

    if (u == v) return u;

    for (int i = 31; i>=0; i--) {
        if (table[u][i] != table[v][i])
            u=table[u][i], v=table[v][i];
    }

    u = table[u][0]; return u;
}



int findCycle (int start, int ccn) {
    int f = start; int s = succ[start];
    while (f != s) f = succ[f], s = succ[succ[s]];

    int cur = succ[f]; int cl = 0; 
    cycle[f] = ccn; cl++;

    while (cur != f) {
        cycle[cur] = ccn; cl++;
        cur = succ[cur];
    }

    clen[ccn] = cl; return f;
}

void sol() {
    vector<int> visited(n, 0); int cn(0);
    for (int j = 0; j<32; j++) for (int i = 0; i<n; i++) table[i][j] = -1;
    
    function<void(int, int, int)> dfs = [&] (int u, int cd, int cr) {

        visited[u] = 1; dist[u] = cd; root[u] = cr;
        for (int v: gr[u]) {
            if (visited[v] == 0) {
                dfs(v, cd+1, cr);
                table[v][0] = u;
            }
        }
        visited[u] = 2;
    };

    for (int i = 0; i<n; i++) {
        if (visited[i] == 0) {
            int cstart = findCycle(i, cn);
            dfs(cstart, 0, cn); cn++; 
        }
    }

    for (int j = 1; j<32; j++) {
        for (int i = 0; i<n; i++) {
            if (table[i][j-1] != -1) table[i][j] = table[table[i][j-1]][j-1];
        }
    }
}

int main () {
    int q; cin >> n >> q;
    succ.resize(n, -1);
    cycle.resize(n, -1);
    dist.resize(n, 0); root.resize(n, -1);
    gr.resize(n, vector<int>());

    for (int i =0; i<n; i++) cin >> succ[i], --succ[i];

    for (int i = 0; i <n; i++) {
        int u = i; int v = succ[i];
        gr[v].push_back(u);
    }

    sol();

    while (q--) {
        int a, b; cin >> a >> b; --a; --b;
        
        if (root[a] != root[b]) cout << -1 << endl;
        else {
            if (cycle[a] == cycle[b]) {
                if (cycle[a] == -1) {
                    int clca = flca(a, b);
                    if ((clca != a && clca != b) || dist[a] < dist[b]) cout << -1 << endl;
                    else {
                        // printf("In the same tree\n");
                        cout << dist[a] - dist[b] << endl;
                        
                    }
                } else {
                    int ccl = clen[cycle[a]];
                    if (dist[b] > dist[a]) {
                        // printf("In the same cycle opp direction\n");                        
                        cout << (ccl - (dist[b] - dist[a]))%ccl << endl;
                    }
                    else {
                        // printf("In the same cycle same direction\n");                        
                        cout << dist[a] - dist[b] << endl;
                    }
                }
            } else {
                if (cycle[b] >=0) {
                    int clca = flca (a, b);
                    int ccl = clen[cycle[b]];
                    if (clca != b) {
                        cout << dist[a] + (ccl - dist[b])%ccl << endl;
                    } else {
                        cout << dist[a] - dist[clca] << endl;
                    }
                }
                else cout << -1 << endl;
            }
        }
    }

    return 0;
}