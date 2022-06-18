// ISAP比较像Dinic，但是只需要进行一次bfs，O(V^2E)
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100
#define MAX_M 10000
#define INF 0x3f3f3f3f

// 流量网络
int head[MAX_N];
struct e {
    int to, f, nxt;
} edge[MAX_M];

// 深度、层计数、当前弧、前驱边
int dep[MAX_N], gap[MAX_N], cur[MAX_N], pre[MAX_N];
// 改进的ISAP主方法，将bfs直接集成
int ISAP(int s, int t, int n) {
    // 初始化
    memset(dep, 0, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    memcpy(cur, head, sizeof(cur));
    gap[0] = n;
    int u = s;
    int ans = 0;
    // 检查是否还有增广路
    while (dep[s] < n) {
        // 找到了一条增广路，所以修改网络并统计答案
        if (u == t) {
            int mn = INF;
            for (int i = pre[t]; i; i = pre[edge[i ^ 1].to])
                mn = std::min(mn, edge[i].f);
            for (int i = pre[t]; i; i = pre[edge[i ^ 1].to]) {
                edge[i].f -= mn;
                edge[i ^ 1].f += mn;
            }
            u = s;
            ans += mn;
            continue;
        }
        // 前进
        bool flg = false;
        for (int i = cur[u]; i; i = edge[i].nxt)
            if (edge[i].f && dep[edge[i].to] + 1 == dep[u]) {
                cur[u] = pre[edge[i].to] = i;
                u = edge[i].to;
                flg = true;
                break;
            }
        if (flg)
            continue;
        // 回退
        int mn = n;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (edge[i].f && dep[edge[i].to] < mn) {
                mn = dep[edge[i].to];
                cur[u] = i;
            }
        --gap[dep[u]];
        if (!gap[dep[u]])
            return ans;
        dep[u] = mn + 1;
        ++gap[dep[u]];
        if (u != s)
            u = edge[pre[u] ^ 1].to;
    }
    return ans;
}
