#include<bits/stdc++.h>
#define i64 long long
#define maxn 300050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<int,int> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,ans,cnt,sum,num,x,y,z;
/*-------------------------------------------------------------------------------------
lowbit()函数，返回最小的二进制位（以10进制的形式）
lowbit_2()函数，返回最小的二进制位（以2进制的形式）
比如8返回3，代表它是第三位。
chk()函数，判断当前位是不是2的指数倍。
---------------------------------------------------------------------------------------*/
i64 lowbit(i64 x){return x&(-x);}
//从0开始，到len-1结束。
i64 lowbit_2(i64 x){int res=0;int y=x&(-x);while(y)res++,y>>=1;return res-1;}
i64 chk(i64 n){return lowbit(n)==n?1:0;}
i64 bit_get(i64 x)//对于2^k，取出k
{
	i64 ans=0;
	while(x%2==0) 
        x/=2,++ans;
	return ans;
}
/*-------------------------------------------------------------------------------------
计算几何：
距离公式与三角形面积：

1、欧几里德距离公式：
d = sqrt((x1 - x2)^2 + (y1 - y2)^2)

2、曼哈顿距离公式:
d = |x1 - x2| + |y1 - y2|

3、切比雪夫距离公式：在多维空间中计算两点之间的最大坐标差的度量方式
二维d = max(|x1 - x2|, |y1 - y2|)
三维d = max(|x1 - x2|, |y1 - y2|, |z1 - z2|)

4、闵可夫斯基距离公式：三个距离公式的集成。
d = (|x1 - x2|^p + |y1 - y2|^p)^(1/p)
P=1是曼哈顿距离公式。
P=2是欧几里得距离公式。
P=∞是切比雪夫距离公式。

5、海伦公式求面积：
s是半周长，s = (a + b + c) / 2
A = sqrt(s * (s - a) * (s - b) * (s - c))
---------------------------------------------------------------------------------------*/
double dist_1(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
i64 dist_2(i64 x1,i64 y1,i64 x2,i64 y2)
{
    return abs(x1-x2)+abs(y1-y2);
}
double dist_3(double x1, double y1, double x2, double y2) 
{
    return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}
double dist_4(double x1, double y1, double x2, double y2, double p) 
{
    return std::pow(std::pow(std::abs(x1 - x2), p) + std::pow(std::abs(y1 - y2), p), 1.0 / p);
}
double square(double a,double b,double c)
{
    double p;
    p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
/*-------------------------------------------------------------------------------------
素数与因数专题：

1、判断一个数是否是素数：
使用lamdba表达式这么写：

(1)、开头auto注意点：
开头不代表返回值，使用auto代表这是lamdba表达式。
开头代表隐式打创建一个函数
不创建真正的函数空间
实际上auto是std::function

auto fun = [](i64 x) 
{
    bool flag = true;
    for (int i = 2; i * i < x; i++)
        if (x % i == 0) {flag = false;break;}
    if(x<=1)flag=false;
    return flag;
};

2、gcd函数：
2.1、系统自带__gcd()
2.2、欧几里得算法：
速度不如内置函数！以O(log(a+b))的复杂度求解最大公约数。与内置函数__gcd()功能基本相同（支持a,b<=0）
具体见gcd函数
2.3、位运算优化，略快于内置函数，用于卡常。
2.4、防止负数的情况：
std::cout<<gcd(a,b)<<"\n";              //5
std::cout<<gcd2(a,b)<<"\n";             //5
std::cout<<gcd2(91,52)<<"\n";           //13
std::cout<<std::__gcd(91,52)<<"\n";     //13
---------------------------------------------------------------------------------------*/
bool fun(i64 x)
{
    bool flag=1;
    for(int i=2;i*i<x;i++)
        if(x%i==0){flag=0;break;}
    if(x<=1)flag=0;
    return flag==1;
}

//貌似更快。
int gcd(int a,int b){return b?gcd(b,a%b):a;}
//我喜欢这么写。
int gcd2(int a,int b){return a%b==0?b:gcd2(b,a%b);}
//卡常
i64 gcd3(i64 a,i64 b)
{
    #define tz __builtin_ctzll
    if(!a||!b) return a|b;
    int t=tz(a|b);
    a >>= tz(a);
    while(b)
    {
        b>>=tz(b);
        if(a>b)std::swap(a,b);
        b-=a;
    }
    return a<<t;
    #undef tz
}
int gcd(int a,int b){return b?gcd(b,a%b):abs(a);}
/*-------------------------------------------------------------------------------------
3、离散化操作：
void Init_hash()
针对 a[N] 数组，进行去重+离散化。
权值线段树问题需要使用。
---------------------------------------------------------------------------------------*/
//离散化过程。
void Init_hash()
{
    // static int tmp[N];
    int tmp[N];
    for(int i=1;i<=n;i++)
        tmp[i]=a[i];
    std::sort(tmp+1,tmp+1+n);
    int len = std::unique(tmp+1,tmp+1+n)-tmp-1;

    for(int i=1;i<=n;i++)
    {
        int pos=std::lower_bound(tmp+1,tmp+1+len,a[i])-tmp;
        a[i]=pos;
    }
}

//c++11
std::cin >> n;
std::vector<int>a(n+1,0);
std::vector<int>tmp;
// std::vector<int>
for(int i = 1;i <= n;i ++)
    std::cin >> a[i];

//离散化过程。
tmp = a;
std::sort(tmp.begin()+1,tmp.end());
int len = std::unique(tmp.begin() + 1,tmp.end())-tmp.begin();
for(int i=1;i<=n;i++)
{
    int pos=std::lower_bound(tmp.begin()+1,tmp.begin()+1+len,a[i])-tmp.begin();
    a[i]=pos;
}
/*-------------------------------------------------------------------------------------
4、排列组合：
4.1、预处理组合数，取模1e9+7，我们用数组zh表示。
首先，这段代码通过 init() 函数预处理了组合数 zh，
即 zh[i][j] 表示从 j个元素中选出 i 个元素的方法数。
这个组合数是通过 Pascal 三角形递推公式
 C(n, m) = C(n-1, m) + C(n-1, m-1) 来计算的。
** 从i中选择j个，并且需要i-1,j-1，因为是从0，0开始的 **
---------------------------------------------------------------------------------------*/
std::vector<std::vector<int>> zh(5005, std::vector<int>(5005, 0));
void init()
{
    //将组合数预处理出来
    //C(n,m)=C(n-1,m-1)+C(n,m-1)
    zh[0][0] = 1;
    for (int i = 1; i <= 5000; i ++)
    {
        zh[i][0] = 1;
        for (int j = 1; j <= i; j++)
            zh[i][j] = (zh[i-1][j] + zh[i-1][j-1]) % mod;
    }
}

/*-------------------------------------------------------------------------------------
5、三角函数
<cmath>库下的函数：
正弦函数: sin
余弦函数: cos
正切函数: tan
反正弦函数: asin
反余弦函数: acos
反正切函数: atan
双变量反正切函数: atan2(y,x)
双曲正弦函数: sinh
双曲余弦函数: cosh
双曲正切函数: tanh
double result = sin(angle_in_radians);
double result = cos(angle_in_radians);
double result = tan(angle_in_radians);
double result = asin(value);
double result = acos(value);
double result = atan(value);
double result = atan2(y, x);
double result = sinh(angle_in_radians);
double result = cosh(angle_in_radians);
double result = tanh(angle_in_radians);
---------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------
6、组合数学：
小费马定理+快速幂
---------------------------------------------------------------------------------------*/
int ksm(int a, int b)
{
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

std::vector<int>fac(100000+10, 0);
std::vector<int>inv(100000+10, 0);

void init()
{
    fac[0]=inv[0]=1;
    for(int i=1;i<=100005;i++)
    {
        fac[i]=fac[i-1]*i%mod;
        inv[i]=inv[i-1]*ksm(i, mod - 2)%mod;
    }
}

auto C = [&](int x,int y)
{
    return fac[x] * inv[x-y] % mod * inv[y] % mod;
};

auto A = [&](int x,int y)
{
    return fac[x] * inv[x - y] % mod;
};

/*-------------------------------------------------------------------------------------
7、隔板法函数
---------------------------------------------------------------------------------------*/
int get(int x)//隔板法
{
    if(x<=2) return 0;
    return (x-1)*(x-2)/2;
}

/*-------------------------------------------------------------------------------------
8、拓展欧几里得算法 与 逆元
以及求逆元，模数可以不是质数。
---------------------------------------------------------------------------------------*/
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x); //这里交换了x和y
    y -= (a / b) * x;
    return d;
}

int inv(int a, int p)
{
    int x, y;
    if(exgcd(a, p, x, y) != 1) //无解的情形
        return -1;
    return (x % p + p) % p;
}

/*-------------------------------------------------------------------------------------
线性递推求逆元
---------------------------------------------------------------------------------------*/
std::vector<int>inv(3000010, 0);
inv[1] = 1;
for(int i = 2; i <= n; ++ i)
    inv[i] = (p - p / i) * inv[p % i] % p;

/*-------------------------------------------------------------------------------------
快速幂求逆元
---------------------------------------------------------------------------------------*/
int ksm(int a, int b, int mod)
{
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int inv(int x, int p)
{
    return ksm(x, p - 2, p);
}

/*-------------------------------------------------------------------------------------
9、完整中国剩余定理
i128情况 + 拓展欧几里得求逆元
---------------------------------------------------------------------------------------*/
#define i128 __int128
#define int i128

namespace FastIO
{
    i128 read()
    {
        i128 x=0;
        int f=1;char c=getchar();
        while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
        while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
        return x*f;
    }
    void write(i128 x)
    {
        if(x<0){putchar('-');x=-x;}
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
    void Write(i128 x,char c='\n')
    {
        write(x);
        putchar(c);
    }
}

using namespace FastIO;

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x); //这里交换了x和y
    y -= (a / b) * x;
    return d;
}

int inv(int a, int p)
{
    int x, y;
    if(exgcd(a, p, x, y) != 1) //无解的情形
        return -1;
    return (x % p + p) % p;
}

//a是模数数组，b是余数数组，len是数组长度
int CRT(std::vector<int>a, std::vector<int>b, int len)
{
    int p = 1, res = 0;
    for(int i = 1;i <= len;i ++)
        p *= a[i];
    for(int i = 1;i <= len;i ++)
    {
        int tmp = p / a[i];
        //注意，逆元是相对于谁的。
        res += (b[i] * tmp * inv(tmp, a[i])) % p;
    }
    return res % p;
}

/*-------------------------------------------------------------------------------------
10、开方sqrtl更好。
---------------------------------------------------------------------------------------*/
sqrtl比sqrt更适合i64
sqrtl >> sqrt

/*-------------------------------------------------------------------------------------
11、全排列函数。
---------------------------------------------------------------------------------------*/
next_permutation()


/*-------------------------------------------------------------------------------------
12、MEX函数
---------------------------------------------------------------------------------------*/
int mex(auto v) // v可以是vector、set等容器
{
    unordered_set<int> S;
    for (auto e : v)
        S.insert(e);
    for (int i = 0;; ++i)
        if (S.find(i) == S.end())
            return i;
}

/*-------------------------------------------------------------------------------------
13、筛选素数
（1）、埃氏筛
（2）、欧拉筛
---------------------------------------------------------------------------------------*/
bool isnp[MAXN]; // is not prime: 不是素数
void init(int n)
{
    for (int i = 2; i * i <= n; i++)
        if (!isnp[i])
            for (int j = i * i; j <= n; j += i)
                isnp[j] = 1;
}

std::vector<bool> isnp;
std::vector<int> primes; // 质数表
std::vector<std::vector<int>> G;
// 欧拉筛素数并且为每个数记录其所有的素因子。
void init(int len)
{
    // 欧拉筛
    isnp.assign(len + 10, false);

    for (int i = 2; i <= len; i++)
    {
        if (!isnp[i])
            primes.push_back(i);

        for (int p : primes)
        {
            if (p * i > len)
                break;

            isnp[p * i] = 1;

            if (i % p == 0)
                break;
        }
    }

    // 记录每个数的素因子。
    G.resize(len + 10);

    for (int i = 0; i < primes.size(); i ++)
        for (int j = primes[i]; j <= len; j += primes[i])
            G[j].push_back(i); // 存的是下标
}

/*-------------------------------------------------------------------------------------
14、筛选素数
（1）、埃氏筛
（2）、欧拉筛
欧拉筛完整版本，全新版本，尤其是minPrime更是最出彩的地方。
函数getPrimeList 用于求解给定正整数 x 的 质因数（不重复）
想要重复可以换换位置。
---------------------------------------------------------------------------------------*/
const int N = 1e6 + 5; // 假设最大范围为 1000000
int primes[N];         // 存储所有素数
int minPrime[N];           // minp[x] 存储 x 的最小质因子

void sieve(int n)
{
    int cnt = 0; // 初始化素数计数器
    for (int i = 2; i <= n; i++)
    {
        if (minPrime[i] == 0)
        {                      // 如果 minp[i] 为 0，说明 i 是素数
            minPrime[i] = i;       // 记录 i 的最小质因子为自身
            primes[cnt++] = i; // 存储素数
        }
        // 利用已找到的素数进行筛选
        for (int j = 0; j < cnt && primes[j] <= n / i; j++)
        {
            minPrime[primes[j] * i] = primes[j]; // 筛掉 i * primes[j]，并记录最小质因子
            if (i % primes[j] == 0)
                break; // 防止重复筛选
        }
    }
}

std::vector<int> getPrimeList(int x)
{
    std::vector<int> P;
    while (x > 1)
    {
        int p = minPrime[x];
        P.emplace_back(p);
        while (x % p == 0)
            x /= p;
    }
    return P;
}



//测试函数用。
void solve()
{
    int a=10,b=5;
    std::cout<<gcd(a,b)<<"\n";
    std::cout<<gcd2(a,b)<<"\n";
    std::cout<<gcd2(91,52)<<"\n";
    std::cout<<std::__gcd(91,52)<<"\n";
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
