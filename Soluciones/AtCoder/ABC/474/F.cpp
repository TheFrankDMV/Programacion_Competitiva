// AtCoder ABC 474 - F "Increment All Divisors"
// https://atcoder.jp/contests/abc474/tasks/abc474_f

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

struct Item {
    ll a, b;
};

ll ceil_div(ll a, ll b) {
    if (b < 0) {
        a *= -1; 
        b *= -1;
    }
    if (a >= 0) return (a + b - 1) / b;
    return a / b;
}
ll floor_div(ll a, ll b) {
    if (b < 0) {
        a *= -1;
        b *= -1; 
    }
    if (a >= 0) return a / b;
    return (a - b + 1) / b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vll A(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];

    vector<Item> C(n + 1, {0, 0});
    ll l = -INF, r = INF;
    for (int i = n; i >= 1; i--) {
        C[i] = {1, -A[i]};

        for (int j = 2 * i; j <= n; j += i) {
            C[i].a -= C[j].a;
            C[i].b -= C[j].b;
        }

        if (C[i].a > 0) {
            l = max(l, ceil_div(-C[i].b, C[i].a));
        } else if (C[i].a < 0 ) {
            r = min(r, floor_div(-C[i].b, C[i].a));
        } else {
            if (C[i].b < 0) {
                cout << "-1\n";
                return 0;
            }
        }
    }

    cout << (l > r ? -1 : l - A[1]) << "\n";
}
