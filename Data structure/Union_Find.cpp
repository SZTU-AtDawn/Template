// 并查集 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

// 注：log*(n)为迭代对数函数，增长极其缓慢，对应复杂度表达式近似为常数，定义如下：
//      log*(n) = 0                  , n <= 1
//      log*(n) = 1 + log*(log n)    , n > 1
// 例：log*(2^65536) = 5
// 故一般认为 O(log*(n)) = O(1)

#define MAX_N 100000
// 并查集主结构
int fa[MAX_N + 5];

// 初始化
int init(int n) {
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
}
// 路径压缩查找父亲 O(log*(n)) = O(1)
inline int find(int x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}
// 检查父亲是否相同
inline bool check(int x, int y) {
    return find(x) == find(y);
}
// 合并
inline void merge(int x, int y) {
    fa[find(y)] = find(x);
}
