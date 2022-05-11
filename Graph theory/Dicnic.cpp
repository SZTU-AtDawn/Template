// Dicnic算法本质上是优化的EK算法 O(V^2E)，适合稠密图
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 10000
#define INF 0x3f3f3f3f

// 流量网络
int head[];
struct e {
    int to, f, nxt;
} edge[];

// 深度、当前弧
int dep[MAX_N], cur[MAX_N];
// 生成分层图
bool bfs(int s, int t) {
    memset(dep, 0, sizeof(dep));
    memcpy(cur, head, sizeof(cur));
    std::queue<int> que;
    que.emplace(s);
    dep[s] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = edge[i].nxt)
            if (!dep[edge[i].to] && edge[i].f > 0) {
                dep[edge[i].to] = dep[u] + 1;
                que.emplace(edge[i].to);
            }
    }
    return dep[t] > 0;
}
// 修改流量，使用当前弧优化
int dfs(int u, int t, int f) {
    if (!f || u == t)
        return f;
    int flow = 0;
    for (int i = cur[u]; i; i = edge[i].nxt) {
        cur[u] = i;
        if (dep[edge[i].to] == dep[u] + 1 && edge[i].f > 0) {
            int tmp = dfs(edge[i].to, t, std::min(f, edge[i].f));
            if (!tmp)
                continue;
            edge[i].f -= tmp;
            edge[i ^ 1].f += tmp;
            flow += tmp;
            f -= tmp;
            if (!f)
                break;
        }
    }
    return flow;
}
// Dicnic主方法
int dicnic(int s, int t) {
    int ans = 0;
    while (bfs(s, t))
        ans += dfs(s, t, INF);
    return ans;
}
