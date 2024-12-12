/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int sq;

struct MO
{
    int l, r, id;

    // 构造函数初始化 l, r, id
    MO(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {}

    // 重载 < 运算符，奇偶化排序。
    bool operator<(const MO & o) const
    {
        // 这里只需要知道每个元素归属哪个块，而块的大小都是sqrt(n)，所以可以直接用l / sq
        if(l / sq != o.l / sq)
            return l < o.l;
        if(l / sq & 1)
            return r < o.r;
        return r > o.r;
    }
};

std::vector<MO>query(m + 1);
std::vector<int>ans(m + 1, 0);

for(int i = 1;i <= m;i ++)
{
    int l, r;
    std::cin >> l >> r;
    query[i] = {l, r, i};
}

std::sort(query.begin() + 1, query.end());

int left = 1, right = 0, res = 0;

auto add = [&](int p)
{
    if(vis[a[p]] == 0)
        res ++;
    vis[a[p]] ++;
};

auto del = [&](int p)
{
    vis[a[p]] --;
    if(vis[a[p]] == 0)
        res --;
};
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
完整版基础莫队。
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e9+5;
int n,m,k;

int sq;

struct MO
{
    int l, r, id;

    // 构造函数初始化 l, r, id
    MO(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {}

    // 重载 < 运算符，奇偶化排序。
    bool operator<(const MO & o) const
    {
        // 这里只需要知道每个元素归属哪个块，而块的大小都是sqrt(n)，所以可以直接用l / sq
        if(l / sq != o.l / sq)
            return l < o.l;
        if(l / sq & 1)
            return r < o.r;
        return r > o.r;
    }
};

void solve()
{
    std::cin >> n;

    sq = sqrt(n);

    std::vector<int>a(n + 1, 0);
    std::vector<int>vis(1000005, 0);

    for(int i = 1;i <= n;i ++)
        std::cin >> a[i];

    std::cin >> m;

    std::vector<MO>query(m + 1);
    std::vector<int>ans(m + 1, 0);

    for(int i = 1;i <= m;i ++)
    {
        int l, r;
        std::cin >> l >> r;
        query[i] = {l, r, i};
    }

    std::sort(query.begin() + 1, query.end());

    int left = 1, right = 0, res = 0;

    auto add = [&](int p)
    {
        if(vis[a[p]] == 0)
            res ++;
        vis[a[p]] ++;
    };

    auto del = [&](int p)
    {
        vis[a[p]] --;
        if(vis[a[p]] == 0)
            res --;
    };

    for(int i = 1;i <= m;i ++)
    {
        auto [l, r, id] = query[i];

        while(left > l)
            add(-- left);
        while(right < r)
            add(++ right);
        while(left < l)
            del(left ++);
        while(right > r)
            del(right --);

        ans[id] = res;
    }

    for(int i = 1;i <= m;i ++)
        std::cout << ans[i] << "\n";
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

