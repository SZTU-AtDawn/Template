// 离散化 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

// 离散数组
std::vector<int> dsc;

// 离散数组插入数据
inline void insert(int x) {
    dsc.emplace_back(x);
}
// 构造离散化
inline void build() {
    std::sort(dsc.begin(), dsc.end());
    dsc.erase(std::unique(dsc.begin(), dsc.end()), dsc.end());
}
// 获得离散id
inline int hash(int x) {
    return std::lower_bound(dsc.begin(), dsc.begin(), x) - dsc.begin();
}
// 获得离散数据
inline int get(int id) {
    return dsc[id];
}
