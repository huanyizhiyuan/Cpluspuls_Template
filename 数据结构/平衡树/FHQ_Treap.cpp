/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
平衡树，这里我们采用FHQ_treap
FHQ树堆。
第一个样例是按值分裂，第二个样例是按照排名分裂。
1、std::mt19937 sj(114514);
特殊的随机数。

2、int add(int v)
新建树结点。

3、void pushup(int u)
类似线段树中，需要随机应变的操作。
这里是算子树的操作。

4、void split(int u,int v,int &x,int &y)+int merge(int x,int y)
核心操作：
* 可以按值分裂。
* 可以按排名分裂。
根据分裂的方式不同，得到的结果，处理的问题也不同。

分裂也就是按照平衡树的方式分裂，具体看语雀平台。

5、其余操作，这些操作都是需要自己写的，自己整理的。
insert erase kth find_rank, find_pre find_nxt
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
#define int i64
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const int INF=2e16+5;
const i64 N=1e6+1e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;

//茅台19937
std::mt19937 sj(114514);
//范浩强
struct FHQ
{
    int L,R,key,sz,val;
}fhq[N];
int root,T1,T2,T3,ck;
struct FHQ_treap
{
    #define ls fhq[u].L
    #define rs fhq[u].R
    //新建结点。
    int add(int v)
    {
        fhq[++ck]={0,0,(int)sj(),1,v};
        return ck;
    }
    //随机应变，可能还有fa,sum之类的。
    void pushup(int u)
    {
        fhq[u].sz=fhq[ls].sz+fhq[rs].sz+1;
    }

    //u是当前fhq-treap的根
    void split(int u,int v,int &x,int &y)
    {
        // &x 和 &y分别是fhq-treap分裂后得到的两个fhq-treap的根，这里用指针(引用)的方式，便于传递值
        if(!u)//如果该节点为空树，则分裂成的左右两个树也应为空
        {
            x=y=0;
            return ;
        }
        // 如果当前节点的val值大于v，则证明该节点的右子树上所有的val值也大于v
        if(fhq[u].val > v)
        {
            //让该节点成为右树的节点
            y=u;
            //继续递归分离当前节点的左子树
            split(ls,v,x,ls);
        }
        // 如果当前节点的val值小于等于v，则证明该节点的左子树上所有的val值也小于等于v
        else
        {
            //让该节点成为左树的节点
            x=u;
            //继续递归分离当前节点的右子树
            split(rs,v,rs,y);
        }
        //一定要记得push_up，因为pos点的左右子树大小发生了改变，否则会导致信息不对
        pushup(u);
    }
    //这里才用到key
    //传入左右子树的根节点
    int merge(int x,int y)
    {
        //如果有空树
        if(!x || !y)
            return x+y;//直接返回非空树(本蒟蒻这样的写法x|y等同于x+y,是用来装杯的)
        if(fhq[x].key > fhq[y].key)
        {
            //如果左树上当前节点的val值大于右树上当前节点的val值
            //将l变为合并后的新fhq-treap的根节点
            fhq[x].R = merge(fhq[x].R, y);//继续递归确定l的右子树该接谁
            pushup(x);//一定记得上传
            return x;//返回新得到的根节点
        }
        else
        {
            fhq[y].L = merge(x,fhq[y].L);
            pushup(y);
            return y;
        }
    }

    //插入删除。
    void insert(int v)
    {
        split(root,v,T1,T2);
        root = merge(merge(T1,add(v)),T2);
    }
    void erase(int x)
    {
        split(root,x,T1,T2);
        split(T1,x-1,T1,T3);
        T3=merge(fhq[T3].L,fhq[T3].R);
        root = merge(merge(T1,T3),T2);
    }

    //找出小于等于x-1的个数。
    int find_rank(int x)
    {
        split(root,x-1,T1,T2);
        int res = fhq[T1].sz+1;
        root = merge(T1,T2);
        return res;
    }
    //找到第k小。
    int kth(int k)
    {
        int u =root;
        while(u)
        {
            int tmp = fhq[ls].sz+1;
            if(tmp == k)
                break;
            else if(k<tmp)
                u=ls;
            //多减去了左子树的内容。
            else
                k-=tmp,u = rs;
        }
        return fhq[u].val;
    }

    int find_pre(int u,int v)
    {
        if(u==0)return -INF;
        if(fhq[u].val < v)
        {
            int res = find_pre(rs,v);
            return res==-INF?fhq[u].val:res;
        }
        else
            return find_pre(ls,v);
    }

    int find_nxt(int u,int v)
    {
        if(u==0)return INF;
        if(fhq[u].val>v)
        {
            int res = find_nxt(ls,v);
            return res == INF?fhq[u].val:res;
        }
        else
            return find_nxt(rs,v);
    }

    // int find_pre2(int x)
    // {
    //     split(root,x-1,T1,T2);
    //     int u=T1;
    //     while(rs)u=rs;
    //     root=merge(T1,T2);
    //     return fhq[u].val;
    // }

    // int find_nxt2(int x)
    // {
    //     split(root,x,T1,T2);
    //     int u=T2;
    //     while(ls)u=ls;
    //     root=merge(T1,T2);
    //     return fhq[u].val;
    // }
    #undef ls
    #undef rs
}Treap;

void solve()
{
    int op,x;
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        std::cin>>x;
        Treap.insert(x);
    }
    int ans=0,res=0;
    while(m--)
    {
        std::cin>>op>>x;
        // if(op>2)
            x^=res;
        if(op==1)
            Treap.insert(x);
        else if(op==2)
            Treap.erase(x);
        else if(op==3)
            res=Treap.find_rank(x);
        else if(op==4)
            res=Treap.kth(x);
        else if(op==5)
            res=Treap.find_pre(root,x);
        else
            res=Treap.find_nxt(root,x);
        // std::cout<<res<<"\n";
        if(op>2)
            ans^=res;
    }
    std::cout<<ans<<"\n";
}

signed main()
{
#ifndef ONLINE_JUDGE
	// freopen("title.in","r",stdin);
	// freopen("title.out","w",stdout);
#endif

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
/*-------------------------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------------------------------------*/

