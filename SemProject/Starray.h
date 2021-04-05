#ifndef STARRAY_H
#define STARRAY_H
#include <cstdlib>
template<typename ArrayElement,size_t S> class Starray{
private:

    ArrayElement* data;
    struct marker
    {
        ArrayElement* Elem;
        size_t Idx;
        size_t markerSize;
    };
public:
    Starray();
    Starray(const Starray& original);
    ~Starray();

    ArrayElement& operator[](size_t idx);
    const ArrayElement& operator[](size_t idx)const;

};
#endif // STARRAY_H
