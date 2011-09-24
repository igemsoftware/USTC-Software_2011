#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "models/common/ModelSymbol.h"
#include "models/igamemodel/IGame.h"
#include "MoDeLDocParser.h"
#include "DesignerDebug.h"


MoDeLDocParser::MoDeLDocParser()
{
}

bool MoDeLDocParser::parse(DesignerModelComponent& modelItf, QTextStream& fin )
{
    IGameModel& model = dynamic_cast<IGameModel&>(modelItf);
    QScriptEngine * engine = model.getEngine();
    QScriptValue root = engine->newObject();
    engine->globalObject().setProperty("model",root);
    QRegExp rx;

    QSqlDatabase db = QSqlDatabase::database("igame");
    QSqlQuery query(db);

    QList<QString> strListParameters;
    QList<QString> strListEvents;
    QList<QString> strListCompartments;
    QList<QString> strListSeedSpecies;

    QString rootCompartmentId;

    QSet<QString> idSpace;
    QSet<QString> paramSpace;
    QMap<QString,QScriptValue> compartmentMap;

    QScriptValueList paramList;
    QScriptValueList eventList;

    QString tmpLine = fin.readLine();
    rx.setPattern("#.*$");
    while (!fin.atEnd()) {
        tmpLine.remove(rx);
        if( tmpLine == "<parameters>" )
        {
            while( ( tmpLine = fin.readLine().remove(rx) ) != "</parameters>" )
            {
                if( fin.atEnd() )
                {
                    QMessageBox::critical( 0 , "Syntex Error!" , "Ending mark </parameters> is not presented!" );
                    return false;
                }
                if( !tmpLine.simplified().remove(" ").isEmpty() ) strListParameters.push_back(tmpLine);
            }
        }else if( tmpLine == "<events>" )
        {
            while( ( tmpLine = fin.readLine().remove(rx) ) != "</events>" )
            {
                if( fin.atEnd() )
                {
                    QMessageBox::critical( 0 , "Syntex Error!" , "Ending mark </events> is not presented!" );
                    return false;
                }
                if( !tmpLine.simplified().remove(" ").isEmpty() ) strListEvents.push_back(tmpLine);
            }
        }else if( tmpLine.startsWith("<compartments>") )
        {
            while( ( tmpLine = fin.readLine().remove(rx) ) != "</compartments>" )
            {
                if( fin.atEnd() )
                {
                    QMessageBox::critical( 0 , "Syntex Error!" , "Ending mark </compartments> is not presented!" );
                    return false;
                }
                if( !tmpLine.simplified().remove(" ").isEmpty() ) strListCompartments.push_back(tmpLine);
            }
        }else if( tmpLine.startsWith("<seedspecies>") )
        {
            while( ( tmpLine = fin.readLine().remove(rx) ) != "</seedspecies>" )
            {
                if( fin.atEnd() )
                {
                    QMessageBox::critical( 0 , "Syntex Error!" , "Ending mark </seedspecies> is not presented!" );
                    return false;
                }
                if( !tmpLine.simplified().remove(" ").isEmpty() ) strListSeedSpecies.push_back(tmpLine);
            }
        }
        tmpLine = fin.readLine();
    }

    rx.setPattern("(\\w+)\\s+(.*)");
    foreach( QString strParam , strListParameters )
    {
        if( rx.indexIn(strParam.simplified()) > -1 )
        {
            QScriptValue tmpParam = engine->newObject();
            tmpParam.setProperty("id", QScriptValue( rx.cap(1) ) );
            tmpParam.setProperty("value" , QScriptValue( rx.cap(2) ) );
            paramList.push_back(tmpParam);
            //add id collision detection later
            idSpace.insert( rx.cap(1) );
            paramSpace.insert( rx.cap(1) );
        }
    }
    root.setProperty( "parameters" , convertModelTypeToScriptValue( engine , paramList ) );

    foreach( QString strCompartment , strListCompartments )
    {
        QList<QString> list = strCompartment.simplified().split(" ");
        if( list.size() < 3 )
        {
            QMessageBox::critical( 0 , "Syntex Error!" , QString("(%1) is not a valid compartment definition").arg(strCompartment) );
            return false;
        }
        QScriptValue compartment = engine->newObject();

        compartment.setProperty("id", list[0]);
        compartment.setProperty("*temp_parent*", list[1]);
        compartment.setProperty("type", list[2]);
        if( list.size() >= 4 )
        {
            if( !paramSpace.contains(list[3]) )
            {
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Parameter (%1) is not defined").arg(list[3]) );
                return false;
            }
            compartment.setProperty("volume", list[3]);
        }
        if( list.size() >= 5 )
        {
            if( !paramSpace.contains(list[4]) )
            {
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Parameter (%1) is not defined").arg(list[4]) );
                return false;
            }
            compartment.setProperty("population", list[4]);
        }
        idSpace.insert(list[0]);
        compartmentMap.insert(list[0], compartment);
    }

    foreach( QString key, compartmentMap.keys() )
    {
        QScriptValue compartment = compartmentMap[key];
        if( compartment.property("*temp_parent*").toString() == "ROOT" )
        {
            rootCompartmentId = key;
        }
    }
    root.setProperty("rootCompartment", convertModelTypeToScriptValue(engine, compartmentMap[rootCompartmentId]));

    QScriptValueList compartmentList;
    foreach( QScriptValue compartment, compartmentMap.values() )
    {
        if( compartment.property("*temp_parent*").toString() == "ROOT" )
        {
            compartment.setProperty("*temp_parent*", QScriptValue() );
            continue;
        }
        if( compartment.property("*temp_parent*").toString() != rootCompartmentId )
        {
            QMessageBox::critical( 0 , "Syntex Error!" , QString("Tree structure of compartments with depth greater than 2 is not allowed") );
            return false;
        }
        compartment.setProperty("*temp_parent*", QScriptValue() );
        compartmentList.append(compartment);
    }
    root.setProperty("childCompartments", convertModelTypeToScriptValue(engine, compartmentList));

    foreach( QString strSpecies, strListSeedSpecies )
    {
        QList<QString> list = strSpecies.simplified().split(" ");
        if( list.size() < 4 )
        {
            QMessageBox::critical( 0 , "Syntex Error!" , QString("(%1) is not a valid seed species definition!").arg(strSpecies) );
            return false;
        }
        if( compartmentMap.find(list[0]) == compartmentMap.end() )
        {
            QMessageBox::critical( 0 , "Syntex Error!" , QString("compartment (%1) required by species (%2) is not defined").arg(list[0]).arg(list[1]) );
            return false;
        }
        rx.setPattern("^\\w+$");
        if( rx.indexIn(list[1]) == -1 )
        {
            QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid species id!") + list[1] );
            return false;
        }

        QScriptValue species = engine->newObject();
        species.setProperty("id",list[1]);
        idSpace.insert(list[1]);

        if( list[2].startsWith("d:") )
        {
            species.setProperty("type","plasmid");
            QScriptValueList structure;
            foreach( QString strPart , list[2].mid(2).split("-") )
            {
                rx.setPattern("^(\\w+)(\\'?)\\((.*)\\)$");
                if( rx.indexIn(strPart) > -1 )
                {
                    QScriptValue part = engine->newObject();
                    part.setProperty( "type" , "dna" );
                    query.exec( QString("SELECT type FROM agents WHERE id = \'%1\'").arg(rx.cap(1)) );
                    if( query.numRowsAffected() < 1 || (query.next(),query.value(0).toString().isEmpty() ) )
                    {
                        part.setProperty( "category" , "other" );
                    }else{
                        part.setProperty( "category" , query.value(0).toString() );
                    }
                    part.setProperty( "agent", QScriptValue( rx.cap(1) ) );
                    part.setProperty( "reversed" , QScriptValue( !rx.cap(2).isEmpty() ) );
                    part.setProperty( "sites" , QScriptValue( rx.cap(3) ) );
                    structure.push_back(part);
                }else{
                    QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid agent definition!\n") + strPart );
                    return false;
                }
            }
            species.setProperty( "structure" , convertModelTypeToScriptValue(engine,structure) );
        }else if( list[2].startsWith("p:") )
        {
            species.setProperty("type","protein");
            rx.setPattern("^(\\w+)(\\'?)\\((.*)\\)$");
            if( rx.indexIn(list[2].mid(2)) > -1 )
            {
                species.setProperty( "agent", QScriptValue( rx.cap(1) ) );
                species.setProperty( "reversed" , QScriptValue( !rx.cap(2).isEmpty() ) );
                species.setProperty( "sites" , QScriptValue( rx.cap(3) ) );
            }else{
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid agent definition!\n") + list[2].mid(2) );
                return false;
            }
        }else if( list[2].startsWith("nb:") )
        {
            species.setProperty("type","molecule");
            rx.setPattern("^(\\w+)(\\'?)\\((.*)\\)$");
            if( rx.indexIn(list[2].mid(3)) > -1 )
            {
                species.setProperty( "agent", QScriptValue( rx.cap(1) ) );
                species.setProperty( "reversed" , QScriptValue( !rx.cap(2).isEmpty() ) );
                species.setProperty( "sites" , QScriptValue( rx.cap(3) ) );
            }else{
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid agent definition!") + list[2].mid(2) );
                return false;
            }
        }else
        {
            QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid species structure!") + list[2] );
            return false;
        }

        if( paramSpace.contains( list[3] ) )
        {
            species.setProperty( "initConcentration" , QScriptValue( list[3] ) );
        }else{
            QMessageBox::critical( 0 , "Syntex Error!" , QString("Undefined parameter used: ") + list[3] );
            return false;
        }

        species.setProperty( "constConcentration", QScriptValue(false) );
        if( list.count() == 5 )
        {
            if( list[4] == "const" )
            {
                species.setProperty( "constConcentration", QScriptValue(true) );
            }else{
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Unknow term: ") + list[4] );
                return false;
            }
        }

        QScriptValue compartment = compartmentMap.find(list[0]).value();
        QScriptValueList tmpSpeciesList;
        qScriptValueToSequence(compartment.property("contains"), tmpSpeciesList);
        tmpSpeciesList.append(species);
        compartment.setProperty("contains", convertModelTypeToScriptValue(engine, tmpSpeciesList));
    }

    foreach( QString strEvent , strListEvents )
    {
        QList<QString> tmpList = strEvent.simplified().split(" ");
        if( tmpList.count() == 3 )
        {
            QScriptValue tmpEvent = engine->newObject();
            tmpEvent.setProperty( "id" , QScriptValue( tmpList[0] ) );
            tmpEvent.setProperty( "condition" , QScriptValue( tmpList[1] ) );
            if( tmpList[2].split("=").count()== 2 && paramSpace.contains( tmpList[2].split("=").at(1) ) && idSpace.contains( tmpList[2].split("=").at(0) ) )
            {
                tmpEvent.setProperty( "variable" , QScriptValue( tmpList[2].split("=").at(0) ) );
                tmpEvent.setProperty( "value" , QScriptValue( tmpList[2].split("=").at(1) ) );
                eventList.push_back(tmpEvent);
            }else
            {
                QMessageBox::critical( 0 , "Syntex Error!" , QString("(%1)\n is not a valid event definition!").arg(strEvent) );
                return false;
            }
        }else
        {
            QMessageBox::critical( 0 , "Syntex Error!" , QString("(%1)\n is not a valid event definition!").arg(strEvent) );
            return false;
        }
    }
    root.setProperty( "events" , convertModelTypeToScriptValue( engine , eventList ) );


    return true;
}

