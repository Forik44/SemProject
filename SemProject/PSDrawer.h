#ifndef PSDRAWER_H
#define PSDRAWER_H
#include <fstream>
class PSDrawer {

    public:
        PSDrawer(const char* filename) {
            fout.open(filename, std::ios_base::trunc);
            if (!fout.is_open()) 
                std::cout << "Can't open or create file\n"; 
        };
        ~PSDrawer() { 
            fout << "stroke";
            fout.close();
        };
        void drawPoint(double x1, double y1) { drawLine(x1, y1, x1+1, y1+1); };
        void drawLine(double x1, double y1, double x2, double y2) {
            if (!fout.is_open())
                std::cout << "Can't open or create file\n";
            else {
                fout <<x1<<" "<< y1 << " moveto\n";
                fout << x2 << " " << y2 << " lineto\n";
            }
        };
        void drawCircle(double x1, double y1, double radius) {
            if (!fout.is_open())
                std::cout << "Can't open or create file\n";
            else {
                fout << x1+radius << " " << y1 << " moveto\n";
                fout << x1 << " " << y1 <<" "<< radius <<" 0 360 arc\n";
            }
        };
    private:
        std::ofstream fout; 
};

//PSDrawer

#endif 