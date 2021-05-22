//#include "Tests.h"
#include <iostream>
#include "Matrix.h"

using namespace std;


int main()
{
	Matrix<int> A(4, 4);
	for (int i = 0; i < A.getSizeH(); i++)
	{
		for (int k = 0; k < A.getSizeV(); k++)
		{
			A[i][k] = i;
		}
	}
	
	Matrix<int> C(4, 4);
	C ^= A;
	A.console_output();
	C.console_output();

	
	
	

	return 0;
}

