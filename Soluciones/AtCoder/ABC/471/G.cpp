// AtCoder ABC 471 - G "Caeser Syllables"
// https://atcoder.jp/contests/abc471/tasks/abc471_g

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vll = vector<ll>;

const ll MOD = 998244353;
const ll ROOT = 62; 

ll binpow(ll a, ll b) {
    ll ret = 1;
    a %= MOD;
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

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k, seed, m;
    cin >> n >> k >> seed >> m;

    ull state = seed;
    vll A(n);
    for (int i = 0; i < n; i++) {
        if (i < m) cin >> A[i];
        else {
            ull x = (((state >> 18) ^ state) >> 27) % (1ull << 32);
            ull r = state >> 59;
            ull y = ((x >> r) + (x << (32 - r))) % (1ull << 32);
            A[i] = y % k;
            state = (state * ull(6364136223846793005) + ull(2026081520260815));
        }
    }

    vll V(k);
    for (int i = 0; i < k; i++) cin >> V[i];

    vector<vll> freq(k, vll(k, 0));
    for (int i = 1; i < n; i++) {
        freq[A[i - 1]][A[i]]++;
    }

    vll B(2 * k, 0);
    for (int i = 0; i < 2 * k; i++) B[i] = V[i % k];

    vll ans(k, 0);
    for (int i = 0; i < k; i++) {
        vll poly(k);
        for (int j = 0; j < k; j++) {
            poly[j] = freq[i][k - j - 1];
        }
        
        vll res = convolution(poly, B);
        for (int j = 0; j < k; j++) {
            if (V[(i + j) % k] == 0) {
                ans[j] += res[k + j - 1];
            }
        }
    }

    for (int i = 0; i < k; i++) {
        if (V[(A[0] + i) % k] == 1) ans[i]++;
        cout << ans[i] << "\n";
    }
}
