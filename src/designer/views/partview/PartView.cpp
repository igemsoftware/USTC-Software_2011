#include <QtScript>

#include "interfaces/DesignerViewItf.h"
#include "interfaces/DesignerModelItf.h"

#include "PartView.h"
#include "common/mainwnd/DesignerMainWnd.h"
#include "documents/common/designerpartdocparser/DesignerPartDocParser.h"

PartView::PartView(DesignerMainWnd *mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model),
    ui(new Ui::PartView)
{
    ui->setupUi(this);
    connect(this, SIGNAL(updateSelectedItem(QScriptValue)),  mainWindow->getPanelWidget("PropertiesPanel"), SLOT(updateTarget(QScriptValue)));

    emit updateSelectedItem(model->getModel());

    {
        this->listviewindex=0;
        QScriptValue parts=model->getModel();
        int length=parts.property("length").toInt32();
        QStringListModel* slm = new QStringListModel(this);
        QStringList* sl = new QStringList();
        for(int i=0;i<length;i++)
        {
            sl->append(parts.property(i).property("*partsregistry.org*").property("part_name").toString());
        }
        slm->setStringList(*sl);
        ui->listView->setModel(slm);        
        ui->textEdit->setText(parts.property(0).property("*partsregistry.org*").property("part_descr").toString());
        ui->textEdit_seq->setText(parts.property(0).property("partsequence").toString());
        ui->partNameEdit->setText(model->getModel().property(0).property("*partsregistry.org*").property("part_name").toString());
        ui->label_length->setText(QString::number(model->getModel().property(0).property("partsequence").toString().length()));
        QString t=parts.property(0).property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_value").toString();
        if(t!="")
            ui->lineEdit_2->setText(t);
        t=parts.property(0).property("*partsregistry.org*").property("part_parameters").property(1).property("parameter_value").toString();
        if(t!="")
            ui->lineEdit->setText(t);
        QPixmap pic(":/designer/partview/icon_"+parts.property(0).property("*partsregistry.org*").property("part_type").toString().toLower()+".png");
        if(!pic.isNull())
            ui->label_image->setPixmap(pic);
    }

}

PartView::~PartView()
{
    delete ui;
}

void PartView::on_listView_clicked(QModelIndex index)
{
    int i=index.row();
    QScriptValue part=this->currentModel->getModel().property(i);
    ui->textEdit->setText(part.property("*partsregistry.org*").property("part_descr").toString());
    ui->textEdit_seq->setText(part.property("partsequence").toString());
    ui->partNameEdit->setText(part.property("*partsregistry.org*").property("part_name").toString());
    ui->label_length->setText(QString::number(part.property("partsequence").toString().length()));
    QString t=part.property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_value").toString();
    if(t!="")
        ui->lineEdit_2->setText(t);
    t=part.property("*partsregistry.org*").property("part_parameters").property(1).property("parameter_value").toString();
    if(t!="")
        ui->lineEdit->setText(t);

    QPixmap pic(":/designer/partview/icon_"+part.property("*partsregistry.org*").property("part_type").toString().toLower()+".png");
    if(!pic.isNull())
        ui->label_image->setPixmap(pic);
}

void PartView::on_pushButton_clicked()
{
    int i=ui->listView->currentIndex().row();
    if(i!=-1)
        this->listviewindex=i;
    i=this->listviewindex;
    QScriptValue part=this->currentModel->getModel().property(i).property("*partsregistry.org*");    
    QScriptValue newcontent=this->currentModel->getEngine()->newArray();
    QScriptValue content;
    ui->textEdit_seq->setText(DesignerPartDocParser::generateSequence(ui->textEdit_seq->toPlainText()));
    //write content accroding to file type
    if(QString(this->currentModel->getCurrentDoc()->metaObject()->className()).toLower()=="fastadoc")
    {
        QString line;
        if(part.property("newcontent").property("length").toInt32()==0)
            line=part.property("content").property(0).toString();
        else
            line=part.property("newcontent").property(0).toString();
        line=line.replace(part.property("part_name").toString(),ui->partNameEdit->text());
        line=line.replace(part.property("part_descr").toString(),ui->textEdit->toPlainText());
        line=line.replace("len="+part.property("part_length").toString(),"len="+QString::number(ui->textEdit_seq->toPlainText().length()));
        newcontent.setProperty(0,line);

        QString seq=ui->textEdit_seq->toPlainText();
        int  linenum=seq.length()/60;
        for(int j=0;j<linenum;j++)
            newcontent.setProperty(j+1,seq.mid(j*60,60));
        if(linenum*60!=seq.length())
            newcontent.setProperty(linenum+1,seq.mid(linenum*60,seq.length()-linenum));
        part.setProperty("newcontent",newcontent);
    }
    if(QString(this->currentModel->getCurrentDoc()->metaObject()->className()).toLower()=="embldoc")
    {
        int prenum=0;
        if(part.property("newcontent").property("length").toInt32()==0)
            content=part.property("content");
        else
            content=part.property("newcontent");
        for(int j=0;j<content.property("length").toInt32();j++)
        {
            QString line=content.property(j).toString();
            if(line.toLower().startsWith("id")||line.toLower().startsWith("ac")||line.toLower().startsWith("sq"))
            {
                line=line.replace(part.property("part_name").toString(),ui->partNameEdit->text());
                line=line.replace(part.property("part_length").toString()+" BP",QString::number(DesignerPartDocParser::generateSequence(ui->textEdit_seq->toPlainText()).length())+" BP");
                line=line.replace(part.property("part_length").toString()+" bp",QString::number(DesignerPartDocParser::generateSequence(ui->textEdit_seq->toPlainText()).length())+" bp");
            }
            if(line.toLower().startsWith("de"))
                line=line.replace(part.property("part_descr").toString(),ui->textEdit->toPlainText());
            if(line.toLower().startsWith("sq"))
            {
                prenum=j;
                newcontent.setProperty(j,line);
                break;
            }
            newcontent.setProperty(j,line);
        }
        QString seq=ui->textEdit_seq->toPlainText();
        int  linenum=seq.length()/60;
        for(int j=0;j<linenum;j++)
            newcontent.setProperty(j+prenum+1,seq.mid(j*60,60));
        if(linenum*60!=seq.length())
        {
            newcontent.setProperty(prenum+linenum+1,seq.mid(linenum*60,seq.length()-linenum));
            linenum++;
        }
        newcontent.setProperty(prenum+linenum+1,"//");
        newcontent.setProperty("length",prenum+linenum+2);
        part.setProperty("newcontent",newcontent);
    }
    if(QString(this->currentModel->getCurrentDoc()->metaObject()->className()).toLower()=="genbankdoc")
    {
        int prenum=0;
        if(part.property("newcontent").property("length").toInt32()==0)
            content=part.property("content");
        else
            content=part.property("newcontent");
        for(int j=0;j<content.property("length").toInt32();j++)
        {
            QString line=content.property(j).toString();
            if(line.toLower().startsWith("locus")||line.toLower().startsWith("accession")||line.toLower().startsWith("origin"))
            {
                line=line.replace(part.property("part_name").toString(),ui->partNameEdit->text());
                line=line.replace(part.property("part_length").toString()+" BP",QString::number(ui->textEdit_seq->toPlainText().length())+" BP");
                line=line.replace(part.property("part_length").toString()+" bp",QString::number(ui->textEdit_seq->toPlainText().length())+" bp");
            }
            if(line.toLower().startsWith("definition"))
                line=line.replace(part.property("part_descr").toString(),ui->textEdit->toPlainText());
            if(line.toLower().startsWith("origin"))
            {
                prenum=j;
                newcontent.setProperty(j,line);
                break;
            }
            newcontent.setProperty(j,line);
        }
        QString seq=ui->textEdit_seq->toPlainText();
        int  linenum=seq.length()/60;
        for(int j=0;j<linenum;j++)
            newcontent.setProperty(j+prenum+1,seq.mid(j*60,60));
        if(linenum*60!=seq.length())
        {
            newcontent.setProperty(prenum+linenum+1,seq.mid(linenum*60,seq.length()-linenum));
            linenum++;
        }
        newcontent.setProperty(prenum+linenum+1,"//");
        newcontent.setProperty("length",prenum+linenum+2);
        part.setProperty("newcontent",newcontent);
    }
    //ui part refresh
    {
        part.setProperty("part_name",ui->partNameEdit->text());
        QStringListModel* slm=dynamic_cast<QStringListModel *>(ui->listView->model());
        QStringList sl=slm->stringList();
        sl[i]=ui->partNameEdit->text();
        slm->setStringList(sl);
        ui->listView->setModel(slm);

        QScriptValue parameter=this->currentModel->getModel().property(i).property("*partsregistry.org*").property("part_parameters").property(1);
        if(!parameter.isNull())
            parameter.setProperty("parameter_value",ui->lineEdit->text());

        parameter=this->currentModel->getModel().property(i).property("*partsregistry.org*").property("part_parameters").property(0);
        if(!parameter.isNull())
            parameter.setProperty("parameter_value",ui->lineEdit_2->text());
        part.setProperty("part_descr",ui->textEdit->toPlainText());

        part=this->currentModel->getModel().property(i);
        QString newsq=DesignerPartDocParser::generateSequence(ui->textEdit_seq->toPlainText());
        part.setProperty("partsequence",newsq);
        part.property("*partsregistry.org*").setProperty("part_length",QString::number(newsq.length()));
        ui->label_length->setText(QString::number(newsq.length()));
    }

    //! \bug This is test code. Will be handled in a more elegant way in the future -CrLF0710
    mainWindow->getCurrentModel()->setModified(true);

    emit updateSelectedItem(this->currentModel->getModel());
}
