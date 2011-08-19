#include "BehaviorViewInterp.h"

BehaviorViewInterp::BehaviorViewInterp(QVector<double> *x, QVector<double> *y, double d0, double dn,int t)
{
    this->x=x;this->y=y;
    int n=x->size()-1;
    h=new QVector<double>();h->resize(n+1);
    c=new QVector<double>();c->resize(n+1);
    a=new QVector<double>();a->resize(n+1);
    fxym=new QVector<double>();fxym->resize(x->size());
    for(int i=0;i<n;i++)
        h->replace(i,x->at(i+1)-x->at(i));
    switch(t){
        case 1:
            {
                c->replace(0,1);a->replace(n,1);
                fxym->replace(0,6*((y->at(1)-y->at(0))/(x->at(1)-x->at(0))-d0)/h->at(0));
                fxym->replace(n,6*(dn-(y->at(n)-y->at(n-1))/(x->at(n)-x->at(n-1)))/h->at(n-1));
                break;
            }
        case 2:
            {
                c->replace(0,0);a->replace(n,0);
                fxym->replace(0,2*d0); fxym->replace(n,2*dn);
                break;
            }
        }
    for(int i=1;i<n;i++)
        fxym->replace(i,6*f(i-1,i,i+1));
    for(int i=1;i<n;i++)
    {
        a->replace(i-1,h->at(i-1)/(h->at(i-1)+h->at(i-1)));
        c->replace(i-1,1-a->at(i-1));
    }
    a->replace(n,h->at(n-1)/(h->at(n-1)+h->at(n)));
    this->cal_m(n);
}

void BehaviorViewInterp::cal_m(int n)
{
    QVector<double> *B=new QVector<double>();
    B->append(c->at(0)/2);
    for(int i = 1; i <n; i++)
        B->append(c->at(i)/(2-a->at(i)*B->at(i-1)));
    fxym->replace(0,fxym->at(0)/2);
    for(int i = 1; i <x->size(); i++)
            fxym->replace(i,(fxym->at(i) - a->at(i)*fxym->at(i-1)) / (2 - a->at(i)*B->at(i-1)));
        for(int i=n-1; i>=0; i--)
            fxym->replace(i, fxym->at(i) - B->at(i)*fxym->at(i+1));
}

double BehaviorViewInterp::f(int x1, int x2, int x3)
{
    double a=(y->at(x3)-y->at(x2))/(x->at(x3)-x->at(x2));
    double b=(y->at(x2)-y->at(x1))/(x->at(x2)-x->at(x1));
    return (a-b)/(x->at(x3)-x->at(x1));
}

double BehaviorViewInterp::value(double X,int i)
{
    double t = fxym->at(i)/(6*h->at(i));
    double answer=0;
    answer+=t*pow((x->at(i+1)-X),3);
    t = fxym->at(i+1)/(6*h->at(i));
    answer+=t*pow((X-x->at(i)),3);
    t = (y->at(i) - fxym->at(i)*h->at(i)*h->at(i)/6)/h->at(i);
    answer+=t*(x->at(i+1)-X);
    t = (y->at(i+1)-fxym->at(i+1)*h->at(i)*h->at(i)/6)/h->at(i);
    answer+=t*(X-x->at(i));
    return answer;
}
