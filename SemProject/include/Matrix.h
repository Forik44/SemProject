#pragma once
#include <iostream>
using namespace std;

template<typename MatrixElement> class Matrix {
private:
    int _v_size, _h_size;
    MatrixElement** data;
public:
    Matrix(const int vertical_size, const int horizontal_size)
    {
        _v_size = vertical_size;
        _h_size = horizontal_size;

        data = new MatrixElement * [_v_size];
        for (int i = 0; i < _v_size; i++)
        {
            data[i] = new MatrixElement[_h_size];
        }
       
    };
    Matrix(const Matrix& original)
    {
        _v_size = original._v_size;
        _h_size = original._h_size;

        data = new MatrixElement * [_v_size];
        for (int i = 0; i < _v_size; i++)
        {
            data[i] = new MatrixElement[_h_size];
        }

        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                data[i][k] = original.data[i][k];
            }
        }
    };
    Matrix(Matrix&& original)
    {
        _v_size = original._v_size;
        _h_size = original._h_size;
        data = original.data;
       
        original.data = nullptr;
        original._h_size = original._v_size = 0;
    };
    ~Matrix()
    {
        for (int i = 0; i < _v_size; i++)
            delete[] data[i];
        _v_size = _h_size = 0;
    }; 

    int v_size() const
    {
        return _v_size;
    };
    int h_size() const
    {
        return _h_size;
    };
    int v_size() 
    {
        return _v_size;
    };
    int h_size() 
    {
        return _h_size;
    };
    void console_output()
    {
        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                cout << data[i][k] << " ";
            }
            cout << endl;
        }

    }

    Matrix& operator= (const Matrix& original)
    {      
        if (original._h_size != _h_size || original._v_size != _v_size)
            throw std::runtime_error("Invalid matrix size\n");

        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                data[i][k] = original.data[i][k];
            }
        }

        return *this;
    }
    Matrix operator~()
    {
        Matrix<MatrixElement> C(_h_size, _v_size);

        for (int i = 0; i < C._v_size; i++)
        {
            for (int k = 0; k < C._h_size; k++)
            {
                 C.data[i][k] = data[k][i];
            }
        }

        return C;
    }

    Matrix& operator+= (const Matrix& original)
    {
        if (original._h_size != _h_size || original._v_size != _v_size)
            throw std::runtime_error("Invalid matrix size\n");
        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                data[i][k] += original.data[i][k];
            }
        }

        return *this;
    }
    Matrix& operator+= (const MatrixElement Num)
    {
        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                data[i][k] += Num;
            }
        }

        return *this;
    }
   
    Matrix& operator-= (const Matrix& original)
    {
        if (original._h_size != _h_size || original._v_size != _v_size)
            throw std::runtime_error("Invalid matrix size\n");
        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                data[i][k] -= original.data[i][k];
            }
        }

        return *this;
    }
    Matrix& operator-= (const MatrixElement Num)
    {
        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                data[i][k] -= Num;
            }
        }

        return *this;
    }

    Matrix& operator*= (const MatrixElement Num)
    {
        for (int i = 0; i < _v_size; i++)
        {
            for (int k = 0; k < _h_size; k++)
            {
                data[i][k] *= Num;
            }
        }

        return *this;
    }

    MatrixElement* operator[](int h_idx)
    {
        if (h_idx>_h_size)
            throw std::runtime_error("Invalid matrix size\n");
        return data[h_idx];
    }

   


    Matrix operator+ (const Matrix& original)
    {
        Matrix<MatrixElement> C(original._v_size, original._h_size);
        C = *this;
        C += original;
        return C;
    }
    Matrix operator+(const MatrixElement Num)
    {
        Matrix<MatrixElement> C(_v_size, _h_size);
        C = *this;
        C += Num;
        return C;
    }

    Matrix operator- (const Matrix& original)
    {
        Matrix<MatrixElement> C(original._v_size, original._h_size);
        C = *this;
        C -= original;
        return C;
    }
    Matrix operator-(const MatrixElement Num)
    {
        Matrix<MatrixElement> C(_v_size, _h_size);
        C = *this;
        C -= Num;
        return C;
    }

    Matrix operator* (const Matrix& original)
    {
        if (_h_size != original._v_size)
            throw std::runtime_error("Invalid matrix size\n");


        Matrix<MatrixElement> C(_v_size, original._h_size);

        for (int i = 0; i < C._v_size; i++)
        {
            for (int k = 0; k < C._h_size; k++)
            {
                MatrixElement Sum = 0;
              
                for (int j = 0; j < _h_size; j++)
                {
                    Sum += data[i][j] * original.data[j][k];
                }

                C[i][k] = Sum;
            }
        }

        return C;
    }
    Matrix operator*(const MatrixElement Num)
    {
        Matrix<MatrixElement> C(_v_size, _h_size);
        C = *this;
        C *= Num;
        return C;
    }
   
    
};
