#ifndef PSDRAWER_H
#define PSDRAWER_H
#include "Array.h"
#include "Errors.h"
#include "objects.h"
#include "basicinterface.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

class PSDrawer {
public:
	/*
		(Названия файла, размер по x, по y, начало коориднат по x, по у) Если указано только название файла, то отсальное определиться автоматом
	*/
	PSDrawer(const char* filename) : PSDrawer(filename, -1, -1, 0, 0,0) {};
	PSDrawer(const char* filename, uint16_t offset) : PSDrawer(filename, -1, -1, 0, 0, offset) {};
	PSDrawer(const char* filename, double sizex, double sizey) : PSDrawer(filename, sizex, sizey, 0, 0, 0) {};
	PSDrawer(const char* filename, double endx, double endy, double startx, double starty,uint16_t offset) {
		_filename = filename;
		_endx = endx;
		_endy = endy;
		_startx = startx;
		_starty = starty;
		_offset = offset;
		if (_endx == -1 && _endy == -1)
			_auto = 1;
		else {
			if (_endx <= 0 || _endy <= 0) throw errors("SIZE <=0");
			_auto = 0;
		}
	};
	~PSDrawer() {
		writefile();
	};
	void setOffset(uint16_t offset) { _offset = offset; }
	void addObj(ID id, BasicInterface bi);
private:
	void addPoint(double x1, double y1) { addCircle(x1, y1, 0.2); }
	void addCircle(double x1, double y1, double radius);
	void addLine(double x1, double y1, double x2, double y2);
	uint16_t _offset;
	const char* _filename;
	uint8_t _auto;
	double _endx, _endy, _startx, _starty;
	struct _obj_circle {
		double x, y, radius;
	};
	Array<_obj_circle> _array_circle;
	struct _obj_line {
		double x1, y1, x2, y2;
	};
	Array<_obj_line> _array_line;
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

	if (_auto == 0) {
		
		fout << "<</PageSize [" << _endx+ 2 * _offset << " " << _endy+ 2*_offset << "] /ImagingBBox null>> setpagedevice\n";
		fout << -_startx + _offset << " " << -_starty + _offset << " translate\n";
	}
	else {
		fout << "<</PageSize [" << _endx - _startx+ 2 * _offset << " " << _endy - _starty+ 2 * _offset << "] /ImagingBBox null>> setpagedevice\n";
		fout << -_startx + _offset << " " << -_starty + _offset << " translate\n";
	}
	fout << "0.5 setlinewidth\n";

	//Output of circles and lines
	for (uint16_t i = 0; i < _array_line.size(); i++) {
		fout << _array_line[i].x1 << " " << _array_line[i].y1  << " moveto\n";
		fout << _array_line[i].x2 << " " << _array_line[i].y2  << " lineto\n";
	}
	for (uint16_t i = 0; i < _array_circle.size(); i++) {
		fout << _array_circle[i].x+_array_circle[i].radius << " " << _array_circle[i].y  << " moveto\n";
		fout << _array_circle[i].x << " " << _array_circle[i].y  << " " << _array_circle[i].radius << " 0 360 arc\n";
	}
	//Output of coordinate axes
	fout << "0.2 setlinewidth\n";
	fout << -_endx + _startx << " " << 0 << " moveto\n";
	fout << _endx - _startx << " " << 0 << " lineto\n";
	fout << 0 << " " << -_endy + _starty << " moveto\n";
	fout << 0 << " " << _endy - _starty << " lineto\n";
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
		if (_endx == -1) {
			_startx = x1 - radius;
			_starty = y1 - radius;
		}
		if (x1 - radius < _startx) _startx = x1 - radius;
		if (x1 + radius > _endx) _endx = x1 + radius;
		if (y1 - radius < _starty) _starty = y1 - radius;
		if (y1 + radius > _endy) _endy = y1 + radius;
	}
	if (radius <= 0) throw errors("RADIUS <=0");
	//Add to array
	_obj_circle temp = { x1,y1,radius };
	_array_circle.push_back(temp);

};
void PSDrawer::addLine(double x1, double y1, double x2, double y2)
{
	//Calculating the sheet size and coordinate axes
	if (_auto) {
		if (_endx == -1) {
			_startx = x1; 
			_starty = y1;
		}
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
	_array_line.push_back(temp);

};
void PSDrawer::addObj(ID id, BasicInterface bi)
{
	TreeDict<ParamType, double> arr = bi.queryObjProperties(id);

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

/*
void testdraw() {
	try {
		//PSDrawer test("test.ps",400,400,-150,-150); 
		PSDrawer test("test.ps");
		///test.addCircle(200.0, 200.0, 90.0);
		//test.addCircle(-200.0, 200.0, 100.0);
		//test.addCircle(-50, -50, 50);
		//test.addPoint(200.0, 200.0);
		//test.addLine(100, 100, 200.0, 200.0);
	}
	catch (errors& A) {
		std::cout << A.message;
	}

}
*/



#endif