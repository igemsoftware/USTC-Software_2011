#include "AssemblyScene.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTextEdit>
#include <QLayout>
#include <QPushButton>
#include "documents/MoDeL/MoDeLDocParser.h"
#include "DesignerDebug.h"

AssemblyScene::AssemblyScene( IGameModel * newModel , QObject *parent) :
    QGraphicsScene(parent) , model(newModel)
{
    connect( this , SIGNAL(selectionChanged()) , this , SLOT(propagateSelectionChange()) );
}

void AssemblyScene::readModel()
{
    clear();
    childrenMap.clear();
    idSpace.clear();

    int width = views().first()->width();
    int height = views().first()->height();

    if( model->getEngine()->globalObject().property("model").isObject() )
    {
        QScriptValue root = model->getEngine()->globalObject().property("model");
        QScriptValue rootCompartment = root.property("rootCompartment");

        idSpace.insert(rootCompartment.property("id").toString());
        if( rootCompartment.property("contains").isArray() )
        {
            QScriptValueList children;
            qScriptValueToSequence( rootCompartment.property("contains") , children );
            foreach( QScriptValue child , children )
            {
                if( child.property("type").toString() == "plasmid" )
                {
                    AssemblyItemPlasmid * plasmid = new AssemblyItemPlasmid(child);
                    QGraphicsScene::addItem( plasmid );
                    plasmid->setPos(qrand()%width, qrand()%height);
                    if( !registerItem( plasmid ) )
                    {
                        delete plasmid;
                    }
                }else if( child.property("type").toString() == "protein" || child.property("type").toString() == "molecule" )
                {
                    AssemblyItemMolecule * molecule = new AssemblyItemMolecule(child);
                    QGraphicsScene::addItem( molecule );
                    molecule->setPos(qrand()%width, qrand()%height);
                    if( !registerItem( molecule ) )
                    {
                        delete molecule;
                    }
                }
            }
        }
        QScriptValueList childCompartments;
        qScriptValueToSequence( root.property("childCompartments") , childCompartments );
        foreach( QScriptValue child , childCompartments )
        {
            AssemblyItemCompartment * compartment = new AssemblyItemCompartment( child );
            QGraphicsScene::addItem( compartment );
            compartment->setPos(qrand()%width, qrand()%height);
            if( !registerItem( compartment ) )
            {
                delete compartment;
            }
        }

        QScriptValueList events,parameters;
        qScriptValueToSequence( root.property("parameters") , parameters );
        qScriptValueToSequence( root.property("events") , events );
        foreach( QScriptValue event , events )
            idSpace.insert(event.property("id").toString());
        foreach( QScriptValue parameter , parameters )
            idSpace.insert(parameter.property("id").toString());
        parameterSpaceChanged();

    }else{
        QScriptValue root , rootCompartment;
        model->getEngine()->globalObject().setProperty("model", root = model->getEngine()->newObject() );
        root.setProperty( "parameters" , model->getEngine()->newArray() );
        root.setProperty( "events" , model->getEngine()->newArray() );
        root.setProperty( "rootCompartment" , rootCompartment = model->getEngine()->newObject() );
        rootCompartment.setProperty( "id" , "flask" );
        rootCompartment.setProperty( "type" , "flask" );
        rootCompartment.setProperty( "contains" , model->getEngine()->newArray() );
        idSpace.insert("flask");
    }
}

void AssemblyScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if ( event->mimeData()->hasFormat( AssemblyItemPart::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if ( event->mimeData()->hasFormat( AssemblyItemMolecule::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else
    {
        QGraphicsScene::dragEnterEvent(event);
    }
}

void AssemblyScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if ( event->mimeData()->hasFormat( AssemblyItemPart::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if ( event->mimeData()->hasFormat( AssemblyItemMolecule::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else
    {
        QGraphicsScene::dragMoveEvent(event);
    }
}

void AssemblyScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    AssemblyItemBase * item = 0;
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemCompartment::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! idSpace.contains(itemId+"_"+stri) ) break;
        }
        itemId += "_"+stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        item = new AssemblyItemCompartment( *scriptValue );
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemPlasmid::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! idSpace.contains(itemId+"_"+stri) ) break;
        }
        itemId += "_"+stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        item = new AssemblyItemPlasmid( *scriptValue );
    }else if( event->mimeData()->hasFormat( AssemblyItemMolecule::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemMolecule::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! idSpace.contains(itemId+"_"+stri) ) break;
        }
        itemId += "_"+stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        item = new AssemblyItemMolecule( *scriptValue );
    }else if( event->mimeData()->hasFormat( AssemblyItemPart::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemPart::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        item = new AssemblyItemPart( *scriptValue );
    }else{
        QGraphicsScene::dropEvent(event);
        return;
    }
    item->setPos( event->scenePos().x() - item->pixmap().width()/2 , event->scenePos().y() - item->pixmap().height()/2 );

    if( addItem( item ) )
    {
        event->accept();
    }else{
        QGraphicsScene::dropEvent(event);
    }
    return;
}

void AssemblyScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if( event->modifiers() == Qt::ControlModifier )
    {
        if( event->delta() > 0 )
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1.1 , 1.1 );
            }
            event->accept();
            return;
        }else
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1/1.1 , 1/1.1 );
            }
            event->accept();
            return;
        }
    }
    QGraphicsScene::wheelEvent(event);
}

void AssemblyScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key() )
    {
    case Qt::Key_Delete:
        foreach( QGraphicsItem * item , selectedItems() )
        {
            if( dynamic_cast<AssemblyItemBase*>(item) )
                delete item;
        }
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
        return;
    }
    event->accept();
}

void AssemblyScene::removeItem( AssemblyItemBase * item )
{
    if( !item->getId().isEmpty() )
    {
        childrenMap.remove( item->getId() );
        idSpace.remove(item->getId());
    }
    foreach( AssemblyItemBase * child , item->getChildren() ) removeItem(child);
    QGraphicsScene::removeItem(item);
    refreshScriptValue();
}

bool AssemblyScene::registerItem(AssemblyItemBase *item)
{
    QString id = item->getId();
    if( id.isEmpty() ) return true;

    if( !idSpace.contains(id) )
    {
        idSpace.insert(id);
        childrenMap.insert(id,item);
        foreach( AssemblyItemBase * childItem , item->getChildren() ) registerItem(childItem);
        return true;
    }else{
        QGraphicsScene::removeItem(item);
        QMessageBox::warning(0,tr("Error"),tr("duplicated id detected while trying to add item %1").arg(id) );
        return false;
    }
}

bool AssemblyScene::addItem(AssemblyItemBase *item,bool flag)
{
    if( item->scene() != this ) QGraphicsScene::addItem(item);
    QList<QGraphicsItem*> candidates = collidingItems( item );
    foreach( QGraphicsItem * candidate , candidates )
    {
        if( dynamic_cast<AssemblyItemBase*>(candidate) && dynamic_cast<AssemblyItemBase*>(candidate)->addChild( candidate->mapFromScene(item->scenePos()) , item ) )
        {
            if( flag ) registerItem( item );
            foreach( QGraphicsItem* item , selectedItems() )
            {
                if( dynamic_cast<AssemblyItemBase*>(item) )
                {
                    emit setScriptValue(dynamic_cast<AssemblyItemBase*>(item)->getScriptValue());
                }
            }
            refreshScriptValue();
            return true;
        }
        if( dynamic_cast<AssemblyItemCompartment*>(candidate) )
        {
            delete item;
            return false;
        }
    }

    if( dynamic_cast<AssemblyItemCompartment*>(item) || dynamic_cast<AssemblyItemMolecule*>(item) || dynamic_cast<AssemblyItemPlasmid*>(item) )
    {
        if( flag ) registerItem( item );
        refreshScriptValue();
        return true;
    }

    if( dynamic_cast<AssemblyItemPart*>(item) && dynamic_cast<AssemblyItemPart*>(item)->getScriptValue().property("category").toString() == "pcs" )
    {
        QString itemId = "Protein";
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! idSpace.contains(itemId+"_"+stri) ) break;
        }
        itemId += "_"+stri;
        QScriptValue scriptValue = item->getScriptValue().engine()->newObject();
        scriptValue.setProperty( "id", QScriptValue(itemId) );
        scriptValue.setProperty( "type" , "protein" );
        scriptValue.setProperty( "agent" , item->getScriptValue().property("agent") );
        scriptValue.setProperty( "reversed" , item->getScriptValue().property("reversed") );
        scriptValue.setProperty( "sites" , item->getScriptValue().property("sites") );

        QPointF pos = item->pos();
        delete item;
        item = new AssemblyItemMolecule( scriptValue );
        item->setPos(pos);
        return addItem( item );
    }

    delete item;
    return false;
}

void AssemblyScene::propagateSelectionChange()
{
    QList<QGraphicsItem*> newSelection = selectedItems();
    foreach( QGraphicsItem* item , items() )
    {
        if( dynamic_cast<AssemblyItemBase*>(item) ) dynamic_cast<AssemblyItemBase*>(item)->loseSelection(newSelection);
    }
    foreach( QGraphicsItem* item , newSelection )
    {
        if( dynamic_cast<AssemblyItemBase*>(item) )
        {
            dynamic_cast<AssemblyItemBase*>(item)->getSelection();
            emit setScriptValue(dynamic_cast<AssemblyItemBase*>(item)->getScriptValue());
        }
    }
    if( newSelection.count() == 0 )
    {
        emit setScriptValue( model->getEngine()->globalObject().property("model") );
    }
}

void AssemblyScene::refreshScriptValue()
{
    QScriptValueList compartments;
    QScriptValueList molecules;
    foreach( QGraphicsItem * item , items() )
    {
        if( item->parentItem() == 0 )
        {
            if( dynamic_cast<AssemblyItemCompartment*>(item) )
            {
                compartments.push_back( dynamic_cast<AssemblyItemBase*>(item)->getScriptValue() );
            }else if( dynamic_cast<AssemblyItemPlasmid*>(item) || dynamic_cast<AssemblyItemMolecule*>(item) )
            {
                molecules.push_back( dynamic_cast<AssemblyItemBase*>(item)->getScriptValue() );
            }
        }
    }
    model->getEngine()->globalObject().property("model").property("rootCompartment").setProperty( "contains" , convertModelTypeToScriptValue( model->getEngine(),molecules ) );
    model->getEngine()->globalObject().property("model").setProperty( "childCompartments" , convertModelTypeToScriptValue( model->getEngine() , compartments ));
    propagateSelectionChange();
}


QString AssemblyScene::outputMoDeLText(DesignerModelComponent *source_model)
{
    QString strAns;
    QTextStream ans(&strAns);
    QScriptValue root = source_model->getEngine()->globalObject().property("model");
    QScriptValueList parameters;
    QScriptValueList events;
    QScriptValueList childCompartments;
    QScriptValue rootCompartment = root.property("rootCompartment");

    qScriptValueToSequence( root.property("parameters") , parameters );
    qScriptValueToSequence( root.property("events") , events );
    qScriptValueToSequence( root.property("childCompartments") , childCompartments );


    //parameters
    ans << "<parameters>\n";
    foreach( QScriptValue parameter , parameters )
        ans << parameter.property("id").toString() << "\t\t" << parameter.property("value").toString() << "\n";
    ans << "</parameters>\n\n";

    ans << "<compartments>\n";
    //rootcompartment
    ans << rootCompartment.property("id").toString() << "\t"
        << "ROOT" << "\t"
        << rootCompartment.property("type").toString() << "\t"
        << rootCompartment.property("volume").toString() << "\t"
        << rootCompartment.property("population").toString() << "\n";
    //childcompartment
    foreach( QScriptValue compartment , childCompartments )
    {
        ans << compartment.property("id").toString() << "\t"
            << rootCompartment.property("id").toString() << "\t"
            << compartment.property("type").toString() << "\t"
            << compartment.property("volume").toString() << "\t"
            << compartment.property("population").toString() << "\n";
    }
    ans << "</compartments>\n\n";

    ans << "<seedspecies>\n";
    childCompartments.append(rootCompartment);
    foreach( QScriptValue compartment, childCompartments )
    {
        QScriptValueList specieses;
        qScriptValueToSequence(compartment.property("contains"), specieses);
        foreach( QScriptValue species, specieses )
            ans << outputSpeciesText(species, compartment.property("id").toString());
    }
    ans << "</seedspecies>\n\n";

    ans << "<events>\n";
    foreach( QScriptValue event , events )
        ans << event.property("id").toString() << "\t" << event.property("condition").toString() << "\t" << event.property("variable").toString() << "=" << event.property("value").toString() << "\n";
    ans << "</events>\n\n";


    return strAns;
}

QString AssemblyScene::outputSpeciesText(QScriptValue species, QString compartment)
{
    QString strAns;
    QTextStream ans(&strAns);

    ans << compartment << "\t"
        << species.property("id").toString() << "\t";

    if( species.property("type").toString() == "plasmid" )
    {
        ans << "d:";
        QScriptValueList structure;
        qScriptValueToSequence( species.property("structure") , structure );
        for( int i = 0 ; i < structure.count() ; i++ )
        {
            QScriptValue agent = structure[i];
            ans << ( (i>0)?"-":"" ) << agent.property("agent").toString() << ( agent.property("reversed").toBool()?"'":"" ) << "(" << agent.property("sites").toString() << ")";
        }
        ans << "\t" << species.property("initConcentration").toString();
        if( species.property("constConcentration").toBool() ) ans << "\t" << "const";
        ans << "\n";
    }else if( species.property("type").toString() == "protein" )
    {
        ans << "p:"
            << species.property("agent").toString()
            << ( species.property("reversed").toBool()?"'":"" )
            << "("  << species.property("sites").toString() << ")\t"
            << species.property("initConcentration").toString();
        if( species.property("constConcentration").toBool() ) ans << "\t" << "const";
        ans << "\n";
    }else if( species.property("type").toString() == "molecule" )
    {
        ans << "nb:"
            << species.property("agent").toString()
            << ( species.property("reversed").toBool()?"'":"" )
            << "(" << species.property("sites").toString() << ")\t"
            << species.property("initConcentration").toString();
        if( species.property("constConcentration").toBool() ) ans << "\t" << "const";
        ans << "\n";
    }

    return strAns;
}

void AssemblyScene::launchTextEditor()
{
    QDialog widget;
    QTextEdit * editor = new QTextEdit;
    QTextDocument document(outputMoDeLText(model));
    QVBoxLayout * vlayout = new QVBoxLayout;
    QHBoxLayout * hlayout = new QHBoxLayout;
    QPushButton * ok = new QPushButton("OK");
    QPushButton * cancel = new QPushButton("CANCEL");
    editor->setWordWrapMode(QTextOption::NoWrap);
    ok->setFixedSize(100,30);
    cancel->setFixedSize(100,30);
    connect( ok , SIGNAL(clicked()) , &widget , SLOT(accept()) );
    connect( cancel , SIGNAL(clicked()) , &widget , SLOT(reject()) );
    hlayout->addWidget(ok);
    hlayout->addWidget(cancel);
    vlayout->addWidget(editor);
    vlayout->addLayout(hlayout);
    editor->setDocument(&document);
    widget.setLayout(vlayout);
    widget.setResult(QDialog::Rejected);

    widget.resize(800,600);
    int code = widget.exec();
    if( code == QDialog::Accepted )
    {
        MoDeLDocParser parser;
        QString tmpStr = document.toPlainText();
        QTextStream fin(&tmpStr);
        if( parser.parse(*model,fin) )
        {
            clear();
            fin.setString(&tmpStr);
            parser.parse(*model,fin);
            readModel();
        }else{
            QMessageBox::information(0,"Error","Can not accept edit due to syntex error!");
        }
    }
}

bool AssemblyScene::reassignId(QString oldId, QString newId)
{
    if( oldId == newId ) return true;
    if( !idSpace.contains(newId) && idSpace.contains(oldId) )
    {
        idSpace.remove(oldId);
        idSpace.insert(newId);
        if( childrenMap.contains(oldId) )
        {
            AssemblyItemBase * item = childrenMap[oldId];
            childrenMap.insert( newId , item );
            childrenMap.remove(oldId);
        }
        return true;
    }
    return false;
}


void AssemblyScene::requestEventEdit()
{
    QScriptValueList original;
    qScriptValueToSequence( model->getEngine()->globalObject().property("model").property("events") , original );

    QScriptValueList mock;
    foreach( QScriptValue value , original )
        mock.push_back( copyFromScriptValue( model->getEngine() , value ) );

    AssemblyPropertyEditor dialog( "event" , mock , model->getEngine() );

    if( dialog.exec() == QDialog::Accepted  )
    {
        if( mock.count() > original.count() && idSpace.contains( mock.last().property("id").toString() ) ) goto FAIL;
        model->getEngine()->globalObject().property("model").setProperty( "events" , convertModelTypeToScriptValue( model->getEngine() , mock ) );
        return;
        FAIL:;
        QMessageBox::critical(0, tr("Error"), tr("Invalid input!"));
    }

}

void AssemblyScene::requestParameterEdit()
{
    QScriptValueList original;
    qScriptValueToSequence( model->getEngine()->globalObject().property("model").property("parameters") , original );

    QScriptValueList mock;
    foreach( QScriptValue value , original )
        mock.push_back( copyFromScriptValue( model->getEngine() , value ) );

    AssemblyPropertyEditor dialog( "parameter" , mock , model->getEngine() );

    if( dialog.exec() == QDialog::Accepted )
    {
        if( mock.count() > original.count() && idSpace.contains( mock.last().property("id").toString() ) ) goto FAIL;
        model->getEngine()->globalObject().property("model").setProperty( "parameters" , convertModelTypeToScriptValue( model->getEngine() , mock ) );
        parameterSpaceChanged();
        return;
        FAIL:;
        QMessageBox::critical(0, tr("Error"), tr("Invalid input!"));
    }
}

void AssemblyScene::parameterSpaceChanged()
{
    QScriptValueList original;
    qScriptValueToSequence( model->getEngine()->globalObject().property("model").property("parameters") , original );

    QList<QScriptValue> * combo = new QList<QScriptValue>;
    foreach( QScriptValue value , original )
        combo->push_back(value.property("id"));
    AssemblyPropertyEditor::setCombo( "parameter" , combo );
}

void AssemblyScene::igameDBRefresh()
{

}
