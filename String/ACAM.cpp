// AC自动机
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100000
#define MAX_M 26

// 类Trie结构
int top;
int fail[MAX_N], mark[MAX_N];
int trie[MAX_N][MAX_M];

// 插入串
void insert(const char s[]) {
	int j = 0;
	for (int i = 0, x; s[i]; ++i) {
		x = s[i] - 'a';
		if (!trie[j][x])
			trie[j][x] = ++top;
		j = trie[j][x];
	}
	++mark[j];
}
// 构造自动机
void build() {
	std::queue<int> que;
    for (int i = 0; i < 26; ++i)
        if (trie[0][i])
            que.emplace(trie[0][i]);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < 26; ++i)
            if (trie[u][i]) {
                fail[trie[u][i]] = trie[fail[u]][i];
                que.emplace(trie[u][i]);
            }
            else
                trie[u][i] = trie[fail[u]][i];
    }
}
// 匹配串
int match(const char s[]) {
	int rtn = 0, j = 0;
	for (int i = 0, x; s[i]; ++i) {
        x = s[i] - 'a';
        if (trie[j][x])
			j = trie[j][x];
		else 
			j = fail[j];
		if (mark[j])
			++rtn;
    }
	return rtn;
}
