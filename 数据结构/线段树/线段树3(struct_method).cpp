/*-------------------------------------------------------------------------------------
�߶�����segment_tree
ʹ���˽ṹ���д������ԭ�ȵ��зǳ���ĸı䣬���������ҷ�һ��
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

    //1��������
    //�ϲ����亯����
    void pushup(const int u)
    {
        tree[u].sum = tree[ls].sum+tree[rs].sum;
        tree[u].maxleft = std::max(tree[ls].maxleft,tree[ls].sum+tree[rs].maxleft);
        tree[u].maxright = std::max(tree[rs].maxright,tree[rs].sum+tree[ls].maxright);
        tree[u].ans = std::max({tree[ls].ans,tree[rs].ans,tree[ls].maxright+tree[rs].maxleft});
    }   

    void build(const int u,int L,int R)
    {
        //����Ҷ���
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

    //�ж�[L,R]�Ƿ�[l,r]����
    bool InRange(int L,int R,int l,int r)
    {
        return (l<=L)&&(R<=r);
    }

    node query(int u,int l,int r)
    {
        //�����ȫ������ֱ�ӷ�������͡�
        if(InRange(tree[u].l,tree[u].r,l,r))
        {
            return tree[u];
        }
        int M=tree[u].l+tree[u].r>>1;
        //��ȫ����ߡ�
        if(r<=M)
            return query(ls,l,r);
        else
        {
            if(l>M)
                return query(rs,l,r);
            else
            {
                //��������Ҷ��Ӷ����ʣ�Ȼ��ϲ�����
                node t,a=query(ls,l,r),b=query(rs,l,r);
                t.maxleft=std::max(a.maxleft,a.sum+b.maxleft);//�����Ƶĺϲ�����
                t.maxright=std::max(b.maxright,a.maxright+b.sum);
                t.ans=std::max(std::max(a.ans,b.ans),a.maxright+b.maxleft);
                return t;//���غϲ��������
            }
        }
    }

    //5�������޸ģ�
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