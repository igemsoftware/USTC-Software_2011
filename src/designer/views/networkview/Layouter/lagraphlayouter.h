#ifndef LAGRAPHLAYOUTER_H
#define LAGRAPHLAYOUTER_H

#include <vector>
#include <algorithm>
#include <utility>
#include <QThread>
#include <QObject>
#include <math.h>
using namespace std;

#define Fa(x) ((x)*(x)/k)
#define Fr(x) (k*k/(x))

class LaGraphLayouterThread;

class LaGraphLayouter : public QObject
{
    Q_OBJECT

    int nNode;
    int nEdge;

    int wFrame;
    int hFrame;

    volatile bool running;
    volatile bool stop;
    LaGraphLayouterThread * thread;

    double iteration;

    vector< pair<double,double> > disp;
    vector< pair<int,int> > edgeList;
    vector< pair<double,double> > posOut;
    vector< pair<double,double> > pos;

    void work();

public:
    LaGraphLayouter( int maxwFrame , int maxhFrame , int maxnNode = 0 , int maxnEdge = 0 );
    virtual ~LaGraphLayouter();

    bool start();
    bool terminate();
    bool reserve( int maxnNode , int maxnEdge );
    bool addNode( int n );
    bool addEdge( int u , int v );
    pair<double,double> getPos( int u );

    friend class LaGraphLayouterThread;

signals:
    void finish();
};

#endif // LAGRAPHLAYOUTER_H
