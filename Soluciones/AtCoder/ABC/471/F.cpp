// AtCoder ABC 471 - F "Concat (maximize)"
// https://atcoder.jp/contests/abc471/tasks/abc471_f

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

struct Item {
    string s; 
    ll sz, val;
};

string solve(vector<string> A) {
    sort(A.begin(), A.end(), [&](auto a, auto b) {
        return a + b > b + a;
    });
    string ret;
    for (auto s : A) ret += s;
    return ret;
}

void remove_leading_zeros(string &s) {
    reverse(s.begin(), s.end());
    while(ll(s.size()) > 1 && s.back() == '0') s.pop_back();
    reverse(s.begin(), s.end());
}

int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    vector<string> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        items[i] = {A[i], ll(A[i].size()), stoll(A[i])};
    }
    sort(items.begin(), items.end(), [&](auto a, auto b) {
        if (a.sz != b.sz) return a.sz > b.sz;
        return a.val > b.val;
    });

    vector<string> res1, res2;
    for (int i = 0; i < k - 1; i++) {
        res1.push_back(items[i].s);
        res2.push_back(items[i].s);
    }

    ll bst = -1, maxi = -1;
    for (int i = k - 1; i < n; i++) {
        if (items[i].val > maxi) {
            bst = i;
            maxi = items[i].val;
        }
    }

    res1.push_back(items[k - 1].s);
    string ans1 = solve(res1);
    remove_leading_zeros(ans1);

    res2.push_back(items[bst].s);
    string ans2 = solve(res2);
    remove_leading_zeros(ans2);

    if (ans1.size() != ans2.size()) {
        cout << (ans1.size() > ans2.size() ? ans1 : ans2) << "\n";
    } else cout << max(ans1, ans2) << "\n";
}
