// 自取模整数
// Author: SNRainiar

template<long long MOD>
struct LL {
    long long num;

    LL(long long x = 0): num(x) {
        while (num < 0)
            num += MOD;
    }

    LL operator+(const LL& tmp) const {
        return (num + tmp.num) % MOD;
    }
    LL operator-(const LL& tmp) const {
        return (num - tmp.num + MOD) % MOD;
    }
    LL operator*(const LL& tmp) const {
        return num * tmp.num % MOD;
    }
    LL operator/(const LL& tmp) const {
        return num * tmp.pow(MOD - 2).num % MOD;
    }

    LL operator&(const LL& tmp) const {
        return num & tmp.num;
    }
    LL operator|(const LL& tmp) const {
        return num | tmp.num;
    }
    LL operator~() const {
        return ~num;
    }
    LL operator^(const LL& tmp) const {
        return num ^ tmp.num;
    }

    LL operator<<(const LL& tmp) const {
        return num << tmp.num;
    }
    LL operator>>(const LL& tmp) const {
        return num >> tmp.num;
    }

    bool operator<(const LL& tmp) const {
        return num < tmp.num;
    }
    bool operator==(const LL& tmp) const {
        return num == tmp.num;
    }
    bool operator>(const LL& tmp) const {
        return num > tmp.num;
    }
    bool operator<=(const LL& tmp) const {
        return num <= tmp.num;
    }
    bool operator!=(const LL& tmp) const {
        return num != tmp.num;
    }
    bool operator>=(const LL& tmp) const {
        return num >= tmp.num;
    }

    LL& operator+=(const LL& tmp) {
        (num += tmp.num) %= MOD;
        return *this;
    }
    LL& operator-=(const LL& tmp) {
        ((num -= tmp.num) += MOD) %= MOD;
        return *this;
    }
    LL& operator*=(const LL& tmp) {
        (num *= tmp.num) %= MOD;
        return *this;
    }
    LL& operator/=(const LL& tmp) {
        (num *= tmp.pow(MOD - 2).num) %= MOD;
        return *this;
    }

    LL& operator&=(const LL& tmp) {
        num &= tmp.num;
        return *this;
    }
    LL& operator|=(const LL& tmp) {
        num |= tmp.num;
        return *this;
    }
    LL& operator^=(const LL& tmp) {
        num ^= tmp.num;
        return *this;
    }

    LL& operator<<=(const LL& tmp) {
        num <<= tmp.num;
        return *this;
    }
    LL& operator>>=(const LL& tmp) {
        num >>= tmp.num;
        return *this;
    }

    long long* operator&() {
        return &num;
    }

    LL pow(LL b) const {
        LL a = num, r = 1;
        while (b != 0) {
            if ((b & 1) != 0)
                r *= a;
            a *= a;
            b >>= 1;
        }
        return r;
    }
};
