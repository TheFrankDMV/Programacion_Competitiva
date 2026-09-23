// ICPC CODEFEM 2026 - F "Cafe Hopping"
// https://codeforces.com/gym/106718/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, b;
    cin >> n >> b;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll ans = 0, sum = 0;
    for (int l = 0, r = 0; l < n; l++) {
        if (r == l) {
            sum += A[l];
            r++;
        }

        while (r < n && sum + A[r] <= b) {
            sum += A[r];
            r++;
        }

        if (sum <= b) ans = max(ans, ll(r-l));
        sum -= A[l];
    }

    cout << ans << "\n";
}
