#include<bits/stdc++.h>
#define i64 long long
// #define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e9+5;
int n,m,k;

// 权值
std::vector<int> w;
// std::vector<PII> prt;
std::vector<std::vector<int>> G;

struct segment_tree
{
    #define ls u << 1
    #define rs u << 1 | 1

    std::vector<int>c, mx, lzy;

    segment_tree(){}

    segment_tree(int size) : c(size << 2, 0), mx(size << 2, 0),
        lzy(size << 2, 0){}

    // 合并
    void pushup(const int u)
    {
        c[u] = c[ls] + c[rs];
        mx[u] = std::max(mx[ls], mx[rs]);
    }

    void pushdown(const int u, int L, int R)
    {
        if(lzy[u])
        {
            int M = L + R >> 1;
            // 更新懒标记。
            lzy[ls] += lzy[u];
            lzy[rs] += lzy[u];
            // 应用懒标记。
            c[ls] = c[ls] + lzy[u] * (M - L + 1);
            c[rs] = c[rs] + lzy[u] * (R - M);
            mx[ls] += lzy[u];
            mx[rs] += lzy[u];
            // 清除当前结点的懒标记。
            lzy[u] = 0;
        }
    }

    // 1、构建(做相应的修改)
    void build(const int u, int L, int R, const std::vector<int>& rank)
    {
        //到达叶结点
        if(L == R)
        {
            c[u] = mx[u] = w[rank[L]];
            // prt[rank[L]]= {c[u], mx[u]};
            // std::cout << std::format("L = {}, u = {}, c[u] = {}, mx[u] = {}\n", rank[L], u, c[u], mx[u]);
            return ;
        }
        int M = L + R >> 1;
        build(ls, L, M, rank);
        build(rs, M + 1, R, rank);
        pushup(u);
    }

    // 2、区间查询极值
    int queryMax(int u, int L, int R, int l, int r)
    {
        if(l <= L and R <= r)
            return mx[u];

        if(l > R or r < L)
            return -inf;    // 极值

        int M = L + R >> 1;
        pushdown(u, L, R);
        return std::max(queryMax(ls, L, M, l, r), queryMax(rs, M + 1, R, l, r));
    }

    // 3、区间查询和
    int querySum(int u, int L, int R, int l, int r)
    {
        if(l <= L and R <= r)
            return c[u];

        if(l > R or r < L)
            return 0;    // 极值

        int M = L + R >> 1;
        pushdown(u, L, R);
        return querySum(ls, L, M, l, r) + querySum(rs, M + 1, R, l, r);
    }

    // 4、单点修改：
    void update1(int u, int L, int R, int p, int x)
    {
        if(L == R)
        {
            mx[u] = c[u] = x;
            return ;
        }

        int M = L + R >> 1;
        pushdown(u, L, R);
        if(p <= M)
            update1(ls, L, M, p, x);
        else
            update1(rs, M + 1, R, p, x);
        pushup(u);
    }

    // 5、区间修改：
    void update(int u, int L, int R, int l, int r, int x)
    {
        if(l <= L and r >= R)
        {
            lzy[u] += x;
            c[u] = c[u] + x * (R - L + 1);
            mx[u] += x;
            return ;
        }

        if(l > R or r < L) return ;

        int M = L + R >> 1;
        pushdown(u, L, R);
        update(ls, L, M, l, r, x);
        update(rs, M + 1, R, l, r, x);
        pushup(u);
    }

    #undef ls
    #undef rs
};

/*----------------------------------------
进行三大操作：
1、修改值。
2、查询区间和。
3、查询极值。
----------------------------------------*/
struct Hchain_decomposition
{
    // top:链头， rnk:DFN序对应的树的结点。
    int id;
    std::vector<int> dep, sz, fa, hson, top, dfn, rdfn, rnk;

    Hchain_decomposition(){}

    Hchain_decomposition(int size) : dep(size + 1, 0), sz(size + 1, 0), fa(size + 1, 0),
        hson(size + 1, -1), top(size + 1, 0), dfn(size + 1, 0), rnk(size + 1, 0),
        rdfn(size + 1, 0){
            id = 0;
        }

    Hchain_decomposition(int size, int st) : dep(size + 1, 0), sz(size + 1, 0), fa(size + 1, 0),
        hson(size + 1, -1), top(size + 1, 0), dfn(size + 1, 0), rnk(size + 1, 0),
        rdfn(size + 1, 0){
            id = 0;
            top[st] = st;
        }

    void dfs1(int u, int d = 1)
    {
        dep[u] = d;     // 子树高度
        hson[u] = -1;   // 重子结点编号。
        sz[u] = 1;
        for(auto v : G[u])
        {
            if(!dep[v])
            {
                fa[v] = u;
                dfs1(v, d + 1);
                sz[u] += sz[v];
                if(hson[u] == -1 or sz[v] > sz[hson[u]]) hson[u] = v;
            }
        }
    }

    // 需要先把根节点的top初始化为自身
    // top[st] = st;
    // 如果自己是重儿子，那就找到链头，如果自己不是重儿子，那就新开链（轻儿子开链）
    void dfs2(int u, int t)
    {
        top[u] = t;
        dfn[u] = ++id;
        rnk[id] = u;
        if(hson[u] == -1)
        {
            rdfn[u] = id;
            return ;
        }
        dfs2(hson[u], t);
        for(auto v : G[u])
        {
            if(v != hson[u] and v != fa[u])
                dfs2(v, v);
        }
        rdfn[u] = id;
    }

    int LCA(int a, int b)
    {
        while(top[a] != top[b])
        {
            if(dep[top[a]] >= dep[top[b]])
                a = fa[top[a]];
            else
                b = fa[top[b]];
        }
        return (dep[a] > dep[b] ? b : a);
    }

    int queryPathMax(int x, int y, segment_tree & Tree)
    {
        int ans = -inf, fx = top[x], fy = top[y];
        // 两个点不在一条链上。
        while(fx != fy)
        {
            // x 更新为top的fa，跳到新的重链上。
            if(dep[fx] >= dep[fy])
            {
                ans = std::max(ans, Tree.queryMax(1, 1, n, dfn[fx], dfn[x]));
                x = fa[fx];
            }
            else
            {
                ans = std::max(ans, Tree.queryMax(1, 1, n, dfn[fy], dfn[y]));
                y = fa[fy];
            }
            // 继续找所在链的top
            fx = top[x];
            fy = top[y];
        }

        // 已经跳到同一条链上，但是两个点，有前后关系。
        if(dfn[x] < dfn[y])
            ans = std::max(ans, Tree.queryMax(1, 1, n, dfn[x], dfn[y]));
        else
            ans = std::max(ans, Tree.queryMax(1, 1, n, dfn[y], dfn[x]));

        return ans;
    }

    int queryPathSum(int x, int y, segment_tree & Tree)
    {
        int ans = 0, fx = top[x], fy = top[y];
        // 两个点不在一条链上。
        while(fx != fy)
        {
            // x 更新为top的fa，跳到新的重链上。
            if(dep[fx] >= dep[fy])
            {
                ans += Tree.querySum(1, 1, n, dfn[fx], dfn[x]);
                x = fa[fx];
            }
            else
            {
                ans += Tree.querySum(1, 1, n, dfn[fy], dfn[y]);
                y = fa[fy];
            }
            // 继续找所在链的top
            fx = top[x];
            fy = top[y];
        }

        // 已经跳到同一条链上，但是两个点，有前后关系。
        if(dfn[x] < dfn[y])
            ans += Tree.querySum(1, 1, n, dfn[x], dfn[y]);
        else
            ans += Tree.querySum(1, 1, n, dfn[y], dfn[x]);

        return ans;
    }

    int querySubtreeMax(int x, segment_tree & Tree)
    {
        return Tree.queryMax(1, 1, n, dfn[x], rdfn[x]);
    }

    int querySubtreeSum(int x, segment_tree & Tree)
    {
        return Tree.querySum(1, 1, n, dfn[x], rdfn[x]);
    }

    void updatePath(int x, int y, int z, segment_tree & Tree)
    {
        int fx = top[x], fy = top[y];

        while(fx != fy)
        {
            if(dep[fx] >= dep[fy])
            {
                Tree.update(1, 1, n, dfn[fx], dfn[x], z);
                x = fa[fx];
            }
            else
            {
                Tree.update(1, 1, n, dfn[fy], dfn[y], z);
                y = fa[fy];
            }
            // 继续找所在链的top
            fx = top[x];
            fy = top[y];
        }

        if(dep[x] >= dep[y])
            Tree.update(1, 1, n, dfn[y], dfn[x], z);
        else
            Tree.update(1, 1, n, dfn[x], dfn[y], z);
    }

    void updateSubtree(int x, int z, segment_tree & Tree)
    {
        Tree.update(1, 1, n, dfn[x], rdfn[x], z);
    }

    void update1(int x, int z, segment_tree & Tree)
    {
        Tree.update1(1, 1, n, dfn[x], z);
    }
};

void solve()
{
    int st = 1;
    std::cin >> n >> m;

    // prt.assign(n + 1, {0, 0});
    w.assign(n + 1, 0);
    G.assign(n + 1, {});

    for (int i = 1; i <= n; i ++)
        std::cin >> w[i];

    for(int i = 1;i < n;i ++)
    {
        int x, y;
        std::cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    Hchain_decomposition HCD(n, st);

    HCD.dfs1(st);

    HCD.dfs2(st, st);

    segment_tree Tree(n + 1);

    Tree.build(1, 1, n, HCD.rnk);

    while(m --)
    {
        int op;
        std::cin >> op;
        if(op == 1)
        {
            int x, y, z;
            std::cin >> x >> y >> z;
            HCD.updatePath(x, y, z, Tree);
        }
        else if(op == 2)
        {
            int x, y;
            std::cin >> x >> y;
            std::cout << HCD.queryPathSum(x, y, Tree) << "\n";
        }
        else if(op == 3)
        {
            int x, z;
            std::cin >> x >> z;
            HCD.updateSubtree(x, z, Tree);
        }
        else
        {
            int x;
            std::cin >> x;
            std::cout << HCD.querySubtreeSum(x, Tree) << "\n";
        }

        // for (int i = 1; i <= n; i ++)
        //     std::cout << "i = " << i << ", " << prt[i].first << " " << prt[i].second << "\n";
    }

    // 7 3 7 8 0
    // 7 3 7 10 0
    // 9 5 9 12 2
    // 12 5 9 12 5
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

