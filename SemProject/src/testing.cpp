#include "Tests.h"
#include <iostream>
#include "Dict.h"
#include "PSDrawer.h"
#include "basicinterface.h"

int main(){
	testdraw();

	BasicInterface bi;
	ID id1 = bi.addObject(OT_SEGMENT);
	ID id2 = bi.addObject(OT_SEGMENT);
	UniDict<ParamType, double> dict = bi.queryObjProperties(id1);
	
	for (UniDict<ParamType, double>::Marker m = dict.init(); m != dict.afterEnd(); m++)
	{
		std::cout << (*m).key << " " << (*m).val << std::endl;
	};


	return 0;
}

