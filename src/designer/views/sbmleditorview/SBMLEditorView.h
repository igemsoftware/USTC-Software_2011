#ifndef SBMLEDITORVIEW_H
#define SBMLEDITORVIEW_H

#include "interfaces/DesignerViewItf.h"
#include "SBMLEditorViewHighlighter.h"

class SBMLEditorView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SBMLEditorView(DesignerMainWnd *mainWnd);

private:
    SBMLEditorViewHighlighter *sbmlHighlighter;

signals:

public slots:

};

#endif // SBMLEDITORVIEW_H
