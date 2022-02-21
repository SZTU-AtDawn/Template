// 一般并查集：
// int fa[] -> 父节点指针

// 注：log*为迭代对数函数，增长极其缓慢，对应复杂度表达式近似为常数
// log*(n) = 0, n <= 1
// log*(n) = log*(logn), n > 1
// log*(2^65536) = 5

// 查找父亲 O(log*n)
int find(int x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}
// 检查是否在同一集合
inline bool judge(int x, int y) {
    return find(x) == find(y);
}
// 合并
inline void merge(int x, int y) {
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

// 带权并查集：
// int fa[] -> 父节点指针
// int len[] -> 当前节点到根的距离
// int siz[] -> 当前节点所属子树大小

// 查找父亲 O(log*n)
int find(int x) {
    if (fa[x] == x)
        return x;
    int tmp = fa[x];
    // 路径压缩
    fa[x] = find(fa[x]);
    // 更新节点距离
    len[x] += len[tmp];
    // 更新子树大小
    siz[x] = siz[fa[x]];
    return fa[x];
}
// 检查是否在同一集合
inline bool judge(int x, int y) {
    return find(x) == find(y);
}
// 合并（具有方向性）
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    // 将x子树接到y后面
    fa[x] = y;
    // 更新节点距离
    len[x] += siz[y];
    // 更新子树大小
    siz[x] = siz[y] += siz[x];
    // 同理，将y子树接到x后面，只需要交换x和y即可
}
// 两节点间的距离
inline int distance(int x, int y) {
    return judge(x, y) ? abs(len[x] - len[y]) : -1;
}
