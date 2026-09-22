// AtCoder ABC 474 - C "Remove and Append"
// https://atcoder.jp/contests/abc474/tasks/abc474_c

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

struct Item {
    ll val, time;
};

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, q;
    cin >> n >> q;
    vector<Item> A(n + 1);
    for (int i = 0; i < n; i++) {
        ll p;
        cin >> p;
        A[p] = {p, i};
    }

    for (int i = 0; i < q; i++) {
        ll a;
        cin >> a;
        A[a].time = i + n;
    }
    sort(A.begin() + 1, A.end(), [&](auto a, auto b) {
        return a.time < b.time;
    });

    for (int i = 1; i <= n; i++) {
        cout << A[i].val << " ";
    }
    cout << "\n";
}
