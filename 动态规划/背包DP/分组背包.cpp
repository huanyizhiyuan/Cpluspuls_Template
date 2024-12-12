#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<int,int> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;
i64 a[500][500],dp[maxn];

//分组背包板子,V为容量，K为组数，GMC为每组元素个数
void group_package(int V,int K,int GMC)
{
	for(int k=1;k<=K;k++)
	{
		for(int v=V;v>0;v--)
		{
			for(int i=1;i<=GMC;i++)
				if(v-a[k][i]>=0)
					dp[v]=std::max(dp[v],dp[v-a[k][i]]+k*i);
		}
	}
}
void solve()
{
	i64 s;
	//s=100,n=100,m=20000
	//输入第一行包含三个正整数 ?,?,?分别表示除了小 C 以外的玩家人数、城堡数和每名玩家拥有的士兵数。
	std::cin>>s>>n>>m;
	//a[j][i] 存储的是第 i 个玩家对第 j 座城堡派遣的士兵数量。
	//以城堡作为组别
	for(int i=1;i<=s;i++)
		for(int j=1;j<=n;j++)
			//这里i与j反过来了。
			std::cin>>a[j][i];

	for(int i=1;i<=n;++i)
    {
        std::sort(a[i]+1,a[i]+1+s);//先排序
        for(int j=1;j<=s;j++)//排序完把玩家兵力改为攻打兵力
            a[i][j]=a[i][j]*2+1;   
    }
	//背包遍历。
	group_package(m,n,s);
	std::cout<<dp[m]<<"\n";
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