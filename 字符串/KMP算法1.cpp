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

i64 b[maxn];
std::string s1,s2,ss;
/*-------------------------------------------------------------------------------------
ǰ׺������KMP�㷨
a��ģʽ����ss���ı�����
PRE���������ǰ׺���顣
KMP���������ƥ���ַ�����
PRE����Ԣ����KMP���������������ǿ�ͷ���ַ��϶��ǹ����õģ�Ҳ����˵���Ͷ�Ӧ�Լ�������
i��1��ʼ��j��0��ʼ��
---------------------------------------------------------------------------------------*/
//����ַ���a��ǰ׺���顣
void PRE(std::string a)
{
    // b[1]=0;
    for(int i=1,j=0;i<a.size();i++)
    {
        while(j>0&&a[i]!=a[j])j=b[j-1];
        if(a[i]==a[j])j++;
        b[i]=j;
    }
}

//ƥ���ַ���a��ss
//a��ģʽ����ss���ı�����
void KMP(std::string s,std::string a)
{
    for(int i=0,j=0;i<a.size();i++)
    {
        while(j>0&&a[i]!=s[j])
            j=b[j-1];
        if(a[i]==s[j])j++;
        if(j==s.size())
        {
            for(int k=i-s.size()+1;k<=i;k++)
                dp[k]=1;
            j=0;
        }
    }
}

void solve()
{
    std::cin>>s1>>s2;
    i64 len1=s1.size(),len2=s2.size();
    for(int i=1,j=0;i<len2;i++)
    {
        while(j>0&&s2[i]!=s2[j])//����ǰ׺���顣
            j=b[j-1];
        if(s2[j]==s2[i])j++;//ƥ�����ˡ�
        b[i]=j;
    }
    for(int i=0,j=0;i<len1;i++)
    {
        while(j>0&&s1[i]!=s2[j])
            j=b[j-1];
        if(s2[j]==s1[i])
            j++;
        if(j==len2)
        {
            std::cout<<(i+1-len2+1)<<"\n";
            j=b[j-1];
        }
    }
    // for(int i=0;i<len2;i++)
    //     std::cout<<b[i]<<" ";
    // std::cout<<"\n";
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