#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int, int>;
using TIII = std::tuple<int, int, int>;
constexpr int mod = 1e9 + 7;
constexpr int inf = 1e9 + 5;
int n, m, k;

void solve()
{
    int st, en;
    std::cin >> n >> m >> st >> en;

    // tuple 存 end, val, id, id代表反向边的位置号。
    std::vector<std::vector<TIII>>G(n + 1);

    for (int i = 1; i <= m; i ++)
    {
        int x, y, z;
        std::cin >> x >> y >> z;
        int id1 = G[x].size();
        int id2 = G[y].size();
        // 反向边先给0
        G[x].emplace_back(y, z, id2);
        G[y].emplace_back(x, 0, id1);
    }

    int ans = 0;
    // 距离， 从哪个点来的， 边的序号。
    std::vector<int>dis(n + 1, 0);
    std::vector<int>lst(n + 1, 0);
    std::vector<int>pre(n + 1, 0);

    auto bfs = [&]()
    {
        std::queue<int>q;
        std::vector<bool>vis(n + 1, 0);

        q.push(st);

        vis[st] = true;
        dis[st] = inf;

        while (!q.empty())
        {
            auto u = q.front(); q.pop();
            for (int i = 0; i < G[u].size(); i ++)
            {
                auto [v, w, id] = G[u][i];
                if (!vis[v] and w)
                {
                    vis[v] = true;
                    dis[v] = std::min(dis[u], w);

                    // # lst 记录当前这个点是从第几个点跳过来的
                    // # pre 记录当前这个点是从第几条边跳过来的（序号id）
                    lst[v] = u;
                    pre[v] = i;

                    if (v == en)
                        return true;

                    q.push(v);
                }
            }
        }
        return false;
    };

    auto EK = [&]() -> void
    {
        while (bfs())
        {
            ans += dis[en];
            for (int i = en; i != st; i = lst[i])
            {
                // 从 lst[i] 沿着 pre[i] 跳到 i 的边是正向边
                // 从 i 沿着 e[lst[i]][pre[i]].id 跳回 lst[i] 的边是反向边
                auto &[v1, w1, id1] = G[lst[i]][pre[i]];
                auto &[v2, w2, id2] = G[i][id1];

                w1 -= dis[en];
                w2 += dis[en];
            }
        }
    };

    EK();

    std::cout << ans << "\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T = 1;
    // std::cin>>T;
    while (T--)
    {
        solve();
    }
    return  0;
}

