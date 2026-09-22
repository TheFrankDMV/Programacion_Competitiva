// AtCoder ABC 473 - G "Wipeout"
// https://atcoder.jp/contests/abc473/tasks/abc473_g

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MOD = 998244353;
const ll ROOT = 62;

ll binpow(ll a, ll b) {
    ll ret = 1;
    while (b > 0) {
        if (b & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        b /= 2;
    }
    return ret;
}
ll inv(ll a) {
    return binpow(a, MOD - 2);
}

void ntt(vll &A) {
    ll n = A.size(), L = 31 - __builtin_clz(n);
    static vll rt(2, 1);
    for (int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, binpow(ROOT, MOD >> s)};
        for (int i = k; i < 2 * k; i++) rt[i] = (rt[i / 2] * z[i & 1]) % MOD;
    }
    vll rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll z = (rt[j + k] * A[i + j + k]) % MOD;
                ll &ai = A[i + j];
                A[i + j + k] = ai - z + (ai < z ? MOD : 0);
                ai = ai + z - (ai + z >= MOD ? MOD : 0);
            }
        }
    }
}
vll convolution(vll A, vll B) {
    if (A.empty() || B.empty()) return {};
    ll s = A.size() + B.size() - 1, e = 32 - __builtin_clz(s);
    ll n = 1 << e, inv_n = binpow(n, MOD - 2);
    vll L(A), R(B), ret(n);
    L.resize(n); R.resize(n);
    ntt(L); ntt(R);
    for (int i = 0; i < n; i++) {
        ret[-i & (n - 1)] = ((L[i] * R[i]) % MOD * inv_n) % MOD; 
    }
    ntt(ret);
    return {ret.begin(), ret.begin() + s};
}

vll solve(ll lx, ll rx) {
    if (rx - lx == 1) return {1, lx};

    ll m = (lx + rx) / 2;
    return convolution(solve(lx, m), solve(m, rx));
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    
    if (k < n || k >= 2 * n) {
        cout << "0\n";
        return 0;
    }
    if (n == 1) {
        cout << "1\n";
        return 0;
    }

    ll f_n = 1;
    for (int i = 1; i <= n; i++) f_n = (f_n * i) % MOD;

    vll poly = solve(1, n);
    ll ans = (poly[k - n] * inv(f_n)) % MOD;

    cout << ans << "\n";
}
