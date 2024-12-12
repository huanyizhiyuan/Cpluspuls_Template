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
    //Ҫ�ŵ�����ȥม�
    // int a[N],w[N<<2];

    void pushup(const int u)
    {
        w[u]=w[ls]+w[rs];
        //w[u]������ͣ�u*2����������u*2+1����������
    }   

    //1����ɢ�����̡�
    //��ǰ�������ڽ�Ԫ�ظ���ӳ�䵽Ҷ�ӽڵ�Ĺ����У���ɢ�̶Ƚϴ�ʱ�ᵼ�¼��͵Ŀռ�����Ч�ʡ�
    //�Ա������ݽṹ�����ǹ��ĵĽ�����Ԫ��֮��Ĵ�С��ϵ����˿��Բ�����ɢ���ķ����Կռ�����Ż���
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

    //2������
    //2.1�����ҵ�KС��
    int find_kth_min(int u, int L, int R, int k)
    {
        if(L == R) 
            return L;
        int M = (L + R) >> 1, num = w[rs];
        //����������Ľ������㹻��Ļ���˵���ұ�����K����Ҫ��
        if(k <= num) 
            return find_kth_min(rs, M+1, R, k);
        else 
            return find_kth_min(ls, L, M, k - num);
    }

    //2.2�����ҵ�K��
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

    //3��������²�����
    //���ƻ����߶������ݹ鵽Ҷ�ӽڵ�+ 1 +1+1Ȼ�����
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

    //4����ѯ
    //4.1��ĳ�������ֵĸ���
    //���϶��ֲ��ҵ�˼�룬�������£���
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

    //4.2����ѯһ������������ֵĴ���

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
            return query(ls,L,M,l,r)+query(rs,M+1,R,l,r);
        }
        //��������ȫ���ཻ��
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