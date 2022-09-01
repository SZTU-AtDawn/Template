// KMP 自动机
// Author: SNRainiar

// KMP 自动机类似于单串形式的 AC 自动机，与一般 KMP 算法不同，这是是严格 O(n) 时间复杂度的，常用于卡 KMP 算法均摊 O(n) 的题目中
// KMP 自动机每个节点的 fail 指针等同于 KMP 算法的 next 数组

#define MAX_LEN 1000000
#define CHARSET_SIZE 26

struct KAM {
    struct Node {
        int fail;
        int next[CHARSET_SIZE];
    } T[MAX_LEN];
    int top;
    
    KAM(): top(0) {}
    
    void insert(int x) {
        for (int i = 0; i < CHARSET_SIZE; ++i)
            if (x == i)
                T[top].next[i] = top + 1;
            else 
                T[top].next[i] = T[T[top].fail].next[i];
        T[top + 1].fail = (top ? T[T[top].fail].next[x] : 0);
        ++top;
    }
};
