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
Dijkstraģ����ܣ�
1��������ȫ�ֶ������飺
dis���飺�������顣
vis���飺��¼�Ƿ��߹�����㡣
С���ѣ�����PII�ġ�

2����ߺ�����
����ߣ�һ��Ҫ�м����ȶ����Ȩ���ٶ���ֵ��
void add_one()�����ߡ�
void add_two()��˫�ߡ�

3����ʼ�������·������
void init()��
��ʼ��һЩdis��vis���飬����st�ߡ�
void shortest_path_solve(i64 st)��
�����·���롣
---------------------------------------------------------------------------------------*/
//��������ͷŵ������ˡ�
i64 st,en;
std::vector<PII>G[maxn];
struct Dijkstra
{
    i64 dis[maxn];
    bool vis[maxn];//��ֹ�ظ���
    //ά��1�Ŷ�Ӧ��ֵ��ά��2�Ŷ�Ӧ�Ľ�㡣
    std::priority_queue<PII,std::vector<PII>,std::greater<>> q; // �������ͣ� ������ ����ʽ
    
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
        //Ҫ�ȶ����Ȩ���ٶ���㡣
        G[x].emplace_back(z,y);
        G[y].emplace_back(z,x);
    }
    
    //��Ҫ����㸳ֵΪ0��
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
    //������յ㡣
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