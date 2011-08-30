#include <cmath>
#include "NetworkViewGraphicsSceneEdge.h"
#include "NetworkViewGraphicsSceneNode.h"
#include "NetworkViewGraphicsSceneLabel.h"

const qreal NetworkViewGraphicsSceneEdge::arrowLength = 12.0;
const qreal NetworkViewGraphicsSceneEdge::arrowAngle  = 0.15;

NetworkViewGraphicsSceneEdge::NetworkViewGraphicsSceneEdge(QGraphicsItem *parent,
                                                           NetworkViewGraphicsSceneNode* node1,
                                                           NetworkViewGraphicsSceneNode* node2,
                                                            EdgeType type)
    : QGraphicsLineItem(parent),
      edgeNode1 (node1), edgeNode2 (node2), edgeType (type)
{
    setFlags( QGraphicsItem::ItemIsFocusable );

    if(edgeNode1)
    {
        edgeNode1->registerEdge(this);
    }
    if(edgeNode2)
    {
        edgeNode2->registerEdge(this);
    }
    for(size_t i = 0; i < 4; i++)
        arrowLines[i].setParentItem(this);
    updatePos();

    labelObject = new NetworkViewGraphicsSceneLabel(this, "");
}


void NetworkViewGraphicsSceneEdge::updatePos(void)
{
    if(edgeNode1&&edgeNode2)
    {
        qreal r  = NetworkViewGraphicsSceneNode::radius;
        qreal r2 = NetworkViewGraphicsSceneEdge::arrowLength;
        qreal a2 = NetworkViewGraphicsSceneEdge::arrowAngle;

        qreal x1 = edgeNode1->scenePos().x(), x2 = edgeNode2->scenePos().x();
        qreal y1 = edgeNode1->scenePos().y(), y2 = edgeNode2->scenePos().y();
        qreal a = atan2( y2-y1, x2-x1 );
        qreal sv  = sin(a), cv = cos(a);
        qreal sv2a = sin(a+a2), cv2a = cos(a+a2);
        qreal sv2b = sin(a-a2), cv2b = cos(a-a2);

        setLine(x1 + cv*r+24, y1 + sv*r+24, x2 - cv*r+24, y2 - sv*r+24);

        if(edgeType==BidirectedEdge)
        {
            arrowLines[0].setLine(x1 + cv*r+24, y1 + sv*r+24,  x1 + cv*r + r2*cv2a+24, y1 + sv*r + r2*sv2a+24);
            arrowLines[1].setLine(x1 + cv*r+24, y1 + sv*r+24,  x1 + cv*r + r2*cv2b+24, y1 + sv*r + r2*sv2b+24);
        }
        else
        {
            arrowLines[0].setLine(x1 + cv*r+24, y1 + sv*r+24,  x1 + cv*r+24, y1 + sv*r+24);
            arrowLines[1].setLine(x1 + cv*r+24, y1 + sv*r+24,  x1 + cv*r+24, y1 + sv*r+24);
        }
        if(edgeType==BidirectedEdge||edgeType==DirectedEdge)
        {
            arrowLines[2].setLine(x2 - cv*r+24, y2 - sv*r+24,  x2 - cv*r - r2*cv2a+24, y2 - sv*r - r2*sv2a+24);
            arrowLines[3].setLine(x2 - cv*r+24, y2 - sv*r+24,  x2 - cv*r - r2*cv2b+24, y2 - sv*r - r2*sv2b+24);
        }
        else
        {
            arrowLines[2].setLine(x2 - cv*r+24, y2 - sv*r+24,  x2 - cv*r+24, y2 - sv*r+24);
            arrowLines[3].setLine(x2 - cv*r+24, y2 - sv*r+24,  x2 - cv*r+24, y2 - sv*r+24);
        }
    }
}
