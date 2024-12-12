/*-------------------------------------------------------------------------------------
�߶�����segment_tree

1�����ݽ��ܣ�

1.1����������
a[maxn]:ԭ����
w[maxn<<2]:��������飬�����4����
lazy[maxn<<2]:��������飬��Ӧ����w��������顣

1.2��L,R,l,r
[L,R]��[l,r]��
[l,r]���������������

2���������ܣ�

2.1��pushup(const int u)
* ����:���½ڵ� u �������,����������������������,���µ���ǰ�ڵ㡣
* ʵ��:�����ӽڵ� w[2*u] �����ӽڵ� w[2*u+1] ����������,��ֵ����ǰ�ڵ� w[u]��

2.2��void build(const int u,int L,int R)
* ����:�ݹ齨���߶�����
* ʵ��:�������Ҷ�ڵ�(�� L == R),��ԭ�����Ӧλ�õ�ֵ������ǰ�ڵ�������;
      ����,�ݹ齨����������,���ڵݹ����� pushup(u) ���µ�ǰ�ڵ������͡�

2.3��int query1(int u,int L,int R,int p)
* ����:�����ѯ,��ѯԭ�������±�Ϊ p ��Ԫ�ص�ֵ��
* ʵ��:�������Ҷ�ڵ�,ֱ�ӷ��ص�ǰ�ڵ�������;����,���� p ��ֵ�����ݹ��ѯ����������������

2.4��int query1(int u,int L,int R,int p)
* ����:�����޸�,��ԭ�������±�Ϊ p ��Ԫ�ص�ֵ�޸�Ϊ x��
* ʵ��:�������Ҷ�ڵ�,����ǰ�ڵ��������޸�Ϊ x;
    ����,���� p ��ֵ�����ݹ��޸�����������������,���ڵݹ����� pushup(u) ���µ�ǰ�ڵ������͡�

2.5��void maketag(int u,int len,int x)
* ����:���ڵ� u ����,��ʾ�ýڵ������������Ԫ�ض����� x��
* ʵ��:���ڵ� u ������� lazy[u] ���� x,�����ڵ� u ������� w[u] ���� len * x��

2.6��void pushdown(int u, int L, int R):
* ����:�·Žڵ� u �������,������Ǵ��ݸ�����������
* ʵ��:�����������������䳤��,�ֱ���� maketag �����������������������,������ǰ�ڵ����������㡣

2.7��bool InRange(int L, int R, int l, int r):
* ����:�ж����� [L, R] �Ƿ����� [l, r] ��ȫ������
* ʵ��:�ж�����Ϊ (l <= L) && (R <= r)��

2.8��bool OutofRange(int L,int R,int l,int r)
* ����:�ж����� [L, R] �Ƿ������� [l, r] ��ȫ���ཻ��
* ʵ��:�ж�����Ϊ (L > r) || (R < l)��

2.9��int query(int u,int L,int R,int l,int r)
* ����:�����ѯ,��ѯ���� [l, r] ������Ԫ�صĺ͡�
* ʵ��:�����ǰ�ڵ�����䱻��ѯ������ȫ����,ֱ�ӷ��ص�ǰ�ڵ�������;�����ǰ�ڵ���������ѯ���䲿���ཻ,
* �����·������,Ȼ��ݹ��ѯ��������,�������������Ĳ�ѯ���֮��;�����ǰ�ڵ���������ѯ������ȫ���ཻ,���� 0��

2.10��void update(int u,int L,int R,int l,int r,int x)
* ע��:����ϸ����һ�£��ʼ��[L,R]>[l,r]��Ȼ������[L,R]��С������[l,r]����ǵ��ڡ�
* ����:�����޸�,������ [l, r] ������Ԫ�ص�ֵ���� x��
* ʵ��:�����ǰ�ڵ�����䱻�޸�������ȫ����,ֱ�Ӹ���ǰ�ڵ���ϱ��;�����ǰ�ڵ���������޸����䲿���ཻ,
* �����·������,Ȼ��ݹ��޸���������,���ڵݹ����� pushup(u) ���µ�ǰ�ڵ�������;�����ǰ�ڵ���������޸�������ȫ���ཻ,�����κβ�����
---------------------------------------------------------------------------------------*/
struct segment_tree
{
    // #define maxn 100050

    #define ls u<<1
    #define rs u<<1|1
    //ע�� a�����w����Ӧ�÷ŵ�����ร�
    int a[N],w[N<<2],lazy[N<<2];

    //1��������
    void pushup(const int u)
    {
        w[u]=w[ls]+w[rs];
        //w[u]������ͣ�u*2����������u*2+1����������
    }   

    void build(const int u,int L,int R)
    {
        //����Ҷ���
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
            if(p <= M)//��ѯ������������
                return update1(ls,L,M,p,x);
            else
                return update1(rs,M+1,R,p,x);
            pushup(u);
            //ΪʲôҪ��������Ҹ����굥��󣬴������ϣ���������ȫ�������伴�ɡ�
        }
    }

    //4�������ѯ
    void maketag(int u,int len,int x)
    {
        lazy[u]+=x;//�޸ĵ�ǰ����tag���
        w[u]+=len*x;//�޸ĵ�ǰ��������͡�
    }

    //pushdown��������Ҫ����״̬��
    void pushdown(int u,int L,int R)
    {
        if(lazy[u])
        {
            int M=L+R>>1;
            maketag(ls,M-L+1,lazy[u]);//������������lazy[u]
            maketag(rs,R-M,lazy[u]);
            lazy[u]=0;
            //��Ϊ�����Ϣ�Ѿ��´�����һ���ˣ�Ϊ�˱����ظ��޸ģ���ǰ��Ҫ��ա�
        }
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
            return query(ls,L,M,l,r)+query(rs,M+1,R,l,r);
        }
        //��������ȫ���ཻ��
        else
            return 0;
    }

    // //����Ч�����Ƶ�
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

    //5�������޸ģ�
    void update(int u,int L,int R,int l,int r,int x)
    {
        if(InRange(L,R,l,r))
            maketag(u,R-L+1,x);//��ȫ����ֱ�Ӵ��Ǽ��ɡ�
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            pushdown(u,L,R);//��ѯ��ʱ��Ҳ��Ҫ��������·š�
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
�߶���Ӧ��1�������ֵ��Сֵ��
������Ҫ��query������pushup������
����query�з���0�����һ��Ҫ�����ı䣬Ҫô��inf��Ҫô��-inf
�����Ķ��ݲ����
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

    //ע�� a�����w����Ӧ�÷ŵ�����ร�
    

    //1��������
    void pushup(const int u)
    {
        w[u]=std::min(w[ls],w[rs]);
        //w[u]������ͣ�u*2����������u*2+1����������
    }   

    void build(const int u,int L,int R)
    {
        w[u]=inf;
        //����Ҷ���
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
            if(p <= M)//��ѯ������������
                update1(ls,L,M,p,x);
            else
                update1(rs,M+1,R,p,x);
            pushup(u);
            //ΪʲôҪ��������Ҹ����굥��󣬴������ϣ���������ȫ�������伴�ɡ�
        }
    }

    //4�������ѯ
    void maketag(int u,int len,int x)
    {
        lazy[u]+=x;//�޸ĵ�ǰ����tag���
        w[u]+=len*x;//�޸ĵ�ǰ��������͡�
    }

    void pushdown(int u,int L,int R)
    {
        int M=L+R>>1;
        maketag(ls,M-L+1,lazy[u]);//������������lazy[u]
        maketag(rs,R-M,lazy[u]);
        lazy[u]=0;
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
            // pushdown(u,L,R);//��ѯ��ʱ��Ҳ��Ҫ��������·š�
            return std::min(query(ls,L,M,l,r),query(rs,M+1,R,l,r));
        }
        //��������ȫ���ཻ��
        else
            return inf;
    }

    //5�������޸ģ�
    void update(int u,int L,int R,int l,int r,int x)
    {
        if(InRange(L,R,l,r))
            maketag(u,R-L+1,x);//��ȫ����ֱ�Ӵ��Ǽ��ɡ�
        else if(!OutofRange(L,R,l,r))
        {
            int M=L+R>>1;
            pushdown(u,L,R);//��ѯ��ʱ��Ҳ��Ҫ��������·š�
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
�߶���Ӧ��2��
0������[l,r]����Ϊ0
1������[l,r]����Ϊ1
2������[l,r]ÿһ��������ȡ��
3��������[l,r]��������
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

//w����������
int a[N],w[N<<2],lzy_xor[N<<2],lzy_set[N<<2];

struct segment_tree
{
    #define ls u<<1
    #define rs u<<1|1
    //1��������
    void pushup(const int u)
    {
        w[u]=w[ls]+w[rs];
        

    }   

    void build(const int u,int L,int R)
    {
        //����Ҷ���
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

    //4�������ѯ
    void maketag(int u,int len,int x,int type)
    {
        //�޸�����
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
        //���ȣ�����Ҫ��ȷ������Ĳ��������ϼ��ֵĲ�����
        //���������Ǳ���Ҫ�����Ǹɵ��ġ�
        //��������õĻ��������á�
        int M=L+R>>1;
        if(lzy_set[u])
        {
            //�������ã�����ȡ����
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
            //��Ϊ�����Ϣ�Ѿ��´�����һ���ˣ�Ϊ�˱����ظ��޸ģ���ǰ��Ҫ��ա�
        }
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

    //���ж��ٸ�1
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
            return query(ls,L,M,l,r)+query(rs,M+1,R,l,r);
        }
        //��������ȫ���ཻ��
        else
            return 0;
    }

    //5�������޸ģ�
    //����x����type����˼��
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
�������ֵ���԰汾��
--------------------------------------------------------------------------------------------------------------------------*/

    // �����޸�
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

    // �����ѯ
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
�����߶�����
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

    // �ϲ�
    void pushup(const int u)
    {
        c[u] = c[ls] + c[rs];
    }

    // 1������
    void build(const int u, int L, int R, int mid)
    {
        //����Ҷ���
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

    // 2�������ѯ
    int query1(int u, int L, int R, int p)
    {
        //����Ҷ��㷵�ؼ��ɣ��������Ҫpushdown��
        if(L == R)
            return c[u];

        pushdown(u, L, R);

        int M = L + R >> 1;
        if(p <= M)//��ѯ������������
            return query1(ls, L, M, p);
        else
            return query1(rs, M + 1, R, p);
    }

    // 3�������ѯ��1�ĸ�����
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

    // 4�������޸�
    void update(int u, int L, int R, int l, int r, int x)
    {
        if(l <= L and r >= R)
        {
            // x = 1���Ǿ���������䣬������ 0
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
