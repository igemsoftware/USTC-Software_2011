#include "DesignerXMLDocWriter.h"

DesignerXMLDocWriter::DesignerXMLDocWriter(QString prototype_file_name)
{
    disabled = false;

    QFile prototype_file(prototype_file_name);
    if( !prototype_file.open(QIODevice::ReadOnly) )
    {
        disabled = true;
        return;
    }

    QTextStream prototype_stream(prototype_file);
    while( !prototype_stream.atEnd() )
    {
        QString line = prototype_stream.readLine();
        QString xml = line.split("=>").at(0).simplified();
        QString model = line.split("=>").at(0).simplified();

    }
}
