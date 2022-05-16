// 快速傅里叶变换
// Author: SNRainiar from SZTU_AtDawn

// PI
const double PI = acos(-1);

// 二进制倒位
int rev[];
void init(int N, int len) {
    rev[0] = 0;
    for (int i = 1; i < N; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

// 自定义复数类
struct Cpx {
    double re, im;
    Cpx operator+(const Cpx& tmp) const {
        return {re + tmp.re, im + tmp.im};
    }
    Cpx operator-(const Cpx& tmp) const {
        return {re - tmp.re, im - tmp.im};
    }
    Cpx operator*(const Cpx& tmp) const {
        return {re * tmp.re - im * tmp.im, re * tmp.im + im * tmp.re};
    }
    Cpx operator/(double tmp) const {
        return {re / tmp, im / tmp};
    }
};

// FFT主方法
// FFT: op == 1; IFFT: op == -1
void FFT(Cpx io[], int N, int len, int op) {
    init(N, len);
    for (int i = 0; i < N; ++i)
        if (i < rev[i])
            std::swap(io[i], io[rev[i]]);
    for (int i = 1; i < N; i <<= 1) {
        Cpx wn = {cos(PI / i), op * sin(PI / i)};
        for (int j = 0, i2 = (i << 1); j < N; j += i2) {
            Cpx w = {1.0, 0.0};
            for (int k = 0; k < i; ++k, w = w * wn) {
                Cpx x = io[j + k], y = w * io[i + j + k];
                io[j + k] = x + y;
                io[i + j + k] = x - y;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; ++i)
            io[i] = io[i] / N;
}
