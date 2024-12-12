/*---------------------------------------------------------------------------------------------------------
主席树，最简单的版本，求第K小
可持久化线段树：维护的是原版本的离散化数据，类似权值线段树，记忆并存储修改的情况。
1、建树。
2、对着前一个版本插入新版本。
3、进行类似前缀和的查询。
----------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9 + 7;
constexpr int inf = 1e9 + 5;
constexpr int N = 3e5 + 10;
int n,m,k;

struct segTree
{
    int L, R;
    int w;
}t[N * 20];

int idx;
std::vector<int>root;

struct Persistable_Segment_Tree
{
    #define lc(x) t[x].L
    #define rc(x) t[x].R

    //这次建空树。
    void build(int &u, int L, int R)
    {
        u = ++ idx;
        if(L == R)
            return ;
        int M = L + R >> 1;
        build(lc(u), L, M);
        build(rc(u), M + 1, R);
    }

    // 给区间[L, R]个数+1
    void insert(int PreVer, int &NexVer, int L, int R, int v)
    {
        // 更新，区间[L, R]数字个数+1
        NexVer = ++ idx, t[NexVer] = t[PreVer], t[NexVer].w ++;
        if(L == R)
            return ;
        int M = L + R >> 1;
        if(v <= M)
            insert(lc(PreVer), lc(NexVer), L, M, v);
        else
            insert(rc(PreVer), rc(NexVer), M + 1, R, v);
    }

    // 查询，区间[L, R]的第K小。
    // 类似前缀和的一点是，我们需要先把之前的树减去。
    // 返回的是顺序，即第L小的。
    int query(int PreVer, int NexVer, int L, int R, int k)
    {
        if(L == R)
            return L;
        int M = L + R >> 1;
        int sum = t[lc(NexVer)].w - t[lc(PreVer)].w;
        //如果在左子树，直接k
        if(k <= sum)
            return query(lc(PreVer), lc(NexVer), L, M, k);
        else
            return query(rc(PreVer), rc(NexVer), M + 1, R, k - sum);
    }

    #undef lc
    #undef rc
};

void solve()
{
    std::cin >> n >> m;

    // 离散化操作。
    std::vector<int>a(n + 1), b;
    for(int i = 1;i <= n;i ++)
        std::cin >> a[i];

    b = a;
    std::sort(b.begin() + 1, b.end());
    b.erase(std::unique(b.begin() + 1, b.end()), b.end());

    for(int i = 1;i <= n;i ++)
        a[i] = std::lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();

    int len = b.size() - 1;

    // 我们使用n个版本。
    root.assign(n + 1, 0);

    // 树最多探讨的区间是[1, len]
    Persistable_Segment_Tree Tree;
    Tree.build(root[0], 1, len);

    for(int i = 1;i <= n;i ++)
        Tree.insert(root[i - 1], root[i], 1, len, a[i]);

    while(m --)
    {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << b[Tree.query(root[l - 1], root[r], 1, len, k)] << "\n";
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

