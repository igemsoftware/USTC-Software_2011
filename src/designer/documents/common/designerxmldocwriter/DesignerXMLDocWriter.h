#ifndef DESIGNERXMLDOCWRITER_H
#define DESIGNERXMLDOCWRITER_H

#include <QtXml>
#include <QtScript>
#include <QMap>
#include "interfaces/DesignerModelItf.h"
#include "DesignerDebug.h"

class DesignerXMLDocWriter
{
public:
    DesignerXMLDocWriter(QString prototype_file_nae);
    QDomDocument *write( DesignerModelItf *model);

private:
    enum M

    QMap<QString,QString> path_map;
    bool disabled;
};

#endif // DESIGNERXMLDOCWRITER_H
