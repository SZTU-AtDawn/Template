// 最小费用最大流
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 1000
#define MAX_M 10000

// 流量网络，边的序号应从1开始，使得通过异或运算就可以得到反流边
int head[MAX_N + 5];
struct e {
    int to, f, c, nxt;
} edge[MAX_M];

// 最小费用路径、前驱节点、前驱边
int dis[MAX_N + 5], prv[MAX_N + 5], pre[MAX_N + 5];
// 集合存在标志
bool vis[MAX_N + 5];
// 寻找最小费用増广路（SPFA）
bool spfa(int st, int ed) {
    std::queue<int> que;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[st] = 0;
    que.emplace(st);
    vis[st] = true;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (dis[edge[i].to] > dis[u] + edge[i].c && edge[i].f > 0) {
                dis[edge[i].to] = dis[u] + edge[i].c;
                prv[edge[i].to] = u;
                pre[edge[i].to] = i;
                if (!vis[edge[i].to]) {
                    vis[edge[i].to] = true;
                    que.emplace(edge[i].to);
                }
            }
    }
    return dis[ed] != 0x3f3f3f3f;
}                
// 最小费用最大流主函数
std::pair<int, int> mcmf(int st, int ed) {
    int cost = 0, flow = 0;
    while (spfa(st, ed)) {
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
