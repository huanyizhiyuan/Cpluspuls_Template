/*---------------------------------------------------------------------------------------------------------------
普通并查集：
直接使用 + DSU
-----------------------------------------------------------------------------------------------------------------*/
auto find = [&](auto self, int u) -> int
{
    if(u == pre[u])
        return u;
    return pre[u] = self(self, pre[u]);
};

for(int i = 1;i <= m;i ++)
{
    int x, y;
    std::cin >> x >> y;
    pre[find(find, x)] = find(find, y);
}
/*-------------------------------------------*/
struct DSU
{
    std::vector<int>pre,siz;

    DSU(){}

    DSU(int n):pre(n + 1), siz(n + 1, 1){
        std::iota(pre.begin(), pre.end(), 0);
    }

    int find(int x)
    {
        if(x == pre[x])
            return x;
        return pre[x] = find(pre[x]);
    }

    bool same(int x,int y)
    {
        return find(x) == find(y);
    }

    //按秩合并，把y合成x+判断
    bool rank_merge(int x,int y)
    {
        int fx = find(x), fy = find(y);
        if(fx == fy) return false;
        if(siz[fx] < siz[fy]) std::swap(fx, fy);
        siz[fx] += siz[fy];
        pre[fy] = fx;
        siz[fy] = 0;
        return true;
    }

    //强制合并，把y合成x+判断
    bool merge(int x,int y)
    {
        int fx = find(x), fy = find(y);
        if(fx == fy) return false;
        siz[fx] += siz[fy];
        pre[fy] = fx;
        siz[fy] = 0;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }
};



/*-------------------------------------------------------------------------------------
使用例子：
---------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 998244353;
constexpr int inf = 1e9+5;
constexpr double s2 = std::sqrt(2);
int n,m,k;

int ksm(int a, int b)
{
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

struct DSU
{
    std::vector<int>pre,siz;

    DSU(int n):pre(n + 1), siz(n + 1, 1){
        std::iota(pre.begin(), pre.end(), 0);
    }

    int find(int x)
    {
        if(x == pre[x])
            return x;
        return pre[x] = find(pre[x]);
    }

    bool same(int x,int y)
    {
        return find(x) == find(y);
    }

    //合并，把y合成x+判断
    bool merge(int x,int y)
    {
        x = find(x), y = find(y);
        if(x == y)
            return false;
        siz[x] += siz[y];
        pre[y] = x;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }
};

void solve()
{
    std::cin >> n;
    std::vector<PII>Edge(n + 1);
    for(int i = 1;i < n;i ++)
    {
        int x, y;
        std::cin >> x >> y;
        Edge[i] = {x, y};
    }

    std::vector<std::vector<int>>G(n + 1);
    for(int i = 1;i < n;i ++)
    {
        int x, y;
        std::cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DSU dsu(n + 1);
    int ans = 1;
    bool ok = false; //无法构造。
    for(int i = 1;i < n;i ++)
    {
        auto [u, v] = Edge[i];
        u = dsu.find(u), v = dsu.find(v);
        int l = dsu.size(u);
        int r = dsu.size(v);

        ans = ans * l % mod * r % mod;

        if(G[u].size() < G[v].size())
            std::swap(u, v);

        int cnt = 0;
        for(auto x:G[v])
        {
            if(dsu.find(x) == u)
                cnt ++;
            else
                G[u].push_back(x);
        }

        if(cnt != 1)
        {
            ok = true;
            break;
        }

        dsu.merge(u, v);
    }

    if(ok)
    {
        std::cout << "0\n";
        return ;
    }

    //ans = 1 / (x * y)

    ans = ksm(ans, mod - 2);
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

