// 快速幂
// Author: SNRainiar from SZTU_AtDawn

// a^b % mod，此处未考虑乘法溢出问题
int qpow(int a, int b, int mod) {
    int r = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            (r *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
}
