// Author：SNRainiar, from SZTU_AtDawn

// 回文自动机
#define MAX_N 10000	// 字符串长度
#define MAX_M 26    // 字符集大小
struct PAM {
    // 节点计数
    int top;
    // 自动机节点类型
    struct Node {
        // len：回文串长度；fail：失配指针；nxt[]子节点指针
        int len, fail;
        int nxt[MAX_M];
    } T[MAX_N * MAX_M];
    // 构造函数
    PAM(): top(0) {}
    // 新建节点
    int newNode(int len) {
        T[top].len = len;
        return top++;
    }
    // 获得失配指针
    int getFail(const char s[], int pos, int n) {
        // 如果无法扩展回文串，则走失配指针
        while (s[pos - T[n].len - 1] != s[pos])
            n = T[n].fail;
        return n;
    }
    // 构建
    void build(const char s[]) {
        newNode(0);
        newNode(-1);
        T[0].fail = 1;
        int lst = 0;
        // 以下可以修改成单字符extend的形式
        for (int i = 0, x, now, tmp; s[i]; ++i) {
            x = s[i] - 'a'; // 看情况修改
            // 通过找失配的方法来找现在状态下需要扩展的节点位置
            now = getFail(s, i, lst);
            // 如果找到了未出现的回文串
            if (!T[now].nxt[x]) {
                // 扩展回文串长度
                tmp = newNode(T[now].len + 2);
                T[tmp].fail = T[getFail(s, i, now)].nxt[x];
                T[now].nxt[x] = tmp;
            }
            lst = T[now].nxt[x];
        }
    }
};
