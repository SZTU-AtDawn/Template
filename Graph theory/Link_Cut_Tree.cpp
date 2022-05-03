// Author：SNRainiar, from SZTU_AtDawn

// int dep[] -> 深度
// int fa[] -> 父节点
// int siz[] -> 子树大小
// int son[] -> 重儿子
// int id[] -> 树链重排后的对应编号
// int top[] -> 树链的起始节点
// int a[] -> 树节点权值
// int b[] -> 树链重排后的节点权值
// int N -> 树节点数量
// int acc -> 树节点重排时使用的递增变量

// int head[] -> 链式前向星头指针
// struct e edge[] -> 链式前向星边跳表

// struct SgT tr -> 线段树 -> https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/Segment_Tree.cpp

// 动态树预处理需要两步dfs：

// 1. 处理节点基本信息：深度、父节点、子树大小、重儿子
// 当前节点x、当前父节点f、当前深度d
void dfs1(int x, int f, int d) {
    dep[x] = d;
    fa[x] = f;
    siz[x] = 1;
    int mx = -1;
    for (int i = head[x]; i; i = edge[i].nxt)
        // 回避父节点
        if (edge[i].to != f) {
            dfs1(edge[i].to, x, d + 1);
            siz[x] += siz[edge[i].to];
            // 更新重儿子
            if (siz[edge[i].to] > mx) {
                mx = siz[edge[i].to];
                son[x] = edge[i].to;
            }
        }
}

// 2. 剖分树链（树链重排）
// 当前节点x，当前树链的起始节点tp
void dfs2(int x, int tp) {
    id[x] = ++acc;
    b[acc] = a[x];
    top[x] = tp;
    // 不用对叶子节点做后续处理
    if (!son[x])
        return;
    // 连接重儿子构造树链
    dfs2(son[x], tp);
    // 处理轻链
    for (int i = head[x]; i; i = edge[i].nxt)
        // 回避父节点和重儿子
        if (edge[i].to != fa[x] && edge[i].to != son[x])
            // 以轻链的目标节点作为下一条树链的起始节点
            dfs2(edge[i].to, edge[i].to);
}

// 整个动态树的初始化
void init() {
    dfs1(1, -1, 0);
    dfs2(1, 1);
    // 将树链挂载到线段树上维护
    tr.build(1, 1, N, b);
}

// 动态树的基本操作：

// 1. 子树的查询与修改
inline int query(int x) {
    // 由动态树定义可知x的子树就是重排后x的编号开始，长度为x的子树大小
    return tr.qry(1, 1, N, id[x], id[x] + siz[x] - 1);
}
inline void update(int x, int y) {
    // 理论同上
    tr.upd(1, 1, N, id[x], id[x] + siz[x] - 1, y);
}

// 2. 路径的查询与修改
int query(int x, int y) {
    int ans = 0;
    // 如果x和y不在同一条链上
    while (top[x] != top[y]) {
        // 调整x使其所在链的起始节点深度更大
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        // 统计x所在链的答案
        ans += tr.qry(1, 1, N, id[top[x]], id[x]);
        // 让x到父节点所在链
        x = fa[top[x]];
    }
    // 调整x使其所在链的起始节点深度更大
    if (dep[top[x]] < dep[top[y]])
        std::swap(x, y);
    // 此时x和y在同一条链上，直接区间查询就能获取答案
    return ans + tr.qry(1, 1, N, id[x], id[y]);
}
void update(int x, int y, int z) {
    // 如果x和y不在同一条链上
    while (top[x] != top[y]) {
        // 调整x使其所在链的起始节点深度更大
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        // 修改x所在链
        tr.upd(1, 1, N, id[top[x]], id[x], z);
        // 让x到父节点所在链
        x = fa[top[x]];
    }
    // 调整x使其所在链的起始节点深度更大
    if (dep[top[x]] < dep[top[y]])
        std::swap(x, y);
    // 此时x和y在同一条链上，直接区间修改即可
    tr.upd(1, 1, N, id[x], id[y], z);
}
