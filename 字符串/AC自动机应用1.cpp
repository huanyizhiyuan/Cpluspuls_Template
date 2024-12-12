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

std::map<std::string,i64>mp;

struct Tree//�ֵ��� 
{
    int fail;//ʧ��ָ��
    int vis[26];//�ӽڵ��λ��
    //  int end;//����м�������������ڵ��β 
    int end;//���������ڵ��β�ĵ��ʱ�� 
};

struct Result
{
    int num;
    int pos;
    bool operator<(const Result & n1)const
    {
        if(num!=n1.num)
            return num>n1.num;
        else
            return pos<n1.pos;
    }
}Ans[300];//���е��ʵĳ��ִ�����

struct AC_AUTO
{
    Tree AC[150*70*26+10];//Trie��
    int cnt=0;//Trie��ָ�� 

    void Clean(int x)
    {
        // if(x==0)cnt=0;
        //����memset����С�ĵ㡣
        for(int i=0;i<sizeof(AC[x].vis);i++)
            AC[x].vis[i]=0;
        // memset(AC[x].vis,0,sizeof(AC[x].vis));
        AC[x].fail=0;
        AC[x].end=0;
    }

    //��������
    void Build(std::string s,int index)
    {
        int l=s.size();
        int u=0;//�ֵ����ĵ�ǰָ�� 
        for(int i=0;i<l;++i)//����Trie��
        {
            if(AC[u].vis[s[i]-'a']==0)//Trie��û������ӽڵ�
            {
                AC[u].vis[s[i]-'a']=++cnt;//�������
                Clean(cnt);//���һ�¡�
            }    
            u=AC[u].vis[s[i]-'a'];//���¹��� 
        }
        AC[u].end=index;//��ǵ��ʽ�β 
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
    void AC_Query(std::string s)
    {
        int l=s.length();
        int u=0;
        // int res;
        for(int i=0;i<l;++i)
        {
            u=AC[u].vis[s[i]-'a'];//����һ��
            for(int t=u;t;t=AC[t].fail)//ѭ�����
                Ans[AC[t].end].num++; 
                //��0����Ҳ������ν�ġ�
        }
        // return res;
    }
}ACAM;

std::string s[300];

void solve()
{
    //�����ֻ��Ҫ�����޸ĵı��Ǻ���AC.Query(s)��
    while(std::cin>>n)
    {
        if(n==0)break;
        cnt=0;
        ACAM.Clean(0);
        for(int i=1;i<=n;i++)
        {
            std::cin>>s[i];
            Ans[i].num=0;
            Ans[i].pos=i;//˳������Ϊ��δ������
            ACAM.Build(s[i],i);//������
        }
        ACAM.AC[0].fail=0;//������־��
        ACAM.Get_fail();

        std::cin>>s[0];//�����ı�����
        ACAM.AC_Query(s[0]);//���в�ѯ�ء�

        std::sort(&Ans[1],&Ans[n+1]);
        std::cout<<Ans[1].num<<"\n";
        std::cout<<s[Ans[1].pos]<<"\n";
        for(int i=2;i<=n;i++)
        {
            if(Ans[i].num==Ans[i-1].num)
                std::cout<<s[Ans[i].pos]<<"\n";
            else
                break;
        }
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