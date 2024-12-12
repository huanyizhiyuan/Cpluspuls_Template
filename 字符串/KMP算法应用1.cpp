/**
 * 二分答案，枚举子串长度的KMP+PRE前缀数组。
 * 我们可以先找重复的，再不断地去除重复。
 * https://codeforces.com/contest/1968/problem/G1
*/

#include<bits/stdc++.h>
#define i64 long long
#define maxn 1000500
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;
i64 a[maxn],b[maxn];
std::vector<PII>G[maxn];
i64 Left,Right;

std::vector<int> ve;

//获得字符串s的前缀函数。
void PRE(std::string s,int len)
{
    for(int i=1,j=0;i<len;i++)
    {
        while(j>0&&s[i]!=s[j])j=b[j-1];
        if(s[i]==s[j])j++;
        b[i]=j;
    }
}

void KMP(std::string s1,std::string s2)
{
    //计算前缀数组。
    int len=s2.size();
    PRE(s2,len);
    for(int i=0,j=0;i<s1.size();i++)
    {
        while(j>0&&s1[i]!=s2[j])
            j=b[j-1];
        if(s1[i]==s2[j])
            j++;
        //与模式串完全匹配。
        if(j==len)
        {
            ve.pb(i-len+1);//存储答案
            j=b[j-1];//继续匹配。
        }
    }
}
bool check(std::string s,std::string a,int k)
{
    KMP(s,a);
    // std::cout<<"到这里了吗？"<<"\n";
    int num=0;
    //去掉重叠的匹配子串。
    if(ve.size()>=1)
    {
        // std::cout<<"ve:";
        // for(auto v:ve)
        //     std::cout<<v<<" ";
        // std::cout<<"\n";
        //开头的算一个。
        num++;
        int last=ve[0];
        for(int i=1;i<ve.size();i++)
        {
            if(ve[i]-last>k-1)
            {
                num++;
                last=ve[i];
            }
        }
    }
    ve.clear();
    // std::cout<<"num="<<num<<"\n";
    if(num>=Left)
        return 1;
    else
        return 0;
}
void solve()
{
    std::string s;
    std::cin>>n>>Left>>Right>>s;
    //为什么r要这么放？
    // int l=0,r=n/Left,mid,ans=l;
    int l=0,r=n,mid,ans=l;
    while(l<=r)
    {
        mid=l+r>>1;
        //前缀字符。
        std::string a=s.substr(0,mid);
        // std::cout<<"mid="<<mid<<",str_a="<<a<<"\n";
        if(check(s,a,mid))
            ans=mid,l=mid+1;
        else
            r=mid-1;
    }
    std::cout<<ans<<"\n";
}

signed main()
{
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    // std::cout.tie(nullptr);
    std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}