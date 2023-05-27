#include<bits/stdc++.h>
using namespace std;

int n, m; 
vector<vector<char>> mat;

class _dsu {
    public:
        vector<int> p; int n; int cc;
        _dsu(int _n) {
            cc = n = _n; p.resize(n, -1);
            for (int i= 0; i <n; i++) p[i] = i;
        }

        void join(int u, int v) {
            if ((u=getp(u)) == (v=getp(v))) return;
            if (u > v) swap(u, v);
            p[v] = u; cc--;
        }

        int getp (int u) {
            if (u == p[u]) return u;
            return (p[u] = getp(p[u]));
        }
};

int main () {
    // freopen("./input.txt", "r", stdin);

    cin >> n >> m;
    mat.resize(n, vector<char>(m));

    for (int i =0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            cin >> mat[i][j];
        }
    }

    _dsu dsu(m*n); int blocks = 0;

    vector<int> id{1, -1, 0, 0};
    vector<int> jd{0, 0, 1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == '#') blocks++;
            else {
                for (int k = 0; k < 4; k++) {
                    int ni = i + id[k]; int nj = j + jd[k];
                    if (ni >=0 && ni < n && nj >=0 && nj < m && mat[ni][nj] == '.') {
                        dsu.join(m*i + j, m*ni + nj);
                    }
                }
            }
        }
    }

    cout << dsu.cc - blocks << endl;
    return 0;
}