// Dijkstra
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100000
#define MAX_M 1000000

// 图结构
int head[MAX_N];
struct e {
    int to, val, nxt;
} edge[MAX_M];
// 最短路
int dis[MAX_N];
// 访问标记
bool vis[MAX_N];

// Dijkstra主方法
void dijkstra() {
    memset(vis, false, sizeof(vis));
    std::priority_queue<std::pair<int, int>> que;
    memset(dis, 0x3F, sizeof(dis));
    que.emplace(0, 1);
    dis[1] = 0;
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
