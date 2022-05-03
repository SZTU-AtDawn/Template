// Author：SNRainiar, from SZTU_AtDawn

// 可持久化01Trie
#define MAX_N 10000

int top;			// 计数
int root[MAX_N];	// 版本根节点
int cnt[MAX_N];		// 节点版本计数
int trie[MAX_N][2];	// 01-Trie主结构

// 插入新版本
// x：数据，lst：上一版本根节点，now：新版本根节点
void insert(int x, int lst, int now) {
    // 视情况调整位数
    for (int i = 24, b; i >= 0; --i) {
        // 更新计数
        cnt[now] = cnt[lst] + 1;
        b = (x >> i) & 1;
        // 连接无需修改的旧版本节点
        trie[now][b ^ 1] = trie[lst][b ^ 1];
        // 分别沿新、旧版本推进
        lst = trie[lst][b];
        now = trie[now][b] = ++top;
    }
    // 叶节点也需要更新计数
    cnt[now] = cnt[lst] + 1;
}
// 历史版本区间查询
// l：区间左端根节点，r：区间右端根节点，x：数据
int query(int l, int r, int x) {
    int rtn = 0;
    // 视情况调整位数
    for (int i = 24, b; i >= 0; --i) {
        b = (x >> i) & 1;
        // 如果计数合法，即当前区间的右端位置大于左端
        if (cnt[trie[r][b ^ 1]] > cnt[trie[l][b ^ 1]]) {
            // 更新答案，此处以最大异或为例
            rtn |= 1 << i;
            // 需要视情况调整接下来的跳转路线（贪心）
            b ^= 1;
        }
        // 沿左右端推进
        l = trie[l][b];
        r = trie[r][b];
    }
    return rtn;
}
