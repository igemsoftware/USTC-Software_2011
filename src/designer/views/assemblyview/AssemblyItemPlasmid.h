#ifndef ASSEMBLYITEMPLASMID_H
#define ASSEMBLYITEMPLASMID_H

#include <QGraphicsRectItem>
#include <QString>
#include <QList>

#include <views/assemblyview/AssemblyLib.h>
#include <views/assemblyview/AssemblyItemBrick.h>

class AssemblyItemPlasmid : public QGraphicsRectItem
{
public:
    explicit AssemblyItemPlasmid( QString & setName , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemPlasmid();

    void addBrick( QPointF eventPos , AssemblyItemBrick * brick  );
    void removeBrick( AssemblyItemBrick * brick );
    void arrangeBricks();

    QString name;

    enum{
        DefaultHeight = 5 ,
        DefaultWidth = ASSEMBLY_ITEM_BRICK_WIDTH
    };

    static const char * MimeFormat;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<AssemblyItemBrick*> bricks;
    QGraphicsTextItem * displayName;
};

#endif // ASSEMBLYITEMPLASMID_H
