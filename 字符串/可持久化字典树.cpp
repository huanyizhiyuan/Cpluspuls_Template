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
// root[i]存的是第i个版本的树根下标
int root[N], idx;
int tr[M][2];

struct Persistent_01_Trie
{
    //const int N = 600010, M = N * 25, POS = 23;
    // 将s[k]这个数插入到Trie里，上一个版本的树根下标是p，新版本的树根下标是q
    #define POS 23
    void insert(int k,int p,int q)
    {
        for(int i=POS;i>=0;i--)
        {
            //取出二进制位。
            int v=s[k]>>i & 1;
            //如果p不空，那么把用不到的那条路复用，即接到q下面。
            if(p)tr[q][v^1] = tr[p][v^1];
            //发生修改的路径开一个新结点。
            tr[q][v]=++idx;
            //同时向下沿着V挪动一步。
            p=tr[p][v],q=tr[q][v];
            //记录一下走到q这个位置能走到的数在s里的下标最大值。
            max_id[q]=k;
        }
    }

    // 从下标为root的那个版本的Trie搜索与C异或最大的路径，L是左边界，返回最大异或
    int query(int root, int C, int L) 
    {
        int p = root;
        for(int i=POS;i>=0;i--)
        {
            int v = C>>i&1;
            // 尽量走和v不同的路，贪心思想。能走当且仅当v ^ 1那条路存在下标大于等于L的数；
            // 不能走的话那就走v这条路
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
    // 为了防止走到空节点上，将空节点的下标设为-1
    max_id[0] = -1;
    //把0前缀加入Trie，作为版本1：
    root[0]=++idx;
    Tree.insert(0,0,root[0]);

    for(int i=1;i<=n;i++)
    {
        int x;
        std::cin>>x;
        s[i]=s[i-1]^x;
        //给新版本的树根开辟个空间。
        root[i]=++idx;
        Tree.insert(i,root[i-1],root[i]);
    }
    
    char op;
    int l,r,x;
    while(m--)
    {
        std::cin>>op;
        //增加一个数字。
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