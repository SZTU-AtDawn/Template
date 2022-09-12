// 任意模数 NTT
// Author: SNRainiar from SZTU_AtDawn

// 使用中国剩余定理合并三次固定模数 NTT 的答案
// 挑选使用三个原根相同的模数计算 MTT

// 初始化二进制倒位
int rvs[MAXN];
void init(int N) {
    // Calculate bits of N
    int len = 0;
    for (int i = N - 1; i; i >>= 1, ++len);
    // Calculate bits reverse
    for (int i = 1; i < N; ++i)
        rvs[i] = (rvs[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

// 快速幂
#define ll long long
ll qpow(ll a, ll b, ll m) {
    ll r = 1;
    while (b) {
        if (b & 1)
            (r *= a) %= m;
        (a *= a) %= m;
        b >>= 1;
    }
    return r;
}

// op == 1: FNTT
// op == -1: IFNTT
void FNTT(ll A[], int N, ll invN, ll g, ll invg, int op, ll m) {
    // 元素交换
    for (int i = 0; i < N; ++i)
        if (i < rvs[i])
            std::swap(A[i], A[rvs[i]]);
    // 层循环
    for (int i = 1; i < N; i <<= 1) {
        // 当前原根
        ll Gn = qpow(op == 1 ? g : invg, (m - 1) / (i << 1), m);
        // 单位循环
        for (int j = 0; j < N; j += (i << 1)) {
            // 原根幂
            ll G = 1;
            // 蝶形运算
            for (int k = 0; k < i; ++k, (G *= Gn) %= m) {
                ll x = A[j + k], y = G * A[i + j + k] % m;
                A[j + k] = (x + y) % m;
                A[i + j + k] = (x - y + m) % m;
            }
        }
    }
    // IFNTT 除 N 处理
    if (op == -1)
        for (int i = 0; i < N; ++i) {
            (A[i].r *= invN) %= m;
            (A[i].i *= invN) %= m;
        }
}

// 合并答案（中国剩余定理）
void mrg(ll *A[3], int N, ll m[], ll p) {
    ll M = m[0] * m[1];
    ll invM = qpow(M, m[2] - 2, m[2]);
    ll k1 = qpow(m[1], m[0] - 2, m[0]);
    ll k2 = qpow(m[0], m[1] - 2, m[1]);
    // Merge answer
    for (int i = 0; i < N; ++i) {
        ll C = (A[0][i] * m[1] % M * k1 % M + A[1][i] * m[0] % M * k2 % M) % M;
        ll t3 = (A[2][i] - C + m[2]) % m[2] * invM % m[2];
        A[0][i] = (t3 * (M % p) % p + C) % p;  
    }
}

// op == 1: MTT
// op == -1: IMTT
void MTT(ll *A[3], int N, ll invN, ll g, ll invg, int op, ll m[], ll p) {
    for (int i = 0; i < 3; ++i)
        FNTT(A[i], N, invN, g, invg, op, m[i]);
    mrg(A, N, m, p);
}
