#include "AssemblyPropertyEditor.h"
#include <QComboBox>
#include <QScriptValue>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScriptValueList>

QMap<QString,QList<QScriptValue>*> AssemblyPropertyEditor::comboMap;
QMap<QString,AssemblyPropertyEditor::ScriptTypeSpecifier> AssemblyPropertyEditor::typeMap;


AssemblyPropertyEditor::AssemblyPropertyEditor( QString newType , QScriptValueList & newScriptValueList , QScriptEngine * newEngine , QWidget *parent ) :
    QDialog(parent) , type(newType) , valueList(newScriptValueList) , engine(newEngine)
{
    initializeOnce();

    QFormLayout * flayout   = new QFormLayout;
    QVBoxLayout * vlayout   = new QVBoxLayout;
    QHBoxLayout * hlayout   = new QHBoxLayout;
    QComboBox   * title     = new QComboBox;
    ScriptTypeSpecifier sts = typeMap[type];

    for( int i = 0 ; i < valueList.count() ; i++ ) title->addItem( valueList.at(i).property("id").toString() );
    if( sts.enableAdd ) title->addItem("<new>");
    connect( title , SIGNAL(currentIndexChanged(int)) , this , SLOT(setIndex(int)) );

    vlayout->addWidget(title);

    for( int i = 0 ; i < sts.properties.count() ; i++ )
    {
        if( sts.properties[i].type == TypeString || sts.properties[i].type == TypeNumber )
        {
            flayout->addRow( new QLabel(sts.properties[i].label) , new QLineEdit);
        }else{
            QComboBox * combo;
            flayout->addRow( new QLabel(sts.properties[i].label) , combo = new QComboBox );
            foreach( QScriptValue value , *comboMap[sts.properties[i].type==TypeCombo?sts.properties[i].combo:"bool"] )
            {
                QVariant tmpVar;
                tmpVar.setValue(value);
                combo->addItem( value.toString() , tmpVar );
            }
        }
    }

    vlayout->addLayout(flayout);

    QPushButton * ok = new QPushButton("Ok");
    hlayout->addWidget(ok);
    QPushButton * cancel = new QPushButton("Cancel");
    hlayout->addWidget(cancel);
    connect( ok , SIGNAL(clicked()) , this , SLOT(accept()) );
    connect( cancel , SIGNAL(clicked()) , this , SLOT(reject()) );

    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    form = flayout;
    setIndex(0);
}

void AssemblyPropertyEditor::setIndex(int newIndex)
{
    index = newIndex;
    ScriptTypeSpecifier sts = typeMap[type];

    for( int i = 0 ; i < sts.properties.count() ; i++ )
    {
        if( sts.properties[i].type == TypeString || sts.properties[i].type == TypeNumber )
        {
            dynamic_cast<QLineEdit*>(form->itemAt(i,QFormLayout::FieldRole)->widget())->setText( index<valueList.count()?valueList.at(index).property( sts.properties[i].name ).toString():"" );
        }else{
            QComboBox * combo = dynamic_cast<QComboBox*>(form->itemAt(i,QFormLayout::FieldRole)->widget());
            combo->setCurrentIndex( index<valueList.count()?combo->findText( valueList.at(index).property( sts.properties[i].name ).toString() ):0 );
        }
    }
}

void AssemblyPropertyEditor::accept()
{
    ScriptTypeSpecifier sts = typeMap[type];
    if( index>=valueList.count() ) valueList.push_back(engine->newObject());
    for( int i = 0 ; i < sts.properties.count() ; i++ )
    {
        if( sts.properties[i].type == TypeString )
        {
            valueList[index].setProperty( sts.properties[i].name , dynamic_cast<QLineEdit*>(form->itemAt(i,QFormLayout::FieldRole)->widget())->text() );
        }else if( sts.properties[i].type == TypeNumber )
        {
            valueList[index].setProperty( sts.properties[i].name , dynamic_cast<QLineEdit*>(form->itemAt(i,QFormLayout::FieldRole)->widget())->text().toDouble() );
        }else if( sts.properties[i].type == TypeCombo ){
            QComboBox * combo = dynamic_cast<QComboBox*>(form->itemAt(i,QFormLayout::FieldRole)->widget());
            valueList[index].setProperty( sts.properties[i].name , combo->itemData( combo->currentIndex() ).toString() );
        }else if( sts.properties[i].type == TypeBool )
        {
            QComboBox * combo = dynamic_cast<QComboBox*>(form->itemAt(i,QFormLayout::FieldRole)->widget());
            valueList[index].setProperty( sts.properties[i].name , combo->itemData( combo->currentIndex() ).toBool() );
        }
    }
    QDialog::accept();
}

void AssemblyPropertyEditor::initializeOnce()
{
    static bool initialized = false;
    if( initialized ) return;

    initialized = true;

    //-------------------------------InitializeCombo-----------------
    QList<QScriptValue> * combo;

    combo = new QList<QScriptValue>;
    combo->push_back( QScriptValue(true) );
    combo->push_back( QScriptValue(false) );
    comboMap.insert("bool",combo);

    combo = new QList<QScriptValue>;
    combo->push_back( QScriptValue("flask") );
    comboMap.insert("compartmentType",combo);

    //combo = new QList<QScriptValue>;
    //comboMap.insert("agent",combo);

    combo = new QList<QScriptValue>;
    comboMap.insert("parameter",combo);

    //--------------------------------InitializeType
    ScriptTypeSpecifier compartment;
    compartment.type = "compartment";
    compartment.enableAdd = false;
    compartment.properties.push_back( PropertySpecifier("id","Compartment Id",TypeString) );
    compartment.properties.push_back( PropertySpecifier("type","RuleSet Name",TypeCombo,"compartmentType") );
    compartment.properties.push_back( PropertySpecifier("population","Initial Concentration",TypeCombo,"parameter") );

    typeMap.insert("compartment",compartment);

    ScriptTypeSpecifier plasmid;
    plasmid.type = "plasmid";
    plasmid.enableAdd = false;
    plasmid.properties.push_back( PropertySpecifier("id","Plasmid Id",TypeString) );
    plasmid.properties.push_back( PropertySpecifier("initConcentration","Initial Concentration",TypeCombo,"parameter") );
    plasmid.properties.push_back( PropertySpecifier("constConcentration","Constant Concentration",TypeBool) );

    typeMap.insert("plasmid",plasmid);

    ScriptTypeSpecifier molecule;
    molecule.type = "molecule";
    molecule.enableAdd = false;
    molecule.properties.push_back( PropertySpecifier("id","Molecule Id",TypeString) );
    molecule.properties.push_back( PropertySpecifier("agent","Agent Id",TypeString) );
    molecule.properties.push_back( PropertySpecifier("initConcentration","Initial Concentration",TypeCombo,"parameter") );
    molecule.properties.push_back( PropertySpecifier("constConcentration","Constant Concentration",TypeBool) );

    typeMap.insert("molecule",molecule);

    ScriptTypeSpecifier part;
    part.type = "part";
    part.enableAdd = false;
    part.properties.push_back( PropertySpecifier("agent","Part Id",TypeString) );
    part.properties.push_back( PropertySpecifier("sites","Sites",TypeString) );
    part.properties.push_back( PropertySpecifier("reversed","Reversed",TypeBool) );

    typeMap.insert("part",part);

    ScriptTypeSpecifier parameter;
    parameter.type = "parameter";
    parameter.enableAdd = true;
    parameter.properties.push_back( PropertySpecifier("id","Parameter Id",TypeString) );
    parameter.properties.push_back( PropertySpecifier("value","Parameter Value",TypeNumber) );

    typeMap.insert("parameter",parameter);

    ScriptTypeSpecifier event;
    event.type = "event";
    event.enableAdd = true;
    event.properties.push_back( PropertySpecifier("id","Event Id",TypeString) );
    event.properties.push_back( PropertySpecifier("condition","Event Condition",TypeString) );
    event.properties.push_back( PropertySpecifier("variable","Set Variable",TypeString) );
    event.properties.push_back( PropertySpecifier("value","To Value",TypeCombo,"parameter") );

    typeMap.insert("event",event);

}

bool AssemblyPropertyEditor::setCombo(QString name, QList<QScriptValue> *combo)
{
    comboMap[name] = combo;
    return true;
}
