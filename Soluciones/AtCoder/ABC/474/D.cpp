// AtCoder ABC 475 - D "Outweigh"
// https://atcoder.jp/contests/abc474/tasks/abc474_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];

    bool flag = false;
    for (int i = 0; i < n; i++) {
        if (A[i] > B[i]) flag = true;
    }

    if (!flag) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        if (A[i] > B[i]) cout << INF << " ";
        else cout << "1 ";
    }
    cout << "\n";
}
