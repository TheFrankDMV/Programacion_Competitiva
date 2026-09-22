/*
 - Descripción: ntt(a) calcula f(k) = sum_x (A[x] * g^{xk}) para todo k, 
   donde g = root^{(mod-1)/N}.
 - N debe ser obligatoriamente una potencia de 2.
 - Útil para convoluciones módulo primos especiales de la forma p = 2^a * b + 1,
   donde el tamaño del arreglo resultante es a lo sumo 2^a. 

 - convolution(a, b) = c, donde c[x] = sum_i (a[i] * b[x-i]).
   En general, esto equivale a la multiplicación de dos polinomios.

 - Para convolución manual: aplica NTT a los arreglos de entrada, multiplica punto a punto, 
   divide entre N, aplica reverse(start+1, end), y aplica NTT de vuelta.
  
 - Módulos alternativos compatibles (NTT Primes) y todos con raíz primitiva g = 62:
        998244353 = 119 * 2^{23} + 1
        1004535809 = 479 * 2^{21} + 1
        469762049 = 7 * 2^{26} + 1
        167772161 = 5 * 2^{25} + 1
 
 - Las entradas deben estar en el intervalo [0, MOD).
 - Tiempo: O(N log N)
*/

const ll MOD = 998244353;
const ll ROOT = 62; 

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
