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
i64 a[maxn],dp[maxn];
std::vector<PII>G[maxn];

struct Tree//�ֵ��� 
{
     int fail;//ʧ��ָ��
     int vis[26];//�ӽڵ��λ��
     int end;//����м�������������ڵ��β 
};

struct AC_AUTO
{
    Tree AC[1000000+10];//Trie��
    int cnt=0;//Trie��ָ�� 

    //��������
    void Build(std::string s)
    {
        int l=s.size();
        int u=0;//�ֵ����ĵ�ǰָ��
        for(int i=0;i<l;++i)//����Trie��
        {
            int ch = s[i] - 'a';
            if(AC[u].vis[ch]==0)//Trie��û������ӽڵ�
                AC[u].vis[ch] = ++cnt;//�������
            u=AC[u].vis[ch];//���¹���
        }
        AC[u].end+=1;//��ǵ��ʽ�β
    }
    
    //����failָ�롣
    void Get_fail()//����failָ��
    {
        std::queue<int>Q;//���� 
        //��ԭ
        for(int i=0;i<26;++i)//�ڶ����failָ����ǰ����һ��
        {
            if(AC[0].vis[i]!=0)
            {
                AC[AC[0].vis[i]].fail=0;//ָ����ڵ�
                Q.push(AC[0].vis[i]);//ѹ����� 
            }
        }
        while(!Q.empty())//BFS��failָ�� 
        {
            int u=Q.front();
            Q.pop();
            for(int i=0;i<26;++i)//ö�������ӽڵ�
            {
                if(AC[u].vis[i]!=0)//��������ӽڵ�
                {
                    AC[AC[u].vis[i]].fail=AC[AC[u].fail].vis[i];
                        //�ӽڵ��failָ��ָ��ǰ�ڵ��
                        //failָ����ָ��Ľڵ����ͬ�ӽڵ� 
                    Q.push(AC[u].vis[i]);//ѹ����� 
                }
                else//����������ӽڵ� 
                    AC[u].vis[i]=AC[AC[u].fail].vis[i];
                    //��ǰ�ڵ������ӽڵ�ָ��
                    //ǰ�ڵ�failָ�������ӽڵ� 
            }
        }
    }

    //AC�Զ���ƥ��
    int AC_Query(std::string s)
    {
        int l=s.length();
        int u=0,res=0;
        for(int i=0;i<l;++i)
        {
            u=AC[u].vis[s[i]-'a'];//����һ��
            for(int t=u;t&&AC[t].end!=-1;t=AC[t].fail)//ѭ�����
            {
                res+=AC[t].end;
                AC[t].end=-1;
            } 
        }
        return res;
    }
}ACAM;

std::string s;

void solve()
{
    std::cin>>n;
    for(int i=1;i<=n;i++)
    {
        std::cin>>s;
        ACAM.Build(s);
    }
    ACAM.AC[0].fail=0;//������־��
    ACAM.Get_fail();
    std::cin>>s;//�����ı�����
    std::cout<<ACAM.AC_Query(s)<<"\n";
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