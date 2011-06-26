#ifndef DESIGNERNETWORKVIEW_SBMLHIGHLIGHTER_H
#define DESIGNERNETWORKVIEW_SBMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <functional>

class NetworkView_SBMLHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit NetworkView_SBMLHighlighter(QTextDocument *parent = 0);

protected:
    virtual void highlightBlock ( const QString & text );

private:
    static QTextCharFormat getSyntaxFormat (const QString & text);

signals:

public slots:

};

#endif // DESIGNERNETWORKVIEW_SBMLHIGHLIGHTER_H
