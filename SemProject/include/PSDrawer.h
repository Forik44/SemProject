#ifndef PSDRAWER_H
#define PSDRAWER_H
#include "Errors.h"
#include <fstream>
#include <iostream>
class PSDrawer {
    public:
        PSDrawer(const char* filename) {
            fout.open(filename, std::ios_base::trunc);
            if (!fout.is_open()) { throw errors("TEST"); }
        };
        ~PSDrawer() {
            fout << "stroke";
            fout.close();
        };
        void drawPoint(double x1, double y1) { drawCircle(x1, y1, 0.5); };
        void drawLine(double x1, double y1, double x2, double y2) {
            if (!fout.is_open()) { throw errors("TEST"); }
            fout << x1 << " " << y1 << " moveto\n";
            fout << x2 << " " << y2 << " lineto\n";
        };
        void drawCircle(double x1, double y1, double radius) {
            if (!fout.is_open()) { throw errors("TEST"); }
            fout << x1 + radius << " " << y1 << " moveto\n";
            fout << x1 << " " << y1 << " " << radius << " 0 360 arc\n";
        };
    private:
        std::ofstream fout;
};

//PSDrawer

#endif 