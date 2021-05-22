#pragma once
#include <iostream>
using namespace std;

template<typename MatrixElement> class Matrix {
private:
    int _v_size, _h_size;
    MatrixElement** data;
    void subLines(MatrixElement* minuendLine, MatrixElement* subsLine, int size)
    {
        for (int i = 0; i < size; i++)
        {
            minuendLine[i] -= subsLine[i];
        }
    }
    void multiplyLineBy(MatrixElement* multipliedLine, MatrixElement Num, int size)
    {
        for (int i = 0; i < size; i++)
        {
            multipliedLine[i] *= Num;
        }
    }
    void divideLineBy(MatrixElement* dividedLine, MatrixElement Num, int size)
    {
        if (Num == 0)
            return;
        for (int i = 0; i < size; i++)
        {
            dividedLine[i] = dividedLine[i] / Num;
        }
    }
    void swapLines(MatrixElement* A1, MatrixElement* A2, int size)
    {
        double tmp;
        for (int i = 0; i < size; i++)
        {
            tmp = A1[i];
            A1[i] = A2[i];
            A2[i] = tmp;
        }
    }
    bool toDiagForm(Matrix& EM)
    {
        MatrixElement** E = EM.data;
        MatrixElement** A = data;
        int size = _v_size;

        for (int i = 0; i < size; i++)
        {
            if (!A[i][i])
            {
                bool isFoundNoZero = false;
                for (int m = i; m < size; m++)
                {
                    if (A[m][i])
                    {
                        isFoundNoZero = true;
                        swapLines(A[m], A[i], size);
                        swapLines(E[m], E[i], size);
                        break;
                    }
                }
                if (!isFoundNoZero)
                    return false;
            }

            if (A[i][i] != 1)
            {
                divideLineBy(E[i], A[i][i], size);
                divideLineBy(A[i], A[i][i], size);
            }

            double NOD;
            for (int k = 0; k < size; k++)
            {
                if (k != i)
                {
                    NOD = A[k][i];
                    if (NOD)
                    {
                        multiplyLineBy(A[i], NOD, size);
                        multiplyLineBy(E[i], NOD, size);

                        subLines(A[k], A[i], size);
                        subLines(E[k], E[i], size);

                        divideLineBy(A[i], NOD, size);
                        divideLineBy(E[i], NOD, size);


                        std::cout << "==================" << std::endl;
                        (*this).console_output();
                        std::cout << "------------------" << std::endl;
                        EM.console_output();
                        std::cout << "==================" << std::endl;
                    }
                }
               
            }
        }
    };
    Matrix generateUnitMatrix()
    {
        int size = _h_size;
        Matrix<MatrixElement> E(size, size);
        for (int i = 0; i < size; i++)
        {
            for (int k = 0; k < size; k++)
            {
                if (i == k)
                    E.data[i][i] = 1;
                else
                    E.data[i][k] = 0;
            }
        }
        return E;
    }
   
public:
    Matrix()
    {
        _v_size = _h_size = 0;
        data = nullptr;
    }
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
        delete data;
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
        for (int i = 0; i < _v_size; i++)
        {
            delete[] data[i];
        }
        delete[] data;

        _v_size = original._v_size;
        _h_size = original._h_size;

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
   
    Matrix operator!()
    {
        if (_h_size != _v_size)
            throw std::runtime_error("Invalid matrix size\n");

        Matrix<MatrixElement> C = (*this);
        Matrix<MatrixElement> E = generateUnitMatrix();
     
        C.toDiagForm(E);
        return E;
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

    MatrixElement* operator[](int v_idx)
    {
        if (v_idx > _v_size)
            throw std::runtime_error("Invalid matrix size\n");
        return data[v_idx];
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

