#include<bits/stdc++.h>
#define i64 long long
#define maxn 300005

i64 T=1,n,m,k,ans,cnt,sum,num,res,x,y,z,zz,p,q,flag=1;
//dg是入度，vis是判环的，不具有普遍性。
i64 a[maxn],dg[maxn],vis[maxn];

void topu()
{
	std::queue<i64>q;
	for(int i=1;i<=n;i++)
		if(dg[i]==0)
			q.push(i);//入队。
	while(!q.empty())
	{
		i64 u=q.front();
		vis[u]=1,q.pop();
		if(!--dg[a[u]])
			q.push(a[u]);
	}
}
void findcir(int u)
{
	//判环函数。
}
void solve()
{
	std::cin>>n>>k;
    //多轮样例初始化。
	for(int i=1;i<=n;i++)
		dg[i]=vis[i]=0;
	for(int i=1;i<=n;i++)
	{
		std::cin>>a[i];
		dg[a[i]]++;//入度。
	}
	topu();
	/**
     * 这道题判环很特殊！
     * 很难搞捏~
    */
	std::cout<<(ans?"YES":"NO")<<"\n";
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