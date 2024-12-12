#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e9+5;
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

// 实际上是向量
// 向量AB 与 向量 BC 叉积
/*
    > 0：顺时针
    < 0：逆时针
    = 0：共线
*/
double cross(Point A, Point B)
{
    return A.x * B.y - A.y * B.x;
}

double dist(Point A, Point B)
{
    return  sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

void solve()
{
    std::cin >> n;
    std::vector<Point>ps(n + 1);
    for(int i = 1;i <= n;i ++)
    {
        double x, y;
        std::cin >> x >> y;
        ps[i] = {x, y};
    }

    std::sort(ps.begin() + 1, ps.end());

    // vector模拟stack
    std::vector<int>stk;

    for(int i = 1;i <= n;i ++)
    {
        // 至少要有三个元素并且斜率符合要求。（加上当前的就是3个了）
        while(stk.size() >= 2 and cross(ps[stk[stk.size() - 2]] - ps[stk.back()], ps[stk.back()] - ps[i]) <= 0)
            stk.pop_back();
        stk.push_back(i);
    }

    // 防止一条线被卡。
    int t = stk.size();

    for(int i = n - 1;i >= 1;i --)
    {
        while(stk.size() > t and cross(ps[stk[stk.size() - 2]] - ps[stk.back()], ps[stk.back()] - ps[i]) <= 0)
            stk.pop_back();
        stk.push_back(i);
    }

    double ans = 0;
    for(int i = 0;i < stk.size() - 1;i ++)
        ans += dist(ps[stk[i]], ps[stk[i + 1]]);
    std::cout << std::fixed << std::setprecision(2) << ans << "\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T=1;
    // std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}

