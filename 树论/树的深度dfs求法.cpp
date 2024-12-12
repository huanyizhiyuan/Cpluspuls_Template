#include<bits/stdc++.h>
#define ll long long
#define int ll
#define maxn 300050
#define mod 998244353
#define pb push_back
using namespace std;
int T=1,n,m,d,k,ans,cnt,sum,num,x,y,z;
int a[maxn],dp[maxn],dis[maxn];
vector<int>ve[maxn];
void dfs(int u,int fa){
    //如果当前能碰到，那就ans++
    if(dis[u]<=d)ans++;
    for(int i=0;i<ve[u].size();i++){
        int v=ve[u][i];
        if(v==fa)continue;
        dis[v]=dis[u]+1;
        dfs(v,u);
    }
}
void solve()
{
    cin>>n>>d;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        ve[u].pb(v),ve[v].pb(u);
    }
    dfs(1,0);
    //减去开头。
    printf("%lld\n",ans-1);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // cin>>T;
    T=1;
    while(T--)
    {
        solve();
    }
    return  0;
}