//#include "Tests.h"
#include <iostream>
#include "Matrix.h"

using namespace std;


int main()
{
	Matrix<int> A(2, 3);
	Matrix<int> B(3, 1);
	for (int i = 0; i < A.getSizeV(); i++)
	{
		for (int k = 0; k < A.getSizeH(); k++)
		{
			A[i][k] = i;
		}
	}
	for (int i = 0; i < B.getSizeV(); i++)
	{
		for (int k = 0; k < B.getSizeH(); k++)
		{
			B[i][k] = i+3;
		}
	}

	A.console_output();
	B.console_output();
	cout << "----------------" << endl;
	Matrix<int> C(2, 1);
	C = A * B;
	
	C.console_output();
	
	
	

	return 0;
}

