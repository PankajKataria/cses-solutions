#include <bits/stdc++.h>
using namespace std;

int main () {
    // freopen("./input.txt", "r", stdin);
    int st(0), en(0);
    int n, m; cin >> n >> m;


    vector<int> id {1, -1, 0, 0};
    vector<int> jd {0, 0, 1, -1};
    vector<char> dir{'D', 'U', 'R', 'L'};

    vector<vector<char>> mat(n, vector<char>(m)), path(n, vector<char>(m));
    vector<vector<bool>> visit(n, vector<bool>(m, false));
    vector<vector<int>> p(n, vector<int>(m, -1));

    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            if (mat[i][j] == 'A') st = m*i + j;
            if (mat[i][j] == 'B') en = m*i + j;
        }
    }

    queue<int> q; q.push(st);
    visit[st/m][st%m] = true;
    

    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto u = q.front(); q.pop();
            int i(u/m), j(u%m);

            if (mat[i][j] == 'B') {

                int cur = u; string cpath = "";
                while (cur != st) {
                    cpath += path[cur/m][cur%m];
                    cur = p[cur/m][cur%m];
                }

                reverse(begin(cpath), end(cpath));
                
                cout << "YES" << endl;
                cout << cpath.size() << endl;
                cout << cpath << endl;
                return 0;
            }          
  
            for (int k = 0; k < 4; k++) {
                int ni = i + id[k];
                int nj = j + jd[k];
                if (ni >=0 && ni < n && nj >=0 && nj < m && visit[ni][nj] == false && mat[ni][nj] != '#') {
                    visit[ni][nj] = true;
                    q.push({ni*m + nj});
                    path[ni][nj] = dir[k];
                    p[ni][nj] = u;
                }
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}