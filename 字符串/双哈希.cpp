#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e9+5;
int n,m,k;


struct DoubleStringHash
{
    std::vector<int>h1, h2, p1, p2;
    int base1 = 131, base2 = 13331;
    int mod1 = 1e9 + 7, mod2 = 1e9 + 9;

    void init(std::string s)
    {
        int len = s.size();
        s = " " + s;
        h1.resize(len + 1), p1.resize(len + 1);
        h2.resize(len + 1), p2.resize(len + 1);

        h1[0] = 0, p1[0] = 1;
        h2[0] = 0, p2[0] = 1;

        for(int i = 1;i <= len;i ++)
        {
            h1[i] = (h1[i - 1] * base1 + s[i]) % mod1;
            p1[i] = p1[i - 1] * base1 % mod1;
            h2[i] = (h2[i - 1] * base2 + s[i]) % mod2;
            p2[i] = p2[i - 1] * base2 % mod2;
        }
    }

    PII get_hash(int l,int r)
    {
        return {(h1[r] - h1[l - 1] * p1[r - l + 1] % mod1 + mod1) % mod1,
                (h2[r] - h2[l - 1] * p2[r - l + 1] % mod2 + mod2) % mod2};
    }

}DHA;//double hash

void solve()
{
    std::string s;
    std::cin >> s;
    n = s.size();
    DHA.init(s);
    s = " " + s;
    int ans = 0;
    for(int i = 1;i < n;i ++)
    {
        int l1 = i, r1 = i;
        int l2 = i + 1, r2 = i + 1;
        while(l1 >= 1 and r2 <= n)
        {
            if(DHA.get_hash(l1, r1) == DHA.get_hash(l2, r2))
            {
                ans ++;
                r1 = l1 - 1, l2 = r2 + 1;
            }
            l1 --, r2 ++;
        }
    }
    std::cout << ans << "\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T=1;
    std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}


/*---------------------------------------------------------------------------------------------------------------
利用取模+merge化大整数为一个新的哈希值
-----------------------------------------------------------------------------------------------------------------*/
void solve()
{
    std::cin >> n;
    std::string s;
    std::vector<int>h1(n + 1, 0);
    std::vector<int>h2(n + 1, 0);

    auto merge = [&](int x,int y) -> int
    {
        return x * (mod2 + 10) + y;
    };

    std::map<int, int>mp;

    // 输入异或值，双哈希
    for(int i = 1;i <= n;i ++)
    {
        std::cin >> s;
        s = " " + s;
        for(int j = 1;j < s.size();j ++)
        {
            h1[i] = (h1[i] * 10 + (s[j] - '0')) % mod1;
            h2[i] = (h2[i] * 10 + (s[j] - '0')) % mod2;
        }
        mp[merge(h1[i], h2[i])] ++;
    }

    int ans = 0;

    for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= n;j ++)
            ans += mp[merge(h1[i] * h1[j] % mod1, h2[i] * h2[j] % mod2)];

    std::cout << ans << "\n";
}
