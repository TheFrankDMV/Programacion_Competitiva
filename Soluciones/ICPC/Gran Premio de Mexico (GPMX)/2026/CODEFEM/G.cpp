// ICPC CODEFEM 2026 - G "Macaron Conveyor"
// https://codeforces.com/gym/106718/problem/G

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    ll sum = accumulate(A.begin(), A.end(), 0);
    if (sum % n != 0) {
        cout << "-1\n";
        return 0;
    }

    ll target = sum / n;
    ll ans = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] + cur < target) {
            cout << "-1\n";
            return 0;
        }

        cur = A[i] + cur - target;
        ans += cur;
    }

    cout << ans << "\n";
}
