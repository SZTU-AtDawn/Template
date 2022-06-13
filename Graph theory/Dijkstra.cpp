// Dijkstra
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 10000
#define MAX_M 100000

// 图结构
int head[MAX_N];
struct e {
    int to, val, nxt;
} edge[MAX_M];
// 最短路
int dis[MAX_N];
// 访问标记
bool vis[MAX_N];

// Dijkstra主方法 O((V+E)logE)
void dijkstra(int s) {
    memset(vis, false, sizeof(vis));
    memset(dis, 0x3F, sizeof(dis));
    std::priority_queue<std::pair<int, int>> que;
    que.emplace(0, s);
    dis[s] = 0;
    while (!que.empty()) {
        auto [d, u] = que.top();
        que.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (!vis[edge[i].to] && dis[edge[i].to] > dis[u] + edge[i].val) {
                dis[edge[i].to] = dis[u] + edge[i].val;
                que.emplace(-dis[edge[i].to], edge[i].to);
            }
    }
}
