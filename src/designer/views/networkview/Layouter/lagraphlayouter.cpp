#include "lagraphlayouter.h"
#include "lagraphlayouterthread.h"

void LaGraphLayouter::work()
{
    running = true;
    double area = wFrame*hFrame;
    double k = sqrt( area/nNode );
    double t = (double)(wFrame+hFrame)/40;

    for( int iter = 0 ; iter < iteration && !stop ; iter++ )
    {
        for( int v = 1 ; v <= nNode ; v++ )
        {
            disp[v].first = disp[v].second = 0;
            for( int u = 1 ; u <= nNode ; u++ )
            {
                if( u == v ) continue;
                double dx = pos[v].first - pos[u].first;
                double dy = pos[v].second - pos[u].second;
                if( dx == 0 || dy == 0 ) dx = 0.1;
                double r = sqrt( dx*dx+dy*dy );
                disp[v].first += dx/r*Fr(r);
                disp[v].second += dy/r*Fr(r);
            }
        }
        for( int e = 1 ; e <= nEdge ; e++ )
        {
            double dx = pos[edgeList[e].first].first - pos[edgeList[e].second].first;
            double dy = pos[edgeList[e].first].second - pos[edgeList[e].second].second;
            if( dx == 0 && dy == 0 ) dx = 0.1;
            double r = sqrt( dx*dx + dy*dy );
            disp[edgeList[e].first].first -= dx/r*Fa(r);
            disp[edgeList[e].first].second -= dy/r*Fa(r);
            disp[edgeList[e].second].first += dx/r*Fa(r);
            disp[edgeList[e].second].second += dy/r*Fa(r);
        }

        for( int v = 1 ; v <= nNode ; v++ )
        {
            double r = sqrt( disp[v].first*disp[v].first + disp[v].second*disp[v].second );
            pos[v].first += disp[v].first/r*min( r , t );
            pos[v].second += disp[v].second/r*min( r , t );
            pos[v].first = min( (double)wFrame , max( 0.0 , pos[v].first ) );
            pos[v].second = min( (double)hFrame , max( 0.0 , pos[v].second ) );
        }
        posOut.assign( pos.begin() , pos.end() );
        //t = cool(t);
    }
    stop = false;
    running = false;
    emit finish();
}

bool LaGraphLayouter::start()
{
    if( running ) return false;
    thread->start();
    return true;
}

bool LaGraphLayouter::terminate()
{
    stop = true;
}

LaGraphLayouter::LaGraphLayouter( int maxwFrame , int maxhFrame , int maxnNode , int maxnEdge ) : QObject()
{
    nNode = 0;
    nEdge = 0;
    running = false;
    stop = false;
    wFrame = maxwFrame;
    hFrame = maxhFrame;
    iteration = 100;
    thread = new LaGraphLayouterThread( this );

    edgeList.reserve( maxnEdge );
    pos.reserve( maxnNode );
    disp.reserve( maxnNode );
    posOut.reserve( maxnNode );
}

LaGraphLayouter::~LaGraphLayouter()
{
    delete thread;
}

bool LaGraphLayouter::reserve( int maxnNode , int maxnEdge )
{
    if( running ) return false;

    edgeList.reserve( maxnEdge );
    pos.reserve( maxnNode );
    disp.reserve( maxnNode );
    posOut.reserve( maxnNode );
    return true;
}

bool LaGraphLayouter::addNode( int n )
{
    if( running ) return false;
    for( int i = nNode+1 ; i <= nNode + n ; i++ )
    {
        pos.push_back( make_pair( (double)(rand()%wFrame) , (double)(rand()%hFrame) ) );
        posOut.push_back( *(--pos.end()) );
        disp.push_back( make_pair( (double)0 , (double)0 ) );
    }
    nNode += n;
    return true;
}

bool LaGraphLayouter::addEdge( int u , int v )
{
    if( running ) return false;
    edgeList.push_back( make_pair(u,v) );
    nEdge++;
    return true;
}

pair<double,double> LaGraphLayouter::getPos( int u )
{
    if( u > nNode || u < 1 ) return make_pair(-1,-1);
    return posOut[u];
}
