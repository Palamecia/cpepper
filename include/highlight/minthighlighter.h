#ifndef MINTHIGHLIGHTER_H
#define MINTHIGHLIGHTER_H

#include <QtGui/QSyntaxHighlighter>

class MintHighlighter : public QSyntaxHighlighter {
	Q_OBJECT
public:
	MintHighlighter(QTextDocument *parent = nullptr);

protected:
	void highlightBlock(const QString &text) override;
};

#endif // MINTHIGHLIGHTER_H
