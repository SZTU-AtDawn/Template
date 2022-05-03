// SNRainiar, from SZTU_AtDawn

// 线段树基础模板（区间和维护）
#define MAX_N 100000
struct SegTree {
    // 数据维护节点，在这里定义需要维护的数据，以区间和为例，包括一个区间和变量和懒标记变量
    struct Node {
        int sum, lazy;
    } T[MAX_N << 2];
    // 上拉函数，用子区间信息更新父区间
    void pushUp(int n) {
        T[n].sum = T[n << 1].sum + T[n << 1 | 1].sum;
    }
    // 下推函数，将父区间的懒标记下推更新子区间信息
    void pushDown(int n, int l, int r) {
        // 判断是否需要下推
        if (T[n].lazy) {
            // 更新子区间
            int mid = (l + r) >> 1;
            T[n << 1].sum += T[n].lazy * (mid - l + 1);
            T[n << 1 | 1].sum += T[n].lazy * (r - mid);
            // 将父区间的懒标记下推到子区间
            T[n << 1].lazy += T[n].lazy;
            T[n << 1 | 1].lazy += T[n].lazy;
            // 一定要清空父区间的懒标记
            T[n].lazy = 0;
        }
    }
    // 建树
    void build(int n, int l, int r, int x[]) {
        // 直接修改叶子结点
        if (l == r) {
            T[n] = {x[l], 0};
            return;
        }
        // 左右子区间分别建树
        int mid = (l + r) >> 1;
        build(n << 1, l, mid, x);
        build(n << 1 | 1, mid + 1, r, x);
        // 上拉
        pushUp(n);
    }
    // 单点修改，修改一个点的数据
    void updateNode(int n, int l, int r, int p, int x) {
        // 直接修改叶子结点
        if (l == r) {
            T[n].sum = x;
            return;
        }
        // 下推
        pushDown(n, l, r);
        // 左右区间搜索修改位置
        int mid = (l + r) >> 1;
        if (p <= mid)
            updateNode(n << 1, l, mid, p, x);
        else 
            updateNode(n << 1 | 1, mid + 1, r, p, x);
        // 上拉
        pushUp(n);
    }
    // 区间修改，将[L, R]区间每个位置加x
    void updateSeg(int n, int l, int r, int L, int R, int x) {
        // 遇到包含区间
        if (L <= l && r <= R) {
            // 直接修改区间和
            T[n].sum += x * (r - l + 1);
            // 修改懒标记
            T[n].lazy += x;
            return;
        }
        // 下推
        pushDown(n, l, r);
        // 左右区间搜索修改位置
        int mid = (l + r) >> 1;
        if (L <= mid)
            updateSeg(n << 1, l, mid, L, R, x);
        if (mid < R)
            updateSeg(n << 1 | 1, mid + 1, r, L, R, x);
        // 上拉
        pushUp(n);
    }
    // 单点查询
    int queryNode(int n, int l, int r, int p) {
        // 找到就直接返回
        if (l == r)
            return T[n].sum;
        // 下推
        pushDown(n, l, r);
        // 左右区间搜索修改位置
        int mid = (l + r) >> 1;
        if (p <= mid)
            return queryNode(n << 1, l, mid, p);
        return queryNode(n << 1 | 1, mid + 1, r, p);
    }
    // 区间查询
    int querySeg(int n, int l, int r, int L, int R) {
        // 遇到包含区间直接返回
        if (L <= l && r <= R)
            return T[n].sum;
        // 下推
        pushDown(n, l, r);
        // 左右区间搜索修改位置
        int mid = (l + r) >> 1, ans1 = 0, ans2 = 0;
        if (L <= mid)
            ans1 = querySeg(n << 1, l, mid, L, R);
        if (mid < R)
            ans2 = querySeg(n << 1 | 1, mid + 1, r, L, R);
        // 合并答案返回
        return ans1 + ans2;
    }
};
