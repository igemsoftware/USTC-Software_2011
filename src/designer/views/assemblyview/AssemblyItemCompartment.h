#ifndef ASSEMBLYITEMCOMPARTMENT_H
#define ASSEMBLYITEMCOMPARTMENT_H

#include <QString>
#include <QGraphicsEllipseItem>

#include <views/assemblyview/AssemblyLib.h>
#include <views/assemblyview/AssemblyItemPlasmid.h>


class AssemblyItemCompartment : public QGraphicsEllipseItem
{
public:
    explicit AssemblyItemCompartment( QString  setName , QGraphicsItem *parent = 0 );
    void addPlasmid( QPointF pos , AssemblyItemPlasmid * plasmid );

    QString name;

    enum{
        DefaultHeight = 200 ,
        DefaultWeight = 400
    };

    static const char * MimeFormat;

protected:

private:
    QMap<QString,AssemblyItemPlasmid*> plasmidMap;
};


#endif // ASSEMBLYITEMCOMPARTMENT_H
