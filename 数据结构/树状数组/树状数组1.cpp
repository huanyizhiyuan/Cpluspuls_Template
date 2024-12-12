/*----------------------------------------------------------------------------
树状数组
大体上就三个函数
1、lowbit
2、前缀和求和
3、添加数进入。

树状数组求区间值需要差分数组。
----------------------------------------------------------------------------*/

// add不能是0和负数
// 方法：加上一个数就行。
// 可以加树状数组，可以加原来的数。
struct Fenwick_Tree_Array
{
    std::vector<int>c;
    int len;

    Fenwick_Tree_Array(int size) : len(size){
        c.assign(size + 1, 0);
    }

    int lowbit(i64 x){return x & (-x);}

    //查找区间和[1,x]。
    int Prefix_Sum(int x)
    {
        int res = 0;
        for(int i = x;i;i -= lowbit(i))
            res += c[i];
        return res;
    }

    // 包含两个端点。
    // 表示范围[l,r]的和。
    int RangeSum(int l, int r)
    {
        return Prefix_Sum(r) - Prefix_Sum(l - 1);
    }

    //给x位置，加上y。
    void add(int x,int y)
    {
        //从小到大修改需要修改的位置。
        for(int i = x;i <= len;i += lowbit(i))
            c[i] += y;
    }
};


/*----------------------------------------------------------------------------
一种简短的写法：
----------------------------------------------------------------------------*/
int pre[N];
void init()
{
    for(int i=1;i<=n;i++)
    {
        pre[i]=pre[i-1]+a[i];
        c[i]=pre[i]-pre[i-lowbit(i)];
    }
}
/*----------------------------------------------------------------------------
vector版本的逆序对求法。
逆序对实质上就是：
单点修改，区间查询问题。
恰恰好可以使用树状数组来解决。
----------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define int i64
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
int n,m,k;
std::vector<int>c(N);
struct Fenwick_Tree_Array
{   
    int lowbit(int x){return x&(-x);}
    //树状数组查找区间和[1,x]，类似前缀和。
    int Prefix_Sum(int x)
    {
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res+=c[i];
        return res;
    }
    //给x位置，加上y。
    void add(int x,int y)
    {
        //从小到大修改需要修改的位置。
        for(int i=x;i<=n;i+=lowbit(i))
            c[i]+=y;
    }
}FTA;

void solve()
{
    std::cin>>n;
    std::vector<int>a(n,0);
    std::vector<int>b(n,0);
    //std::fill(c.begin(), c.end(), 0); // 初始化树状数组
    c.assign(N,0);
    //首先需要我们离散化，当然这道题不需要。
    for(int i=0;i<n;i++)
    {
        std::cin>>a[i];
        b[i]=a[i];
    }
    std::sort(b.begin(),b.end());
    for(auto &v:a)
    {
        v = std::lower_bound(b.begin(),b.end(),v)-b.begin()+1;
    }
    //单点修改+前缀和查找。
    int ans=0;
    for(auto v:a)
    {
        ans += FTA.Prefix_Sum(n)-FTA.Prefix_Sum(v-1);
        FTA.add(v,1);
    }
    std::cout<<ans<<"\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T=1;
    std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}

/*----------------------------------------------------------------------------
树状数组也可以维护最大值：
----------------------------------------------------------------------------*/
std::vector<int>c(200005, 0);

struct Fenwick_Tree_Array
{
    int lowbit(i64 x){return x&(-x);}
    //树状数组查找区间最大值[1,x]。
    int get(int x)
    {
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res = std::max(res, c[i]);
        return res;
    }
    //给x位置，加上y。
    void add(int x,int y,int z)
    {
        //从小到大修改需要修改的位置。
        for(int i=x;i<=200005;i+=lowbit(i))
            c[i] = std::max(c[i], y);
    }
}FTA;
