#include <iostream>
#include "Array.h"
#include "basicinterface.h"
#include <algorithm>
#include <vector>

class Base{
public:
    Base(){ m_i = 3;}
    virtual ~Base(){std::cout << "Base destructor called" << std::endl; }
    virtual int getI()const{return m_i;}
private:
    int m_i;
};

class Follower:public Base{
public:
    Follower(){m_d = 3.1415926;}
    virtual ~Follower(){std::cout << "Follower destructor called" << std::endl; }
    virtual int getI()const{return 6;}
    double getD()const {return m_d;}
private:
    double m_d;
};

void OutObj(Base &b){
    std::cout << b.getI() << std::endl;
}

std::vector<int> generateArr(){
    std::vector<int> res;
    res.push_back(1);
    res.push_back(3);
    res.push_back(5);
    res.push_back(7);
    return res;
}

std::vector<Segment> generateSeg( ){
    std::vector<Segment> ase;
    ase.push_back({{1,2},{2,1}});
    ase.push_back({{1,3},{3,1}});
    ase.push_back({{2,2},{2,3}});
    return ase;
}
struct printse{
    void operator()(const Segment&s){
        std::cout << '(' << s.p1.x << ','<<s.p1.y << ") -> (" << s.p2.x << ',' << s.p2.y << ')' << std::endl;
    }
};
struct printa{
    void operator()(Array<int>&a){
        for (auto v:a)
            std::cout << v << ' ';
            std::cout << std::endl;
    }
};

class is_longer_than{
    double l;
public:
    is_longer_than(double d):l(d) {}
    bool operator()(const Segment&s){
        double len = std::sqrt( (s.p1.x - s.p2.x)*(s.p1.x - s.p2.x) + (s.p1.y - s.p2.y)*(s.p1.y - s.p2.y));
        return l < len;
    }
};

class is_shorter_than{
    double l;
public:
    is_shorter_than(double d):l(d) {}
    bool operator()(const Segment&s){
        double len = std::sqrt( (s.p1.x - s.p2.x)*(s.p1.x - s.p2.x) + (s.p1.y - s.p2.y)*(s.p1.y - s.p2.y));
        return l > len;
    }
};


struct normalizer{
    void operator()(Segment&s){
        double len = std::sqrt( (s.p1.x - s.p2.x)*(s.p1.x - s.p2.x) + (s.p1.y - s.p2.y)*(s.p1.y - s.p2.y));
        s.p2.x = s.p1.x + (s.p2.x - s.p1.x)/len;
        s.p2.y = s.p1.y + (s.p2.y - s.p1.y)/len;

    }
};
class length_sum{

};


bool iseq3_fun(int n) {
    return n == 3;
}
struct is_eq3{
    bool operator()(int n){
        return n == 3;
    }
};

int main(){

    std::vector<int> a;
    a.operator=(generateArr());
    for (std::vector<int>::iterator m = a.begin(); m != a.end() ; ++m)
        std::cout << "*m " << *m << std::endl;
    for (auto v:a)
        std::cout << "v " << v << std::endl;
    std::cout << "Done" << std::endl;
    std::cout << "3 s = " << std::count(a.begin(),a.end(),3) << std::endl;
    std::cout << "3 s = " << std::count_if(a.begin(),a.end(),is_eq3{}) << std::endl;
    std::cout << "3 s = " << std::count_if(a.begin(),a.end(),iseq3_fun) << std::endl;

    std::vector<Segment> as = generateSeg();

    std::for_each(as.begin(),as.end(), printse());
    std::cout << "longer than 1 = " << std::count_if(as.begin(),as.end(),is_longer_than{1}) << std::endl;
    std::cout << "longer than 1.5 = " << std::count_if(as.begin(),as.end(),is_longer_than{1.5}) << std::endl;
    std::cout << "After remove" << std::endl;
    std::vector<Segment>::iterator it = std::remove_if(as.begin(),as.end(),is_longer_than(1.3));
    std::for_each(as.begin(),it, printse());
    std::cout << "All " << std::endl;
    std::for_each(as.begin(),as.end(), printse());




    std::vector<Array<int> > aa;
    aa.push_back(Array<int>());
    aa.back().push_back(1);
    aa.push_back(Array<int>());
    aa.back().push_back(2);
    aa.back().push_back(3);
    aa.push_back(Array<int>());
    aa.back().push_back(4);
    aa.back().push_back(6);
    std::for_each(aa.begin(),aa.end(), printa());

    struct has_less_than{
        size_t  s;
        has_less_than(size_t a):s(a){}
        bool operator()(const Array<int>&a ){
            return a.size() < s;
        }
    };
    size_t size_thresh = 2;
    // std::cin >> size_thresh ;

    std::vector<Array<int> >::iterator it1 =
            std::remove_if(aa.begin(),aa.end(),[size_thresh](const Array<int>&a){return a.size() < size_thresh;});
    std::for_each(aa.begin(),it1, printa());
    std::cout << "All " << std::endl;
    std::for_each(aa.begin(),aa.end(), printa());
    std::cout << "Done" << std::endl;





    //std::cout << "Normalizer " << std::endl;
    //std::for_each(as.begin(),as.end(),normalizer());
    //std::cout << "longer than 1 = " << std::count_if(as.begin(),as.end(),is_longer_than{1}) << std::endl;





/*
    std::cout << "--------------------" << std::endl;
    Array<int> b(generateArr());
    for (Array<int>::Marker m = b.init(); m != b.afterEnd() ; ++m)
        std::cout << "*m " << *m << std::endl;
    std::cout << "--------------------" << std::endl;
    Array<int> c = generateArr();
    for (Array<int>::Marker m = c.init(); m != c.afterEnd() ; ++m)
        std::cout << "*m " << *m << std::endl;
    std::cout << "=======================" << std::endl;
*/





    /**
    BasicInterface bi;
    ID idp1 = bi.addObject(OT_POINT);
    //ID idp1 = bi.addObject(OT_POINT);
    std::cout << "=========================" << std::endl;
    UniDict<ParamType, double> props;
    std::cout << "------------------------" << std::endl;
    props = bi.queryObjProperties(idp1);
    std::cout << "------------------------" << std::endl;

    std::cout << "=========================" << std::endl;
    UniDict<ParamType, double> props1(bi.queryObjProperties(idp1));
    std::cout << "------------------------" << std::endl;

    for (UniDict<ParamType, double>::Marker m = props.init(); m != props.afterEnd(); m ++ ){
        std::cout << (*m).key << " " << (*m).val << std::endl;
    }
    */

/*    Base b;
    Follower f;

    std::cout << "b " p(*first)<< b.getI() << std::endl;
    std::cout <<"f " << f.getI() << std::endl;

    OutObj(b);
    OutObj(f);


    Array<Base> arb;
    arb.add(b);
    arb.add(f);



    for ( Array<Base>::Marker m = arb.init();m != arb.afterEnd();++m ){
        std::cout << "Item " << (*m).getI() << std::endl;
        //std::cout << "Item.getD " << (*m).getD() << std::endl;
    }
    std::cout << "Sizeof(Base) = " << sizeof(Base) << std::endl;
    std::cout << "Sizeof(Follower) = " << sizeof(Follower) << std::endl;
    std::cout << "Sizeof(Base*) = " << sizeof(&b) << std::endl;
    std::cout << "Sizeof(Follower*) = " << sizeof(&f) << std::endl;



    Array<Base*> arbp;
    arbp.add(&b);
    arbp.add(&f);
    std::cout << "Pointers " << std::endl;
    for ( Array<Base*>::Marker m = arbp.init();m != arbp.afterEnd();++m ){
        std::cout << "sizeof(*m) = " << sizeof(*m) << std::endl;
        std::cout << "Item " << (*m)->getI() << std::endl;
        //std::cout << "Item.getD " << (*m).getD() << std::endl;
    }
*/
    //Follower* pf = dynamic_cast<Follower*>(arbp[0]);
    //std::cout <<  "pf =" << pf << std::endl;
    //std::cout << "Converted pf  " << pf->getD() << std::endl;

/*
    Array<Base*> arbpn;
    arbpn.add(new Base() );
    arbpn.add(new Follower() );
    std::cout << "Pointers for heap " << std::endl;
    for ( Array<Base*>::Marker m = arbpn.init();m != arbpn.afterEnd();++m ){
        //std::cout << "sizeof(*m) = " << sizeof(*m) << std::endl;
        std::cout << "Item " << (*m)->getI() << std::endl;
        //std::cout << "Item.getD " << (*m).getD() << std::endl;
    }
    std::cout << "===========================" << std::endl;
    for ( Array<Base*>::Marker m = arbpn.init();m != arbpn.afterEnd();++m )
        delete *m;
    std::cout << "---------------------------" << std::endl;
*/

    return 0;
}
