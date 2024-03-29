// Floyd 算法 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100

// 邻接矩阵
int g[MAX_N + 5][MAX_N + 5];

// k必须在外层
void floyd() {
    for (int k = 1; k <= MAX_N; ++k)
        for (int i = 1; i <= MAX_N; ++i)
            for (int j = 1; j <= MAX_N; ++j)
                g[i][j] = std::min(g[i][j], g[i][k] +g[k][j]);
}
