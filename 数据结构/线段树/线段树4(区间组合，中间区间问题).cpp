/*--------------------------------------------------------------------------------------------
区间合并问题+中间区间问题：
这类题目难度比较大，我这里多介绍几个板子：
1、洛谷P6492
会涉及到中间区间，我们需要根据ls的右端点区间以及rs的左端点区间进行求解。
我们往往会设置很多数组。
● len[i]：线段树中第 i 个节点所维护的区间的长度；
● L[i]：线段树中第 i 个节点所维护的区间的左端点；
● R[i]：线段树中第 i 个节点所维护的区间的右端点；
● S[i]：线段树中第 i 个节点所维护的区间的最左端开始最长的符合条件的区间长度（前缀）；
● H[i]：线段树中第 i 个节点所维护的区间的最右端开始最长的符合条件的区间长度（后缀）；
● ans[i]：线段树中第 i 个节点所维护的区间的最长符合条件的区间长度；
-------------------------------------------------------------------------------------------*/
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

//这题不需要懒标记。
int LL[N<<2],RR[N<<2],S[N<<2],H[N<<2],len[N<<2],ans[N<<2];

struct segment_tree
{
    // #define maxn 100050

    #define ls u<<1
    #define rs u<<1|1

    //将u的结点的值赋值为K，并更新一下该点信息。
    void work(int u,int x)
    {
        ans[u]=S[u]=H[u]=1;
        LL[u]=RR[u]=x;
    }

    //1、建树：
    void pushup(const int u)
    {
        //合并中间的长度+左右两端的长度。
        //题目条件下必须要异或才可以考虑。
        if(RR[ls]^LL[rs])
        {
            //结合
            //考虑两端合并后的符合条件的区间长度 
            ans[u]=H[ls]+S[rs];
            //与左区间的进行比较 
            ans[u]=std::max(ans[u],ans[ls]);
            //与右区间的进行比较 
            ans[u]=std::max(ans[u],ans[rs]);
        }
        //否则只用考虑左右区间中最长的区间。
        else
            ans[u]=std::max(ans[ls],ans[rs]);

        //L和R数组的维护显而易见 
        //左端点是ls的左端点，右端点是rs的右端点
        LL[u]=LL[ls],RR[u]=RR[rs];
        ////左区间的S包含整个区间并且左区间的右端点与右区间的左端点不同,则两个区间的S合并成大区间的S 
        if(S[ls]==len[ls]&&RR[ls]^LL[rs])
            S[u]=S[ls]+S[rs];
        else
            S[u]=S[ls];
        if(H[rs]==len[rs]&&RR[ls]^LL[rs])
            H[u]=H[rs]+H[ls];
        else
            H[u]=H[rs];
    }   

    void build(const int u,int L,int R)
    {
        len[u]=R-L+1;   //区间长度。
        //到达叶结点
        if(L==R)    
        {
            //将该点赋值为0，并更新一下该点信息。
            work(u,0);
            return ;
        }
        int M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        pushup(u);
    }

    void update1(int u,int L,int R,int x)
    {
        if(L==R)
        {
            work(u,!LL[u]);
            return ;
        }
        int M=L+R>>1;
        if(x<=M)
            update1(ls,L,M,x);
        else
            update1(rs,M+1,R,x);
        pushup(u);
    }

    // #undef maxn
    #undef ls
    #undef rs
}Tree;

void solve()
{
    std::cin>>n>>m;
    Tree.build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int x;
        std::cin>>x;
        Tree.update1(1,1,n,x);
        std::cout<<ans[1]<<"\n";
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
/*--------------------------------------------------------------------------------------------
2、P2572 [SCOI2010] 序列操作
要进行五大操作：
lxhgww 最近收到了一个 01 序列，序列里面包含了 n 个数，下标从 0 开始。这些数要么是 0，要么是 1，现在对于这个序列有五种变换操作和询问操作：
- 0 l r 把 [l, r] 区间内的所有数全变成 0；
- 1 l r 把 [l, r] 区间内的所有数全变成 1；
- 2 l r 把 [l, r] 区间内的所有数全部取反，也就是说把所有的 0 变成 1，把所有的 1 变成 0；
- 3 l r 询问 [l, r] 区间内总共有多少个 1；
- 4 l r 询问 [l, r] 区间内最多有多少个连续的 1。
对于每一种询问操作，lxhgww 都需要给出回答，聪明的程序员们，你们能帮助他吗？
对于100% 的数据， n,m <= 10^5。
-------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
//#define int ll
// using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;
int a[N];
struct segTree
{
    int L,R;
    int w;
    int len;
    int lazy;   //-1 NULL,0全为0,1全为1。
    int rev;
    int max[2],lmax[2],rmax[2];
}t[N<<2];
struct segment_Tree
{
    #define ls u<<1
    #define rs u<<1|1
    void pushup(int u)
    {
        t[u].w=t[ls].w+t[rs].w;
        for(int i=0;i<=1;i++)
        {
            t[u].lmax[i] = t[ls].lmax[i];
            //左区间全满，i=1时候可以跨越。
            if(i==1 && t[ls].w == t[ls].len)
                t[u].lmax[i] += t[rs].lmax[i];
            //左区间全空，i=0时候可以跨越。
            else if(i==0 && t[ls].w==0)
                t[u].lmax[i] += t[rs].lmax[i];

            t[u].rmax[i] = t[rs].rmax[i];
            //右区间全满，i=1时候可以跨越。
            if(i==1 && t[rs].w == t[rs].len)
                t[u].rmax[i] += t[ls].rmax[i];
            //右区间全空，i=0时候可以跨越。
            else if(i==0 && t[rs].w==0)
                t[u].rmax[i] += t[ls].rmax[i];

            //中间区间。
            //先由中间组合。
            t[u].max[i] = t[ls].rmax[i] + t[rs].lmax[i];
            //再看左边最大的。
            t[u].max[i] = std::max(t[u].max[i],t[ls].max[i]);
            //再看右边最大的。
            t[u].max[i] = std::max(t[u].max[i],t[rs].max[i]);
        }
    }
    void build(int u,int L,int R)
    {
        //lazy == -1为NULL
        t[u].L=L,t[u].R=R,t[u].lazy=-1;
        t[u].len=R-L+1;
        if(L==R)
        {
            t[u].w=a[L];
            t[u].max[0]=t[u].lmax[0]=t[u].rmax[0]=a[L]==0;
            t[u].max[1]=t[u].lmax[1]=t[u].rmax[1]=a[L]==1;
            return ;
        }
        int M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        pushup(u);
    }
    void pushdown(int u)
    {
        //优先级最高
        if(t[u].lazy!=-1)
        {
            t[u].rev = 0;//清空标记。
            int val = t[u].lazy;
            t[ls].w = t[ls].len*val;
            t[rs].w = t[rs].len*val;

            t[ls].lazy = t[rs].lazy = val;
            //设置优先级高于rev
            t[ls].rev = t[rs].rev = 0;

            //最长连续子片段0和1。
            t[ls].max[val]=t[ls].lmax[val]=t[ls].rmax[val]=t[ls].len;
            t[ls].max[val^1] = t[ls].lmax[val^1] = t[ls].rmax[val^1] = 0;

            //最长连续子片段0和1。
            t[rs].max[val]=t[rs].lmax[val]=t[rs].rmax[val]=t[rs].len;
            t[rs].max[val^1] = t[rs].lmax[val^1] = t[rs].rmax[val^1] = 0;

            t[u].lazy=-1;
        }
        //这个时候可能lazy仍然存在。
        if(t[u].rev)
        {
            t[ls].w = t[ls].len -t[ls].w;
            t[rs].w = t[rs].len- t[rs].w;

            if(t[ls].lazy != -1)
                t[ls].lazy ^=1;
            else
                t[ls].rev ^=1;

            if(t[rs].lazy != -1)
                t[rs].lazy ^=1;
            else
                t[rs].rev ^=1;

            std::swap(t[ls].max[0], t[ls].max[1]);
            std::swap(t[ls].lmax[0], t[ls].lmax[1]);
            std::swap(t[ls].rmax[0], t[ls].rmax[1]);
            
            std::swap(t[rs].max[0], t[rs].max[1]);
            std::swap(t[rs].lmax[0], t[rs].lmax[1]);
            std::swap(t[rs].rmax[0], t[rs].rmax[1]);
            
            t[u].rev = 0;
        }
    }
    
    void update(int u,int val,int l,int r)
    {
        pushdown(u);
        if(t[u].L==l&&t[u].R==r)
        {
            if(val==0||val==1)
            {
                t[u].w = t[u].len * val;
                t[u].lazy = val;

                t[u].max[val] = t[u].lmax[val] = t[u].rmax[val] = t[u].len;
                t[u].max[val^1] = t[u].lmax[val^1] = t[u].rmax[val^1] = 0;
            }
            else if(val==2)
            {
                t[u].w = t[u].len -t[u].w;
                t[u].rev ^= 1;

                std::swap(t[u].max[0],t[u].max[1]);
                std::swap(t[u].lmax[0],t[u].lmax[1]);
                std::swap(t[u].rmax[0],t[u].rmax[1]);
            }
            return ;
        }
        int M = t[u].L + t[u].R >>1;
        if(M < l) update(rs, val, l, r);
        else if(M >= r) update(ls ,val, l, r);

        else update(ls,val,l,M), update(rs,val,M+1,r);
        pushup(u);
    }

    int query(int u,int l,int r)
    {
        pushdown(u);
        if(t[u].L==l&&t[u].R==r)
        {
            return t[u].w;
        }
        int M = t[u].L + t[u].R >>1;
        if(M < l) 
            return query(rs, l, r);
        else if(M >= r) 
            return query(ls ,l, r);
        else 
            return query(ls,l,M)+ query(rs,M+1,r);
    }

    segTree query2(int u,int l,int r)
    {
        pushdown(u);
        if(t[u].L==l&&t[u].R==r)
            return t[u];
        int M = t[u].L + t[u].R >>1;
        if(M < l) 
            return query2(rs, l, r);
        else if(M >= r) 
            return query2(ls ,l, r);
        //这里比较麻烦。
        else
        {
            segTree ret,L=query2(ls,l,M), R=query2(rs,M+1,r);
            ret.w = L.w+ R.w;
            for(int i=0;i<=1;i++)
            {
                ret.lmax[i] = L.lmax[i];
                //左区间全满，可以跨越。
                if(i==1 && L.w == L.len)
                    ret.lmax[i] += R.lmax[i];
                else if(i==0 && L.w == 0)
                    ret.lmax[i] += R.lmax[i];

                ret.rmax[i] = R.rmax[i];
                //右区间全满，可以跨越。
                if(i==1 && R.w == R.len)
                    ret.rmax[i] += L.rmax[i];
                else if(i==0 && R.w == 0)
                    ret.rmax[i] += L.rmax[i];

                ret.max[i] = L.rmax[i]+ R.lmax[i];
                ret.max[i] = std::max(ret.max[i], L.max[i]);
                ret.max[i] = std::max(ret.max[i], R.max[i]);
            }
            return ret;
        }
    }
    #undef ls
    #undef rs
}Tree;
void solve()
{
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)
        std::cin>>a[i];
    Tree.build(1,1,n);
    while(m--)
    {
        int op;
        std::cin>>op>>x>>y;
        x++,y++;
        if(op==0)
        {
            Tree.update(1,0,x,y);
        }
        else if(op==1)
        {
            Tree.update(1,1,x,y);
        }
        else if(op==2)
        {
            Tree.update(1,2,x,y);
        }
        else if(op==3)
        {
            std::cout<<Tree.query(1,x,y)<<"\n";
        }
        else if(op==4)
        {
            std::cout<<Tree.query2(1,x,y).max[1]<<"\n";
        }
    }
}

signed main()
{
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    // std::cout.tie(nullptr);
    // std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}