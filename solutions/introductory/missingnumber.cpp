#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n; cin >> n;
    ll cxor(0), txor(0); int cn; 
    for (int i=1; i<n; i++) scanf("%d", &cn), cxor^=cn, txor^=i;
    cout << ((txor ^ n) ^ cxor) << endl;
    return 0;
}