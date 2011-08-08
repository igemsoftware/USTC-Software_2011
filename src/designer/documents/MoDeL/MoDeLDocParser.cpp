#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include "models/common/ModelSymbol.h"
#include "models/igamemodel/IGame.h"
#include "MoDeLDocParser.h"
#include "DesignerDebug.h"


MoDeLDocParser::MoDeLDocParser()
{
}

bool MoDeLDocParser::parse(DesignerModelItf& modelItf, QTextStream& fin )
{
    IGameModel& model = dynamic_cast<IGameModel&>(modelItf);
    QScriptEngine * engine = model.getEngine();
    QScriptValue root = engine->newObject();
    engine->globalObject().setProperty("model",root);
    QRegExp rx;

    QList<QString> strListParameters;
    QList<QString> strListEvents;
    QString strRootCompartment;
    QList<QString> strListCompartments;

    QSet<QString> parameterSet;

    QScriptValue rootCompartment;
    QScriptValueList paramList;
    QScriptValueList eventList;


    QString tmpLine = fin.readLine();
    while (!fin.atEnd()) {
        if( tmpLine == "<Parameters>" )
        {
            while( ( tmpLine = fin.readLine() ) != "<Parameters>" ) if( !tmpLine.startsWith("#") ) strListParameters.push_back(tmpLine);
        }else if( tmpLine == "<Events>" )
        {
            while( ( tmpLine = fin.readLine() ) != "<Events>" ) if( !tmpLine.startsWith("#") ) strListEvents.push_back(tmpLine);
        }else if( tmpLine.startsWith("<RootCompartment") )
        {
            strRootCompartment = tmpLine + '\n';
            while( ( tmpLine = fin.readLine() ) != "<RootCompartment>" )
            {
                if( fin.atEnd() )
                {
                    QMessageBox::critical( 0 , "Syntex Error!" , "Ending mark <RootCompartment> not found!" );
                    return false;
                }
                if( !tmpLine.startsWith("#") ) strRootCompartment += tmpLine + '\n';
            }
        }else if( tmpLine.startsWith("<ChildCompartment") )
        {
            QString tmpString = tmpLine + '\n';
            while( ( tmpLine = fin.readLine() ) != "<ChildCompartment>" )
            {
                if( fin.atEnd() )
                {
                    QMessageBox::critical( 0 , "Syntex Error!" , "Ending mark <ChildCompartment> not found!" );
                    return false;
                }
                if( !tmpLine.startsWith("#") ) tmpString += tmpLine + '\n';
            }
            strListCompartments.push_back(tmpString);
        }
        tmpLine = fin.readLine();
    }

    rx.setPattern("(\\w+)\\s+(.*)");
    foreach( QString strParam , strListParameters )
    {
        if( rx.indexIn(strParam) > -1 )
        {
            QScriptValue tmpParam = engine->newObject();
            tmpParam.setProperty("id", QScriptValue( rx.cap(1) ) );
            tmpParam.setProperty("value" , QScriptValue( rx.cap(2).toDouble() ) );
            paramList.push_back(tmpParam);
            parameterSet.insert( rx.cap(1) );
        }
    }
    root.setProperty( "parameters" , convertModelTypeToScriptValue( engine , paramList ) );

    foreach( QString strEvent , strListEvents )
    {
        QList<QString> tmpList = strEvent.simplified().split(" ");
        if( tmpList.count() == 3 )
        {
            QScriptValue tmpEvent = engine->newObject();
            tmpEvent.setProperty( "id" , QScriptValue( tmpList[0] ) );
            tmpEvent.setProperty( "condition" , QScriptValue( tmpList[1] ) );
            if( tmpList[2].split("=").count()== 2 && parameterSet.contains( tmpList[2].split("=").at(1) ) )
            {
                tmpEvent.setProperty( "variable" , QScriptValue( tmpList[2].split("=").at(0) ) );
                tmpEvent.setProperty( "value" , QScriptValue( tmpList[2].split("=").at(1) ) );
                eventList.push_back(tmpEvent);
            }
        }
    }
    root.setProperty( "events" , convertModelTypeToScriptValue( engine , eventList ) );

    if( !readCompartment( engine , parameterSet , rootCompartment , strRootCompartment , "RootCompartment" ) )
    {
        return false;
    }
    root.setProperty("rootCompartment",rootCompartment);

    QScriptValueList compartmentList;
    foreach( QString strCompartment , strListCompartments )
    {
        QScriptValue compartment;
        if( !readCompartment( engine , parameterSet , compartment , strCompartment , "ChildCompartment" ) )
        {
            return false;
        }
        compartmentList.push_back(compartment);
    }
    root.setProperty("childCompartments", convertModelTypeToScriptValue( engine , compartmentList ) );

    return true;
}

bool MoDeLDocParser::readCompartment( QScriptEngine * engine , QSet<QString> & parameterSet , QScriptValue & compartment , QString & strCompartment, QString tag )
{
    QRegExp rx;
    compartment = engine->newObject();
    QScriptValueList speciesList;
    if( strCompartment.isEmpty() )
    {
        QMessageBox::critical( 0 , "Syntex Error!" , "RootCompartment is not defined!" );
        return false;
    }
    foreach( QString line , strCompartment.split("\n",QString::SkipEmptyParts) )
    {
        if( line.startsWith( QString("<") + tag ) )
        {
            rx.setPattern("id=\"(\\w+)\"");
            if( rx.indexIn(line) > -1 )
            {
                compartment.setProperty( "id" , QScriptValue( rx.cap(1) ) );
            }else{
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Compartment Id not specified!\n") + line );
                return false;
            }

            rx.setPattern("type=\"(\\w+)\"");
            if( rx.indexIn(line) > -1 )
            {
                compartment.setProperty( "type" , QScriptValue( rx.cap(1) ) );
            }else{
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Compartment Type not specified!\n") + line );
                return false;
            }

            rx.setPattern("population=\"(\\w+)\"");
            if( rx.indexIn(line) > -1 )
            {
                if( parameterSet.contains( rx.cap(1) ) )
                    compartment.setProperty( "population" , QScriptValue( rx.cap(1) ) );
                else{
                    QMessageBox::critical( 0 , "Syntex Error!" , QString("Undefined parameter used!\n") + rx.cap(1) );
                    return false;
                }
            }
        }else{
            QList<QString> tmpList = line.simplified().split(" ");
            if( tmpList.count() != 3 && tmpList.count() != 4 )
            {
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid Species definition!\n") + line );
                return false;
            }

            QScriptValue species = engine->newObject();
            rx.setPattern("^\\w+$");
            if( rx.indexIn(tmpList[0]) == -1 )
            {
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid species id!") + tmpList[0] );
                return false;
            }
            species.setProperty("id",tmpList[0]);


            if( tmpList[1].startsWith("d:") )
            {
                species.setProperty("type","plasmid");
                QScriptValueList structure;
                foreach( QString strPart , tmpList[1].mid(2).split("-") )
                {
                    rx.setPattern("^(\\w+)(\\'?)\\((.*)\\)$");
                    if( rx.indexIn(strPart) > -1 )
                    {
                        QScriptValue part = engine->newObject();
                        part.setProperty( "type" , "dna" );
                        part.setProperty( "agent", QScriptValue( rx.cap(1) ) );
                        part.setProperty( "reversed" , QScriptValue( !rx.cap(2).isEmpty() ) );
                        part.setProperty( "sites" , QScriptValue( rx.cap(3) ) );
                        structure.push_back(part);
                    }else{
                        QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid agent definition!") + strPart );
                        return false;
                    }
                }
                species.setProperty( "structure" , convertModelTypeToScriptValue(engine,structure) );
            }else if( tmpList[1].startsWith("p:") )
            {
                species.setProperty("type","protein");
                rx.setPattern("^(\\w+)(\\'?)\\((.*)\\)$");
                if( rx.indexIn(tmpList[1].mid(2)) > -1 )
                {
                    species.setProperty( "agent", QScriptValue( rx.cap(1) ) );
                    species.setProperty( "reversed" , QScriptValue( !rx.cap(2).isEmpty() ) );
                    species.setProperty( "sites" , QScriptValue( rx.cap(3) ) );
                }else{
                    QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid agent definition!") + tmpList[1].mid(2) );
                    return false;
                }
            }else if( tmpList[1].startsWith("m:") )
            {
                species.setProperty("type","molecule");
                rx.setPattern("^(\\w+)(\\'?)\\((.*)\\)$");
                if( rx.indexIn(tmpList[1].mid(2)) > -1 )
                {
                    species.setProperty( "agent", QScriptValue( rx.cap(1) ) );
                    species.setProperty( "reversed" , QScriptValue( !rx.cap(2).isEmpty() ) );
                    species.setProperty( "sites" , QScriptValue( rx.cap(3) ) );
                }else{
                    QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid agent definition!") + tmpList[1].mid(2) );
                    return false;
                }
            }else
            {
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Invalid species structure!") + tmpList[1] );
                return false;
            }

            if( parameterSet.contains( tmpList[2] ) )
            {
                species.setProperty( "initConcentration" , QScriptValue( tmpList[2] ) );
            }else{
                QMessageBox::critical( 0 , "Syntex Error!" , QString("Undefined parameter used!") + tmpList[2] );
                return false;
            }

            species.setProperty( "constConcentration", QScriptValue(false) );

            if( tmpList.count() == 4 )
            {
                if( tmpList[3] == "const" )
                {
                    species.setProperty( "constConcentration", QScriptValue(true) );
                }else{
                    QMessageBox::critical( 0 , "Syntex Error!" , QString("Unknow term!") + tmpList[3] );
                    return false;
                }
            }

            speciesList.push_back( species );
        }
    }

    compartment.setProperty( "contains" , convertModelTypeToScriptValue( engine , speciesList ) );

    return true;
}
