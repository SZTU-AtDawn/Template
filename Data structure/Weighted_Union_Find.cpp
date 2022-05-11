// 加权并查集 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

// 注：log*(n)为迭代对数函数，增长极其缓慢，对应复杂度表达式近似为常数，定义如下：
//      log*(n) = 0                  , n <= 1
//      log*(n) = 1 + log*(log n)    , n > 1
// 例：log*(2^65536) = 5
// 故一般认为 O(log*(n)) = O(1)

#define MAX_N 100000
// 父节点指针、当前节点到根的距离、当前节点所属子树大小
int fa[MAX_N], len[MAX_N], siz[MAX_N];

// 初始化
void init(int n) {
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        len[i] = 0;
        siz[i] = 1;
    }
}
// 查找父亲 O(log*(N)) = O(1)
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
bool judge(int x, int y) {
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
int distance(int x, int y) {
    return judge(x, y) ? abs(len[x] - len[y]) : -1;
}
