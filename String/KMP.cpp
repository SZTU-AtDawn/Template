// const char* a[] -> 匹配串
// const char* b[] -> 模式串
// int next[] -> Next数组
// N -> 匹配串长度
// M -> 模式串长度

// 无优化版本的getNext
// 注：getNext函数是用来处理**模式串**的
void getNext() {
    next[0] = -1;
    for (int i = 0, j = -1; i < M;)
        if(j == -1 || b[i] == b[j]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else 
            j = next[j];
}

// 优化版getNext
// 注：优化版的getNext仅能用来解决**字符串匹配**问题，其他的诸如循环节等问题就不行了
void getNextOptimized() {
    next[0] = -1;
    for (int i = 0, j = -1; i < M;)
        if (j == -1 || b[i] == b[j]) {
            ++i;
            ++j;
            if (b[i] == b[j])
                next[i] = next[j];
            else 
                next[i] = j;
        }
        else 
            j = next[j];
}

// 匹配函数，返回第一次匹配位置，可以修改实现多重匹配
int match() {
    for (int i = 0, j = 0; i < N;)
        if (j == -1 || a[i] == b[j]) {
            ++i;
            ++j;
            // 找到一个匹配，返回匹配起始位置
            if (j == M)
                return i - M;
        }
        else 
            j = next[j];
    // 无匹配返回-1
    return -1;
}
