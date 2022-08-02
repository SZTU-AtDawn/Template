// 树状数组 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100000    // 范围

// 数组数组结构
int bit[MAX_N + 5];

// Lowbit操作，取最低的二进制位
inline int lowbit(int x) {
    return x & -x;
}

// 更新
void update(int p, int x) {
    while (p <= MAX_N) {
        bit[p] += x;
        p += lowbit(p);
    }
}

// 求和
int sum(int p) {
    int rtn = 0;
    while (p) {
        rtn += bit[p];
        p -= lowbit(p);
    }
    return rtn;
}
