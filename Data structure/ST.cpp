// SNRainiar, from SZTU_AtDawn

#include <cmath>
#include <algorithm>

// ST表 - 快速核心
#define ST_T int
#define ST_SZ 1024
#define ST_SZ_LOG 12

int lg2[ST_SZ + 1];
ST_T st[ST_SZ][ST_SZ_LOG]; // st[i][j]: 以i为起点，长度为2^j的区间最大/最小值

// 预处理log2值 O(n)
void init() {
	for (int i = 2; i <= ST_SZ; ++i)
		lg2[i] = lg2[i >> 1] + 1;
}
// 构造 O(nlogn)
void build(ST_T a[]) {
	for (int i = 0; i < ST_SZ; ++i)
		st[i][0] = a[i];
	for (int i = 1; i < ST_SZ_LOG; ++i)
		for (int j = 0; j + (1 << i) - 1 < ST_SZ; ++j)
			// 合并左半边和右半边结果
			st[j][i] = std::max(st[j][i - 1], st[j + (1 << i)][i - 1]);
}
// 查询最值 O(1)
inline ST_T qry(int l, int r) {
	// 求区间长度的log2值
	int k = lg2[r - l + 1];
	// 拆分区间分别取值，再合并答案
	return std::max(st[l][k], st[r - (1 << k) + 1][k]);
}

// ST表 - 模板类
template<class INT_T>
struct ST {
	int size, sizelog;
	int *lg2;
	INT_T **st;
	ST(int sz): 
		size(sz), sizelog(log2(sz) + 2), 
		lg2(new int[sz + 2]), st(new INT_T*[sz + 2]) {
		lg2[1] = 0;
		for (int i = 2; i <= size; ++i)
			lg2[i] = lg2[i >> 1] + 1;
		for (int i = 0; i < size; ++i)
			st[i] = new INT_T[sizelog + 2];
	}
	~ST() {
		for (int i = 0; i < size; ++i)
			delete[] st[i];
		delete[] st;
	}
	void build(INT_T a[]) {
		for (int i = 0; i < ST_SZ; ++i)
		st[i][0] = a[i];
		for (int i = 1; i < ST_SZ_LOG; ++i)
			for (int j = 0; j + (1 << i) - 1 < ST_SZ; ++j)
				st[j][i] = std::max(st[j][i - 1], st[j + (1 << i)][i - 1]);
	}
	INT_T qry(int l, int r) {
		int k = lg2[r - l + 1];
		return std::max(st[l][k], st[r - (1 << k) + 1][k]);
	}
};
