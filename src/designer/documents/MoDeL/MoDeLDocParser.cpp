#include <QRegExp>
#include <QString>
#include <QStringList>
#include "models/common/ModelSymbol.h"
#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "models/reactionnetworkmodel/ReactionNetworkDataTypes.h"
#include "MoDeLDocParser.h"

using namespace ReactionNetworkDataTypes;

MoDeLDocParser::MoDeLDocParser()
{
}

bool MoDeLDocParser::parse(DesignerModelItf& modelItf, QTextStream& fin )
{
    ReactionNetworkModel& model = dynamic_cast<ReactionNetworkModel&>(modelItf);
    QScriptEngine * engine = model.getEngine();
    QRegExp rx;
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
        rx.setPattern("^(\\w+)\\((.*)\\)$");
        if( rx.indexIn(line) > -1 )
        {
            QScriptValue compValue = engine->newObject();
            compValue.setProperty( "*type*" , "compartment" );
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
    QScriptValue flask = copyFromScriptValue(engine,compartmentMap[rx.cap(1)]);
    QScriptValueList flaskSub;
    QMap<QString,int> compartmentCnt;
    foreach( QString key , compartmentMap.keys() ) compartmentCnt.insert( key , 0 );

    foreach( QString line , rx.cap(2).split("&&") )
    {
        rx.setPattern("^(\\w+)\\{(.*)\\}(\\w+)$");
        if( rx.indexIn(line) > -1 )
        {
            if( compartmentMap.contains( rx.cap(1) ) )
            {
                QScriptValue compValue = copyFromScriptValue( engine , compartmentMap[rx.cap(1)] );
                compartmentCnt[rx.cap(1)]++;
                compValue.setProperty( "name" , rx.cap(1) + ((compartmentCnt[rx.cap(1)])>1?QString("_%1").arg(compartmentCnt[rx.cap(1)]):"") );
                compValue.setProperty( "initialAmount" , QScriptValue( parameterMap[rx.cap(3)] ) );

                foreach( QString plasmid , rx.cap(2).split(";") )
                {

                }


                flaskSub.push_back(compValue);
            }else{
                return false;
            }
        }else if( rx.setPattern("(\\w+)\\((.*)\\)(.+)"),rx.indexIn(line) > -1 )
        {

        }else
        {
            return false;
        }
    }
    flask.setProperty( "contains" , convertModelTypeToScriptValue(engine,flaskSub) );
    return true;
}
