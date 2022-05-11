// ST表 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100000
#define MAX_N_LOG 17
// log2表
int lg2[MAX_N + 5];
// st[i][j]: 以i为起点，长度为2^j的区间最值
int st[MAX_N + 5][MAX_N_LOG + 5];

// 最大/最小函数
inline int mxmn(int x, int y) {
	return std::max(x, y);
	// return std::min(x, y);
}
// 预处理log2表
void init() {
	for (int i = 2; i <= MAX_N; ++i)
		lg2[i] = lg2[i >> 1] + 1;
}
// 构造 O(nlogn)
void build(int a[]) {
	for (int i = 0; i < MAX_N; ++i)
		st[i][0] = a[i];
	for (int j = 1; j <= MAX_N_LOG; ++j)
		for (int i = 0; i + (1 << j) - 1 < MAX_N; ++i)
			// 合并左半边和右半边结果
			st[i][j] = mxmn(st[i][j - 1], st[i + (1 << j)][j - 1]);
}
// 查询最值
inline int query(int l, int r) {
	// 求区间长度的log2值
	int k = lg2[r - l + 1];
	// 拆分区间分别取值，再合并答案
	return mxmn(st[l][k], st[r - (1 << k) + 1][k]);
}
