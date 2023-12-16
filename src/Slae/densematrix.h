#ifndef SLAE_DENSEMATRIX_H
#define SLAE_DENSEMATRIX_H

#include <ostream>
#include <vector>
#include <set>
#include <stdexcept>

template<typename T>
class DenseMatrix{
public:
    using elm_t = T;
    using idx_t = std::size_t;

private:

    std::vector<T> matrix_;
    idx_t row_size_, col_size_;

    template<typename EL>
    friend std::vector<EL> operator*(const DenseMatrix<EL> &A, const std::vector<EL> &b);
public:

    DenseMatrix(const idx_t &h, const idx_t& w)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
    }

    DenseMatrix(const idx_t &h, const idx_t& w, const std::vector<T> &data)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
        for (int i = 0; i < data.size(); i++)
        {
            matrix_[i] = data.at(i);
        }
    }

    DenseMatrix(const idx_t &h, const idx_t& w, T fill)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
        for (int i = 0; i < h * w; i++)
            matrix_[i] = fill;
    }


    elm_t& operator()(const idx_t& i, const idx_t& j)
    {
        return matrix_[i * col_size_ + j];
    }

    const elm_t& operator()(const idx_t& i, const idx_t& j) const
    {
        return matrix_[i * col_size_ + j];
    }

    void operator-=(const DenseMatrix<elm_t> &A){
        for(int i = 0; i < matrix_.size(); i++)
        {
            matrix_[i] -= A.matrix_[i];
        }
    }
    
    DenseMatrix<T> inverse()
    {
        T temp;
        auto N = col_size_;

        DenseMatrix<T> E(N, N);
        DenseMatrix<T> ret = *this;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                E(i,j) = 0.0;

                if (i == j)
                    E(i, j) = 1.0;
            }

        for (int k = 0; k < N; k++)
        {
            temp = ret(k,k);

            for (int j = 0; j < N; j++)
            {
                ret(k, j) /= temp;
                E(k, j) /= temp;
            }

            for (int i = k + 1; i < N; i++)
            {
                temp = ret(i, k);

                for (int j = 0; j < N; j++)
                {
                    ret(i, j) -= ret(k, j) * temp;
                    E(i, j) -= E(k, j) * temp;
                }
            }
        }

        for (int k = N - 1; k > 0; k--)
        {
            for (int i = k - 1; i >= 0; i--)
            {
                temp = ret(i, k);

                for (int j = 0; j < N; j++)
                {
                    ret(i, j) -= ret(k, j) * temp;
                    E(i, j) -= E(k, j) * temp;
                }
            }
        }

        return E;
    }

    [[nodiscard]] const idx_t& get_row_size() const
    {
        return row_size_;
    }

    [[nodiscard]] const idx_t& get_col_size() const
    {
        return col_size_;
    }

    std::vector<T> get_col(unsigned i) const
    {
        std::vector<T> col(row_size_);

        for (unsigned j = 0; j < row_size_; j++)
            col[j] = matrix_[j * col_size_ + i];

        return col;
    }

    void swap(const idx_t& first, const idx_t& second)
    {
        if (first == second)
        {
            throw std::exception();
        }

        if (first > row_size_ || second > row_size_)
        {
            throw std::exception();
        }

        std::vector<T> tmp(col_size_);

        for (int i = 0; i < col_size_; ++i)
        {
            tmp[i] = matrix_[(first - 1) * col_size_ + i];
        }

        for (int i = 0; i < col_size_; ++i)
        {
            matrix_[(first - 1) * col_size_ + i] = matrix_[(second - 1) * col_size_ + i];
        }

        for (int i = 0; i < col_size_; ++i)
        {
            matrix_[(second - 1) * col_size_ + i] = tmp[i];
        }

    }

    DenseMatrix<T> transpose() {
        DenseMatrix<T> tr(col_size_, row_size_);
        for (size_t i = 0; i < row_size_; ++i) {
            for (size_t j = 0; j < col_size_; ++j) {
                tr(j, i) = matrix_[i * col_size_ + j];
            }
        }
        return tr;
    }


    void deleteLastRow()
    {
        matrix_.erase(matrix_.end() - col_size_, matrix_.end());
        row_size_--;
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const DenseMatrix<T> &A)
{
    for (int i = 0; i < A.get_row_size(); ++i)
    {
        for (int j = 0; j < A.get_col_size(); ++j)
            os << A(i, j) << " ";
        os << std::endl;
    }

    return os;
}

template <typename T>
DenseMatrix<T> operator*(const DenseMatrix<T> &A, const DenseMatrix<T> &B) {
    DenseMatrix<T> result(A.get_row_size(), B.get_col_size(), 0);

    for (int i = 0; i < A.get_row_size(); i++) {
        for (int j = 0; j < B.get_col_size(); j++) {
            for (int k = 0; k < A.get_col_size(); k++)
                result(i, j) += A(i, k) * B(k, j);
        }
    }

    return result;
}

template <typename T>
std::vector<T> operator*(const DenseMatrix<T> &A, const std::vector<T> &b) {
    auto result = A;
    result = result * DenseMatrix<T>(b.size(), 1, b);
    return result.matrix_;
}

template <typename T>
DenseMatrix<T> operator*(const T &a, const DenseMatrix<T> &A) {
    DenseMatrix<T> result(A.get_row_size(), A.get_col_size(), 0);

    for (int i = 0; i < A.get_row_size(); i++) {
        for (int j = 0; j < A.get_col_size(); j++) {
            result(i, j) = A(i, j) * a;
        }
    }

    return result;
}

#endif