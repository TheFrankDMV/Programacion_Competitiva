// ICPC GPMX 2026 Repechaje - J "Jalisco's Hydration Stations"
// https://codeforces.com/gym/106710/problem/J

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAX_N = 1e5 + 5;
const ll MAX_K = 26;
const ll INF = 1e18;

vector<vll> dp(MAX_K, vll(MAX_N, INF));
vll X(MAX_N), psum(MAX_N); 

ll calc(ll lx, ll rx) {
    ll len = rx - lx + 1, mid = (lx + rx) / 2;

    if (len % 2 == 0) {
        return (psum[rx] - psum[mid]) - (psum[mid - 1] - psum[lx - 1]) - X[mid];
    } else {
        return (psum[rx] - psum[mid]) - (psum[mid - 1] - psum[lx - 1]);
    }
}

void solve(ll level, ll l, ll r, ll optL, ll optR) {
    if (l > r) return;

    ll mid = (l + r) / 2;
    
    ll mini = INF, bst = -1;
    for (int i = optL; i <= min(mid - 1, optR); i++) {
        ll val = dp[level - 1][i] + calc(i + 1, mid);
        if (val < mini) {
            mini = val;
            bst = i;
        }
    }

    dp[level][mid] = mini;
    solve(level, l, mid - 1, optL, bst);
    solve(level, mid + 1, r, bst, optR);
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> X[i];
        psum[i] += psum[i - 1] + X[i];
    }

    dp[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        solve(i, 1, n, 0, n);
    }

    cout << dp[k][n] << "\n";
}
