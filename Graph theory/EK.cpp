// Author：SNRainiar, from SZTU_AtDawn

#include <cstring>

#include <queue>

// EK最大流算法 O(VE^2) ，适合稀疏图
int head[];
struct e {
    int to, f, nxt;
} edge[];

// 找增广路径，EK算法每次只找一条最短的增广路
#define MAX_N 10000
#define INF 0x3f3f3f3f

int pre[MAX_N], dis[MAX_N], pth[MAX_N];

int bfs(int s, int t) {
    memset(pre, -1, sizeof(pre));
    std::queue<int> que;
    que.emplace(s);
    dis[s] = INF;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == t)
            break;
        for (int i = head[u]; i; i = edge[i].nxt)
            if (pre[edge[i].to] == -1 && edge[i].f > 0) {
                pre[edge[i].to] = u;
                pth[edge[i].to] = i;
                dis[edge[i].to] = std::min(dis[u], edge[i].f);
                que.emplace(edge[i].to);
            }
    }
    return pre[t] == -1 ? -1 : dis[t];
}

int EK(int s, int t) {
    int ans = 0;
    while (true) {
        int f = bfs(s, t);
        if (f == -1)
            break;
        for (int i = t; i != s; i = pre[i]) {
            edge[pth[i]].f -= f;
            edge[pth[i] ^ 1].f += f;
        }
        ans += f;
    }
    return ans;
}
