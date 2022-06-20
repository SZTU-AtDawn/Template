// 基于SPFA的最小费用最大流
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 1000
#define MAX_M 10000
#define INF 0x3f3f3f3f

// 流量网络，边的序号应从1开始，使得通过异或运算就可以得到反流边
int head[MAX_N];
struct e {
    int to, f, c, nxt;
} edge[MAX_M];

// 最小费用路径、前驱节点、前驱边
int dis[MAX_N], prv[MAX_N], pre[MAX_N];
// 集合存在标志
bool vis[MAX_N];
// 寻找最小费用増广路（SPFA）
bool spfa(int st, int ed) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    std::queue<int> que;
    dis[st] = 0;
    vis[st] = true;
    que.emplace(st);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (edge[i].f && dis[edge[i].to] > dis[u] + edge[i].c) {
                dis[edge[i].to] = dis[u] + edge[i].c;
                prv[edge[i].to] = u;
                pre[edge[i].to] = i;
                if (!vis[edge[i].to]) {
                    vis[edge[i].to] = true;
                    que.emplace(edge[i].to);
                }
            }
    }
    return dis[ed] != INF;
}
// SPFA_EK主函数 O(V^2 E^2)，实际情况远小于理论时间复杂度
std::pair<int, int> mcmf(int st, int ed) {
    int cost = 0, flow = 0;
    while (spfa(st, ed)) {
        int mn = INF;
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
