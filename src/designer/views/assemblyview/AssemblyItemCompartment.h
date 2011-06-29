#ifndef ASSEMBLYITEMCOMPARTMENT_H
#define ASSEMBLYITEMCOMPARTMENT_H

#include <QString>
#include <QGraphicsEllipseItem>

#include <views/assemblyview/AssemblyLib.h>
#include <views/assemblyview/AssemblyItemPlasmid.h>
#include "AssemblyItemSizer.h"

class AssemblyItemCompartment : public QGraphicsEllipseItem
{
public:
    explicit AssemblyItemCompartment( QString  setName , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemCompartment();
    void addPlasmid( QPointF pos , AssemblyItemPlasmid * plasmid );
    void removePlasmid( AssemblyItemPlasmid * plasmid );
    void loseSelection();
    void getSelection();
    void resize( qreal newWidth , qreal newHeight );
    QString name;

    enum{
        DefaultHeight = 200 ,
        DefaultWidth = 400
    };

    static const char * MimeFormat;

protected:

private:
    QMap<QString,AssemblyItemPlasmid*> plasmidMap;
    QGraphicsTextItem * displayName;
    AssemblyItemSizer * sizer;
};


#endif // ASSEMBLYITEMCOMPARTMENT_H
