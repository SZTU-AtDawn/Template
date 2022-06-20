// 基于Dijkstra的最小费用最大流
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 1000
#define MAX_M 10000
#define INF 0x3f3f3f3f

// 流量网络，边的序号应从1开始，使得通过异或运算就可以得到反流边
int head[MAX_N];
struct e {
    int to, f, c, nxt;
} edge[MAX_M];

// 最小费用路径、前驱节点、前驱边、势函数
int dis[MAX_N], prv[MAX_N], pre[MAX_N], h[MAX_N];
// 集合存在标志
bool vis[MAX_N];
// 寻找最小费用増广路（Dijkstra）
bool dijkstra(int s, int t) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    std::priority_queue<std::pair<int, int>> que;
    dis[s] = 0;
    que.emplace(0, s);
    while (!que.empty()) {
        auto [d, u] = que.top();
        que.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (edge[i].f && dis[edge[i].to] > dis[u] + edge[i].c + h[u] - h[edge[i].to]) {
                dis[edge[i].to] = dis[u] + edge[i].c + h[u] - h[edge[i].to];
                prv[edge[i].to] = u;
                pre[edge[i].to] = i;
                que.emplace(-dis[edge[i].to], edge[i].to);
            }
    }
    for (int i = 1; i < MAX_N; ++i)
        if (dis[i] != INF)
            h[i] += dis[i];
    return dis[t] != INF;
}
// 最小费用最大流主函数 O((V^2E+VE^2)logE)，实际情况远小于理论时间复杂度
std::pair<int, int> mcmf(int s, int t) {
    int cost = 0, flow = 0;
    while (dijkstra(s, t)) {
        int mn = INF;
        for (int i = t; i != s; i = prv[i])
            mn = std::min(mn, edge[pre[i]].f);
        flow += mn;
        cost += mn * dis[ed];
        for (int i = t; i != s; i = prv[i]) {
            edge[pre[i]].f -= mn;
            // 反流边
            edge[pre[i] ^ 1].f += mn;
        }
    }
    return {cost, flow};
}
