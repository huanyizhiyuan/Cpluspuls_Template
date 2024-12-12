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
1、#include <iomanip>
C++保留小数点：
std::cout << std::fixed << std::setprecision(12) << ans << "\n";

2、C++11 引入的 Lambda 表达式
[](node x,node y){return x.p>y.p;}
[]: 这是 Lambda 表达式的捕获子句(capture clause)。它指定了 Lambda 表达式可以访问的外部变量。在这个例子中,捕获子句为空,表示 Lambda 表达式不捕获任何外部变量。
(node x, node y): 这是 Lambda 表达式的参数列表。它指定了 Lambda 表达式接受的参数类型和名称。在这个例子中,Lambda 表达式接受两个 node 类型的参数,分别命名为 x 和 y。
{ return x.p > y.p; }: 这是 Lambda 表达式的函数体。它定义了 Lambda 表达式的行为。在这个例子中,Lambda 表达式比较两个 node 对象的 p 成员,并返回比较结果。

以下三个都是Lambda表达式的例子。
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
//调用自身的实例。
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
3、__int128
扩展的数据范围，但是不可以使用cin,cout,printf,scanf
所以我们要手动写快读。
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
4、unique去重操作
（1）、去重前需要我们先排序。
（2）、使用unique函数，并且减去tmp-1
这里为什么要减去tmp再减1？减去tmp我理解，再减1是什么操作？
我们想要的是去重后的元素个数，而不是去重后的逻辑终点的位置。
由于 std::unique 返回的是最后一个唯一元素的下一个位置，所以我们需要再减 1 才能得到去重后的元素个数。
---------------------------------------------------------------------------------------*/
int tmp[N],n;
std::sort(tmp+1,tmp+1+n);
int len = std::unique(tmp+1,tmp+1+n)-tmp-1;

//两种都可以。
std::vector<std::string>vals;
std::sort(vals.begin(),vals.end());
vals.erase(std::unique(vals.begin(),vals.end()),vals.end());
/*-------------------------------------------------------------------------------------
5、for(auto v:G[u]):系列操作：
起源于：for (auto &&i : mp) if (i.second >= 2) ans += pailie(i.second, 2);
在这里，auto &&i声明了一个变量i，它是容器mp中每个元素的引用。使用&&而不是&的原因是，&&允许我们修改容器中的元素，而&只允许我们读取元素。
————————————————————————————————————————————————————
总的来说，在范围基础for循环中：
* 如果你想修改容器中的元素，使用auto &&。
* 如果你只想读取容器中的元素，使用auto &或const auto &。
* 如果你想复制容器中的元素，使用auto。
---------------------------------------------------------------------------------------*/
for (auto &&i : mp) if (i.second >= 2) ans += pailie(i.second, 2);


/*-------------------------------------------------------------------------------------
6、vector的二维操作以及更多函数：
（1）、二维for each操作，
还是要一步一步来的。

（2）、常用函数
初始化使用assign更快一点。
assign O(n)
fill O(nlogn)
resize O(nlogn)

（3）、简化声明方式：
std::vector dp(n + 1, std::vector<i64>(m + 1, 0));
---------------------------------------------------------------------------------------*/
std::vector<std::vector<int>>a(n,std::vector<int>(m,0));
    for(auto &x:a)
        for(auto &y:x)
            std::cin>>y;

//std::fill(c.begin(), c.end(), 0); // 初始化树状数组
c.assign(N,0);


/*-------------------------------------------------------------------------------------
7、C++的高级操作
(1)、求和，初始值是 0
accumlate(a.begin(),a.end().0);
要注意这个地方LONG LONG 要开给 0 ，0 要变成0LL

(2)、设置初值为x的公差为1的等差序列
std::iota(a.begin(),a.end(),0);
(3)、求最大值最小值
std::max_element(a.begin(),a.end())
它是 C++ 标准库中的一个算法函数，用于查找给定范围内的最大元素。它返回一个指向最大元素的迭代器。
---------------------------------------------------------------------------------------*/
std::vector<int>a(n);
int sum = accumulate(a.begin(), a.end(), 0LL); // 计算初始数组的和
std::iota(a.begin(),a.end(),0);
int pos = std::max_element(a.begin(),a.end())-a.begin();

std::cout << std::accumulate(s.begin(),s.end(),0,[&](int total,char ch)
{
    return total + (ch == 'o');
}) << "\n";
/*-------------------------------------------------------------------------------------
8、std::string的操作
s.insert(pos,num,ch)
在pos插入num个字符ch。
s.find(ch)
查找字符，找不到返回-1。
s.erase(pos,len);
从pos处删除len个。
---------------------------------------------------------------------------------------*/
int p2 = s.rfind(ch1);
if(p2==-1)
    return ;
s.erase(p2,1);


/*-------------------------------------------------------------------------------------
9、std::transform的操作
std::transform(s.begin(), s.end(), s.begin(), ::tolower);
容器的起点末尾，然后存储到哪里去，干什么操作。
---------------------------------------------------------------------------------------*/
std::transform(s.begin(), s.end(), s.begin(), ::tolower);


/*-------------------------------------------------------------------------------------
10、__builtin_popcount(n)
__builtin_popcount(n) 是 内建函数，用于计算整数 n 的二进制表示中 1 的个数。
这个函数的返回值是 n 的二进制表示中 1 的数量


//无符号数。C++20
std::popcount(x)
---------------------------------------------------------------------------------------*/

int n = 29; // 二进制表示为 11101，有 4 个 1
std::cout << "__builtin_popcount(n): " << __builtin_popcount(n) << std::endl;

/*-------------------------------------------------------------------------------------
11、字符串与整型之间的转换：
（1）、std::string 和 std::vector<char> 之间的转换
直接换：
    std::string str = "Hello, World!";
    std::vector<char> vec(str.begin(), str.end());

    std::vector<char> vec = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    std::string str(vec.begin(), vec.end());
（2）、std::string 和 int / long long 之间的转换

std::stoi(s)
std::stoll(s)
std::to_string(num)

    std::string str = "12345";
    int num = std::stoi(str);
    long long num = std::stoll(str);
    std::string str = std::to_string(num);
---------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------
12、关于STL的set、map结合上vector。
std::set<std::vector<int>>的时间复杂度很小，也就是O(logk + n)，其中k是红黑树中的个数,n是线性表自己的。
std::map<int, std::vector<int>> mp;也差不多。

但是关于map查找的时候，很特殊。
-------------------------------------------------------------------------------------------------*/
std::map<int, std::vector<int>> mp;
int key = 2;
//找到了。
if(mp.find(key) != mp.end())
{
    ...
};

/*------------------------------------------------------------------------------------------------
13、关于STL的multiset、set
使用se.find() 可以查找迭代器，然后再删除的时间复杂度很小。
set自带lower_bound，这个的时间复杂度较小。
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
