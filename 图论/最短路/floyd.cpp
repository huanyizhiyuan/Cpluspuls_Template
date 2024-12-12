#include<bits/stdc++.h>
#define i64 long long
#define maxn 200050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;
std::vector<PII>G[maxn];
i64 dis[300][300];
void floyd()
{
    //���ڸ������Ի�������
    for(int k=1;k<=n;k++)//Floyd���岿��
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
}
void solve()
{
    i64 q;
    std::cin>>n>>m>>q;
    //Դ�㵽Դ�㱾��ľ���Ϊ0 ������Dijkstra��ȷ����Դ��Ϊ1 ���Գ�ʼ��dist[1]=0�Ϳ����� ��FloydΪ��Դ�� 
    //����Ҫ��ʼ��i==j�����п��ܵ�Դ�� ������Dijkstra��ʼ������Դ��Ҳ�ǿ��Ե�
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j)
                dis[i][j]=0;
            else
                dis[i][j]=inf;
        }

    for(int i=1;i<=m;i++)
    {
        i64 x,y,z;
        std::cin>>x>>y>>z;
        //��������رߵ����������̵�һ����
        dis[x][y]=std::min(dis[x][y],z);
    }
    floyd();
    while(q--)
    {
        i64 x,y;
        std::cin>>x>>y;
        if(dis[x][y]>=inf/2)
            std::cout<<"impossible\n";
        else
            std::cout<<dis[x][y]<<"\n";
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