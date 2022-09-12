// 序列自动机
// 对于一个序列，查询其是否存在某一个子序列
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100000	// 序列长度
#define MAX_M 26 		// 字符集大小

int next[MAX_N][MAX_M];	// next[i][j]: 从第i个位置开始，下一个字符j的位置

// 生成自动机 O(n)
void build(const char s[]) {
    for (int i = MAX_N - 1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j)
            next[i][j] = next[i + 1][j];
        next[i][s[i] - 'a'] = i;
    }
}
// 子序列查询 O(n)
bool search(const char t[]) {
    for (int i = 0, j = -1; t[i]; ++i) {
        j = next[j + 1][t[i] - 'a'];
        if (j == -1)
            return false;
    }
    return true;
}
