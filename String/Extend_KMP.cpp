// 扩展KMP（Z函数）
#define MAX_N 100000

int Z[MAX_N];	// Z[i]: 模式串 S[0..MAX_N - 1] 与其第i个后缀 S[i..MAX_N - 1] 的最长公共前缀
int ext[MAX_N];	// ext[i]: 模式串 S[0..MAX_N - 1] 与匹配串第i个后缀 T[i..MAX_M - 1] 的最长公共前缀

// 计算Z函数
void getZ(const char s[], int len) {
	Z[0] = len;
	int a = 0, p = 0;
	for (int i = 1; i < len; ++i)
		if (i >= p || i + Z[i - a] >= p) {
			if (i >= p)
				p = i;
			while (p < len && s[p] == s[p - i])
				++p;
			Z[i] = p - i;
			a = i;
		}
		else 
			Z[i] = Z[i - a];
}
// 计算Extend数组
void getExt(const char s1[], int l1, const char s2[], int l2) {
	int a = 0, p = 0;
	getZ(s1, l1);
	for (int i = 0; i < l2; ++i)
		if (i >= p || i + Z[i - a] >= p) {
			if (i >= p)
				p = i;
			while (p < l2 && s2[p] == s1[p - i])
				++p;
			ext[i] = p - i;
			a = i;
		}
		else 
			ext[i] = Z[i - a];
}
