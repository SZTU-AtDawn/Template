// 快速数论变换
// Author: SNRainiar from SZTU_AtDawn

// 常用原根表
// 81788929    7
// 415236097   5
// 469762049   3
// 924844033   5
// 962592769   7
// 998244353   3
// 1004535809  3
// 1138753537  5
// 1214251009  7

// 初始化二进制倒位（递推）
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
