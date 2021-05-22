//#include "Tests.h"
#include <iostream>
#include "Matrix.h"

using namespace std;


int main()
{
	Matrix<int> A(1, 3);
	Matrix<int> B(3, 1);

	for (int i = 0; i < B.v_size(); i++)
	{
		for (int k = 0; k < B.h_size(); k++)
		{
			B[i][k] = i+3;
		}
	}

	A = ~B;
	A.console_output();
	
	cout << "----------------" << endl;

	B.console_output();
	
	
	

	return 0;
}

