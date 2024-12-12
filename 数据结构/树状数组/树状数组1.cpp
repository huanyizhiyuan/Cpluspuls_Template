/*----------------------------------------------------------------------------
��״����
�����Ͼ���������
1��lowbit
2��ǰ׺�����
3����������롣

��״����������ֵ��Ҫ������顣
----------------------------------------------------------------------------*/

// add������0�͸���
// ����������һ�������С�
// ���Լ���״���飬���Լ�ԭ��������
struct Fenwick_Tree_Array
{
    std::vector<int>c;
    int len;

    Fenwick_Tree_Array(int size) : len(size){
        c.assign(size + 1, 0);
    }

    int lowbit(i64 x){return x & (-x);}

    //���������[1,x]��
    int Prefix_Sum(int x)
    {
        int res = 0;
        for(int i = x;i;i -= lowbit(i))
            res += c[i];
        return res;
    }

    // ���������˵㡣
    // ��ʾ��Χ[l,r]�ĺ͡�
    int RangeSum(int l, int r)
    {
        return Prefix_Sum(r) - Prefix_Sum(l - 1);
    }

    //��xλ�ã�����y��
    void add(int x,int y)
    {
        //��С�����޸���Ҫ�޸ĵ�λ�á�
        for(int i = x;i <= len;i += lowbit(i))
            c[i] += y;
    }
};


/*----------------------------------------------------------------------------
һ�ּ�̵�д����
----------------------------------------------------------------------------*/
int pre[N];
void init()
{
    for(int i=1;i<=n;i++)
    {
        pre[i]=pre[i-1]+a[i];
        c[i]=pre[i]-pre[i-lowbit(i)];
    }
}
/*----------------------------------------------------------------------------
vector�汾��������󷨡�
�����ʵ���Ͼ��ǣ�
�����޸ģ������ѯ���⡣
ǡǡ�ÿ���ʹ����״�����������
----------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define int i64
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
int n,m,k;
std::vector<int>c(N);
struct Fenwick_Tree_Array
{   
    int lowbit(int x){return x&(-x);}
    //��״������������[1,x]������ǰ׺�͡�
    int Prefix_Sum(int x)
    {
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res+=c[i];
        return res;
    }
    //��xλ�ã�����y��
    void add(int x,int y)
    {
        //��С�����޸���Ҫ�޸ĵ�λ�á�
        for(int i=x;i<=n;i+=lowbit(i))
            c[i]+=y;
    }
}FTA;

void solve()
{
    std::cin>>n;
    std::vector<int>a(n,0);
    std::vector<int>b(n,0);
    //std::fill(c.begin(), c.end(), 0); // ��ʼ����״����
    c.assign(N,0);
    //������Ҫ������ɢ������Ȼ����ⲻ��Ҫ��
    for(int i=0;i<n;i++)
    {
        std::cin>>a[i];
        b[i]=a[i];
    }
    std::sort(b.begin(),b.end());
    for(auto &v:a)
    {
        v = std::lower_bound(b.begin(),b.end(),v)-b.begin()+1;
    }
    //�����޸�+ǰ׺�Ͳ��ҡ�
    int ans=0;
    for(auto v:a)
    {
        ans += FTA.Prefix_Sum(n)-FTA.Prefix_Sum(v-1);
        FTA.add(v,1);
    }
    std::cout<<ans<<"\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T=1;
    std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}

/*----------------------------------------------------------------------------
��״����Ҳ����ά�����ֵ��
----------------------------------------------------------------------------*/
std::vector<int>c(200005, 0);

struct Fenwick_Tree_Array
{
    int lowbit(i64 x){return x&(-x);}
    //��״��������������ֵ[1,x]��
    int get(int x)
    {
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res = std::max(res, c[i]);
        return res;
    }
    //��xλ�ã�����y��
    void add(int x,int y,int z)
    {
        //��С�����޸���Ҫ�޸ĵ�λ�á�
        for(int i=x;i<=200005;i+=lowbit(i))
            c[i] = std::max(c[i], y);
    }
}FTA;
