/*-------------------------------------------------------------------------------------
线段树：segment_tree
使用了结构体的写法，与原先的有非常大的改变，在这里暂且放一下
---------------------------------------------------------------------------------------*/
struct node
{
    int l,r;
    i64 maxleft,maxright,sum,ans;
}tree[N<<2];

struct segment_tree
{
    // #define maxn 100050

    #define ls 2*u
    #define rs 2*u+1

    //1、建树：
    //合并区间函数。
    void pushup(const int u)
    {
        tree[u].sum = tree[ls].sum+tree[rs].sum;
        tree[u].maxleft = std::max(tree[ls].maxleft,tree[ls].sum+tree[rs].maxleft);
        tree[u].maxright = std::max(tree[rs].maxright,tree[rs].sum+tree[ls].maxright);
        tree[u].ans = std::max({tree[ls].ans,tree[rs].ans,tree[ls].maxright+tree[rs].maxleft});
    }   

    void build(const int u,int L,int R)
    {
        //到达叶结点
        tree[u].l=L,tree[u].r=R;
        if(L==R)
        {
            std::cin>>tree[u].sum;
            tree[u].maxleft=tree[u].maxright=tree[u].ans=tree[u].sum;
            return ;
        }
        int M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        pushup(u);
    }

    //判断[L,R]是否被[l,r]包含
    bool InRange(int L,int R,int l,int r)
    {
        return (l<=L)&&(R<=r);
    }

    node query(int u,int l,int r)
    {
        //如果完全包含则直接返回区间和。
        if(InRange(tree[u].l,tree[u].r,l,r))
        {
            return tree[u];
        }
        int M=tree[u].l+tree[u].r>>1;
        //完全在左边。
        if(r<=M)
            return query(ls,l,r);
        else
        {
            if(l>M)
                return query(rs,l,r);
            else
            {
                //否则就左右儿子都访问，然后合并区间
                node t,a=query(ls,l,r),b=query(rs,l,r);
                t.maxleft=std::max(a.maxleft,a.sum+b.maxleft);//做类似的合并区间
                t.maxright=std::max(b.maxright,a.maxright+b.sum);
                t.ans=std::max(std::max(a.ans,b.ans),a.maxright+b.maxleft);
                return t;//返回合并后的区间
            }
        }
    }

    //5、区间修改：
    void update(int u,int x,int y)
    {
        if(tree[u].l==tree[u].r)
        {
            tree[u].maxleft = tree[u].maxright = tree[u].ans = tree[u].sum = y;
            return ;
        }
        int M = tree[u].l+tree[u].r>>1;
        if(x<=M)update(ls,x,y);
        else update(rs,x,y);
        pushup(u);
    }

    // #undef maxn
    #undef ls
    #undef rs
}Tree;