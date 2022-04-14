// 树状数组 - 快速核心
#define BIT_T int
#define BIT_SZ 1000

BIT_T bit[BIT_SZ];

inline int lowbit(int x) {
	return x & -x;
}
void upd(int p, BIT_T x) {
	while (p <= BIT_SZ) {
		bit[p] += x;
		p += lowbit(p);
	}
}
BIT_T sum(int p) {
	BIT_T rtn = 0;
	while (p) {
		rtn += bit[p];
		p -= lowbit(p);
	}
	return rtn;
}

// 树状数组 - 模板类
template<class INT_T>
struct BIT {
	int size;
	INT_T *tr;
	INT_T(int sz): size(sz), tr(new INT_T[sz + 5]) {}
	~INT_T() {delete[] tr;}
	int lowbit(int x) {
		return x & -x;
	}
	void upd(int p, INT_T x) {
		while (p <= size) {
			tr[p] += x;
			p += lowbit(p);
		}
	}
	INT_T sum(int p) {
		INT_T rtn = 0;
		while (p) {
			rtn += tr[p];
			p -= lowbit(p);
		}
		return rtn;
	}
};
