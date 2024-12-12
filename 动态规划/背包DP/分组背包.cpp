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

//���鱳������,VΪ������KΪ������GMCΪÿ��Ԫ�ظ���
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
	//�����һ�а������������� ?,?,?�ֱ��ʾ����С C ���������������Ǳ�����ÿ�����ӵ�е�ʿ������
	std::cin>>s>>n>>m;
	//a[j][i] �洢���ǵ� i ����ҶԵ� j ���Ǳ���ǲ��ʿ��������
	//�ԳǱ���Ϊ���
	for(int i=1;i<=s;i++)
		for(int j=1;j<=n;j++)
			//����i��j�������ˡ�
			std::cin>>a[j][i];

	for(int i=1;i<=n;++i)
    {
        std::sort(a[i]+1,a[i]+1+s);//������
        for(int j=1;j<=s;j++)//���������ұ�����Ϊ�������
            a[i][j]=a[i][j]*2+1;   
    }
	//����������
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