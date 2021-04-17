#include "Tests.h"
#include <iostream>
#include "TreeDict.h"

int main(){

	TreeDict<int, int> tree;
	int N = 20;
	for (int i = 0; i < N; i++)
	{
		tree.add(rand(), i);
	}

	for (TreeDict<int, int>::Marker m = tree.init(); m != tree.afterEnd(); m++)
	{
		std::cout << (*m).key << " " << (*m).value << std::endl;
	}
	
	tree.removeElementByKey(3);
	for (TreeDict<int, int>::Marker m = tree.init(); m != tree.afterEnd(); m++)
	{
		std::cout << (*m).key << " " << (*m).value << std::endl;
	}


	return 0;
}

