#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e16+5;
int n,m,k;

void solve()
{
    std::cin >> n >> m;

    std::vector<TIII>G;

    for(int i = 1;i <= m;i ++)
    {
        int x, y, z;
        std::cin >> x >> y >> z;
        G.emplace_back(x, y, z);
    }

    // 从小到大。
    std::sort(G.begin(), G.end(), [&](TIII a,TIII b){
        auto [x1, y1, z1] = a;
        auto [x2, y2, z2] = b;
        return z1 < z2;
    });

    //并查集的处理
    std::vector<int>pre(n + 3, 0);
    auto find = [&](auto self, int x) -> int
    {
        if(x == pre[x])
            return x;
        return pre[x] = self(self, pre[x]);
    };

    auto merge = [&](int x,int y) -> bool
    {
        x = find(find, x), y = find(find, y);
        if(x == y)return 0;
        return pre[y] = x; // 其实就是1
    };

    //kruskal函数
    auto kruskal = [&]() -> int
    {
        int res = 0, cnt = 0;
        std::iota(pre.begin(), pre.end(), 0);

        for(auto [u, v, w] : G)
        {
            if(merge(u, v))
                res += w, cnt ++;
        }

        return cnt == n - 1 ? res : inf;
    };

    int ans = kruskal();
    if(ans == inf)
        std::cout << "orz\n";
    else
        std::cout << ans << "\n";
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

