/*-------------------------------------------------------------------------------------
�߶�����segment_tree

0����Ŀ�Ķ���
����P3373 ��ģ�塿�߶��� 2 ��Ϊ���������
��1������[l,r]�γ���x
��2������[l,r]�μ���x
�������ԭ���߶��������ĵط���

1�����ݽ��ܣ�

1.1������������

lzy_add[N<<2]:����Ǽӣ���ԭ��lazy����Ĺ�����
lzy_mul[N<<2]:����ǳˣ������顣

����������Ҫע�⣬����ǳ����ȼ���������Ǽӣ��ȳ��ټӡ�

1.2���������һ��mod

2�������Ķ���

2.1��void pushup(const int u)
����mod

2.2��void build(const int u,int L,int R)
��ʼ��lzy_mul[u]=1;

2.3��void maketag(int u,int len,int x,int type)
���������type
��Ķ����ӷ�����ȡģ���˷��ȳ�����������ǩ�ٸ�w[u]����Ҫȡģ��

2.4��void pushdown(int u,int L,int R)
�ȳ��ټ��·�tag

2.5��int query(int u,int L,int R,int l,int r)
����mod

2.6��void update(int u,int L,int R,int l,int r,int x,int type)
����type�����Լ���make_tag��Ҫ����type
---------------------------------------------------------------------------------------*/
struct segment_tree
{
    // #define maxn 100050

    #define ls 2*u
    #define rs 2*u+1
    //ע�� a�����w����Ӧ�÷ŵ�����ร�
    int a[N],w[N<<2],lzy_add[N<<2],lzy_mul[N<<2],mod;

    //1��������
    void pushup(const int u)
    {
        w[u]=(w[ls]+w[rs])%mod;
        //w[u]������ͣ�u*2����������u*2+1����������
    }   

    void build(const int u,int L,int R)
    {
        //����Ҷ���
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

    //2�������ѯ
    int query1(int u,int L,int R,int p)
    {
        //����Ҷ��㷵�ؼ��ɡ�
        if(L==R)
            return w[u];
        else
        {
            int M=L+R>>1;
            if(M>=p)//��ѯ������������
                return query1(ls,L,M,p);
            else
                return query1(rs,M+1,R,p);
        }
    }

    //3�������޸ģ�Ҫ��p���ֵ��Ϊx
    void update1(int u,int L,int R,int p,int x)
    {
        if(L==R)
            w[u]=x;
        else
        {
            int M=L+R>>1;
            if(M>=p)//��ѯ������������
                return update1(ls,L,M,p,x);
            else
                return update1(rs,M+1,R,p,x);
            pushup(u);
            //ΪʲôҪ��������Ҹ����굥��󣬴������ϣ���������ȫ�������伴�ɡ�
        }
    }

    //4�������ѯ ����Ķ���
    void maketag(int u,int len,int x,int type)
    {
        if(type==2)
        {
            (lzy_add[u]+=x)%=mod;//�޸ĵ�ǰ����tag���
            (w[u]+=len*x)%=mod;//�޸ĵ�ǰ��������͡�
        }
        else
        {
            //�ӵ�����ǩҲҪ����x
            (lzy_add[u]*=x)%=mod;
            (lzy_mul[u]*=x)%=mod;
            (w[u]*=x)%=mod;
        }
    }

    void pushdown(int u,int L,int R)
    {
        int M=L+R>>1;
        //�ȳ˺��
        maketag(ls,M-L+1,lzy_mul[u],1);//������������lazy[u]
        maketag(ls,M-L+1,lzy_add[u],2);//������������lazy[u]
        maketag(rs,R-M,lzy_mul[u],1);
        maketag(rs,R-M,lzy_add[u],2);
        lzy_add[u]=0;
        lzy_mul[u]=1;
        //��Ϊ�����Ϣ�Ѿ��´�����һ���ˣ�Ϊ�˱����ظ��޸ģ���ǰ��Ҫ��ա�
    }

    //�ж�[L,R]�Ƿ�[l,r]����
    bool InRange(int L,int R,int l,int r)
    {
        return (l<=L)&&(R<=r);
    }
    //�ж�[L,R]�Ƿ��[l,r]��ȫ�޽�
    bool OutofRange(int L,int R,int l,int r)
    {
        return (L>r)||(R<l);
    }

    int query(int u,int L,int R,int l,int r)
    {
        //�����ȫ������ֱ�ӷ�������͡�
        if(InRange(L,R,l,r))
        {
            return w[u];
        }
        //���ཻһ���֣�����Ҫ�ݹ鴦��
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            pushdown(u,L,R);//��ѯ��ʱ��Ҳ��Ҫ��������·š�
            return (query(ls,L,M,l,r)+query(rs,M+1,R,l,r))%mod;
        }
        //��������ȫ���ཻ��
        else
            return 0;
    }

    //5�������޸ģ�
    void update(int u,int L,int R,int l,int r,int x,int type)
    {
        if(InRange(L,R,l,r))
            maketag(u,R-L+1,x,type);//��ȫ����ֱ�Ӵ��Ǽ��ɡ�
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            pushdown(u,L,R);//��ѯ��ʱ��Ҳ��Ҫ��������·š�
            update(ls,L,M,l,r,x,type);
            update(rs,M+1,R,l,r,x,type);
            pushup(u);
        }
    }

    // #undef maxn
    #undef ls
    #undef rs
}Tree;