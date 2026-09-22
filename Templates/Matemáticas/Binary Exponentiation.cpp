/*
 - Descripción: binpow(a, b) calcula (a^b) % mod.
   inv(a) calcula el inverso multiplicativo modular de a, tal que (a * inv(a)) % mod = 1.
 - Útil para divisiones modulares: (a / b) % mod = (a * inv(b)) % mod.
 - Para que inv(a) funcione el modulo debe ser obligatoriamente un número primo.

 - Las entradas a y b deben ser >= 0.
 - Tiempo: O(log b) para binpow, O(log mod) para inv.
*/

const ll MOD = 998244353;

ll binpow(ll a, ll b) {
    ll ret = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        b /= 2;
    }
    return res;
}
ll inv(ll a) {
    return binpow(a, MOD - 2);
}
