#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=6e5+10;
const i64 M = N * 25;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;
int max_id[M],s[N];
// root[i]����ǵ�i���汾�������±�
int root[N], idx;
int tr[M][2];

struct Persistent_01_Trie
{
    //const int N = 600010, M = N * 25, POS = 23;
    // ��s[k]��������뵽Trie���һ���汾�������±���p���°汾�������±���q
    #define POS 23
    void insert(int k,int p,int q)
    {
        for(int i=POS;i>=0;i--)
        {
            //ȡ��������λ��
            int v=s[k]>>i & 1;
            //���p���գ���ô���ò���������·���ã����ӵ�q���档
            if(p)tr[q][v^1] = tr[p][v^1];
            //�����޸ĵ�·����һ���½�㡣
            tr[q][v]=++idx;
            //ͬʱ��������VŲ��һ����
            p=tr[p][v],q=tr[q][v];
            //��¼һ���ߵ�q���λ�����ߵ�������s����±����ֵ��
            max_id[q]=k;
        }
    }

    // ���±�Ϊroot���Ǹ��汾��Trie������C�������·����L����߽磬����������
    int query(int root, int C, int L) 
    {
        int p = root;
        for(int i=POS;i>=0;i--)
        {
            int v = C>>i&1;
            // �����ߺ�v��ͬ��·��̰��˼�롣���ߵ��ҽ���v ^ 1����·�����±���ڵ���L������
            // �����ߵĻ��Ǿ���v����·
            if (max_id[tr[p][v ^ 1]] >= L) 
                p = tr[p][v ^ 1];
            else 
                p = tr[p][v];
        }
        return C ^ s[max_id[p]];
    }
    #undef POS
}Tree;

void solve()
{
    std::cin>>n>>m;
    // Ϊ�˷�ֹ�ߵ��սڵ��ϣ����սڵ���±���Ϊ-1
    max_id[0] = -1;
    //��0ǰ׺����Trie����Ϊ�汾1��
    root[0]=++idx;
    Tree.insert(0,0,root[0]);

    for(int i=1;i<=n;i++)
    {
        int x;
        std::cin>>x;
        s[i]=s[i-1]^x;
        //���°汾���������ٸ��ռ䡣
        root[i]=++idx;
        Tree.insert(i,root[i-1],root[i]);
    }
    
    char op;
    int l,r,x;
    while(m--)
    {
        std::cin>>op;
        //����һ�����֡�
        if(op=='A')
        {
            std::cin>>x;
            n++;
            s[n]=s[n-1]^x;
            root[n]=++idx;
            Tree.insert(n,root[n-1],root[n]);
        }
        else
        {
            std::cin>>l>>r>>x;
            std::cout<<Tree.query(root[r-1],s[n]^x,l-1)<<"\n";
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