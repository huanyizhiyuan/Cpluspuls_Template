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

/*-------------------------------------------------------------------------------------
1��#include <iomanip>
C++����С���㣺
std::cout << std::fixed << std::setprecision(12) << ans << "\n";

2��C++11 ����� Lambda ���ʽ
[](node x,node y){return x.p>y.p;}
[]: ���� Lambda ���ʽ�Ĳ����Ӿ�(capture clause)����ָ���� Lambda ���ʽ���Է��ʵ��ⲿ�����������������,�����Ӿ�Ϊ��,��ʾ Lambda ���ʽ�������κ��ⲿ������
(node x, node y): ���� Lambda ���ʽ�Ĳ����б���ָ���� Lambda ���ʽ���ܵĲ������ͺ����ơ������������,Lambda ���ʽ�������� node ���͵Ĳ���,�ֱ�����Ϊ x �� y��
{ return x.p > y.p; }: ���� Lambda ���ʽ�ĺ����塣�������� Lambda ���ʽ����Ϊ�������������,Lambda ���ʽ�Ƚ����� node ����� p ��Ա,�����رȽϽ����

������������Lambda���ʽ�����ӡ�
---------------------------------------------------------------------------------------*/
std::cout << std::fixed << std::setprecision(12) << ans << "\n";

struct node{
	int p,id;
};

if(s[0]>=s[len-1])
    std::sort(ans+1,ans+cnt+1,[](node x,node y){return x.p>y.p;});
else
    std::sort(ans+1,ans+cnt+1,[](node x,node y){return x.p<y.p;});

auto query = [&](int l,int x)->int {
    std::cout<<"? "<< l << " " << x <<std::endl;
    int r;
    std::cin>>r;
    return r;
};

auto check = [&](int m)->bool{
    int cur = 0;
    for(int i = 0;i<k;i++)
    {
        if(cur==n){
            return false;
        }
        int pos=query(cur+1,m);
        if(pos==n+1)
        {
            return false;
        }
        cur=pos;
    }
    return cur==n;
};

auto output = [&](int m)->void{
    std::cout<<"! "<< m << std::endl;
    int r;
    std::cin>>r;
};
//���������ʵ����
auto dfs = [&](auto self,i64 u,i64 now)
{
    if(dis[u])return ;
    dis[u]=now;
    for(auto [v,w]:G[u])
    {
        if(flag)
            return;
        if(!dis[v])
            self(self,v,dis[u]+w);
        else
        {
            if(dis[v]!=dis[u]+w)
            {
                std::cout<<"NO\n";
                flag=true;
                return ;
            }
        }
        if(flag) return ;
    }
};

/*-------------------------------------------------------------------------------------
3��__int128
��չ�����ݷ�Χ�����ǲ�����ʹ��cin,cout,printf,scanf
��������Ҫ�ֶ�д�����
---------------------------------------------------------------------------------------*/

using i128 = __int128;

i128 read() 
{
	char arr[30];
	i128 res = 0;
	scanf("%s", arr);
	for (int i = 1; i <= strlen(arr); i++) 
    {
		res *= 10;
		res += arr[i]-'0';
	}
	return res;
}
void print (i128 num) 
{
	if (num > 9) { print(num / 10); }
	putchar(num % 10 + '0');
}


void solve()
{
    i128 a,b;
    // a=read(),b=read();
    a = ((i128)1)<<100;
    // std::cout<<(print(a))<<" "<<(print(b))<<"\n";
    print(a);
    // std::cout<<" ";
    // print(b);
}

/*-------------------------------------------------------------------------------------
4��uniqueȥ�ز���
��1����ȥ��ǰ��Ҫ����������
��2����ʹ��unique���������Ҽ�ȥtmp-1
����ΪʲôҪ��ȥtmp�ټ�1����ȥtmp����⣬�ټ�1��ʲô������
������Ҫ����ȥ�غ��Ԫ�ظ�����������ȥ�غ���߼��յ��λ�á�
���� std::unique ���ص������һ��ΨһԪ�ص���һ��λ�ã�����������Ҫ�ټ� 1 ���ܵõ�ȥ�غ��Ԫ�ظ�����
---------------------------------------------------------------------------------------*/
int tmp[N],n;
std::sort(tmp+1,tmp+1+n);
int len = std::unique(tmp+1,tmp+1+n)-tmp-1;

//���ֶ����ԡ�
std::vector<std::string>vals;
std::sort(vals.begin(),vals.end());
vals.erase(std::unique(vals.begin(),vals.end()),vals.end());
/*-------------------------------------------------------------------------------------
5��for(auto v:G[u]):ϵ�в�����
��Դ�ڣ�for (auto &&i : mp) if (i.second >= 2) ans += pailie(i.second, 2);
�����auto &&i������һ������i����������mp��ÿ��Ԫ�ص����á�ʹ��&&������&��ԭ���ǣ�&&���������޸������е�Ԫ�أ���&ֻ�������Ƕ�ȡԪ�ء�
��������������������������������������������������������������������������������������������������������
�ܵ���˵���ڷ�Χ����forѭ���У�
* ��������޸������е�Ԫ�أ�ʹ��auto &&��
* �����ֻ���ȡ�����е�Ԫ�أ�ʹ��auto &��const auto &��
* ������븴�������е�Ԫ�أ�ʹ��auto��
---------------------------------------------------------------------------------------*/
for (auto &&i : mp) if (i.second >= 2) ans += pailie(i.second, 2);


/*-------------------------------------------------------------------------------------
6��vector�Ķ�ά�����Լ����ຯ����
��1������άfor each������
����Ҫһ��һ�����ġ�

��2�������ú���
��ʼ��ʹ��assign����һ�㡣
assign O(n)
fill O(nlogn)
resize O(nlogn)

��3������������ʽ��
std::vector dp(n + 1, std::vector<i64>(m + 1, 0));
---------------------------------------------------------------------------------------*/
std::vector<std::vector<int>>a(n,std::vector<int>(m,0));
    for(auto &x:a)
        for(auto &y:x)
            std::cin>>y;

//std::fill(c.begin(), c.end(), 0); // ��ʼ����״����
c.assign(N,0);


/*-------------------------------------------------------------------------------------
7��C++�ĸ߼�����
(1)����ͣ���ʼֵ�� 0
accumlate(a.begin(),a.end().0);
Ҫע������ط�LONG LONG Ҫ���� 0 ��0 Ҫ���0LL

(2)�����ó�ֵΪx�Ĺ���Ϊ1�ĵȲ�����
std::iota(a.begin(),a.end(),0);
(3)�������ֵ��Сֵ
std::max_element(a.begin(),a.end())
���� C++ ��׼���е�һ���㷨���������ڲ��Ҹ�����Χ�ڵ����Ԫ�ء�������һ��ָ�����Ԫ�صĵ�������
---------------------------------------------------------------------------------------*/
std::vector<int>a(n);
int sum = accumulate(a.begin(), a.end(), 0LL); // �����ʼ����ĺ�
std::iota(a.begin(),a.end(),0);
int pos = std::max_element(a.begin(),a.end())-a.begin();

std::cout << std::accumulate(s.begin(),s.end(),0,[&](int total,char ch)
{
    return total + (ch == 'o');
}) << "\n";
/*-------------------------------------------------------------------------------------
8��std::string�Ĳ���
s.insert(pos,num,ch)
��pos����num���ַ�ch��
s.find(ch)
�����ַ����Ҳ�������-1��
s.erase(pos,len);
��pos��ɾ��len����
---------------------------------------------------------------------------------------*/
int p2 = s.rfind(ch1);
if(p2==-1)
    return ;
s.erase(p2,1);


/*-------------------------------------------------------------------------------------
9��std::transform�Ĳ���
std::transform(s.begin(), s.end(), s.begin(), ::tolower);
���������ĩβ��Ȼ��洢������ȥ����ʲô������
---------------------------------------------------------------------------------------*/
std::transform(s.begin(), s.end(), s.begin(), ::tolower);


/*-------------------------------------------------------------------------------------
10��__builtin_popcount(n)
__builtin_popcount(n) �� �ڽ����������ڼ������� n �Ķ����Ʊ�ʾ�� 1 �ĸ�����
��������ķ���ֵ�� n �Ķ����Ʊ�ʾ�� 1 ������


//�޷�������C++20
std::popcount(x)
---------------------------------------------------------------------------------------*/

int n = 29; // �����Ʊ�ʾΪ 11101���� 4 �� 1
std::cout << "__builtin_popcount(n): " << __builtin_popcount(n) << std::endl;

/*-------------------------------------------------------------------------------------
11���ַ���������֮���ת����
��1����std::string �� std::vector<char> ֮���ת��
ֱ�ӻ���
    std::string str = "Hello, World!";
    std::vector<char> vec(str.begin(), str.end());

    std::vector<char> vec = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    std::string str(vec.begin(), vec.end());
��2����std::string �� int / long long ֮���ת��

std::stoi(s)
std::stoll(s)
std::to_string(num)

    std::string str = "12345";
    int num = std::stoi(str);
    long long num = std::stoll(str);
    std::string str = std::to_string(num);
---------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------
12������STL��set��map�����vector��
std::set<std::vector<int>>��ʱ�临�ӶȺ�С��Ҳ����O(logk + n)������k�Ǻ�����еĸ���,n�����Ա��Լ��ġ�
std::map<int, std::vector<int>> mp;Ҳ��ࡣ

���ǹ���map���ҵ�ʱ�򣬺����⡣
-------------------------------------------------------------------------------------------------*/
std::map<int, std::vector<int>> mp;
int key = 2;
//�ҵ��ˡ�
if(mp.find(key) != mp.end())
{
    ...
};

/*------------------------------------------------------------------------------------------------
13������STL��multiset��set
ʹ��se.find() ���Բ��ҵ�������Ȼ����ɾ����ʱ�临�ӶȺ�С��
set�Դ�lower_bound�������ʱ�临�ӶȽ�С��
-------------------------------------------------------------------------------------------------*/


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
