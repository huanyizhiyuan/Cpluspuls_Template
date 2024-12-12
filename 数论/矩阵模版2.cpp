namespace MatrixExpo
{
    // 方阵
    class Matrix
    {
    private:
        std::vector<std::vector<int>> matrix;

    public:
        // 默认构造函数：创建空矩阵
        Matrix() = default;

        // 指定大小的构造函数：初始化为n*n矩阵，元素为0
        Matrix(int n) : matrix(n, std::vector<int>(n, 0)) {}

        // 拷贝构造函数：根据二维vector初始化矩阵
        Matrix(const std::vector<std::vector<int>> &a) : matrix(a) {}

        // 拷贝构造函数
        Matrix(const Matrix &a) : matrix(a.matrix) {}

        // **新增加的构造函数**：通过一维`initializer_list`初始化方阵
        Matrix(std::initializer_list<int> init) {
            int n = std::sqrt(init.size());  // 假设是n*n的方阵
            if (n * n != static_cast<int>(init.size())) {
                throw std::invalid_argument("Initializer list size must be a perfect square.");
            }
            matrix.assign(n, std::vector<int>(n, 0));

            auto it = init.begin();
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    matrix[i][j] = *it++;
                }
            }
        }

        // 矩阵大小
        int size() const { return matrix.size();}

        // 获取矩阵元素
        int &operator()(int i, int j) { return matrix[i][j]; }
        const int &operator()(int i, int j) const { return matrix[i][j]; }

        // 输入流重载 >>
        friend std::istream &operator>>(std::istream &in, Matrix &A)
        {
            for (auto &row : A.matrix)
                for (auto &val : row)
                    in >> val;
            return in;
        }

        // 输出流重载 <<
        friend std::ostream &operator<<(std::ostream &out, const Matrix &A)
        {
            for (const auto &row : A.matrix)
            {
                for (const auto &val : row)
                    out << val << " ";
                out << "\n";
            }
            return out;
        }

        // 矩阵乘法
        friend Matrix operator*(const Matrix &A, const Matrix &B)
        {
            int n = A.size();
            Matrix C(n);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        C(i, j) = (C(i, j) + A(i, k) * B(k, j) % mod) % mod;
            return C;
        }

        // 矩阵加法
        friend Matrix operator+(const Matrix &A, const Matrix &B)
        {
            int n = A.size();
            Matrix C(n);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    C(i, j) = (A(i, j) + B(i, j)) % mod;
            return C;
        }

        // 矩阵减法
        friend Matrix operator-(const Matrix &A, const Matrix &B)
        {
            int n = A.size();
            Matrix C(n);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    C(i, j) = (A(i, j) - B(i, j) + mod) % mod;
            return C;
        }

        // += 运算符重载
        Matrix &operator+=(const Matrix &B)
        {
            *this = *this + B;
            return *this;
        }

        // -= 运算符重载
        Matrix &operator-=(const Matrix &B)
        {
            *this = *this - B;
            return *this;
        }

        // *= 运算符重载
        Matrix &operator*=(const Matrix &B)
        {
            *this = *this * B;
            return *this;
        }

        // 矩阵快速幂
        // Matrix C = power(A, exp);
        friend Matrix power(Matrix A, int exp)
        {
            int n = A.size();

            Matrix res(n);
            for (int i = 0; i < n; ++i)
                res(i, i) = 1;

            while (exp > 0)
            {
                if (exp & 1)
                    res = res * A;
                A = A * A;
                exp >>= 1;
            }
            return res;
        }

        // 矩阵快速幂：作为成员函数
        // Matrix C = A.power(exp);
        Matrix power(int exp) const
        {
            int n = size();

            Matrix res(n);
            for (int i = 0; i < n; ++i)
                res(i, i) = 1;  // 初始化为单位矩阵

            Matrix base = *this;
            while (exp > 0)
            {
                if (exp & 1)
                    res = res * base;
                base = base * base;
                exp >>= 1;
            }
            return res;
        }
    };
}
