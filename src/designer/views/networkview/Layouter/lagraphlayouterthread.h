#ifndef LAGRAPHLAYOUTERTHREAD_H
#define LAGRAPHLAYOUTERTHREAD_H

#include "lagraphlayouter.h"

class LaGraphLayouterThread : public QThread
{
    LaGraphLayouter * laGL;
public:
    LaGraphLayouterThread( LaGraphLayouter * inLaGL ) : QThread() , laGL(inLaGL) {}
    void run();
};

#endif // LAGRAPHLAYOUTERTHREAD_H
