// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 1000
#define MAX_M 10000

// 最小费用最大流
int head[MAX_N + 5];
struct e {
    int to, f, c, nxt;
} edge[MAX_M];

// 寻找最小费用増广路
int dis[MAX_N + 5], pren[MAX_N + 5], pres[MAX_N + 5];
bool vis[MAX_N + 5];
bool spfa(int st, int ed) {
    std::queue<int> que;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[st] = 0;
    pren[st] = pres[st] = -1;
    que.emplace(st);
    vis[st] = true;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (dis[edge[i].to] > dis[u] + edge[i].c && edge[i].f > 0) {
                dis[edge[i].to] = dis[u] + edge[i].c;
                pren[edge[i].to] = u;
                pres[edge[i].to] = i;
                if (!vis[edge[i].to) {
                    vis[edge[i].to] = true;
                    que.emplace(edge[i].to);
                }
            }
    }
    return dis[ed] != 0x3f3f3f3f;
}
                         
// 最小费用最大流
std::pair<int, int> mcmf(int st, int ed) {
    int cost = 0, flow = 0;
    while (spfa(st, ed)) {
        int mn = 0x3f3f3f3f;
        for (int i = pren[ed]; i != st; i = pren[i])
            mn = std::min(mn, edge[pres[i]].f);
        flow += mn;
        cost += mn * dis[ed];
        for (int i = pren[ed]; i != st; i = pren[i]) {
            edge[pres[i]].f -= mn;
            // 反流边
            edge[pres[i] ^ 1].f += mn;
        }
    }
    return {cost, flow};
}
                         
