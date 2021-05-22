#pragma once
#include <iostream>
using namespace std;

template<typename MatrixElement> class Matrix {
private:
    int v_size, h_size;
    MatrixElement** data;
public:
    Matrix(const int vertical_size, const int horizontal_size)
    {
        v_size = vertical_size;
        h_size = horizontal_size;

        data = new MatrixElement * [v_size];
        for (int i = 0; i < v_size; i++)
        {
            data[i] = new MatrixElement[h_size];
        }
       
    };
    Matrix(const Matrix& original)
    {
        v_size = original.v_size;
        h_size = original.h_size;

        data = new MatrixElement * [v_size];
        for (int i = 0; i < v_size; i++)
        {
            data[i] = new MatrixElement[h_size];
        }

        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] = original.data[i][k];
            }
        }
    };
    Matrix(Matrix&& original)
    {
        v_size = original.v_size;
        h_size = original.h_size;
        data = original.data;
       
        original.data = nullptr;
        original.h_size = original.v_size = 0;
    };
    ~Matrix()
    {
        for (int i = 0; i < v_size; i++)
            delete[] data[i];
        v_size = h_size = 0;
    }; 

    int getSizeV() const
    {
        return v_size;
    };
    int getSizeH() const
    {
        return h_size;
    };
    void console_output()
    {
        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                cout << data[i][k] << " ";
            }
            cout << endl;
        }

    }

    Matrix& operator= (const Matrix& original)
    {      
        if (original.h_size != h_size || original.v_size != v_size)
            throw - 1;

        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] = original.data[i][k];
            }
        }

        return *this;
    }
    Matrix& operator^=(const Matrix& original)
    {
        if (h_size != original.v_size || v_size != original.h_size)
            throw - 1;

        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[k][i] = original.data[i][k];
            }
        }
        return *this;
    }

    Matrix& operator+= (const Matrix& original)
    {
        if (original.h_size != h_size || original.v_size != v_size)
            throw;
        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] += original.data[i][k];
            }
        }

        return *this;
    }
    Matrix& operator+= (const MatrixElement Num)
    {
        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] += Num;
            }
        }

        return *this;
    }
   
    Matrix& operator-= (const Matrix& original)
    {
        if (original.h_size != h_size || original.v_size != v_size)
            throw - 1;
        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] -= original.data[i][k];
            }
        }

        return *this;
    }
    Matrix& operator-= (const MatrixElement Num)
    {
        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] -= Num;
            }
        }

        return *this;
    }

    Matrix& operator*= (const Matrix& original)
    {
        if (h_size != original.v_size)
            throw std::runtime_error("Invalid matrix size\n");

        Matrix<MatrixElement> C(v_size, original.h_size);

        for (int i = 0; i < C.v_size; i++)
        {
            for (int k = 0; k < C.h_size; k++)
            {
                MatrixElement Sum = 0;

                for (int j = 0; j < h_size; j++)
                {
                    Sum += data[i][j] * original.data[j][k];
                }

                C[i][k] = Sum;
            }
        }

        return C;
        
        
    }
    Matrix& operator*= (const MatrixElement Num)
    {
        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] *= Num;
            }
        }

        return *this;
    }

    MatrixElement* operator[](int h_idx)
    {
        return data[h_idx];
    }

   


    Matrix operator+ (const Matrix& original)
    {
        Matrix<MatrixElement> C(original.v_size, original.h_size);
        C = *this;
        C += original;
        return C;
    }
    Matrix operator+(const MatrixElement Num)
    {
        Matrix<MatrixElement> C(v_size, h_size);
        C = *this;
        C += Num;
        return C;
    }

    Matrix operator- (const Matrix& original)
    {
        Matrix<MatrixElement> C(original.v_size, original.h_size);
        C = *this;
        C -= original;
        return C;
    }
    Matrix operator-(const MatrixElement Num)
    {
        Matrix<MatrixElement> C(v_size, h_size);
        C = *this;
        C -= Num;
        return C;
    }

    Matrix operator* (const Matrix& original)
    {
        if (h_size != original.v_size)
            throw;

        Matrix<MatrixElement> C(v_size, original.h_size);

        for (int i = 0; i < C.v_size; i++)
        {
            for (int k = 0; k < C.h_size; k++)
            {
                MatrixElement Sum = 0;
              
                for (int j = 0; j < h_size; j++)
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
        Matrix<MatrixElement> C(v_size, h_size);
        C = *this;
        C *= Num;
        return C;
    }
   
    
};
