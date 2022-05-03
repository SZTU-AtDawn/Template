// Author：SNRainiar, from SZTU_AtDawn

#include <cstdio>

// 注：快读不能与其他标准读入方法混用

// 替代getchar()
inline char gc() {
    static char buff[0xFFFF], *p1 = buff, *p2 = buff;
    return p1 == p2 && (p2 = (p1 = buff) + fread(buff, 1, 0xFFFF, stdin), p1 == p2) ? EOF : *p1++;
}

// 读整数，类型可以换成其他整数类型，修改宏定义即可
#define INT_TYPE int
INT_TYPE readInt() {
    INT_TYPE t = 0;
    bool f = true;
    char c = gc();
    while ((c < '0' || c > '9') && c != '-' && c != EOF)
        c = gc();
    if (c == '-') {
        f = false;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        t = t * 10 + c - '0';
        c = gc();
    }
    return f ? t : -t;
}

// 读字符串
int readString(char s[]) {
    int len = 0;
    char c = gc();
    while ((c == ' ' || c == '\n' || c == '\r') && c != EOF)
        c = gc();
    while (c != ' ' && c != '\n' && c != '\r' && c != EOF) {
        s[len++] = c;
        c = gc();
    }
    return s[len] = 0, len;
}

// 读行
int readLine(char s[]) {
    int len = 0;
    char c = gc();
    while ((c == ' ' || c == '\n' || c == '\r') && c != EOF)
        c = gc();
    while (c != '\n' && c != '\r' && c != EOF) {
        s[len++] = c;
        c = gc();
    }
    return s[len] = 0, len;
}
