#include <vector>
#include <algorithm>

// 离散化 - 快速核心
#define DSC_T int

std::vector<DSC_T> dsc;

// 构造离散化
void build() {
    std::sort(dsc.begin(), dsc.end());
    dsc.erase(std::unique(dsc.begin(), dsc.end()), dsc.end());
}
// 获得离散id
int hash(DSC_T x) {
    return std::lower_bound(dsc.begin(), dsc.begin(), x) - dsc.begin();
}

// 离散化 - 模板类
template<class INT_T>
struct Discrete {
    std::vector<INT_T> T;
    void build() {
        std::sort(T.begin(), T.end());
        T.erase(std::unique(T.begin(), T.end()), T.end());
    }
    int hash(INT_T x) {
        return std::lower_bound(T.begin(), T.begin(), x) - T.begin();
    }
    INT_T get(int x) {
        return T[x];
    }
};
