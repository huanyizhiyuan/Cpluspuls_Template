#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int, int>;
using TIII = std::tuple<int, int, int>;
constexpr int mod = 1e9 + 7;
constexpr int inf = 1e16 + 5;
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

    std::vector<int>dep(n + 1, 0);
    std::vector<int>cur(n + 1, 0);


    auto bfs = [&]() -> bool
    {
        dep.assign(n + 1, -1);
        cur.assign(n + 1, 0);

        std::queue<int>q;
        q.push(st);

        dep[st] = 0;

        while(!q.empty())
        {
            auto u = q.front();q.pop();
            for(auto [v, w, id] : G[u])
            {
                if(dep[v] == -1 and w)
                {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }

        return dep[en] != -1;
    };

    auto dfs = [&](auto self, int u, int limit) -> int
    {
        if(u == en) return limit;

        for(int i = cur[u];i < G[u].size();i ++)
        {
            // 当前弧优化
            cur[u] = i;
            auto &[v1, w1, id1] = G[u][i];
            auto &[v2, w2, id2] = G[v1][id1];
            if(dep[v1] == dep[u] + 1 and w1)
            {
                int res = self(self, v1, std::min(w1, limit));
                if(res)
                {
                    w1 -= res;
                    w2 += res;
                    return res;
                }
                else
                    dep[v1] = -1;
            }
        }

        return 0;
    };

    int ans = 0;

    auto Dinic = [&]() -> void
    {
        int flow;
        while(bfs())
            while(flow = dfs(dfs, st, inf))
                ans += flow;
    };

    Dinic();

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

