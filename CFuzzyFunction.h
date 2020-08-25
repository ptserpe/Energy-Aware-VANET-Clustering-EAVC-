#ifndef CFUZZYFUNCTION_H
#define CFUZZYFUNCTION_H

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;


class CFuzzyFunction{

    protected :
        double dLeft, dRight;
        char   cType;
        char*  sName;

    public:
        CFuzzyFunction();
        ~CFuzzyFunction();

        void setInterval(double l, double r);

        void setMiddle( double dL=0, double dR=0);

        void setType(char c);

        void setName(const char* s);

        bool isDotInInterval(double t);

        char getType(void)const;

        void getName()const;

        double getValue(double t);
};

class CTriangle : public CFuzzyFunction{

    private:
        double dMiddle;

    public:
        CTriangle();
        ~CTriangle();
        void setMiddle(double dL, double dR);
        double getValue(double t);
};

class CTrapezoid : public CFuzzyFunction{

    private:
        double dLeftMiddle;
        double dRightMiddle;

    public:
        CTrapezoid();
        ~CTrapezoid();
        void setMiddle(double dL, double dR);
        double getValue(double t);
};

#endif // CFUZZYFUNCTION_H
