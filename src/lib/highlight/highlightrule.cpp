#include "highlight/highlightrule.h"

HighlightRule::HighlightRule(const QString &expression, CodeStyleFormat format) :
	m_expression(expression),
	m_format(format) {

}

HighlightRule::HighlightRule(const QRegularExpression &expression, CodeStyleFormat format) :
	m_expression(expression),
	m_format(format) {

}

QRegularExpressionMatchIterator HighlightRule::match(const QString &text) const {
	return m_expression.globalMatch(text);
}

QTextCharFormat HighlightRule::format() const {
	return CodeStyleManager::instance().format(m_format);
}
