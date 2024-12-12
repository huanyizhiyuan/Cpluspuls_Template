template<class T>
struct Matrix
{
    int row, col;
    std::vector<std::vector<T>> mat;

    constexpr Matrix(int n = 0, int m = 0, T initial_value = T()) : row(n), col(m) {
        mat.assign(n, std::vector<T>(m, initial_value));
    }

    constexpr Matrix(std::initializer_list<std::initializer_list<T>> init) {
        row = init.size(), col = init.begin() -> size(); 

        mat.reserve(row);

        for (const auto& row_list : init) {
            mat.emplace_back(row_list);
        }
    }

    constexpr Matrix(const Matrix &init) {
        const int n = init.row, m = init.col;
        row = n, col = m;
        mat.assign(n, std::vector<T>(m, T()));

        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                mat[i][j] = init.mat[i][j];
            }
        }
    }

    constexpr Matrix Identify() const {
        Matrix res(row, col);
        for(int i = 0; i < row; i++) {
            res.mat[i][i] = T(1);
        }
        return res;
    }

    constexpr Matrix power(i64 b) const {
        if (b == 0) {
            return Identify();
        }
        Matrix res = *this;
        Matrix base = *this;
        b --;
        while (b) {
            if (b % 2) {
                res *= base;
            }
            base *= base;
            b /= 2;
        }
        return res;
    }

    constexpr T rank() {
        Matrix t = *this;
        const int n = t.row, m = t.col;

        if (n == 0) {
            return T();
        }

        T rank = T();

        for (int j = 0; j < m; j++) {
            if (rank == T(n)) break;

            if (t.mat[(int)rank][j] == T()) {
                for (int i = (int)rank + 1; i < n; i ++) {
                    if (t.mat[i][j] != T()) {
                        std::swap(t.mat[(int)rank], t.mat[i]);
                        break;
                    }
                }
            }
            if (t.mat[(int)rank][j] == T())  {
                continue;
            }
            T c = T(1) / t.mat[(int)rank][j];

            for (int k = j; k < m; k ++) {
                t.mat[(int)rank][k] *= c;
            }

            for (int i = (int)rank + 1; i < n; i++) {
                T c = t.mat[i][j];
                for (int k = j; k < m; k ++) {
                    t.mat[i][k] -= t.mat[(int)rank][k] * c;
                }
            }
            rank += 1;
        }
        return rank;
    }

    constexpr T determinant() {
        Matrix t = *this;

        assert(t.row == t.col);

        const int n = t.row;

        bool flip = false;
        for (int x = 0; x < n; x ++) {
            int p = -1;
            for (int y = x; y < n; y ++) {
                if (t.mat[y][x] > T()) {
                    p = y;
                    break;
                }
            }
            if (p == -1) {
                return 0;
            }

            if (x != p) {
                std::swap(t.mat[x], t.mat[p]);
                flip = !flip;
            }

            for (int y = x + 1; y < n; y ++) {
                if (t.mat[y][x] == T()) {
                    continue;
                }
                auto freq = t.mat[y][x] / t.mat[x][x];

                for (int k = x; k < n; k++) {
                    t.mat[y][k] -= freq * t.mat[x][k];
                }
            }
        }

        T det = T(!flip ? 1 : -1);

        for (int i = 0; i < n; i ++) {
            det *= t.mat[i][i];
        }

        return det;
    }

    constexpr Matrix &operator+=(const Matrix &rhs) & {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mat[i][j] += rhs.mat[i][j];
            }
        }
        return *this;
    }

    constexpr Matrix &operator-=(const Matrix &rhs) & {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mat[i][j] -= rhs.mat[i][j];
            }
        }
        return *this;
    }

    constexpr Matrix &operator*=(const Matrix &rhs) & {
        assert(col == rhs.row); 
        Matrix res(row, rhs.col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < rhs.col; j++) {
                for (int k = 0; k < col; k++) {
                    res.mat[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        *this = res;
        return *this;
    }

    constexpr Matrix &operator/=(const Matrix &rhs) & {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mat[i][j] /= rhs.mat[i][j];
            }
        }
        return *this;
    }

    friend constexpr Matrix operator+(Matrix lhs, const Matrix &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend constexpr Matrix operator-(Matrix lhs, const Matrix &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr Matrix operator*(Matrix lhs, const Matrix &rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr Matrix operator/(Matrix lhs, const Matrix &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend std::istream &operator>>(std::istream &is, Matrix &mat) {
        for (int i = 0; i < mat.row; i++) {
            for (int j = 0; j < mat.col; j++) {
                is >> mat.mat[i][j];
            }
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
        for (const auto &row : mat.mat) {
            for (const auto &element : row) {
                os << element << " ";
            }
            os << std::endl;
        }
        return os;
    }
};