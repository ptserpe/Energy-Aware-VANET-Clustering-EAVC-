#include "CFuzzyFunction.h"
#include <iostream>
#include <cmath>
#include <cstring>


using namespace std;

CFuzzyFunction::CFuzzyFunction(){}

CFuzzyFunction::~CFuzzyFunction(){
    delete [] sName;
    sName=NULL;
}

void CFuzzyFunction::setInterval(double l,double r){
    dLeft=l;
    dRight=r;
}

void CFuzzyFunction::setMiddle( double dL,double dR){
    dL=0;
    dR=0;
}


void CFuzzyFunction::setType(char c){
    cType=c;
}

void CFuzzyFunction::setName(const char* s){
	  sName = new char[strlen(s)+1];
	  strcpy(sName,s);
}

bool CFuzzyFunction::isDotInInterval(double t){

    if((t>=dLeft)&&(t<=dRight)) return true;
    else return false;
}

char CFuzzyFunction::getType(void)const{
    return cType;
}

void CFuzzyFunction::getName() const{
    cout<<sName<<endl;
}

double CFuzzyFunction::getValue(double t){
    t = 0;
}

//CTriangle
CTriangle::CTriangle(){}

CTriangle::~CTriangle(){
    delete [] sName;
    sName=NULL;
}

void CTriangle::setMiddle(double dL, double dR){
    dMiddle=dL;
}

double CTriangle::getValue(double t){
    if(t<=dLeft)
        return 0;
    else if(t<dMiddle)
        return ((t-dLeft)/(dMiddle-dLeft));
    else if(t==dMiddle)
        return 1.0;
    else if(t<dRight)
        return ((dRight-t)/(dRight-dMiddle));
    else
        return 0;
}

CTrapezoid::CTrapezoid(){}

CTrapezoid::~CTrapezoid(){
    delete [] sName;
    sName=NULL;
}

void CTrapezoid::setMiddle(double dL, double dR){
    dLeftMiddle=dL;
    dRightMiddle=dR;
}

double CTrapezoid::getValue(double t){
    if(t<=dLeft)
        return 0;
    else if(t<dLeftMiddle)
        return ((t-dLeft)/(dLeftMiddle-dLeft));
    else if(t<=dRightMiddle)
        return 1.0;
    else if(t<dRight)
        return ((dRight-t)/(dRight-dRightMiddle));
    else
        return 0;

}

