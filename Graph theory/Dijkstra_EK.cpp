// 基于Dijkstra的最小费用最大流
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 1000
#define MAX_M 10000

// 流量网络，边的序号应从1开始，使得通过异或运算就可以得到反流边
int head[MAX_N + 5];
struct e {
    int to, f, c, nxt;
} edge[MAX_M];

// 最小费用路径、前驱节点、前驱边、势函数
int dis[MAX_N + 5], prv[MAX_N + 5], pre[MAX_N + 5], h[MAX_N + 5];
// 集合存在标志
bool vis[MAX_N + 5];
// 寻找最小费用増广路（Dijkstra）
bool dijkstra(int st, int ed) {
    memset(dis, 0xx3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    std::priority_queue<std::pair<int, int>> que;
    dis[st] = 0;
    que.emplace(0, st);
    while (!que.empty()) {
        auto [d, u] = que.top();
        que.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (dis[edge[i].to] > dis[u] + edge[i].c + h[u] - h[edge[i].to] && edge[i].f > 0) {
                dis[edge[i].to] = dis[u] + edge[i].c + h[u] - h[edge[i].to];
                prv[edge[i].to] = u;
                pre[edge[i].to] = i;
                que.emplace(-dis[edge[i].to], edge[i].to);
            }
    }
    for (int i = 1; i <= MAX_N; ++i)
        if (dis[i] < 0x3f3f3f3f)
            h[i] += dis[i];
    return dis[ed] != 0x3f3f3f3f;
}
// 最小费用最大流主函数 O((V^2E+VE^2)logE)，实际情况远小于理论时间复杂度
std::pair<int, int> mcmf(int st, int ed) {
    int cost = 0, flow = 0;
    while (dijkstra(st, ed)) {
        int mn = 0x3f3f3f3f;
        for (int i = ed; i != st; i = prv[i])
            mn = std::min(mn, edge[pre[i]].f);
        flow += mn;
        cost += mn * dis[ed];
        for (int i = ed; i != st; i = prv[i]) {
            edge[pre[i]].f -= mn;
            // 反流边
            edge[pre[i] ^ 1].f += mn;
        }
    }
    return {cost, flow};
}
