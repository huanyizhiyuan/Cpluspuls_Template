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
前缀数组与KMP算法
a是模式串，ss是文本串。
PRE函数：求出前缀数组。
KMP函数：求出匹配字符串。
PRE函数寓意是KMP表构建，首先是我们开头的字符肯定是构建好的，也就是说它就对应自己，所以
i从1开始，j从0开始。
---------------------------------------------------------------------------------------*/
//求出字符串a的前缀数组。
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

//匹配字符串a与ss
//a是模式串，ss是文本串。
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
        while(j>0&&s2[i]!=s2[j])//计算前缀数组。
            j=b[j-1];
        if(s2[j]==s2[i])j++;//匹配上了。
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