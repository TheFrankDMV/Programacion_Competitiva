// ICPC GPMX 2026 Repechaje - M "Miguel and His Chess Tournament"
// https://codeforces.com/gym/106710/problem/M

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll B(n);
    for (int i = 0; i < n; i++) cin >> B[i];

    if (accumulate(B.begin(), B.end(), 0) != n * (n - 1) / 2) {
        cout << "NO\n";
        return 0;
    }

    vector<pair<ll, ll>> ord(n);
    for (int i = 0; i < n; i++) ord[i] = {B[i], i};

    vector<vll> ans(n + 1, vll(n + 1, false));
    for (int i = 1; i <= n; i++) {
        sort(ord.begin(), ord.end());
        ll wins = ord[0].first, loses = n - i - wins;
        if (wins < 0 || loses > n - i) {
            cout << "NO\n";
            return 0;
        }

        for (int j = 1; j <= wins; j++) {
            ans[ord[0].second][ord[j].second] = true;
        }
        for (int j = wins + 1; j <= n - i; j++) {
            ord[j].first--;
            ans[ord[j].second][ord[0].second] = true;
        }

        ord.erase(ord.begin());
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << ans[i][j];
        cout << "\n";
    }
}
