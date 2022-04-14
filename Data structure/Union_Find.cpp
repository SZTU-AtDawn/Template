// 注：log*(n)为迭代对数函数，增长极其缓慢，对应复杂度表达式近似为常数，定义如下：
//      log*(n) = 0             , n <= 1
//      log*(n) = log*(log n)    , n > 1
// 例：log*(2^65536) = 5
// 故一般认为 O(log*(n)) = O(1)

// 并查集 - 快速核心
#define UF_SZ 1000

int fa[UF_SZ + 2];

int init() {
	for (int i = 1; i <= UF_SZ; ++i)
		fa[i] = i;
}
// 路径压缩查找父亲 O(log*(n)) = O(1)
inline int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}
inline bool check(int x, int y) {
	return find(x) == find(y);
}
inline void merge(int x, int y) {
	fa[find(y)] = find(x);
}

// 并查集 - 模板类
struct UnionFind {
	int size;
	int *fa;
	UnionFind(int sz): size(sz), fa(new int[sz + 2]) {}
	~UnionFind() {delete[] fa;}
	int init() {
		for (int i = 1; i <= size; ++i)
			fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}
	bool check(int x, int y) {
		return find(x) == find(y);
	}
	void merge(int x, int y) {
		fa[find(y)] = find(x);
	}
};
