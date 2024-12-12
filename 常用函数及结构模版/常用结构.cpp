/*-------------------------------------------------------------------------------------
����ṹ��
---------------------------------------------------------------------------------------*/
namespace FastIO{
	template<typename T> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}

namespace FastIO{
    // template class T = i128;
    template<typename T = i128>
    T read(){
        T x=0;int f=1;char c=getchar();
        while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
        while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
        return x*f;
    }
    template<typename T = i128>
    void write(T x){
        if(x<0){putchar('-');x=-x;}
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
    template<typename T = i128>
    void Write(T x,char c='\n')
    {
        write(x);putchar(c);
    }
}

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
/*-------------------------------------------------------------------------------------
��������ݼ��ṹ��
---------------------------------------------------------------------------------------*/
namespace MatrixExpo
{
    //����ṩģ��
    // constexpr int mod = 1e9+7;
    using Matrix = std::vector<std::vector<int>>;

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

    Matrix inputMatrix(int n)
    {
        Matrix A(n,std::vector<int>(n,0));
        for(auto &row:A)
            for(auto &v:row)
                std::cin>>v;
        return A;
    }

    Matrix operator*(const Matrix &A,const Matrix &B)
    {
        int n = A.size();
        Matrix C(n,std::vector<int>(n,0));
        for(int i = 0;i < n;i ++)
            for(int j = 0;j < n;j ++)
                for(int k = 0;k < n;k ++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j] % mod) % mod;
        return C;
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

/*-------------------------------------------------------------------------------------
�����ļ���
---------------------------------------------------------------------------------------*/
#ifndef ONLINE_JUDGE
    //freopen("title.in","r",stdin);
    //freopen("title.out","w",stdout);
#endif
