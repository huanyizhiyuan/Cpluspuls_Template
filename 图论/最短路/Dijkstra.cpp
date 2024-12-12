#include<bits/stdc++.h>
#define i64 long long
#define maxn 200050
#define pb push_back
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,num,res,avg,x,y,z,zz,p,flag=1;

/*-------------------------------------------------------------------------------------
Dijkstra模版介绍：
1、首先是全局定义数组：
dis数组：距离数组。
vis数组：记录是否走过这个点。
小顶堆：关于PII的。

2、填边函数：
读入边，一定要切记是先读入边权，再读入值。
void add_one()：单边。
void add_two()：双边。

3、初始化与最短路函数：
void init()：
初始化一些dis与vis数组，还有st边。
void shortest_path_solve(i64 st)：
求最短路距离。
---------------------------------------------------------------------------------------*/
//这两玩意就放到外面了。
i64 st,en;
std::vector<PII>G[maxn];
struct Dijkstra
{
    i64 dis[maxn];
    bool vis[maxn];//防止重根。
    //维度1放对应的值，维度2放对应的结点。
    std::priority_queue<PII,std::vector<PII>,std::greater<>> q; // 数据类型， 容器， 排序方式
    
    void add_one()
    {
        i64 x,y,z;
        std::cin>>x>>y>>z;
        G[x].emplace_back(z,y);
    }

    void add_two()
    {
        i64 x,y,z;
        std::cin>>x>>y>>z;
        //要先读入边权，再读入点。
        G[x].emplace_back(z,y);
        G[y].emplace_back(z,x);
    }
    
    //需要给起点赋值为0；
    void init(i64 st)
    {
        for(int i=0;i<=n;i++)
            dis[i]=inf,vis[i]=0;
        dis[st]=0;
    } 

    
    void shortest_path_solve(i64 st)
    {
        init(st);
        q.emplace(0,st);
        while(!q.empty())
        {
            i64 u=q.top().second;
            q.pop();
            if(vis[u])continue;
            vis[u]=1;
            for(auto [w, v]: G[u])
            {
                if(dis[v]>dis[u]+w)
                {
                    dis[v]=dis[u]+w;
                    q.emplace(dis[v],v);
                }
            }
        }
    }
}dijk;

void solve()
{
    std::cin>>n>>m;
    for(int i=1;i<=m;i++)
        dijk.add_one();
    //起点与终点。
    // std::cin>>st>>en;
    st=1,en=n;
    dijk.shortest_path_solve(st);
    if(dijk.dis[en]==inf)
        std::cout<<-1<<"\n";
    else
        std::cout<<dijk.dis[en]<<"\n";
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