/*---------------------------------------------------------------------------------------------------------
主席树，最简单的版本。
可持久化线段树：维护的是原版本的数值，记忆并存储修改的情况。
1、建树。
2、对着前一个版本插入新版本。
3、输出。
----------------------------------------------------------------------------------------------------------*/

#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9 + 7;
constexpr int inf = 1e9 + 5;
constexpr int N = 1e6 + 1000;
int n,m,k;

std::vector<int>root;
std::vector<int>a;

struct segTree
{
    int L, R;
    int w;
}t[N * 23];

int idx = 0;

struct Persistable_Segment_Tree
{
    #define lc(x) t[x].L
    #define rc(x) t[x].R

    // 1、建空树
    // 给u引用，是为了每次改变它的结点编号。
    // Tree.build(root[0],1,n);
    void build(int &u,int L,int R)
    {
        u = ++ idx;
        if(L == R)
        {
            t[u].w = a[L];
            return ;
        }
        int M = L + R >> 1;
        build(lc(u), L, M);
        build(rc(u), M + 1, R);
    }

    // 2、插入新版本结点，时间复杂度O(logn)
    // 把前一版本的值找到，再此版本的基础上增加现在这个版本的值。
    // 每一次建树都在新的版本上建树。

    void insert(int PreVer, int &NexVer, int L, int R, int x, int y)
    {
        NexVer = ++ idx, t[NexVer] = t[PreVer];
        if(L == R)
        {
            t[NexVer].w = y;
            return ;
        }
        int M = L + R >> 1;
        if(x <= M)
            insert(lc(PreVer), lc(NexVer), L, M, x, y);
        else
            insert(rc(PreVer), rc(NexVer), M + 1, R, x, y);
    }

    // 3、查询：主席树上查询版本ver的第i个位置。
    int query(int ver, int L, int R, int x)
    {
        if(L == R)
            return t[ver].w;
        int M = L + R >> 1;
        if(x <= M)
            return query(lc(ver), L, M, x);
        else
            return query(rc(ver), M + 1, R, x);
    }

    #undef lc
    #undef rc
};

void solve()
{
    std::cin >> n >> m;

    a.assign(n + 100, 0);
    root.assign(m + 100, 0);
    for(int i = 1;i <= n;i ++)
        std::cin >> a[i];

    Persistable_Segment_Tree Tree;

    // 最开始的版本是版本0。
    Tree.build(root[0], 1, n);

    for(int i = 1;i <= m;i ++)
    {
        int version, opt, x, y;
        std::cin >> version >> opt >> x;
        if(opt == 1)
        {
            std::cin >> y;
            Tree.insert(root[version], root[i], 1, n, x, y);
        }
        else
        {
            std::cout << Tree.query(root[version], 1, n, x) << "\n";
            root[i] = root[version];
        }
    }
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

