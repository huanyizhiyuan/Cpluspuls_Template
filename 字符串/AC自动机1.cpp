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

struct Tree//字典树 
{
     int fail;//失配指针
     int vis[26];//子节点的位置
     int end;//标记有几个单词以这个节点结尾 
};

struct AC_AUTO
{
    Tree AC[1000000+10];//Trie树
    int cnt=0;//Trie的指针 

    //构建树。
    void Build(std::string s)
    {
        int l=s.size();
        int u=0;//字典树的当前指针
        for(int i=0;i<l;++i)//构造Trie树
        {
            int ch = s[i] - 'a';
            if(AC[u].vis[ch]==0)//Trie树没有这个子节点
                AC[u].vis[ch] = ++cnt;//构造出来
            u=AC[u].vis[ch];//向下构造
        }
        AC[u].end+=1;//标记单词结尾
    }
    
    //构建fail指针。
    void Get_fail()//构造fail指针
    {
        std::queue<int>Q;//队列 
        //还原
        for(int i=0;i<26;++i)//第二层的fail指针提前处理一下
        {
            if(AC[0].vis[i]!=0)
            {
                AC[AC[0].vis[i]].fail=0;//指向根节点
                Q.push(AC[0].vis[i]);//压入队列 
            }
        }
        while(!Q.empty())//BFS求fail指针 
        {
            int u=Q.front();
            Q.pop();
            for(int i=0;i<26;++i)//枚举所有子节点
            {
                if(AC[u].vis[i]!=0)//存在这个子节点
                {
                    AC[AC[u].vis[i]].fail=AC[AC[u].fail].vis[i];
                        //子节点的fail指针指向当前节点的
                        //fail指针所指向的节点的相同子节点 
                    Q.push(AC[u].vis[i]);//压入队列 
                }
                else//不存在这个子节点 
                    AC[u].vis[i]=AC[AC[u].fail].vis[i];
                    //当前节点的这个子节点指向当
                    //前节点fail指针的这个子节点 
            }
        }
    }

    //AC自动机匹配
    int AC_Query(std::string s)
    {
        int l=s.length();
        int u=0,res=0;
        for(int i=0;i<l;++i)
        {
            u=AC[u].vis[s[i]-'a'];//向下一层
            for(int t=u;t&&AC[t].end!=-1;t=AC[t].fail)//循环求解
            {
                res+=AC[t].end;
                AC[t].end=-1;
            } 
        }
        return res;
    }
}ACAM;

std::string s;

void solve()
{
    std::cin>>n;
    for(int i=1;i<=n;i++)
    {
        std::cin>>s;
        ACAM.Build(s);
    }
    ACAM.AC[0].fail=0;//结束标志。
    ACAM.Get_fail();
    std::cin>>s;//输入文本串；
    std::cout<<ACAM.AC_Query(s)<<"\n";
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