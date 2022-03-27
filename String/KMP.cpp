// KMP需要先预处理next数组，再用于匹配

// 无优化版本的getNext
// 注：getNext函数是用来处理**模式串**的
void getNext(const char pat[], int next[]) {
    next[0] = -1;
    for (int i = 0, j = -1; pat[i];)
        if(j == -1 || pat[i] == pat[j]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else 
            j = next[j];
}

// 优化版getNext
// 注：优化版的getNext仅能用来解决**字符串匹配**问题，其他的诸如循环节等问题就不行了
void getNextOptimized(const char pat[], int next[]) {
    next[0] = -1;
    for (int i = 0, j = -1; pat[i];)
        if (j == -1 || pat[i] == pat[j]) {
            ++i;
            ++j;
            if (pat[i] == pat[j])
                next[i] = next[j];
            else 
                next[i] = j;
        }
        else 
            j = next[j];
}

// 匹配函数，返回第一次匹配位置，可以修改实现多重匹配
int match(const char str[], const char pat[], const int next[]) {
    for (int i = 0, j = 0; str[i];)
        if (j == -1 || str[i] == pat[j]) {
            ++i;
            ++j;
            // 找到一个匹配，返回匹配起始位置
            if (!pat[j])
                return i - M;
        }
        else 
            j = next[j];
    // 无匹配返回-1
    return -1;
}

// 扩展知识点：
// 一个字符串的最短可能循环节长度为 len - next[len] ，len为字符串长度
// 当且仅当 len % (len - next[len]) == 0 且 next[len] != 0 时，该字符串完全由2个及以上循环节组成
