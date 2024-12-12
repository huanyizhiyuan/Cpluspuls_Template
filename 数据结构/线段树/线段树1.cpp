/*-------------------------------------------------------------------------------------
线段树：segment_tree

1、数据介绍：

1.1、三个数组
a[maxn]:原数组
w[maxn<<2]:区间和数组，大概是4倍。
lazy[maxn<<2]:懒标记数组，对应的是w区间和数组。

1.2、L,R,l,r
[L,R]比[l,r]大
[l,r]是我们需求的区间

2、函数介绍：

2.1、pushup(const int u)
* 作用:更新节点 u 的区间和,即将左右子树的区间和相加,更新到当前节点。
* 实现:将左子节点 w[2*u] 和右子节点 w[2*u+1] 的区间和相加,赋值给当前节点 w[u]。

2.2、void build(const int u,int L,int R)
* 作用:递归建立线段树。
* 实现:如果到达叶节点(即 L == R),将原数组对应位置的值赋给当前节点的区间和;
      否则,递归建立左右子树,并在递归后调用 pushup(u) 更新当前节点的区间和。

2.3、int query1(int u,int L,int R,int p)
* 作用:单点查询,查询原数组中下标为 p 的元素的值。
* 实现:如果到达叶节点,直接返回当前节点的区间和;否则,根据 p 的值决定递归查询左子树还是右子树

2.4、int query1(int u,int L,int R,int p)
* 作用:单点修改,将原数组中下标为 p 的元素的值修改为 x。
* 实现:如果到达叶节点,将当前节点的区间和修改为 x;
    否则,根据 p 的值决定递归修改左子树还是右子树,并在递归后调用 pushup(u) 更新当前节点的区间和。

2.5、void maketag(int u,int len,int x)
* 作用:给节点 u 打标记,表示该节点的区间内所有元素都加上 x。
* 实现:将节点 u 的懒标记 lazy[u] 加上 x,并将节点 u 的区间和 w[u] 加上 len * x。

2.6、void pushdown(int u, int L, int R):
* 作用:下放节点 u 的懒标记,将懒标记传递给左右子树。
* 实现:计算左右子树的区间长度,分别调用 maketag 函数给左右子树打上懒标记,并将当前节点的懒标记清零。

2.7、bool InRange(int L, int R, int l, int r):
* 作用:判断区间 [L, R] 是否被区间 [l, r] 完全包含。
* 实现:判断条件为 (l <= L) && (R <= r)。

2.8、bool OutofRange(int L,int R,int l,int r)
* 作用:判断区间 [L, R] 是否与区间 [l, r] 完全不相交。
* 实现:判断条件为 (L > r) || (R < l)。

2.9、int query(int u,int L,int R,int l,int r)
* 作用:区间查询,查询区间 [l, r] 内所有元素的和。
* 实现:如果当前节点的区间被查询区间完全包含,直接返回当前节点的区间和;如果当前节点的区间与查询区间部分相交,
* 则先下放懒标记,然后递归查询左右子树,返回左右子树的查询结果之和;如果当前节点的区间与查询区间完全不相交,返回 0。

2.10、void update(int u,int L,int R,int l,int r,int x)
* 注意:再详细解释一下，最开始是[L,R]>[l,r]，然后逐渐让[L,R]变小，最终[l,r]大或是等于。
* 作用:区间修改,将区间 [l, r] 内所有元素的值加上 x。
* 实现:如果当前节点的区间被修改区间完全包含,直接给当前节点打上标记;如果当前节点的区间与修改区间部分相交,
* 则先下放懒标记,然后递归修改左右子树,并在递归后调用 pushup(u) 更新当前节点的区间和;如果当前节点的区间与修改区间完全不相交,不做任何操作。
---------------------------------------------------------------------------------------*/
struct segment_tree
{
    // #define maxn 100050

    #define ls u<<1
    #define rs u<<1|1
    //注意 a数组和w数组应该放到外面喔！
    int a[N],w[N<<2],lazy[N<<2];

    //1、建树：
    void pushup(const int u)
    {
        w[u]=w[ls]+w[rs];
        //w[u]是区间和，u*2是左子树，u*2+1是右子树。
    }   

    void build(const int u,int L,int R)
    {
        //到达叶结点
        if(L==R)
        {
            w[u]=a[L];
            return ;
        }
        int M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        pushup(u);
    }

    //2、单点查询
    int query1(int u,int L,int R,int p)
    {
        //到达叶结点返回即可。
        if(L==R)
            return w[u];
        else
        {
            int M=L+R>>1;
            if(M>=p)//查询的在左子区间
                return query1(ls,L,M,p);
            else
                return query1(rs,M+1,R,p);
        }
    }

    //3、单点修改，要把p结点值变为x
    void update1(int u,int L,int R,int p,int x)
    {
        if(L==R)
            w[u]=x;
        else
        {
            int M=L+R>>1;
            if(p <= M)//查询的在左子区间
                return update1(ls,L,M,p,x);
            else
                return update1(rs,M+1,R,p,x);
            pushup(u);
            //为什么要放这里：等我更新完单点后，从下往上，继续更新全部的区间即可。
        }
    }

    //4、区间查询
    void maketag(int u,int len,int x)
    {
        lazy[u]+=x;//修改当前结点的tag标记
        w[u]+=len*x;//修改当前结点的区间和。
    }

    //pushdown往往不需要设置状态。
    void pushdown(int u,int L,int R)
    {
        if(lazy[u])
        {
            int M=L+R>>1;
            maketag(ls,M-L+1,lazy[u]);//给左子树加上lazy[u]
            maketag(rs,R-M,lazy[u]);
            lazy[u]=0;
            //因为标记信息已经下传到下一层了，为了避免重复修改，当前层要清空。
        }
    }

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
            pushdown(u,L,R);//查询的时候也需要将结点标记下放。
            return query(ls,L,M,l,r)+query(rs,M+1,R,l,r);
        }
        //否则是完全不相交。
        else
            return 0;
    }

    // //两个效果类似的
    // i64 query2(int u, int L,int R, int l, int r)
    // {
    //     if(L >= l && R <= r) return gcd[u];
    //     else 
    //     {
    //         int M = L+R >> 1;
    //         if(r <= M) return query2(ls, L,M,l, r);
    //         else if(l > M) return query2(rs,M+1,R, l, r);
    //         else return fun(query2(ls,L,M, l, r), query2(rs,M+1,R, l, r));
    //     }
    // }

    //5、区间修改：
    void update(int u,int L,int R,int l,int r,int x)
    {
        if(InRange(L,R,l,r))
            maketag(u,R-L+1,x);//完全包含直接打标记即可。
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            pushdown(u,L,R);//查询的时候也需要将结点标记下放。
            update(ls,L,M,l,r,x);
            update(rs,M+1,R,l,r,x);
            pushup(u);
        }
    }

    // #undef maxn
    #undef ls
    #undef rs
}Tree;

/*-----------------------------------------------
线段树应用1：求最大值最小值。
至少需要改query，还有pushup这两个
并且query中返回0的情况一定要做出改变，要么是inf，要么是-inf
其他改动暂不深究。
-----------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e9+5;
const i64 N=1e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;

int a[N],w[N<<2],lazy[N<<2];

struct segment_tree
{
    // #define maxn 100050

    #define ls u<<1
    #define rs u<<1|1

    //注意 a数组和w数组应该放到外面喔！
    

    //1、建树：
    void pushup(const int u)
    {
        w[u]=std::min(w[ls],w[rs]);
        //w[u]是区间和，u*2是左子树，u*2+1是右子树。
    }   

    void build(const int u,int L,int R)
    {
        w[u]=inf;
        //到达叶结点
        if(L==R)
        {
            w[u]=a[L];
            return ;
        }
        int M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        pushup(u);
    }

    //2、单点查询
    int query1(int u,int L,int R,int p)
    {
        //到达叶结点返回即可。
        if(L==R)
            return w[u];
        else
        {
            int M=L+R>>1;
            if(M>=p)//查询的在左子区间
                return query1(ls,L,M,p);
            else
                return query1(rs,M+1,R,p);
        }
    }

    //3、单点修改，要把p结点值变为x
    void update1(int u,int L,int R,int p,int x)
    {
        if(L==R)
            w[u]=x;
        else
        {
            int M=L+R>>1;
            if(p <= M)//查询的在左子区间
                update1(ls,L,M,p,x);
            else
                update1(rs,M+1,R,p,x);
            pushup(u);
            //为什么要放这里：等我更新完单点后，从下往上，继续更新全部的区间即可。
        }
    }

    //4、区间查询
    void maketag(int u,int len,int x)
    {
        lazy[u]+=x;//修改当前结点的tag标记
        w[u]+=len*x;//修改当前结点的区间和。
    }

    void pushdown(int u,int L,int R)
    {
        int M=L+R>>1;
        maketag(ls,M-L+1,lazy[u]);//给左子树加上lazy[u]
        maketag(rs,R-M,lazy[u]);
        lazy[u]=0;
        //因为标记信息已经下传到下一层了，为了避免重复修改，当前层要清空。
    }

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
            return std::min(query(ls,L,M,l,r),query(rs,M+1,R,l,r));
        }
        //否则是完全不相交。
        else
            return inf;
    }

    //5、区间修改：
    void update(int u,int L,int R,int l,int r,int x)
    {
        if(InRange(L,R,l,r))
            maketag(u,R-L+1,x);//完全包含直接打标记即可。
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            pushdown(u,L,R);//查询的时候也需要将结点标记下放。
            update(ls,L,M,l,r,x);
            update(rs,M+1,R,l,r,x);
            pushup(u);
        }
    }

    // #undef maxn
    #undef ls
    #undef rs
}Tree;

void solve()
{
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        std::cin>>a[i];
    }
    Tree.build(1,1,n);
    // for(int i=1;i<=16;i++)
    //     std::cout<<w[i]<<" \n"[i==16];
    while(m--)
    {
        int x,y;
        std::cin>>x>>y;
        std::cout<<Tree.query(1,1,n,x,y)<<" ";
    }
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


/*-----------------------------------------------
线段树应用2：
0、区间[l,r]设置为0
1、区间[l,r]设置为1
2、区间[l,r]每一个数各自取反
3、求区间[l,r]的数量。
-----------------------------------------------*/
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
i64 T=1,n,m,k,_a,_b,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;

//w代表数量。
int a[N],w[N<<2],lzy_xor[N<<2],lzy_set[N<<2];

struct segment_tree
{
    #define ls u<<1
    #define rs u<<1|1
    //1、建树：
    void pushup(const int u)
    {
        w[u]=w[ls]+w[rs];
        

    }   

    void build(const int u,int L,int R)
    {
        //到达叶结点
        if(L==R)
        {
            w[u]=a[L];
            LL[u]=a[L];
            RR[u]=a[L];
            ans[u]=S[u]=H[u]=1;
            return ;
        }
        int M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        pushup(u);
    }

    //4、区间查询
    void maketag(int u,int len,int x,int type)
    {
        //修改设置
        if(type==0)
        {
            if(x==-1)
                w[u]=0,lzy_set[u]=-1;
            else
                w[u]=len,lzy_set[u]=1;
        }
        else if(type==1)
        {
            lzy_xor[u]^=1;
            w[u]=len-w[u];
        }
    }

    void pushdown(int u,int L,int R)
    {
        //首先，我们要明确，这里的操作都是上几轮的操作，
        //我们这里是必须要把他们干掉的。
        //如果有设置的话优先设置。
        int M=L+R>>1;
        if(lzy_set[u])
        {
            //优先设置，覆盖取反。
            maketag(ls,M-L+1,lzy_set[u],0);
            maketag(rs,R-M,lzy_set[u],0);
            lzy_xor[u]=0;
            lzy_set[u]=0;
        }
        else if(lzy_xor[u])
        {
            maketag(ls,M-L+1,lzy_xor[u],1);
            maketag(rs,R-M,lzy_xor[u],1);
            lzy_xor[u]=0;
            //因为标记信息已经下传到下一层了，为了避免重复修改，当前层要清空。
        }
    }

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

    //求有多少个1
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
            pushdown(u,L,R);//查询的时候也需要将结点标记下放。
            return query(ls,L,M,l,r)+query(rs,M+1,R,l,r);
        }
        //否则是完全不相交。
        else
            return 0;
    }

    //5、区间修改：
    //这里x就是type的意思。
    void update(int u,int L,int R,int l,int r,int x,int type)
    {
        if(InRange(L,R,l,r))
            maketag(u,R-L+1,x,type);//完全包含直接打标记即可。
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            pushdown(u,L,R);//查询的时候也需要将结点标记下放。
            update(ls,L,M,l,r,x,type);
            update(rs,M+1,R,l,r,x,type);
            pushup(u);
        }
    }

    // #undef maxn
    #undef ls
    #undef rs
}Tree;


void solve()
{
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        std::cin>>a[i];
    }
    Tree.build(1,1,n);
    while(m--)
    {
        int op;
        std::cin>>op>>x>>y;
        if(op==0)
        {
            Tree.update(1,1,n,x,y,-1,0);
        }
        else if(op==1)
        {
            Tree.update(1,1,n,x,y,1,0);
        }
        else if(op==2)
        {
            Tree.update(1,1,n,x,y,0,1);
        }
        else if(op==3)
        {
            std::cout<<Tree.query(1,1,n,x,y)<<"\n";
        }
    }
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


/*-------------------------------------------------------------------------------------------------------------------------
区间最大值简略版本。
--------------------------------------------------------------------------------------------------------------------------*/

    // 单点修改
    auto update = [&](auto self, int u, int L, int R, int p, int x) -> void
    {
        // std::cout << std::format("l = {}, r = {}, u = {}, p = {}, x = {}\n", L, R, u, p, x);
        if(L == R)
        {
            mx[u] = std::max(mx[u], x);
            return ;
        }
        int M = L + R >> 1;
        if(p > M) self(self, rs, M + 1, R, p, x);
        else self(self, ls, L, M, p, x);
        mx[u] = std::max(mx[ls], mx[rs]);
    };

    // 区间查询
    auto query = [&](auto self, int u, int L, int R, int l, int r) -> int
    {
        if(L >= l and R <= r)
            return mx[u];
        int M = L + R >> 1;
        if(l > M)
            return self(self, rs, M + 1, R, l, r);
        else if(r <= M)
            return self(self, ls, L, M, l, r);
        else
            return std::max(self(self, ls, L, M, l, r), self(self, rs, M + 1, R, l, r));
    };


/*----------------------------------------------------------------------------------------------------------------------------------------
新型线段树。
-------------------------------------------------------------------------------------------------------------------------------------*/
struct segment_tree
{
    #define ls u << 1
    #define rs u << 1 | 1

    std::vector<int>c;
    std::vector<int>lzy;

    segment_tree(){}

    segment_tree(int size) : c(size << 2, 0), lzy(size << 2, 0){

    }

    // 合并
    void pushup(const int u)
    {
        c[u] = c[ls] + c[rs];
    }

    // 1、构建
    void build(const int u, int L, int R, int mid)
    {
        //到达叶结点
        if(L == R)
        {
            c[u] = (a[L] >= mid);
            lzy[u] = 0;
            return ;
        }
        int M= L + R >> 1;
        build(ls, L, M, mid);
        build(rs, M + 1, R, mid);
        pushup(u);
        lzy[u] = 0;
    }

    void pushdown(const int u, int L, int R)
    {
        // -1
        if(lzy[u])
        {
            int M = L + R >> 1;
            lzy[ls] = lzy[rs] = lzy[u];
            if(lzy[u] == 1)
                c[ls] = M - L + 1, c[rs] = R - M;
            else
                c[ls] = c[rs] = 0;
            lzy[u] = 0;
        }
    }

    // 2、单点查询
    int query1(int u, int L, int R, int p)
    {
        //到达叶结点返回即可，这个不需要pushdown。
        if(L == R)
            return c[u];

        pushdown(u, L, R);

        int M = L + R >> 1;
        if(p <= M)//查询的在左子区间
            return query1(ls, L, M, p);
        else
            return query1(rs, M + 1, R, p);
    }

    // 3、区间查询（1的个数）
    int query(int u, int L, int R, int l, int r)
    {
        if(l <= L and R <= r)
            return c[u];

        if(l > R or r < L)
            return 0;

        int M = L + R >> 1;
        pushdown(u, L, R);
        return query(ls, L, M, l, r) + query(rs, M + 1, R, l, r);
    }

    // 4、区间修改
    void update(int u, int L, int R, int l, int r, int x)
    {
        if(l <= L and r >= R)
        {
            // x = 1，那就是这个区间，否则是 0
            c[u] = x * (R - L + 1);
            lzy[u] = (x ? 1 : -1);
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
}Tree;
