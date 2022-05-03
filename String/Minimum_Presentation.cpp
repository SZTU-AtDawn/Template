// Author：SNRainiar, from SZTU_AtDawn

#include <cstring>

// 最小表示法
// 寻找一个收尾连接字符串的特定位置，使得从该位置开始的字符串是字典序最小的
int minimumPresentation(const char s[]) {
    int i = 0, j = 1, k = 0, t, len = strlen(s);
    while (i < len && j < len && k < len) {
        t = s[(i + k) % len] - s[(j + k) % len];
        // 字典序相同，扩展k
        if (!t)
            ++k;
        else {
            // 起点调整
            if (t > 0)
                i += k + 1;
            else 
                j += k + 1;
            // 错位调整
            if (i == j)
                ++j;
            // 匹配归零
            k = 0;
        }
    }
    return i > j ? j : i;
}
