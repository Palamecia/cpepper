#ifndef HIGHLIGHTRULE_H
#define HIGHLIGHTRULE_H

#include <QtCore/QRegularExpression>
#include <QtCore/QRegularExpressionMatchIterator>

#include "highlight/codestylemanager.h"

class HighlightRule {
public:
	HighlightRule(const QString &expression, CodeStyleFormat format);
	HighlightRule(const QRegularExpression &expression, CodeStyleFormat format);

	QRegularExpressionMatchIterator match(const QString &text) const;
	QTextCharFormat format() const;

private:
	QRegularExpression m_expression;
	CodeStyleFormat m_format;
};

#endif // HIGHLIGHTRULE_H
