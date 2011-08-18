#ifndef BEHAVIORVIEWINTERP_H
#define BEHAVIORVIEWINTERP_H
#include <QtCore>

class BehaviorViewInterp
{
public:
   QVector<double> *x,*y,*h,*c,*a,*fxym;
   BehaviorViewInterp(QVector<double> *x,QVector<double> *y,double d1,double dn,int t);
   double f(int x1,int x2,int x3);
   void cal_m(int n);
   double value(double x,int i);
};

#endif // BEHAVIORVIEWINTERP_H
