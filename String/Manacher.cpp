#include <algorithm>

// Manacher算法
#define MAX_N 10000

int p[MAX_N << 1];		// p[i]: 以i为中心的双倍回文串半径，其中 p[i] - 1 为原回文串长度
char mS[MAX_N << 1];	// 修饰过的字符串

void manacher(const char s[]) {
	// 需要处理偶数长度的回文串，所以需要对原字符串进行修饰，如果只需要奇数长度的回文串，可以不用修饰
	int mLen = 0;
	for (int i = 0; i < MAX_N; ++i) {
		mS[mLen++] = '#';	// 一种没有出现的字符
		mS[mLen++] = s[i];
	}
	mS[mLen++] = '#';
	// Manacher
	int r = -1, c = -1;
	for (int i = 0; i < mLen; ++i) {
		p[i] = (r > i ? std::min(r - i, p[(c << 1) - i]) : 1);
		while (i + p[i] < mLen && i - p[i] >= 0)
			if (mS[i + p[i]] == mS[i - p[i]])
				++p[i];
			else 
				break;
		if (i + p[i] > r) {
			r = i + p[i];
			c = i;
		}
	}
}
