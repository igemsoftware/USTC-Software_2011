#include <QtMmlWidget>
#include "ODEView.h"

ODEView::ODEView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model)
{
    mmlWidget = new QtMmlWidget(this);
    mmlWidget->show();
    textWidget = new QTextEdit(this);
    textWidget->show();
    mmlWidget->setContent("      <math xmlns=\"http://www.w3.org/1998/Math/MathML\">        <mrow>          <mi>x</mi>          <mo>=</mo>          <mfrac>            <mrow>              <mo form=\"prefix\">&#x2212;<!-- &minus; --></mo>              <mi>b</mi>              <mo>&#x00B1;<!-- &PlusMinus; --></mo>              <msqrt>                <msup>                  <mi>b</mi>                  <mn>2</mn>                </msup>                <mo>&#x2212;<!-- &minus; --></mo>                <mn>4</mn>                <mo>&#x2062;<!-- &InvisibleTimes; --></mo>                <mi>a</mi>                <mo>&#x2062;<!-- &InvisibleTimes; --></mo>                <mi>c</mi>              </msqrt>            </mrow>            <mrow>              <mn>2</mn>              <mo>&#x2062;<!-- &InvisibleTimes; --></mo>              <mi>a</mi>            </mrow>          </mfrac>        </mrow>      </math>");
    connect(textWidget, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void ODEView::resizeEvent ( QResizeEvent * event )
{
    mmlWidget->move(0, 0);
    mmlWidget->resize(event->size().width()/2, event->size().height());
    textWidget->move(event->size().width()/2, 0);
    textWidget->resize(event->size().width()/2, event->size().height());
}

void ODEView::textChanged()
{
    mmlWidget->setContent(textWidget->toPlainText());
}
