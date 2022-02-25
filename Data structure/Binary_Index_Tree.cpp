// int N -> 数据段长度

struct BIT {
    // 数据段，以维护前缀和为例
    int T[N];
    // 取二进制最低位函数
    int lowbit(int x) {
        return x & -x;
    }
    // 单点更新
    void update(int p, int x) {
        while (p <= N) {
            T[p] += x;
            p += lowbit(p);
        }
    }
    // 前缀查询
    void query(int p) {
        int rtn = 0;
        while (p) {
            rtn += T[p];
            p -= lowbit(p);
        }
        return rtn;
    }
};
