// Author：SNRainiar, from SZTU_AtDawn

// Trie树
#define MAX_N 10000
#define MAX_M 26

int top;
int mark[MAX_N];
int trie[MAX_N][MAX_M];

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
bool match(const char s[]) {
	int j = 0;
	for (int i = 0, x; s[i]; ++i) {
		x = s[i] - 'a';
		if (!trie[j][x])
			return false;
		j = trie[j][x];
	}
	return mark[j];
}
