// ICPC GPMX 2026 Repechaje - H "Hlaalu's Ebony"
// https://codeforces.com/gym/106710/problem/H

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll P(n);
    for (int i = 0; i < n; i++) cin >> P[i];

    ll maxi = *max_element(P.begin(), P.end());
    ll mini = *min_element(P.begin(), P.end());
    cout << maxi - mini << "\n";
}
