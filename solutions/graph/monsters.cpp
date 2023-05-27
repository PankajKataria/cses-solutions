#include <bits/stdc++.h> 
using namespace std;

#define MONSTER 23
#define HERO 11

int main () {
    // freopen("./input.txt", "r", stdin);
    int n, m; cin >> n >> m;
    queue<int> q;
    vector<vector<char>> mat(n, vector<char>(m)), drn(n, vector<char>(m));
    vector<vector<int>> color(n, vector<int>(m, 0)), dist(n, vector<int>(m, INT_MAX));
    vector<vector<int>> p(n, vector<int>(m, -1));

    for (int i = 0; i <n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            if (mat[i][j] == 'M') {
                q.push(i*m + j); 
                color[i][j] = MONSTER;
                dist[i][j] = 0;
            }
            if (mat[i][j] == 'A') {
                q.push(i*m + j);
                color[i][j] = HERO;
                dist[i][j] = 0;
            }
        }
    }
    

    vector<int> id{1, -1, 0, 0};
    vector<int> jd{0, 0, 1, -1};
    vector<char> dirs{'D', 'U', 'R', 'L'};

    int cd = 0;

    while (!q.empty()) {
        int sz = q.size(); cd++;
        while (sz--) {
            int encu = q.front(); q.pop();
            int i(encu/m), j(encu%m);

            if ((i == 0 || i == (n-1) || j == 0 || j == (m-1)) && color[i][j] == HERO) {
                string path = "";
                int cur = encu; while (cur != -1) path += drn[cur/m][cur%m], cur = p[cur/m][cur%m]; 

                reverse(path.begin(), path.end()); path = path.substr(1);
                cout << "YES" << endl << path.size() << endl << path << endl;
                return 0;
            }

            for (int k = 0; k < 4; k++) {
                int ni = i + id[k];
                int nj = j + jd[k];
            
                if (ni>=0 && ni < n && nj>=0 && nj < m && mat[ni][nj] == '.') {
                    if ((dist[i][j] + 1) < dist[ni][nj]) {
                        drn[ni][nj] = dirs[k];
                        dist[ni][nj] = dist[i][j] + 1;
                        p[ni][nj] = i * m + j;
                        color[ni][nj] = color[i][j];
                        q.push(ni*m + nj);
                    } else if ((dist[i][j]+1) == dist[ni][nj]) {
                        if (color[i][j] == MONSTER && color[ni][nj] == HERO) {
                            color[ni][nj] = MONSTER; 
                        }
                    }
                }
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}