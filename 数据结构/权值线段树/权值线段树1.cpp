#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;

int a[N],w[N<<2];

struct Frequency_segment_tree
{
    #define ls u<<1
    #define rs u<<1|1
    //要放到外面去喔。
    // int a[N],w[N<<2];

    void pushup(const int u)
    {
        w[u]=w[ls]+w[rs];
        //w[u]是区间和，u*2是左子树，u*2+1是右子树。
    }   

    //1、离散化过程。
    //如前所述，在将元素个数映射到叶子节点的过程中，离散程度较大时会导致极低的空间利用效率。
    //对本种数据结构，我们关心的仅仅是元素之间的大小关系，因此可以采用离散化的方法对空间进行优化。
    void Init_hash()
    {
        // static int tmp[N];
        int tmp[N];
        for(int i=1;i<=n;i++)
            tmp[i]=a[i];
        std::sort(tmp+1,tmp+1+n);
        int len = std::unique(tmp+1,tmp+1+n)-tmp-1;

        for(int i=1;i<=n;i++)
        {
            int pos=std::lower_bound(tmp+1,tmp+1+len,a[i])-tmp;
            a[i]=pos;
        }
    }

    //2、查找
    //2.1、查找第K小。
    int find_kth_min(int u, int L, int R, int k)
    {
        if(L == R) 
            return L;
        int M = (L + R) >> 1, num = w[rs];
        //如果右子树的结点个数足够多的话，说明右边满足K个的要求。
        if(k <= num) 
            return find_kth_min(rs, M+1, R, k);
        else 
            return find_kth_min(ls, L, M, k - num);
    }

    //2.2、查找第K大。
    int find_kth_max(int u, int L, int R, int k)
    {
        if(L == R) 
            return L;
        int M = (L + R) >> 1, num = w[ls];
        if(k <= num) 
            return find_kth_max(ls, L, M, k);
        else 
            return find_kth_max(rs, M+1, R, k - num);
    }

    //3、单点更新操作：
    //类似基础线段树，递归到叶子节点+ 1 +1+1然后回溯
    void add(int u, int L, int R, int x)
    {
        if (L == R) 
            w[u]++;
        else
        {
            int M = (L + R) >> 1;
            if (x <= M) 
                add(ls, L, M, x);
            else 
                add(rs, M+1, R, x);
            pushup(u);
        }
    }

    //4、查询
    //4.1、某个数出现的个数
    //树上二分查找的思想，代码如下：、
    int query1(int u, int L, int R, int x)
    {
        if (L == R) 
            return w[u];
        else
        {
            int M = (L + R) >> 1;
            if (x <= M) 
                return query1(ls, L, M, x);
            else 
                return query1(rs, M+1, R, x);
        }
    }

    //4.2、查询一段区间的数出现的次数

    //判断[L,R]是否被[l,r]包含
    bool InRange(int L,int R,int l,int r)
    {
        return (l<=L)&&(R<=r);
    }
    //判断[L,R]是否和[l,r]完全无交
    bool OutofRange(int L,int R,int l,int r)
    {
        return (L>r)||(R<l);
    }

    int query(int u,int L,int R,int l,int r)
    {
        //如果完全包含则直接返回区间和。
        if(InRange(L,R,l,r))
        {
            return w[u];
        }
        //若相交一部分，则需要递归处理。
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            // pushdown(u,L,R);//查询的时候也需要将结点标记下放。
            return query(ls,L,M,l,r)+query(rs,M+1,R,l,r);
        }
        //否则是完全不相交。
        else
            return 0;
    }

    #undef ls
    #undef rs
}Tree;


void solve()
{
    std::cin>>n;
    for(int i=1;i<=n;i++)
        std::cin>>a[i];
    Tree.Init_hash();
    // for(int i=1;i<=n;i++)
    // {
    //     std::cout<<a[i]<<" \n"[i==n];
    // }

}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}