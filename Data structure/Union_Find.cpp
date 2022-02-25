// int N -> 最大独立集数量

// 注：log*(n)为迭代对数函数，增长极其缓慢，对应复杂度表达式近似为常数，定义如下：
//      log*(n) = 0             , n <= 1
//      log*(n) = log*(log n)    , n > 1
// 例：log*(2^65536) = 5

struct UnionFind {
    // 父节点指针
    int fa[N];
    // 初始化
    void init() {
        for (int i = 1; i <= N; ++i)
            fa[i] = i;
    }
    // 查找父亲 O(log*(N))
    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    // 检查是否在同一集合
    bool judge(int x, int y) {
        return find(x) == find(y);
    }
    // 合并
    void merge(int x, int y) {
        // 优先合并到y
        fa[find(x)] = find(y);
        // 同理：优先合并到x
        // fa[find(y)] = find(x);
        // 同理：优先合并到下标较小
        // x = find(x);
        // y = find(y);
        // x < y ? (fa[y] = x) : (fa[x] = y);
        // 三种可以任选
    }
};
