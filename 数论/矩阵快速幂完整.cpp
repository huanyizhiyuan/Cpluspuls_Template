#include<bits/stdc++.h>
#define i64 long long
#define int i64
using PII = std::pair<int,int>;
using TIII = std::tuple<int,int,int>;
constexpr int mod = 1e9+7;
constexpr int inf = 1e9+5;
int n,m,k;

namespace MatrixExpo
{
    //����ṩģ��
    // constexpr int mod = 1e9+7;
    using Matrix = std::vector<std::vector<int>>;

    //����˷�
    Matrix multiply(const Matrix &A,const Matrix &B)
    {
        int n = A.size();
        Matrix C(n,std::vector<int>(n,0));
        for(int i = 0;i < n;i ++)
            for(int j = 0;j < n;j ++)
                for(int k = 0;k < n;k ++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j] % mod) % mod;
        return C;
    }

    //���������
    Matrix power2(Matrix A,int exp)
    {
        int n = A.size();

        //��λ����
        Matrix res(n,std::vector<int>(n,0));
        for(int i = 0;i < n;i ++)
            res[i][i] = 1;

        while(exp > 0)
        {
            if(exp&1)
                res = multiply(res,A);
            A = multiply(A,A);
            exp >>= 1;
        }

        return res;
    }

    Matrix inputMatrix(int n)
    {
        Matrix A(n,std::vector<int>(n,0));
        for(auto &row:A)
            for(auto &v:row)
                std::cin>>v;
        return A;
    }

    //�����ӡ
    void printMatrix(const Matrix &A)
    {
        //��0��ʼ�Ĵ�ӡ
        for(const auto &row : A)
        {
            for(const auto &val : row)
                std::cout << val <<" ";
            std::cout << "\n";
        }
    }

    Matrix operator*(const Matrix &A,const Matrix &B)
    {
        // int n = A.size();
        // Matrix C(n+1,std::vector<int>(n+1,0));
        // for(int i = 1;i <= n;i ++)
        //     for(int j = 1;j <= n;j ++)
        //         for(int k = 1;k <= n;k ++)
        //             C[i][j] = (C[i][j] + A[i][k] * B[k][j] % mod) % mod;
        // return C;
        return multiply(A,B);
    }

    Matrix operator+(const Matrix &A,const Matrix &B)
    {
        int n = A.size();
        Matrix C(n,std::vector<int>(n,0));
        for(int i = 0;i < n;i ++)
            for(int j = 0;j < n;j ++)
                C[i][j] = (A[i][j] + B[i][j]) % mod;
        return C;
    }

    Matrix operator-(const Matrix &A,const Matrix &B)
    {
        int n = A.size();
        Matrix C(n,std::vector<int>(n,0));
        for(int i = 0;i < n;i ++)
            for(int j = 0;j < n;j ++)
                C[i][j] = (A[i][j] - B[i][j] + mod) % mod;
        return C;
    }

    // ���������
    Matrix power(Matrix A, int exp)
    {
        int n = A.size();
        Matrix res(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
            res[i][i] = 1;

        while (exp > 0)
        {
            if (exp & 1)
                res = res * A;
            A = A * A;
            exp >>= 1;
        }
        return res;
    }
}

using namespace MatrixExpo;

void solve()
{
    // std::cin>>n>>k;
    Matrix A = {{1,2},{1,3}};
    Matrix B = {{2,3},{4,5}};

    printMatrix(A);
    printMatrix(B);

    printMatrix(A+B);
    printMatrix(B-A);

    printMatrix(A*B);

    printMatrix(power2(A,2));

    printMatrix(power(A,2));
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T=1;
    // std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}

