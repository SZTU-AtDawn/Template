// int lg2[] -> 预处理的log2值
// int st[][] -> ST表
// int N -> 数组长度
// int lgN -> 数组长度的log2值向上取整（还可以稍大一点）

// st[i][j]代表以i为起点，长度为2^j的区间最大/最小值
// 故ST表实际数组大小为st[N][lgN + 1]

// 预处理 O(nlogn)
void init() {
    // 预处理lg2
    for (int i = 2; i <= N; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    // 预处理ST表
    for (int i = 1; i <= lgN; ++i)
        for (int j = 0; j + (1 << i) - 1 < N; ++j)
            // 合并左半边和右半边结果
            st[j][i] = std::max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
}

// 查询最值 O(1)
int query(int l, int r) {
    // 求区间长度的log2值
    int s = lg2[r - l + 1];
    // 拆分区间分别取值，再合并答案
    return std::max(st[l][s], st[r - (1 << s) + 1][s]);
}
