// AtCoder ABC 476 - F "Chebyshev Cafe"
// https://atcoder.jp/contests/abc476/tasks/abc476_f

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

vector<vll> rotate(ll n, vector<vll> A) {
    vector<vll> B(n, vll(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[j][(n - 1) - i] = A[i][j];
        }
    }
    return B;
}

vector<vll> solve(ll n, vector<vll> A) {
    vector<vll> psum(n + 1, vll(n + 1, 0));
    vll rowSum(n + 1, 0), colSum(n + 1, 0), diagSum(2 * n - 1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll id = (i - j) + (n - 1);
            psum[i + 1][j + 1] = rowSum[i] + colSum[j] - diagSum[id];

            rowSum[i] += A[i][j];
            colSum[j] += A[i][j];
            diagSum[id] += A[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            psum[i][j] += psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        }
    }
    
    return psum;
}

vector<vll> solve_extra(ll n, vector<vll> A) {
    vector<vll> res(n, vll(n));

    for (int i = 1; i <= n; i++) {
        ll curSum = 0;
        vll psum(n + 1, 0);
        for (int j = 1; j <= n; j++) {
            res[i - 1][j - 1] = curSum;

            psum[j] = psum[j - 1] + A[i - 1][j - 1];
            curSum += psum[j];
        }
    }
    
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, m;
    cin >> n >> m;
    vll A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];

    vector<vll> grid(n, vll(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = (A[i] * B[j]) % m;
        }
    }

    vector<vll> F(n, vll(n, 0));
    for (int r = 0; r < 4; r++) {
        vector<vll> res = solve(n, grid);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) F[i][j] += res[i + 1][j + 1];
        }

        grid = rotate(n, grid);
        F = rotate(n, F);
    }

    for (int r = 0; r < 4; r++) {
        vector<vll> res = solve_extra(n, grid);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) F[i][j] -= res[i][j];
        }

        grid = rotate(n, grid);
        F = rotate(n, F);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) ans ^= (F[i][j] + i * n + j);
    }

    cout << ans << "\n";
}
