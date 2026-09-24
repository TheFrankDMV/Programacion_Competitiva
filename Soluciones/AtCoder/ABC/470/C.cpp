// AtCoder ABC 470 - C "Inc, Dec, Xor"
// https://atcoder.jp/contests/abc470/tasks/abc470_c

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, q;
    cin >> n >> q;
    
    vll A(n, 0);
    set<ll> st;
    ll ans = 0;
    for (int i = 0; i < q; i++) {
        ll op;
        cin >> op;

        if (op == 1) {
            ll id;
            cin >> id;
            id--;
            
            ans ^= A[id];
            A[id]++;
            ans ^= A[id];

            if (A[id] == 1) st.insert(id);
        } else {
            vll temp = vll(st.begin(), st.end());
            for (auto id : temp) {
                ans ^= A[id];
                A[id]--;
                ans ^= A[id];

                if (A[id] == 0) st.erase(id);
            }
        }

        cout << ans << "\n";
    }
}
