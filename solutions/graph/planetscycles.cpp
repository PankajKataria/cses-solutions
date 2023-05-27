#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> succ, cycle, dist;
vector<bool> visited;
vector<vector<int>> gr;

unordered_map<int,int> clen;

int findCycle (int start, int label){    
    int f = start; int s = succ[start];
    while (f != s) f = succ[f], s = succ[succ[s]];

    visited[f] = true;

    int cl = 1; cycle[f] = label; s = succ[f];
    while (s != f) cycle[s] = label, s = succ[s], cl++;
    clen[label] = cl;
    return f;
}


void sol () {
    cycle.resize(n, -1);  visited.resize(n, false); dist.resize(n, -1);

    int clb = 0;
    function<void(int,int)> dfs = [&] (int u, int cd) {
        dist[u] = cd; visited[u] = true;
        for (int v: gr[u]) {
            if (visited[v] == false) {
                if (cycle[v] >= 0) dfs(v, cd);
                else dfs(v, cd + 1);
            }
        }
    };

    for (int i = 0; i<n; i++) {
        if (visited[i] == false) {
            int start = findCycle(i, clb);
            dfs(start, clen[clb]);
            clb++;
        }
    }
}


int main () {
    // freopen("./input.txt", "r", stdin);
    cin >> n;   succ.resize(n);
    for (int i = 0; i <n; i++) cin >> succ[i], --succ[i];
    gr.resize(n, vector<int>());

    for (int i = 0; i<n; i++)
    {
        int u(i), v(succ[i]);
        gr[v].push_back(u); 
    }
    
    sol();
    for (int x : dist) cout << x << " "; cout << endl;

    return 0;
}