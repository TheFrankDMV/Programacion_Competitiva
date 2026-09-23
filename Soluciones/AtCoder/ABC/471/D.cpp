// AtCoder ABC 471 - D "Chargers"
// https://atcoder.jp/contests/abc471/tasks/abc471_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll q, v;
    cin >> q >> v;

    multiset<ll> st;
    for (int i = 0; i < q; i++) {
        ll op;
        cin >> op;
        
        if (op == 1) {
            ll a, b;
            cin >> a >> b;

            st.insert(a - b);
        } else {
            ll a;
            cin >> a;

            if (st.empty()) {
                cout << "-1\n";
                continue;
            }

            ll ans = a - *st.begin();
            st.erase(st.begin());
            cout << min(ans, v) << "\n";
        }
    }
}
