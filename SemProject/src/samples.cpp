#include <iostream>
#include "Array.h"
#include "basicinterface.h"

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

Array<int> generateArr(){
    Array<int> res;
    res.add(1);
    res.add(3);
    res.add(5);
    res.add(7);
    return res;
}

int main(){
    Array<int> a;
    a.operator=(generateArr());
    for (Array<int>::Marker m = a.init(); m != a.afterEnd() ; ++m)
        std::cout << "*m " << *m << std::endl;
    std::cout << "--------------------" << std::endl;
    Array<int> b(generateArr());
    for (Array<int>::Marker m = b.init(); m != b.afterEnd() ; ++m)
        std::cout << "*m " << *m << std::endl;
    std::cout << "--------------------" << std::endl;
    Array<int> c = generateArr();
    for (Array<int>::Marker m = c.init(); m != c.afterEnd() ; ++m)
        std::cout << "*m " << *m << std::endl;
    std::cout << "=======================" << std::endl;






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

    std::cout << "b " << b.getI() << std::endl;
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