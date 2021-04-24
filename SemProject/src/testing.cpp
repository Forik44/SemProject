#include "Tests.h"
#include <iostream>
#include "TreeDict.h"
#include "PSDrawer.h"
int main(){
	/*testdraw();*/
	TreeDict<int, int> tree;
	int N = 20;
	for (int i = 0; i < N; i++)
	{
		tree.add(rand()%1000, i);
		for (TreeDict<int, int>::Marker m = tree.init(); m != tree.afterEnd(); m++)
		{
			std::cout << (*m).key << " " << (*m).value << std::endl;
		}
		std::cout << '\n';
	}

	for (TreeDict<int, int>::Marker m = tree.init(); m != tree.afterEnd(); m++)
	{
		std::cout << (*m).key << " " << (*m).value << std::endl;
	}
	std::cout << '\n';
	std::cout << tree.getHeight();
	std::cout << '\n';

	tree.removeElementByKey(2);
	for (TreeDict<int, int>::Marker m = tree.init(); m != tree.afterEnd(); m++)
	{
		std::cout << (*m).key << " " << (*m).value << std::endl;
	}


	return 0;
}

