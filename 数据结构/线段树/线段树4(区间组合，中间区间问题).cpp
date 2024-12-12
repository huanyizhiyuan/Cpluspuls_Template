/*--------------------------------------------------------------------------------------------
����ϲ�����+�м��������⣺
������Ŀ�ѶȱȽϴ����������ܼ������ӣ�
1�����P6492
���漰���м����䣬������Ҫ����ls���Ҷ˵������Լ�rs����˵����������⡣
�������������úܶ����顣
�� len[i]���߶����е� i ���ڵ���ά��������ĳ��ȣ�
�� L[i]���߶����е� i ���ڵ���ά�����������˵㣻
�� R[i]���߶����е� i ���ڵ���ά����������Ҷ˵㣻
�� S[i]���߶����е� i ���ڵ���ά�������������˿�ʼ��ķ������������䳤�ȣ�ǰ׺����
�� H[i]���߶����е� i ���ڵ���ά������������Ҷ˿�ʼ��ķ������������䳤�ȣ���׺����
�� ans[i]���߶����е� i ���ڵ���ά�����������������������䳤�ȣ�
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

//���ⲻ��Ҫ����ǡ�
int LL[N<<2],RR[N<<2],S[N<<2],H[N<<2],len[N<<2],ans[N<<2];

struct segment_tree
{
    // #define maxn 100050

    #define ls u<<1
    #define rs u<<1|1

    //��u�Ľ���ֵ��ֵΪK��������һ�¸õ���Ϣ��
    void work(int u,int x)
    {
        ans[u]=S[u]=H[u]=1;
        LL[u]=RR[u]=x;
    }

    //1��������
    void pushup(const int u)
    {
        //�ϲ��м�ĳ���+�������˵ĳ��ȡ�
        //��Ŀ�����±���Ҫ���ſ��Կ��ǡ�
        if(RR[ls]^LL[rs])
        {
            //���
            //�������˺ϲ���ķ������������䳤�� 
            ans[u]=H[ls]+S[rs];
            //��������Ľ��бȽ� 
            ans[u]=std::max(ans[u],ans[ls]);
            //��������Ľ��бȽ� 
            ans[u]=std::max(ans[u],ans[rs]);
        }
        //����ֻ�ÿ�������������������䡣
        else
            ans[u]=std::max(ans[ls],ans[rs]);

        //L��R�����ά���Զ��׼� 
        //��˵���ls����˵㣬�Ҷ˵���rs���Ҷ˵�
        LL[u]=LL[ls],RR[u]=RR[rs];
        ////�������S�����������䲢����������Ҷ˵������������˵㲻ͬ,�����������S�ϲ��ɴ������S 
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
        len[u]=R-L+1;   //���䳤�ȡ�
        //����Ҷ���
        if(L==R)    
        {
            //���õ㸳ֵΪ0��������һ�¸õ���Ϣ��
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
2��P2572 [SCOI2010] ���в���
Ҫ������������
lxhgww ����յ���һ�� 01 ���У�������������� n �������±�� 0 ��ʼ����Щ��Ҫô�� 0��Ҫô�� 1�����ڶ���������������ֱ任������ѯ�ʲ�����
- 0 l r �� [l, r] �����ڵ�������ȫ��� 0��
- 1 l r �� [l, r] �����ڵ�������ȫ��� 1��
- 2 l r �� [l, r] �����ڵ�������ȫ��ȡ����Ҳ����˵�����е� 0 ��� 1�������е� 1 ��� 0��
- 3 l r ѯ�� [l, r] �������ܹ��ж��ٸ� 1��
- 4 l r ѯ�� [l, r] ����������ж��ٸ������� 1��
����ÿһ��ѯ�ʲ�����lxhgww ����Ҫ�����ش𣬴����ĳ���Ա�ǣ������ܰ�������
����100% �����ݣ� n,m <= 10^5��
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
    int lazy;   //-1 NULL,0ȫΪ0,1ȫΪ1��
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
            //������ȫ����i=1ʱ����Կ�Խ��
            if(i==1 && t[ls].w == t[ls].len)
                t[u].lmax[i] += t[rs].lmax[i];
            //������ȫ�գ�i=0ʱ����Կ�Խ��
            else if(i==0 && t[ls].w==0)
                t[u].lmax[i] += t[rs].lmax[i];

            t[u].rmax[i] = t[rs].rmax[i];
            //������ȫ����i=1ʱ����Կ�Խ��
            if(i==1 && t[rs].w == t[rs].len)
                t[u].rmax[i] += t[ls].rmax[i];
            //������ȫ�գ�i=0ʱ����Կ�Խ��
            else if(i==0 && t[rs].w==0)
                t[u].rmax[i] += t[ls].rmax[i];

            //�м����䡣
            //�����м���ϡ�
            t[u].max[i] = t[ls].rmax[i] + t[rs].lmax[i];
            //�ٿ�������ġ�
            t[u].max[i] = std::max(t[u].max[i],t[ls].max[i]);
            //�ٿ��ұ����ġ�
            t[u].max[i] = std::max(t[u].max[i],t[rs].max[i]);
        }
    }
    void build(int u,int L,int R)
    {
        //lazy == -1ΪNULL
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
        //���ȼ����
        if(t[u].lazy!=-1)
        {
            t[u].rev = 0;//��ձ�ǡ�
            int val = t[u].lazy;
            t[ls].w = t[ls].len*val;
            t[rs].w = t[rs].len*val;

            t[ls].lazy = t[rs].lazy = val;
            //�������ȼ�����rev
            t[ls].rev = t[rs].rev = 0;

            //�������Ƭ��0��1��
            t[ls].max[val]=t[ls].lmax[val]=t[ls].rmax[val]=t[ls].len;
            t[ls].max[val^1] = t[ls].lmax[val^1] = t[ls].rmax[val^1] = 0;

            //�������Ƭ��0��1��
            t[rs].max[val]=t[rs].lmax[val]=t[rs].rmax[val]=t[rs].len;
            t[rs].max[val^1] = t[rs].lmax[val^1] = t[rs].rmax[val^1] = 0;

            t[u].lazy=-1;
        }
        //���ʱ�����lazy��Ȼ���ڡ�
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
        //����Ƚ��鷳��
        else
        {
            segTree ret,L=query2(ls,l,M), R=query2(rs,M+1,r);
            ret.w = L.w+ R.w;
            for(int i=0;i<=1;i++)
            {
                ret.lmax[i] = L.lmax[i];
                //������ȫ�������Կ�Խ��
                if(i==1 && L.w == L.len)
                    ret.lmax[i] += R.lmax[i];
                else if(i==0 && L.w == 0)
                    ret.lmax[i] += R.lmax[i];

                ret.rmax[i] = R.rmax[i];
                //������ȫ�������Կ�Խ��
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