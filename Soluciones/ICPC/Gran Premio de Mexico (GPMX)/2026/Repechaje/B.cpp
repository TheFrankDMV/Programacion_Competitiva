// ICPC GPMX 2026 Repechaje - B "Bridges of Koninsberg ii"
// https://codeforces.com/gym/106710/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n;
    cin >> n;
    vector<vll> M(n + 1, vll(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> M[i][j];
    }

    ll m;
    vector<vll> psum(n + 2, vll(n + 2));
    cin >> m;
    for (int i = 0; i < m; i++) {
        ll ax, ay, bx, by, k;
        cin >> ax >> ay >> bx >> by >> k;

        if (ax > bx) swap(ax, bx);
        if (ay > by) swap(ay, by);
        
        psum[ax][ay] += k;
        psum[bx + 1][ay] -= k;
        psum[ax][by + 1] -= k;
        psum[bx + 1][by + 1] += k;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            psum[i][j] += psum[i][j - 1] + psum[i - 1][j] - psum[i - 1][j - 1];
        }
    }

    vector<vll> dis(n + 1, vll(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (M[i][j] <= 0) dis[i][j] = M[i][j];
            else dis[i][j] = M[i][j] + psum[i][j];
        }
    }
    
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis[i][k] == -1 || dis[k][j] == -1) continue;

                if (dis[i][j] == -1) dis[i][j] = dis[i][k] + dis[k][j];
                else dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    ll q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        ll a, b;
        cin >> a >> b;
        cout << dis[a][b] << "\n"; 
    }
}
