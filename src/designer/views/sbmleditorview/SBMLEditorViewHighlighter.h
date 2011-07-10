#ifndef SBMLEDITORVIEWHIGHLIGHTER_H
#define SBMLEDITORVIEWHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SBMLEditorViewHighlighter : public QSyntaxHighlighter
{
public:
    explicit SBMLEditorViewHighlighter(QTextDocument *parent = 0);

protected:
    virtual void highlightBlock ( const QString & text );

private:
    static QTextCharFormat getSyntaxFormat (const QString & text);

};

#endif // SBMLEDITORVIEWHIGHLIGHTER_H
