#include <QtMmlWidget>
#include "ODEView.h"

ODEView::ODEView(DesignerMainWnd *mainWnd) :
    DesignerViewItf(mainWnd)
{
    QtMmlWidget* widget = new QtMmlWidget(this);
    widget->resize(this->size());
    widget->setContent("      <math xmlns=\"http://www.w3.org/1998/Math/MathML\">        <mrow>          <mi>x</mi>          <mo>=</mo>          <mfrac>            <mrow>              <mo form=\"prefix\">&#x2212;<!-- &minus; --></mo>              <mi>b</mi>              <mo>&#x00B1;<!-- &PlusMinus; --></mo>              <msqrt>                <msup>                  <mi>b</mi>                  <mn>2</mn>                </msup>                <mo>&#x2212;<!-- &minus; --></mo>                <mn>4</mn>                <mo>&#x2062;<!-- &InvisibleTimes; --></mo>                <mi>a</mi>                <mo>&#x2062;<!-- &InvisibleTimes; --></mo>                <mi>c</mi>              </msqrt>            </mrow>            <mrow>              <mn>2</mn>              <mo>&#x2062;<!-- &InvisibleTimes; --></mo>              <mi>a</mi>            </mrow>          </mfrac>        </mrow>      </math>");
    widget->show();
}
