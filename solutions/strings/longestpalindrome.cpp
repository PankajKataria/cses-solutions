#include<bits/stdc++.h>
using namespace std;

#define pb(x) push_back(x)

void lp ()
{
    string str; cin >> str;
    string nstr = "#"; for (auto& x: str) nstr.pb(x), nstr.pb('#');

    int n = nstr.size(); int c(0), r(0);
    vector<int> lp(n, 1); 
    
    for (int i = 0; i < n; i++) {
        int lc = 2*c - i; if (lc >=0) lp[i] = min(lp[lc], r - i); 
        while ((0 <= (i-lp[i])) && ((i + lp[i]) < n) && (nstr[i-lp[i]] == nstr[i+lp[i]])) lp[i]++;
        if (r < (i+lp[i])) c = i, r = i + lp[i];
    }

    int mvidx = max_element(begin(lp), end(lp)) - begin(lp);
    int stidx = (mvidx - lp[mvidx] + 1)/2; 
    int eidx = (mvidx + lp[mvidx])/2;
    for (int i = stidx; i < eidx; i++) cout << str[i]; cout << endl;
}


int main ()
{
    lp();
    return 0;
}
