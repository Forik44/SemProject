#ifndef PSDRAWER_H
#define PSDRAWER_H
#include "Errors.h"
#include "objects.h"
#include "basicinterface.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

class PSDrawer {
public:
	/*
		(�������� �����, ������ �� x, �� y, ������ ��������� �� x, �� �) ���� ������� ������ �������� �����, �� ��������� ������������ ���������
	*/
	PSDrawer(const char* filename) : PSDrawer(filename, -1, -1, 0, 0) {};
	PSDrawer(const char* filename, double sizex, double sizey) : PSDrawer(filename, sizex, sizey, 0, 0) {};
	PSDrawer(const char* filename, double endx, double endy, double startx, double starty) {
		_filename = filename;
		_size_circle = 0;
		_array_circle = nullptr;
		_size_line = 0;
		_array_line = nullptr;
		_endx = endx;
		_endy = endy;
		_startx = startx;
		_starty = starty;
		if (_endx == -1 && _endy == -1)
			_auto = 1;
		else {
			if (_endx <= 0 || _endy <= 0) throw errors("SIZE <=0");
			_auto = 0;
		}
	};
	~PSDrawer() {
		writefile();
		delete[] _array_circle;
		delete[] _array_line;

	};
	void addObj(ID id, BasicInterface bi);


	//return to private
	void addPoint(double x1, double y1) { addCircle(x1, y1, 0.2); }
	void addCircle(double x1, double y1, double radius);
	void addLine(double x1, double y1, double x2, double y2);



private:

	const char* _filename;
	uint8_t _auto;
	double _endx, _endy, _startx, _starty;
	//array circle
	struct _obj_circle {
		double x, y, radius;
	};
	_obj_circle* _array_circle;
	uint16_t _size_circle;
	//array line
	struct _obj_line {
		double x1, y1, x2, y2;
	};
	_obj_line* _array_line;
	uint16_t _size_line;

	void writefile();
};

void PSDrawer::writefile() {

	if (_endx <= 0 || _endy <= 0) return;
	//Check file
	char* _pathtofile = new char[8 + strlen(_filename)];
	memcpy(_pathtofile, "Drawer/", 7);
	for (int i = 7; i < 8 + strlen(_filename); i++) {
		_pathtofile[i] = _filename[i - 7];
	}
	std::ofstream fout;
	fout.open(_pathtofile, std::ios_base::trunc);
	delete[] _pathtofile;
	if (!fout.is_open()) { throw errors("Cant open file"); }
	//Setting the sheet size and coordinate axes
	
	if (_auto == 0 ) {
		fout << _startx << " " << _starty << " translate\n";
		fout << "<</PageSize [" << _endx << " " << _endy << "] /ImagingBBox null>> setpagedevice\n";
	}
	else {
		fout << _startx << " " << _starty << " translate\n";
		fout << "<</PageSize [" << _endx - _startx << " " << _endy - _starty << "] /ImagingBBox null>> setpagedevice\n";
	}
	fout << "0.5 setlinewidth\n";

	//Output of circles and lines
	for (uint16_t i = 0; i < _size_line; i++) {
		fout << _array_line[i].x1 - _startx << " " << _array_line[i].y1 - _starty << " moveto\n";
		fout << _array_line[i].x2 - _startx << " " << _array_line[i].y2 - _starty << " lineto\n";
	}
	for (uint16_t i = 0; i < _size_circle; i++) {
		fout << _array_circle[i].x - _startx + _array_circle[i].radius << " " << _array_circle[i].y - _starty << " moveto\n";
		fout << _array_circle[i].x - _startx << " " << _array_circle[i].y - _starty << " " << _array_circle[i].radius << " 0 360 arc\n";
	}
	//Output of coordinate axes
	fout << "0.2 setlinewidth\n";
	fout << -_startx << " " << -_endy - _starty << " moveto\n";
	fout << -_startx << " " << _endy - _starty << " lineto\n";
	fout << -_endx + _startx << " " << -_starty << " moveto\n";
	fout << _endx - _startx << " " << -_starty << " lineto\n";

	fout << "stroke";
	fout.close();

	//Start convert ps2pdf and open pdf
	char* _temp = new char[10 + strlen(_filename)];
	memcpy(_temp, "draw.bat ", 9);
	for (int i = 9; i < 10 + strlen(_filename); i++) {
		_temp[i] = _filename[i - 9];
	}
	system(_temp);
	delete[] _temp;
}
void PSDrawer::addCircle(double x1, double y1, double radius)
{
	//Calculating the sheet size and coordinate axes
	if (_auto) {
		if (x1 - radius < _startx) _startx = x1 - radius;
		if (x1 + radius > _endx) _endx = x1 + radius;
		if (y1 - radius < _starty) _starty = y1 - radius;
		if (y1 + radius > _endy) _endy = y1 + radius;
	}
	if (radius <= 0) throw errors("RADIUS <=0");
	//Add to array
	_obj_circle temp = { x1,y1,radius };
	if (_size_circle == 0)
	{
		_array_circle = new _obj_circle[1];
		_array_circle[0] = temp;
		_size_circle = 1;
	}
	else
	{
		_obj_circle* tmp = new _obj_circle[_size_circle + 1];
		for (size_t i = 0; i < _size_circle; i++)
		{
			tmp[i] = _array_circle[i];
		}
		tmp[_size_circle] = temp;
		delete[] _array_circle;
		_array_circle = tmp;
		_size_circle++;
	}

};
void PSDrawer::addLine(double x1, double y1, double x2, double y2)
{
	//Calculating the sheet size and coordinate axes
	if (_auto) {
		if (x1 < _startx) _startx = x1;
		if (x1 > _endx) _endx = x1;
		if (x2 < _startx) _startx = x2;
		if (x2 > _endx) _endx = x2;
		if (y1 < _starty) _starty = y1;
		if (y1 > _endy) _endy = y1;
		if (y2 < _starty) _starty = y2;
		if (y2 > _endy) _endy = y2;
	}
	//Add to array
	_obj_line temp = { x1,y1,x2,y2 };
	if (_size_line == 0)
	{
		_array_line = new _obj_line[1];
		_array_line[0] = temp;
		_size_line = 1;
	}
	else
	{
		_obj_line* tmp = new _obj_line[_size_line + 1];
		for (size_t i = 0; i < _size_line; i++)
		{
			tmp[i] = _array_line[i];
		}
		tmp[_size_line] = temp;
		delete[] _array_line;
		_array_line = tmp;
		_size_line++;
	}

};
void PSDrawer::addObj(ID id, BasicInterface bi)
{
	UniDict<ParamType, double> arr = bi.queryObjProperties(id);
	
	switch (bi.identifyObjTypeByID(id))
	{
	case OT_CIRCLE:
		addCircle(arr[PT_CX], arr[PT_CY], arr[PT_R]);
		break;
	case OT_POINT:
		addPoint(arr[PT_PX], arr[PT_PY]);
		break;
	case OT_SEGMENT:
		addLine(arr[PT_P1X], arr[PT_P1Y], arr[PT_P2X], arr[PT_P2Y]);
		break;
	case OT_ERROR:
		throw;
	}
}

//
//void testdraw() {
//	try {
//		//PSDrawer test("test.ps",400,400,-150,-150); 
//		PSDrawer test("test.ps");
//		test.addCircle(200.0, 200.0, 90.0);
//		test.addCircle(-200.0, 200.0, 100.0);
//		test.addCircle(-50, -50, 50);
//		test.addPoint(200.0, 200.0);
//		test.addLine(100, 100, 200.0, 200.0);
//	}
//	catch (errors& A) {
//		std::cout << A.message;
//	}
//
//}




#endif