// int N -> 数据量

struct Discrete {
    // 计数器
    int top;
    // 离散数组
    int T[N];
    // 添加数据
    Discrete& append(int x) {
        T[top++] = x;
        return *this;
    }
    // 构造离散化
    void build() {
        std::sort(T, T + top);
        top = std::unique(T, T + top) - T;
    }
    // 获得离散id
    int hash(int x) {
        return std::lower_bound(T, T + top, x) - T;
    }
    // 获得源数据
    int get(int x) {
        return T[x];
    }
};
