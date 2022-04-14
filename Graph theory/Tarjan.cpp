#include <stack>
#include <algorithm>

// Tarjan算法，用来解决有向图强连通分量、无向图双联通分量、无向图割点与桥、离线LCA问题等
int head[];
struct e {
	int to, nxt;
} edge[];

// 离线LCA，需要用并查集
#define MAX_N 10000
#define MAX_Q 1000

int q[MAX_N][MAX_Q];
int ans[MAX_N][MAX_N];
bool vis[];

void tarjan(int u) {
	// 遍历子节点
	for (int i = head[u]; i; i = edge[i].nxt) {
		tarjan(edge[i].to);
		// 将子节点连到父节点上（可能有并查集方向性问题）
		merge(u, edge[i].to);
	}
	vis[u] = true;
	// 在离线请求中寻找可满足的
	for (int i = 1; i <= q[u][0]; ++i)
		if (vis[q[u][i]])
			ans[u][q[u][i]] = find(q[u][i]);
}

// 无向图割点与桥
#define MAX_N 10000

int top;
int dfn[MAX_N], low[MAX_N];
bool isBridge[], isCut[MAX_N];

void tarjan(int u, int fa) {
	// 更新dfs序和环路最小dfs序
	dfn[u] = low[u] = ++top;
	// 子节点计数，用来判断根节点是否为割点，对其他节点无作用
	int size = 0;
	// 遍历子节点
	for (int i = head[u]; i; i = edge[i].nxt)
		// 如果没有走过
		if (!dfn[edge[i].to]) {
			tarjan(edge[i].to, u);
			// 更新环路最小dfs序
			low[u] = std::min(low[u], low[edge[i].to]);
			// 子节点的环路最小dfs序大于父节点的dfs序，则意味着子节点在父节点之后可能产生了环或者没有成环，所以这条边一定是桥
			if (low[edge[i].to] > dfn[u])
				isBridge[i] = isBridge[i ^ 1] = true;
			// 同理如上，但是需要判断当前节点不是根节点
			if (low[edge[i].to] >= dfn[u] && u != fa)
				isCut[u] = true;
			// 对根节点而言，更新子树数量
			if (u == fa)
				++size;
		}
		// 如果走过且不是父节点，更新环路最小dfs序
		else if (edge[i].to != fa)
			low[u] = std::min(low[u], dfn[edge[i].to]);
	// 如果根节点有超过1个子树，那么根节点一定是割点
	if (size >= 2 && u == fa)
		isCut[u] = true;
}

// 对于无向图的双联通分量，通过把桥从边集中删除，再遍历边用并查集求解

// 有向图强连通分量
#define MAX_N 10000

int top;
int dfn[MAX_N], low[MAX_N], blk[MAX_N];
bool vis[MAX_N], inStk[MAX_N];
std::stack<int> stk;

void tarjan(int u) {
	dfn[u] = low[u] = ++top;
	vis[u] = true;
	stk.emplace(u);
	inStk[u] = true;
	for (int i = head[u]; i; i = edge[i].nxt)
		if (!vis[edge[i].to]) {
			tarjan(edge[i].to);
			low[u] = std::min(low[u], low[edge[i].to]);
		}
		else if (inStk[edge[i].to])
			low[u] = std::min(low[u], dfn[edge[i].to]);
	// 如果该节点是强连通分量的根
	if (dfn[u] == low[u]) {
		while (stk.top() != u) {
			blk[stk.top()] = u;
			inStk[stk.top()] = false;
			stk.pop();
		}
		blk[u] = u;
		inStk[u] = false;
		stk.pop();
	}
}
