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
lowbit()������������С�Ķ�����λ����10���Ƶ���ʽ��
lowbit_2()������������С�Ķ�����λ����2���Ƶ���ʽ��
����8����3���������ǵ���λ��
chk()�������жϵ�ǰλ�ǲ���2��ָ������
---------------------------------------------------------------------------------------*/
i64 lowbit(i64 x){return x&(-x);}
//��0��ʼ����len-1������
i64 lowbit_2(i64 x){int res=0;int y=x&(-x);while(y)res++,y>>=1;return res-1;}
i64 chk(i64 n){return lowbit(n)==n?1:0;}
i64 bit_get(i64 x)//����2^k��ȡ��k
{
	i64 ans=0;
	while(x%2==0) 
        x/=2,++ans;
	return ans;
}
/*-------------------------------------------------------------------------------------
���㼸�Σ�
���빫ʽ�������������

1��ŷ����¾��빫ʽ��
d = sqrt((x1 - x2)^2 + (y1 - y2)^2)

2�������پ��빫ʽ:
d = |x1 - x2| + |y1 - y2|

3���б�ѩ����빫ʽ���ڶ�ά�ռ��м�������֮�����������Ķ�����ʽ
��άd = max(|x1 - x2|, |y1 - y2|)
��άd = max(|x1 - x2|, |y1 - y2|, |z1 - z2|)

4���ɿɷ�˹�����빫ʽ���������빫ʽ�ļ��ɡ�
d = (|x1 - x2|^p + |y1 - y2|^p)^(1/p)
P=1�������پ��빫ʽ��
P=2��ŷ����þ��빫ʽ��
P=�����б�ѩ����빫ʽ��

5�����׹�ʽ�������
s�ǰ��ܳ���s = (a + b + c) / 2
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
����������ר�⣺

1���ж�һ�����Ƿ���������
ʹ��lamdba���ʽ��ôд��

(1)����ͷautoע��㣺
��ͷ��������ֵ��ʹ��auto��������lamdba���ʽ��
��ͷ������ʽ�򴴽�һ������
�����������ĺ����ռ�
ʵ����auto��std::function

auto fun = [](i64 x) 
{
    bool flag = true;
    for (int i = 2; i * i < x; i++)
        if (x % i == 0) {flag = false;break;}
    if(x<=1)flag=false;
    return flag;
};

2��gcd������
2.1��ϵͳ�Դ�__gcd()
2.2��ŷ������㷨��
�ٶȲ������ú�������O(log(a+b))�ĸ��Ӷ�������Լ���������ú���__gcd()���ܻ�����ͬ��֧��a,b<=0��
�����gcd����
2.3��λ�����Ż����Կ������ú��������ڿ�����
2.4����ֹ�����������
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

//ò�Ƹ��졣
int gcd(int a,int b){return b?gcd(b,a%b):a;}
//��ϲ����ôд��
int gcd2(int a,int b){return a%b==0?b:gcd2(b,a%b);}
//����
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
3����ɢ��������
void Init_hash()
��� a[N] ���飬����ȥ��+��ɢ����
Ȩֵ�߶���������Ҫʹ�á�
---------------------------------------------------------------------------------------*/
//��ɢ�����̡�
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

//��ɢ�����̡�
tmp = a;
std::sort(tmp.begin()+1,tmp.end());
int len = std::unique(tmp.begin() + 1,tmp.end())-tmp.begin();
for(int i=1;i<=n;i++)
{
    int pos=std::lower_bound(tmp.begin()+1,tmp.begin()+1+len,a[i])-tmp.begin();
    a[i]=pos;
}
/*-------------------------------------------------------------------------------------
4��������ϣ�
4.1��Ԥ�����������ȡģ1e9+7������������zh��ʾ��
���ȣ���δ���ͨ�� init() ����Ԥ����������� zh��
�� zh[i][j] ��ʾ�� j��Ԫ����ѡ�� i ��Ԫ�صķ�������
����������ͨ�� Pascal �����ε��ƹ�ʽ
 C(n, m) = C(n-1, m) + C(n-1, m-1) ������ġ�
** ��i��ѡ��j����������Ҫi-1,j-1����Ϊ�Ǵ�0��0��ʼ�� **
---------------------------------------------------------------------------------------*/
std::vector<std::vector<int>> zh(5005, std::vector<int>(5005, 0));
void init()
{
    //�������Ԥ�������
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
5�����Ǻ���
<cmath>���µĺ�����
���Һ���: sin
���Һ���: cos
���к���: tan
�����Һ���: asin
�����Һ���: acos
�����к���: atan
˫���������к���: atan2(y,x)
˫�����Һ���: sinh
˫�����Һ���: cosh
˫�����к���: tanh
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
6�������ѧ��
С������+������
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
7�����巨����
---------------------------------------------------------------------------------------*/
int get(int x)//���巨
{
    if(x<=2) return 0;
    return (x-1)*(x-2)/2;
}

/*-------------------------------------------------------------------------------------
8����չŷ������㷨 �� ��Ԫ
�Լ�����Ԫ��ģ�����Բ���������
---------------------------------------------------------------------------------------*/
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x); //���ｻ����x��y
    y -= (a / b) * x;
    return d;
}

int inv(int a, int p)
{
    int x, y;
    if(exgcd(a, p, x, y) != 1) //�޽������
        return -1;
    return (x % p + p) % p;
}

/*-------------------------------------------------------------------------------------
���Ե�������Ԫ
---------------------------------------------------------------------------------------*/
std::vector<int>inv(3000010, 0);
inv[1] = 1;
for(int i = 2; i <= n; ++ i)
    inv[i] = (p - p / i) * inv[p % i] % p;

/*-------------------------------------------------------------------------------------
����������Ԫ
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
9�������й�ʣ�ඨ��
i128��� + ��չŷ���������Ԫ
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
    int d = exgcd(b, a % b, y, x); //���ｻ����x��y
    y -= (a / b) * x;
    return d;
}

int inv(int a, int p)
{
    int x, y;
    if(exgcd(a, p, x, y) != 1) //�޽������
        return -1;
    return (x % p + p) % p;
}

//a��ģ�����飬b���������飬len�����鳤��
int CRT(std::vector<int>a, std::vector<int>b, int len)
{
    int p = 1, res = 0;
    for(int i = 1;i <= len;i ++)
        p *= a[i];
    for(int i = 1;i <= len;i ++)
    {
        int tmp = p / a[i];
        //ע�⣬��Ԫ�������˭�ġ�
        res += (b[i] * tmp * inv(tmp, a[i])) % p;
    }
    return res % p;
}

/*-------------------------------------------------------------------------------------
10������sqrtl���á�
---------------------------------------------------------------------------------------*/
sqrtl��sqrt���ʺ�i64
sqrtl >> sqrt

/*-------------------------------------------------------------------------------------
11��ȫ���к�����
---------------------------------------------------------------------------------------*/
next_permutation()


/*-------------------------------------------------------------------------------------
12��MEX����
---------------------------------------------------------------------------------------*/
int mex(auto v) // v������vector��set������
{
    unordered_set<int> S;
    for (auto e : v)
        S.insert(e);
    for (int i = 0;; ++i)
        if (S.find(i) == S.end())
            return i;
}

/*-------------------------------------------------------------------------------------
13��ɸѡ����
��1��������ɸ
��2����ŷ��ɸ
---------------------------------------------------------------------------------------*/
bool isnp[MAXN]; // is not prime: ��������
void init(int n)
{
    for (int i = 2; i * i <= n; i++)
        if (!isnp[i])
            for (int j = i * i; j <= n; j += i)
                isnp[j] = 1;
}

std::vector<bool> isnp;
std::vector<int> primes; // ������
std::vector<std::vector<int>> G;
// ŷ��ɸ��������Ϊÿ������¼�����е������ӡ�
void init(int len)
{
    // ŷ��ɸ
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

    // ��¼ÿ�����������ӡ�
    G.resize(len + 10);

    for (int i = 0; i < primes.size(); i ++)
        for (int j = primes[i]; j <= len; j += primes[i])
            G[j].push_back(i); // ������±�
}

/*-------------------------------------------------------------------------------------
14��ɸѡ����
��1��������ɸ
��2����ŷ��ɸ
ŷ��ɸ�����汾��ȫ�°汾��������minPrime��������ʵĵط���
����getPrimeList ���������������� x �� �����������ظ���
��Ҫ�ظ����Ի���λ�á�
---------------------------------------------------------------------------------------*/
const int N = 1e6 + 5; // �������ΧΪ 1000000
int primes[N];         // �洢��������
int minPrime[N];           // minp[x] �洢 x ����С������

void sieve(int n)
{
    int cnt = 0; // ��ʼ������������
    for (int i = 2; i <= n; i++)
    {
        if (minPrime[i] == 0)
        {                      // ��� minp[i] Ϊ 0��˵�� i ������
            minPrime[i] = i;       // ��¼ i ����С������Ϊ����
            primes[cnt++] = i; // �洢����
        }
        // �������ҵ�����������ɸѡ
        for (int j = 0; j < cnt && primes[j] <= n / i; j++)
        {
            minPrime[primes[j] * i] = primes[j]; // ɸ�� i * primes[j]������¼��С������
            if (i % primes[j] == 0)
                break; // ��ֹ�ظ�ɸѡ
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



//���Ժ����á�
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
