#include <QtGui>
#include <QXmlStreamWriter>
#include "SBMLEditorView.h"

SBMLEditorView::SBMLEditorView(DesignerMainWnd* mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model)
{
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    QTextEdit* SBMLTextEdit = new QTextEdit(this);
    SBMLTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    SBMLTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    gridLayout->addWidget(SBMLTextEdit, 0, 0, 1, 1);

    sbmlHighlighter = new SBMLEditorViewHighlighter(SBMLTextEdit->document());


}
