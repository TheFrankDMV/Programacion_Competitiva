// AtCoder ABC 471 - C "Cookies and Greedy Takahashi"
// https://atcoder.jp/contests/abc471/tasks/abc471_c

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll INF = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    
    set<ll> st;
    st.insert(-INF); st.insert(INF);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        st.insert(a);
    }

    ll ans = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        ll l = *prev(st.lower_bound(cur));
        ll r = *st.lower_bound(cur);

        if (cur - l <= r - cur) {
            ans += cur - l;
            cur = l;
            st.erase(l);
        } else {
            ans += r - cur;
            cur = r;
            st.erase(r);
        }
    }

    cout << ans << "\n";
}
