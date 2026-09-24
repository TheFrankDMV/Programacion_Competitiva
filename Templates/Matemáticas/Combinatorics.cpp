/*
 - Descripción: Precalcula factoriales y sus inversos modulares para responder 
   consultas de coeficientes binomiales en tiempo constante.
   
 - binom(a, b) calcula aCb (a tomando b) módulo mod.

 - Uso: Llamar a setup() una sola vez al inicio del main().
 - Detalles: binom(a, b) maneja de forma segura los casos donde b < 0 o b > a 
   retornando 0.
   
 - Tiempo: O(MAX_N) para setup(), O(1) para binom(a, b).
*/

const ll MAX_N = 2e5 + 5;

vll fact(MAX_N), inv_fact(MAX_N);

void setup() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv_fact[MAX_N - 1] = inv(fact[MAX_N - 1]);
    for (int i = MAX_N - 2; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}
ll binom(ll a, ll b) {
    if (a < b || b < 0) return 0;
    return ((fact[a] * inv_fact[b]) % MOD * inv_fact[a - b]) % MOD; 
}
