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
    Matrix(const Matrix&& original)
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
    Matrix& operator*(const Matrix& original)///////////////////////////////////////////////////////////
    {
        if (h_size != original.v_size)
            throw - 1;

        Matrix<MatrixElement> result(v_size, original.h_size);

        for (int i = 0; i < result.v_size; i++)
        {
            for (int k = 0; k < result.h_size; i++)
            {

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
            throw - 1;
        for (int i = 0; i < v_size; i++)
        {
            for (int k = 0; k < h_size; k++)
            {
                data[i][k] += original.data[i][k];
            }
        }

        return *this;
    }
    Matrix& operator+= (const int Num)
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
    Matrix& operator+= (const double Num)
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
    Matrix& operator-= (const int Num)
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
    Matrix& operator-= (const double Num)
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
    

    Matrix& operator*= (const int Num)
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
    Matrix& operator*= (const double Num)
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

   
    
};
