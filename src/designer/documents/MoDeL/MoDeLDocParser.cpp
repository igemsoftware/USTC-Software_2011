#include <QtXml>
#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "MoDeLDocParser.h"

MoDeLDocParser::MoDeLDocParser()
{
}

bool MoDeLDocParser::parse(DesignerModelItf& modelItf, QTextStream& fin )
{
    ReactionNetworkModel& model = dynamic_cast<ReactionNetworkModel&>(modelItf);
    DesignerModelFormatProxyItf* importProxy = model.createImportProxy("ReactionNetworkMoDeLImportProxy");

    if(!importProxy) return false;

    QMap<QString, QPair<int,QString> > section;

    section["<ModelName>"]  = qMakePair(0,QString(""));
    section["<Parameter>"]  = qMakePair(0,QString(""));
    section["<Function>"]   = qMakePair(0,QString(""));
    section["<Rule>"]       = qMakePair(0,QString(""));
    section["<Event>"]      = qMakePair(0,QString(""));
    section["<Compartment>"]= qMakePair(0,QString(""));
    section["<SeedSpecies>"]= qMakePair(0,QString(""));

    while (!fin.atEnd()) {
        QString line = fin.readLine();

        if( section.contains(line) )
        {
            section[line].first++;
        }else
        {
            foreach( QString key , section.keys() )
            {
                if( section[key].first == 1 ) section[key].second += line;
            }
        }

    }
    foreach( QString key , section.keys() )
    {
        if( section[key].first !=0 && section[key].first != 2 ) return false;
        section[key].second = section[key].second.simplified().remove(" ");
    }

    //model name
    if( section["<ModelName>"].first == 0 ) return false;
    importProxy->setModelObjectProperty(0,"ModelName",section["<ModelName>"].second);

    //parameter
    if( section["<Parameter>"].first == 0 ) return false;
    QMap<QString,double> parameterMap;
    foreach( QString line , section["<Parameter>"].second.split(",") )
    {
        rx.setPattern("^(\\w+)\\((.*)\\)$");
        if( rx.indexIn(line) > -1 )
        {
            parameterMap.insert( rx.cap(1) , rx.cap(2).toDouble() );
        }else{
            return false;
        }
    }

    //compartment
    QMap<QString,QScriptValue> compartmentMap;
    foreach( QString line , section["<Compartment>"].second.split(",") )
    {
        ReactionNetworkDataTypes::Compartment compStruct;
        QScriptValue compValue = compStruct.fromScriptValue(engine,compStruct);
        rx.setPattern("^(\\w+)\\((.*)\\)$");
        if( rx.indexIn(line) > -1 )
        {
            compValue.setProperty( "name" , rx.cap(1) );
            compValue.setProperty( "size" , QScriptValue(rx.cap(2).toDouble()) );
            compartmentMap.insert( rx.cap(1) , compValue );
        }else{
            return false;
        }
    }

    //event
    QList< QPair<QString,QString> > eventList;
    foreach( QString line , section["<Event>"].second.split(",") )
    {
        rx.setPattern("^(.*)WHEN(.*)$");
        if( rx.indexIn(line) > -1 )
        {
            eventList.push_back( qMakePair( rx.cap(1) , rx.cap(2) ) );
        }else{
            return false;
        }
    }

    //seed Species
    rx.setPattern("^(\\w+)\\{(.*)\\}$");
    if( rx.indexIn( section["<SeedSpecies>"].second ) <= -1 || !compartmentMap.contains(rx.cap(1)) )
    {
        return false;
    }
    QScriptValue flask = compartmentMap[rx.cap(1)];
    foreach( QString line , rx.cap(2).split("&&") )
    {
        rx.setPattern("^(\\w+)\\{(.*)\\}(\\w+)$");
        if( rx.indexIn(line) > -1 )
        {

        }else{
            if( rx.indexIn("(\\w+)\\((.*)\\)(.+)") > -1 )
            {
            }
        }
    }

    return true;
}
