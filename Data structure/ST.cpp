// ST表 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100005        // 范围
#define MAX_N_LOG 20        // 范围log2对数

// st[i][j]: 以i为起点，长度为2^j的区间最值
int st[MAX_N][MAX_N_LOG];

// 预处理log2对数表
int lg2[MAX_N];
void init() {
    for (int i = 2; i <= MAX_N; ++i)
        lg2[i] = lg2[i >> 1] + 1;
}

// 构造 O(nlogn)
void build(int a[]) {
    for (int i = 1; i <= MAX_N; ++i)
        st[i][0] = a[i];
    for (int j = 1; j <= MAX_N_LOG; ++j)
        for (int i = 1, lmt = MAX_N + 1 - (1 << j); i <= lmt; ++i)
           // 合并左半边和右半边结果（多种维护方案只需要满足倍增可合并性质即可）
            st[i][j] = std::max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);       // 最大值维护
            // st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);    // 最小值维护
}

// 查询最值 O(1)
inline int query(int l, int r) {
    // 求区间长度的log2对数值
    int k = lg2[r - l + 1];
    // 拆分区间分别取值，再合并答案
    return std::max(st[l][k], st[r - (1 << k) + 1][k]);     // 最大值查询
    // return std::min(st[l][k], st[r - (1 << k) + 1][k]);  // 最小值查询
}
