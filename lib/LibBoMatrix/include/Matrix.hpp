//
// Created by niubo on 2/29/20.
//

#ifndef BOMATRIX_MATRIX_HPP
#define BOMATRIX_MATRIX_HPP

#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include<istream>
#include <string>
#include <sstream>
#include <cassert>
#include<omp.h>
#include <cmath>

namespace Bo {

    template<typename T>
    class Matrix {

    public:

        Matrix(size_t rows, size_t cols) {
            assert(rows > 0 && cols > 0);
            _rows = rows;
            _cols = cols;

            _mat = new T *[rows];
            for (int i = 0; i < rows; i++)
                _mat[i] = new T[cols];
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    _mat[i][j] = 0;
        }

        Matrix(const Matrix<T> &matrix) {
            _cols = matrix._cols;
            _rows = matrix._rows;
            _mat = new T *[matrix._rows];

            for (int i = 0; i < matrix._rows; i++)
                _mat[i] = new T[matrix._cols];
            for (int i = 0; i < matrix._rows; i++)
                for (int j = 0; j < matrix._cols; j++)
                    _mat[i][j] = matrix[i][j];
        }

        virtual ~Matrix() {
            if (_mat == nullptr)return;
            for (int i = 0; i < _rows; i++)
                delete[] _mat[i];
            delete[] _mat;
        }

        Matrix<T> transpose() {
            Matrix<T> transpose(_cols, _rows);
            for (int i = 0; i < _cols; ++i)
                for (int j = 0; j < _rows; ++j) {
                    transpose[i][j] = _mat[j][i];
                }

            return transpose;
        }

        size_t getRows() const {
            return _rows;
        }

        size_t getCols() const {
            return _cols;
        }

//        T *getArray() const;

        void operator=(const Matrix<T> &matrix) {
            for (int i = 0; i < matrix._rows; i++)
                for (int j = 0; j < matrix._cols; j++)
                    _mat[i][j] = matrix[i][j];
            _rows = matrix._rows;
            _cols = matrix._cols;
        }

        Matrix<T> operator-() const {
            Matrix<T> temp(_rows, _cols);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    temp[i][j] = -_mat[i][j];
            return temp;
        }

        Matrix<T> operator-(const Matrix<T> &matrix) const {
            assert(_rows == matrix._rows && _cols == matrix._cols);
            Matrix temp(_rows, _cols);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    temp[i][j] = _mat[i][j] - matrix[i][j];
            return temp;
        }

        Matrix<T> operator+(const Matrix<T> &matrix) const {
            assert(_rows == matrix._rows && _cols == matrix._cols);
            Matrix temp(_rows, _cols);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    temp.Mat[i][j] += matrix[i][j] + _mat[i][j];
            return temp;
        }

        friend Matrix<T> operator+(const T &num, const Matrix<T> &t) {
            Matrix<T> res = t;
            for (int i = 0; i < res._rows; ++i) {
                for (int j = 0; j < res._cols; ++j) {
                    res._mat[i][j] += num;
                }
            }
            return res;
        }

        Matrix<T> operator+(const T &num) const {
            return num + *this;
        }

        Matrix<T> operator*(const Matrix<T> &matrix) const {
            assert(_cols == matrix._rows);
            Matrix<T> res(_rows, matrix._cols);

            for (size_t i = 0; i < _rows; i++) {
                #pragma omp for
                for (size_t j = 0; j < matrix._cols; j++) {
                    for (size_t k = 0; k < _cols; k++) {
                        res._mat[i][j] += _mat[i][k] * matrix._mat[k][j];
                    }
                }
            }

            return res;
        }

        Matrix<T> operator*(const T &num) const {
            Matrix temp(_rows, _cols);
            for (int i = 0; i < _rows; i++)
                    #pragma omp for
                    for (int j = 0; j < _cols; j++)
                        temp[i][j] = _mat[i][j] * num;
            return temp;
        }

        friend Matrix<T> operator*(const T &num, const Matrix<T> &m) {
            return m * num;
        }

        bool operator==(const Matrix<T> &m) {
            if (_cols != m._cols || _rows != m._rows)return false;
            for (int i = 0; i < m._rows; i++) {
                for (int j = 0; j < m._cols; j++) {
                    if (std::fabs(m[i][j] - _mat[i][j]) > 1e-9)return false;
                }
            }
            return true;
        }

        inline T *&operator[](const size_t &index) const {
            return _mat[index];
        }

        friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) {
            for (int i = 0; i < m._rows; ++i) {
                for (int j = 0; j < m._cols; ++j) {
                    os << std::to_string(m[i][j]) << "  ";
                }
                os << '\n';
            }
            return os;
        }

        Matrix<T> &operator<<(T x) {
            _mat[0][0] = x;
//            printf("operator << : ind = %d\n_mat[0][0] = %lf;\n", _ind, x);
            ++_ind;
            return *this;
        }

        Matrix<T> &operator,(T x) {
            _mat[_ind / _cols][_ind - _cols * (_ind / _cols)] = x;
            ++_ind;
            return *this;
        }

    private:
        T **_mat = nullptr;
        size_t _rows = 0;
        size_t _cols = 0;
        size_t _ind = 0;//for comma initializer.



    };


}


#endif //BOMATRIX_MATRIX_HPP