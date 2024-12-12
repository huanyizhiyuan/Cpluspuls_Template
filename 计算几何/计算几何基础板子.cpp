#include<bits/stdc++.h>
#define i64 long long
#define int i64
// #define double long double
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e9+5;
constexpr double Pi = std::atan2(0, -1);
constexpr double eps = 1e-12;
int n,m,k;

struct Point
{
    double x, y;

    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    bool operator<(const Point & P) const
    {
        return (x < P.x or (x == P.x and y < P.y));
    }
    Point operator+(const Point & P) const
    {
        return Point(x + P.x, y + P.y);
    }
    Point operator-(const Point & P) const
    {
        return Point(x - P.x, y - P.y);
    }
};

// 向量AB 与 向量 BC 叉积
/*
    > 0：顺时针
    < 0：逆时针
    = 0：共线
*/
// 实际上是向量
double cross(Point A, Point B)
{
    return A.x * B.y - A.y * B.x;
}


double dist(Point A, Point B)
{
    return  sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

// 点P绕着原点逆时针旋转rad角度
Point rotate(Point P, double rad)
{
    auto [x1, y1] = P;
    double x2 = x1 * cos(rad) - y1 * sin(rad);
    double y2 = x1 * sin(rad) + y1 * cos(rad);
    return Point(x2, y2);
}

// 点P绕着点Q逆时针旋转rad角度
Point rotate(Point P, Point Q, double rad)
{
    return Q + rotate(P - Q, rad);
}



void solve()
{
    double a, b, r;
    double ans = 0;

    std::cin >> n;
    std::cin >> a >> b >> r;

    a /= 2, b /= 2;

    ans += Pi * r * 2;

    std::vector<Point>ps(n * 4 + 1);

    for(int i = 1;i <= n;i ++)
    {
        // 圆心坐标(x,y)还有偏转角度z。
        double x, y, z;
        std::cin >> x >> y >> z;

        // x += eps, y += eps, z += eps;

        // 未旋转时的四个角的相对坐标
        std::vector<Point> rect = {
            { b - r, a - r },
            { b - r, r - a },
            { r - b, a - r },
            { r - b, r - a }
        };

        // 旋转矩形的四个顶点
        for (int j = 0; j < 4; j++)
        {
            auto P = rect[j];
            auto Q = Point(x, y);
            ps[(i - 1) * 4 + j + 1] = rotate(P, z) + Q;
        }
    }

    std::sort(ps.begin() + 1, ps.end());

    // vector模拟stack
    std::vector<int>stk;

    for(int i = 1;i <= n * 4;i ++)
    {
        // 至少要有三个元素并且斜率符合要求。（加上当前的就是3个了）
        while(stk.size() >= 2 and cross(ps[stk[stk.size() - 2]] - ps[stk.back()], ps[stk.back()] - ps[i]) <= 0)
            stk.pop_back();
        stk.push_back(i);
    }

    // 防止一条线被卡。
    int t = stk.size();

    for(int i = n * 4 - 1;i >= 1;i --)
    {
        while(stk.size() > t and cross(ps[stk[stk.size() - 2]] - ps[stk.back()], ps[stk.back()] - ps[i]) <= 0)
            stk.pop_back();
        stk.push_back(i);
    }

    for(int i = 0;i < stk.size() - 1;i ++)
        ans += dist(ps[stk[i]], ps[stk[i + 1]]);
    std::cout << std::fixed << std::setprecision(2) << ans << "\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T = 1;
    // std::cin>>T;

    while(T--)
    {
        solve();
    }
    return  0;
}

