#ifndef PSDRAWER_H
#define PSDRAWER_H

class PSDrawer{

public:
    PSDrawer(const char* filename);
    ~PSDrawer();
    void drawPoint(double x1,double y1);
    void drawLine(double x1,double y1,double x2, double y2);
};
#endif // PSDRAWER_H
