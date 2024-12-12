/*-------------------------------------------------------------------------------------
线段树：segment_tree

0、题目改动：
根据P3373 【模板】线段树 2 分为两种情况：
（1）、给[l,r]段乘上x
（2）、给[l,r]段加上x
这是相比原版线段树进化的地方！

1、数据介绍：

1.1、两个新数组

lzy_add[N<<2]:懒标记加，由原先lazy数组改过来。
lzy_mul[N<<2]:懒标记乘，新数组。

这里我们需要注意，懒标记乘优先级高于懒标记加，先乘再加。

1.2、往往会多一个mod

2、函数改动：

2.1、void pushup(const int u)
增加mod

2.2、void build(const int u,int L,int R)
初始化lzy_mul[u]=1;

2.3、void maketag(int u,int len,int x,int type)
两种情况：type
大改动，加法增加取模，乘法先乘上两类懒标签再给w[u]，还要取模。

2.4、void pushdown(int u,int L,int R)
先乘再加下方tag

2.5、int query(int u,int L,int R,int l,int r)
加上mod

2.6、void update(int u,int L,int R,int l,int r,int x,int type)
加上type，给自己和make_tag都要加上type
---------------------------------------------------------------------------------------*/
struct segment_tree
{
    // #define maxn 100050

    #define ls 2*u
    #define rs 2*u+1
    //注意 a数组和w数组应该放到外面喔！
    int a[N],w[N<<2],lzy_add[N<<2],lzy_mul[N<<2],mod;

    //1、建树：
    void pushup(const int u)
    {
        w[u]=(w[ls]+w[rs])%mod;
        //w[u]是区间和，u*2是左子树，u*2+1是右子树。
    }   

    void build(const int u,int L,int R)
    {
        //到达叶结点
        lzy_mul[u]=1;
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
            if(M>=p)//查询的在左子区间
                return update1(ls,L,M,p,x);
            else
                return update1(rs,M+1,R,p,x);
            pushup(u);
            //为什么要放这里：等我更新完单点后，从下往上，继续更新全部的区间即可。
        }
    }

    //4、区间查询 （大改动）
    void maketag(int u,int len,int x,int type)
    {
        if(type==2)
        {
            (lzy_add[u]+=x)%=mod;//修改当前结点的tag标记
            (w[u]+=len*x)%=mod;//修改当前结点的区间和。
        }
        else
        {
            //加的懒标签也要乘上x
            (lzy_add[u]*=x)%=mod;
            (lzy_mul[u]*=x)%=mod;
            (w[u]*=x)%=mod;
        }
    }

    void pushdown(int u,int L,int R)
    {
        int M=L+R>>1;
        //先乘后加
        maketag(ls,M-L+1,lzy_mul[u],1);//给左子树乘上lazy[u]
        maketag(ls,M-L+1,lzy_add[u],2);//给左子树加上lazy[u]
        maketag(rs,R-M,lzy_mul[u],1);
        maketag(rs,R-M,lzy_add[u],2);
        lzy_add[u]=0;
        lzy_mul[u]=1;
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
            pushdown(u,L,R);//查询的时候也需要将结点标记下放。
            return (query(ls,L,M,l,r)+query(rs,M+1,R,l,r))%mod;
        }
        //否则是完全不相交。
        else
            return 0;
    }

    //5、区间修改：
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