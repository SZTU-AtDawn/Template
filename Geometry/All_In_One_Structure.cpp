// 计算几何多合一结构包
// Author: SNRainiar, from SZTU_AtDawn

const double PI = acos(-1);
const double EPS = 1e-8;

// 二维正矩形
struct Rect {
    double x, y, w, h;
    // 相交测试
    bool intersect(const Rect& tmp) const {
        return !(x > tmp.x + tmp.w || x + w < tmp.x || y > tmp.y + tmp.h || y + h < tmp.y);
    }
    // 点包含测试
    bool contains(double a, double b) const {
        return !(x > a || x + w < a || y > b || y + h < b);
    }
};

// 二维向量
struct Vec2 {
    double x, y;
    // 向量加
    Vec2 operator+(const Vec2& tmp) const {
        return {x + tmp.x, y + tmp.y};
    }
    // 向量反向
    Vec2 operator-() const {
        return {-x, -y};
    }
    // 向量减
    Vec2 operator-(const Vec2& tmp) const {
        return {x - tmp.x, y - tmp.y);
    }
    // 向量数乘
    Vec2 operator*(double tmp) const {
        return {x * tmp, y * tmp};
    }
    // 向量点乘
    double operator*(const Vec2& tmp) const {
        return x * tmp.x + y * tmp.y;
    }
    // 向量数除
    Vec2 operator/(double tmp) const {
        return {x / tmp, y / tmp};
    }
    // 向量叉乘
    double operator^(const Vec2& tmp) const {
        return x * tmp.y - y * tmp.x;
    }
    // 向量模
    double length() const {
        return hypot(x, y);
    }
    // 向量斜率
    double slope() const {
        return y / x;
    }
    // 向量逆时针旋转（弧度）
    Vec2 rotate(double theta) const {
        return {x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta)};
    }
    // 方向单位向量
    Vec2 direction() const {
        return length() < EPS ? *this : *this / length();
    }
    // 法向量
    Vec2 normal() const {
        return direction().rotate(PI / 2);
    }
    // 组合向量叉乘，以当前点为起始点
    double cross(const Vec2& a, const Vec2& b) const {
        return (a - *this) ^ (b - *this);
    }
};

// 二维线段/直线
struct Line {
    Vec2 a, b;
    // 直接点内差
    Vec2 operator()() const {
        return b - a;
    }
    // 线段长度
    double length() const {
        return (b - a).length();
    }
    // 斜率
    double slope() const {
        return (b - a).slope();
    }
    // 直线X截距
    double interceptX() const {
        return (b ^ a) / (a.y - b.y);
    }
    // 直线Y截距
    double interceptY() const {
        return (a ^ b) / (a.x - b.x);
    }
    // 方向向量
    Vec2 direction() const {
        return (b - a).direction();
    }
    // 法向量
    Vec2 normal() const {
        return (b - a).normal();
    }
    // 线段的矩形区域
    Rect area() const {
        return {std::min(a.x, b.x), std::min(a.y, b.y), abs(a.x - b.x), abs(a.y - b.y)};
    }
    // 平行关系检查
    bool parallel(const Line& tmp) const {
        return fabs(*this() ^ tmp()) < EPS;
    }
    // 垂直关系检查
    bool vertical(const Line& tmp) const {
        return fabs(*this() * tmp()) < EPS;
    }
    // 直线相交检查
    bool lineCross(const Line& tmp) const {
        if (!parallel(tmp))
            return true;
        if (fabs(*this().x) < EPS)
            return fabs(*this().x - tmp().x) < EPS;
        return fabs(interceptY() - tmp.interceptY()) < EPS;
    }
    // 线段相交检查
    bool segmentCross(const Line& tmp) const {
        if (!area().intersect(tmp.area()))
            return false;
        double d1 = a.cross(b, tmp.a) * a.cross(b, tmp.b);
        double d2 = tmp.a.cross(tmp.b, a) * tmp.a.cross(tmp.b, b);
        return !(d1 > 0 && d2 > 0);
    }
};
