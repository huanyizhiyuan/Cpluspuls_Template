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
i64 a[maxn],dp[maxn];
std::vector<PII>G[maxn];

struct trie_01
{
    // std::vector<std::vector<int>> nex;
    // std::vector<int> word;
    // i64 tot;

    // trie_01() : nex(n * 31 + 10, std::vector<int>(2, 0)), word(n * 31 + 10, 0), tot(0) {}

    i64 nex[maxn*31+10][2], tot=0;//ÿ����㶼������26���ӽ�㡣
    // bool word[maxn];  // �ý���β���ַ����Ƿ���ڡ�
    // int word[maxn];  // ���ڼ�¼��������Ϊ����ĩβ���ʸ�����

    // ������
    void insert(i64 a) 
    {  
        i64 u = 0;//����㡣
        for (i64 i=(1ll<<30);i;i>>=1) 
        {
            i64 c = bool(a&i);
            if (!nex[u][c]) nex[u][c] = ++tot;  // ���û�У�����ӽ��
            u = nex[u][c];
            // res+=word[u];    //�����Ѿ����ڵġ�
        }
        // word[u]++;
    }

    // �����ַ��������Ҫ���ر������Ҫ��Ϊint
    i64 find(i64 a)
    {  
        i64 p = 0,res = 0;
        for (i64 i=(1ll<<30);i;i>>=1) 
        {
            i64 c = bool(a&i);
            if (nex[p][!c])//����ѡ�񷴷��� 
            {
                res+=i;//˵���Ҳ�ͬ��
                p = nex[p][!c];
            }
            else
                p = nex[p][c];
        }
        //�����word[p]�������жϵ����Ƿ���ڵġ�
        //ǰ��ı���˵������������������֤����������ʡ�
        return res;
    }
}Tree;



void solve()
{
    
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}

/*-----------------------------------------------------------------------------
�°汾��
1�����á�
2�����롣
3�������ֵ��
4������Сֵ��
-----------------------------------------------------------------------------------*/
struct trie_01
{
    int nex[N*20][2], tot=0;

    void reset()
    {
        for(int i = 0;i <= tot;i ++)
            nex[i][0] = nex[i][1] = 0;
        tot = 0;
    }

    // ������
    void insert(i64 a)
    {
        i64 u = 0;//����㡣
        for (i64 i=(1ll<<20);i;i>>=1)
        {
            i64 c = bool(a&i);
            if (!nex[u][c]) nex[u][c] = ++tot;  // ���û�У�����ӽ��
            u = nex[u][c];
        }
    }

    i64 find_max(i64 a)
    {
        i64 p = 0, res = 0;
        for (i64 i=(1ll<<20);i;i>>=1)
        {
            i64 c = bool(a&i);
            if (nex[p][!c])
            {
                res+=i;
                p = nex[p][!c];
            }
            else
                p = nex[p][c];
        }
        return res;
    }

    i64 find_min(i64 a)
    {
        i64 p = 0, res = 0;
        for(i64 i = (1ll << 20);i;i >>= 1)
        {
            i64 c = bool(a & i);
            if(nex[p][c])
                p = nex[p][c];
            else
            {
                p = nex[p][!c];
                res += i;
            }
        }
        return res;
    }
}Tree;