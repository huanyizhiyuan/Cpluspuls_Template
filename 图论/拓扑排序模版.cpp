#include<bits/stdc++.h>
#define i64 long long
#define maxn 300005

i64 T=1,n,m,k,ans,cnt,sum,num,res,x,y,z,zz,p,q,flag=1;
//dg����ȣ�vis���л��ģ��������ձ��ԡ�
i64 a[maxn],dg[maxn],vis[maxn];

void topu()
{
	std::queue<i64>q;
	for(int i=1;i<=n;i++)
		if(dg[i]==0)
			q.push(i);//��ӡ�
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
	//�л�������
}
void solve()
{
	std::cin>>n>>k;
    //����������ʼ����
	for(int i=1;i<=n;i++)
		dg[i]=vis[i]=0;
	for(int i=1;i<=n;i++)
	{
		std::cin>>a[i];
		dg[a[i]]++;//��ȡ�
	}
	topu();
	/**
     * ������л������⣡
     * ���Ѹ���~
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