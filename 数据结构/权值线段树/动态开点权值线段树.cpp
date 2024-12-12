/*-------------------------------------------------------------------------------------------------------------
动态开点权值线段树，可以处理[1,10^9]的数据集。
1、可以处理动态变化的前缀和。
2、可以找第K小。
-------------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e9 + 7;
int n,m,k;

std::vector<int>a;

// 动态开点权值线段树。

struct segTree
{
    int L, R, w; // w 是权值，即出现次数
    int sum; // 多维护一个前缀和
    segTree() : L(0), R(0), w(0), sum(0) {}
}t;

struct Frequency_segment_tree
{
    #define lc(x) t[x].L
    #define rc(x) t[x].R
    #define val(x) t[x].w
    #define s(x) t[x].sum

    int id;
    std::vector<segTree>t;

    // 动态开点不需要build

    Frequency_segment_tree(){}

    Frequency_segment_tree(int size) : id(0){
        t.resize(size << 6);
        t[0] = segTree(); // 初始化 t[0]，所有成员变量为零
    }


    // 在pos处更新 1 or -1，代表增加一个pos或者减少一个pos
    void update(int &u, int L, int R, int p, int x)
    {
        // 给根赋值。
        if(!u) u = ++ id;

        // 出现次数
        val(u) += x;
        s(u) += x * p;

        if(L == R) return ;

        int M = L + R >> 1;

        if(p <= M)
            update(lc(u), L, M, p, x);
        else
            update(rc(u), M + 1, R, p, x);
    }

    // 累加值的次数
    int query(int u, int L, int R, int sum)
    {
        // std::cout << std::format("L = {}, R = {}, u = {}\n", L , R, u);
        if(L == R)
        {
            // 我们会加负数的（代表抵消）
            if(sum <= 0)
                return 0;
            else // 能取多少个pos，不一定可以整除。
                return (sum + L - 1) / L;
        }

        int M = L + R >> 1;

        // 因为我们目前的sum不一定能恰好变成0，所以呢，我们
        // 奔向大的地方，促进我们<=0。
        // 如果奔向小的地方，不一定能把sum消耗完。

        // 只需要右边
        if(sum <= s(rc(u)))
            return query(rc(u), M + 1, R, sum);

        // 左边 + 右边
        return query(lc(u), L, M, sum - s(rc(u))) + val(rc(u));
    }

    #undef s
    #undef val
    #undef lc
    #undef rc
};

void solve()
{
    int q;

    std::cin >> n >> q;

    a.assign(n + 1, 0);

    Frequency_segment_tree Tree(n);

    // 累加值的次数，当前根
    int cnt = 0, root = 0, sum = 0;

    for(int i = 1;i <= n;i ++)
    {
        std::cin >> a[i];
        if(a[i] > 0)
            Tree.update(root, 1, inf, a[i], 1), cnt++;
        sum += a[i];
    }

    while(q --)
    {
        int x, v;
        std::cin >> x >> v;

        // 每次轮回root都会变成1。
        // std::cout << "rt = " << root << "\n";

        if(a[x] > 0)
            Tree.update(root, 1, inf, a[x], -1), cnt--;
        if(v > 0)
            Tree.update(root, 1, inf, v, 1), cnt ++;

        sum = sum - a[x] + v;

        a[x] = v;

        std::cout << cnt - Tree.query(1, 1, inf, sum) + 1 << "\n";
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

