#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename Type>
class Matrix {
private:
    std::vector<std::vector<Type>> m;

public:
    Matrix(const unsigned int x, const unsigned int y) {
        m.resize(x, std::vector<Type>(y, 0));
    }

    class MatrixRow {
        std::vector<Type>& row;
    public:
        MatrixRow(std::vector<Type>& r) : row(r) {}

        Type& operator[](unsigned int y) {
            return row.at(y);
        }

        Type operator[](unsigned int y) const {
            return row.at(y);
        }
    };

    MatrixRow operator[](unsigned int x) {
        return MatrixRow(m.at(x));
    }

    size_t nRows() const
    {
      return m.size();
    }

    size_t nColumns() const
    {
      return m[0].size();
    }

    bool addRow() {
      m.push_back(std::vector<Type>(nColumns(), 0));
      return true;
    }

    bool addColumn() {
      for (auto& row : m) {
        row.push_back(0);
      }
      return true;
    }

    bool removeRow(const unsigned int row) {
      if (row >= nRows()) {
        return false;
      }
      m.erase(m.begin() + row);
      return true;
    }

    bool removeColumn(const unsigned int column) {
      if (column >= nColumns()) {
        return false;
      }
      for (auto& row : m) {
        row.erase(row.begin() + column);
      }
      return true;
    }

    class ConstMatrixRow {
        const std::vector<Type>& row;
    public:
        ConstMatrixRow(const std::vector<Type>& r) : row(r) {}

        Type operator[](unsigned int y) const {
            return row.at(y);
        }
    };

    ConstMatrixRow operator[](unsigned int x) const {
        return ConstMatrixRow(m.at(x));
    }

    Matrix& operator=(const Matrix<Type>& other) {
        if (this != &other)
            m = other.m;
        return *this;
    }
};

#endif