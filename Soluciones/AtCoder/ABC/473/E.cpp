// AtCoder ABC 473 - E "K-Divisible Subarrays"
// https://atcoder.jp/contests/abc473/tasks/abc473_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

struct Range {
    ll l, r;
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    vll A(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];

    vll psum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        psum[i] = (psum[i - 1] + A[i]) % k;
    }

    vector<Range> ranges;
    map<ll, ll> lst;
    for (int i = n; i >= 1; i--) {
        lst[psum[i]] = i;

        if (lst.count(psum[i - 1])) {
            ranges.push_back({i, lst[psum[i - 1]]});
        }
    }

    sort(ranges.begin(), ranges.end(), [&](auto a, auto b) {
        if (a.r != b.r) return a.r < b.r;
        return a.l < b.l;
    });

    ll ans = 0, curR = -INF;
    for (auto [l, r] : ranges) {
        if (curR < l) {
            ans++;
            curR = r;
        }
    }
    
    cout << ans << "\n";
}
