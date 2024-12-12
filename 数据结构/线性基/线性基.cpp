#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 998244353;
constexpr int inf = 1e9+5;
int n,m,k;

struct linear_basis
{
    int cnt;
    bool zero;
    std::vector<int>p;
    std::vector<int>d;

    // 构造函数，初始化 p 为 64 个元素的向量，所有元素初始值为 0
    linear_basis() : p(100, 0), d(100, 0){
        cnt = 0;
        zero = false;
    }

    //插入线性基，时间复杂度O(logx)
    void insert(int x)
    {
        for(int i = 62;i >= 0;i --)
            if(x & (1ll << i))
            {
                if(!p[i])
                {
                    p[i] = x;
                    return ;
                }
                else
                    x ^= p[i];
            }
        zero = true;
    }

    //用这种方法判断能否通过原数列异或得到一个数x
    bool check(int x)
    {
        for(int i = 62;i >= 0;i --)
            if(x & (1ll << i))
            {
                if(!p[i])
                    return false;
                else
                    x ^= p[i];
            }
        return true;
    }

    //求最大值和最小值。
    int qmax()
    {
        int res = 0;
        for(int i = 62;i >= 0;i --)
            res = std::max(res, res ^ p[i]);
        return res;
    }

    int qmin()
    {
        if(zero)return 0;
        for(int i = 0;i <= 62;i ++)
            if(p[i])
                return p[i];
    }

    void rebuild()
    {
        cnt = 0;
        for(int i = 62;i >= 0;i --)
            for(int j = i - 1;j >= 0;j --)
            {
                if(p[i] & (1ll << j))
                    p[i] ^= p[j];
            }

        for(int i = 0;i <= 62;i ++)
            if(p[i])
                d[cnt ++] = p[i];
    }

    //查询第x小：
    //需要特判0的情况：
    //printf("%lld\n",tmp-zero?kth(tmp-zero):0LL);
    int kth(int k)
    {
        if(zero)
        {
            if(k - zero)
                k = k - 1;
            else
                return 0;
        }

        //超出了。
        if(k >= (1ll << cnt))
            return -1;

        int res = 0;
        for(int i = 0;i < cnt;i ++)
            if(k & (1ll << i))
                res ^= d[i];

        return res;
    }

    //查询排名：（可能有问题。）
    int rank(int x)
    {
        int res = 0;
        //这个从大到小没问题。
        for(int i = cnt - 1;i >= 0;i --)
        {
            if(x >= d[i])
                res += (1ll << i), x ^= d[i];
        }
        return res + zero;
    }

    //删除操作等遇到了再写。
}LB;

void solve()
{
    std::cin >> n;

    // linear_basis LB;

    for(int i = 1;i <= n;i ++)
    {
        int x;
        std::cin >> x;
        LB.insert(x);
    }

    LB.rebuild();

    for(int i = 1;i <= 20;i ++)
        std::cout << LB.kth(i) << " ";

    // std::cout << LB.qmax() << "\n";
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
