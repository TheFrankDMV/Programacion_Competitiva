// AtCoder ABC 472 - F "Centroid of a Slice"
// https://atcoder.jp/contests/abc472/tasks/abc472_f

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, q;
    cin >> n >> q;
    vll X(2 * n), Y(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> X[i] >> Y[i];
        X[i + n] = X[i];
        Y[i + n] = Y[i];
    }

    vll psum(2 * n + 1, 0), psum_X(2 * n + 1, 0), psum_Y(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++) {
        ll id = (i + 1) % (2 * n);
        ll x1 = X[i], y1 = Y[i], x2 = X[id], y2 = Y[id];

        ll tot = x1 * y2 - x2 * y1;
        ll tot_X = (x1 + x2) * tot;
        ll tot_Y = (y1 + y2) * tot;
        
        psum[i + 1] = psum[i] + tot;
        psum_X[i + 1] = psum_X[i] + tot_X;
        psum_Y[i + 1] = psum_Y[i] + tot_Y;
    }

    for (int i = 0; i < q; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        if (a > b) b += n;

        ll tot = psum[b] - psum[a];
        ll tot_X = psum_X[b] - psum_X[a];
        ll tot_Y = psum_Y[b] - psum_Y[a];

        ll x1 = X[a], y1 = Y[a], x2 = X[b], y2 = Y[b];
        ll extra = x2 * y1 - x1 * y2;
        ll extra_X = (x1 + x2) * extra;
        ll extra_Y = (y1 + y2) * extra;

        tot += extra; tot_X += extra_X; tot_Y += extra_Y;

        ld ans_X = ld(tot_X) / (3.0 * tot);
        ld ans_Y = ld(tot_Y) / (3.0 * tot);
        cout << fixed << setprecision(10) << ans_X << " " << ans_Y << "\n";
    }
}
