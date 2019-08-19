#include "highlight/minthighlighter.h"
#include "highlight/codestylemanager.h"
#include "highlight/highlightrule.h"

static const QList<HighlightRule> Rules = {
	{"\\band\\b", CodeStyleFormat::KeyWord},
	{"\\bassert\\b", CodeStyleFormat::KeyWord},
	{"\\bbreak\\b", CodeStyleFormat::KeyWord},
	{"\\bcase\\b", CodeStyleFormat::KeyWord},
	{"\\bcatch\\b", CodeStyleFormat::KeyWord},
	{"\\bclass\\b", CodeStyleFormat::KeyWord},
	{"\\bconst\\b", CodeStyleFormat::KeyWord},
	{"\\bcontinue\\b", CodeStyleFormat::KeyWord},
	{"\\bdef\\b", CodeStyleFormat::KeyWord},
	{"\\bdefault\\b", CodeStyleFormat::KeyWord},
	{"\\bdefined\\b", CodeStyleFormat::KeyWord},
	{"\\belif\\b", CodeStyleFormat::KeyWord},
	{"\\belse\\b", CodeStyleFormat::KeyWord},
	{"\\benum\\b", CodeStyleFormat::KeyWord},
	{"\\bexit\\b", CodeStyleFormat::KeyWord},
	{"\\bfalse\\b", CodeStyleFormat::KeyWord},
	{"\\bfor\\b", CodeStyleFormat::KeyWord},
	{"\\bif\\b", CodeStyleFormat::KeyWord},
	{"\\bin\\b", CodeStyleFormat::KeyWord},
	{"\\bis\\b", CodeStyleFormat::KeyWord},
	{"\\blib\\b", CodeStyleFormat::KeyWord},
	{"\\bload\\b", CodeStyleFormat::KeyWord},
	{"\\bmembersof\\b", CodeStyleFormat::KeyWord},
	{"\\bnone\\b", CodeStyleFormat::KeyWord},
	{"\\bnot\\b", CodeStyleFormat::KeyWord},
	{"\\bnull\\b", CodeStyleFormat::KeyWord},
	{"\\bor\\b", CodeStyleFormat::KeyWord},
	{"\\bpackage\\b", CodeStyleFormat::KeyWord},
	{"\\bprint\\b", CodeStyleFormat::KeyWord},
	{"\\braise\\b", CodeStyleFormat::KeyWord},
	{"\\breturn\\b", CodeStyleFormat::KeyWord},
	{"\\bswitch\\b", CodeStyleFormat::KeyWord},
	{"\\btrue\\b", CodeStyleFormat::KeyWord},
	{"\\btry\\b", CodeStyleFormat::KeyWord},
	{"\\btypeof\\b", CodeStyleFormat::KeyWord},
	{"\\bwhile\\b", CodeStyleFormat::KeyWord},
	{"\\bxor\\b", CodeStyleFormat::KeyWord},
	{"\\byield\\b", CodeStyleFormat::KeyWord},
	{"\\bself\\b", CodeStyleFormat::KeyWord},
	{"\\bva_args\\b", CodeStyleFormat::KeyWord},
	{"\".*\"", CodeStyleFormat::String},
	{"'.*'", CodeStyleFormat::String},
	{"\\b\\d+\\.\\d*\\b", CodeStyleFormat::Number},
	{"\\b\\d+\\b", CodeStyleFormat::Number},
	{"\\b0x[0-9a-fA-F]+\\b", CodeStyleFormat::Number},
	{"\\b0b[0-1]+\\b", CodeStyleFormat::Number},
	{"\\.{2,3}", CodeStyleFormat::None},
	{"\\/\\/.*$", CodeStyleFormat::Comment},
	{"#!.*$", CodeStyleFormat::Comment},
	{QRegularExpression("\\/\\*(\\*(?!\\/)|[^*])*\\*\\/", QRegularExpression::MultilineOption), CodeStyleFormat::Comment},
};

MintHighlighter::MintHighlighter(QTextDocument *parent) :
	QSyntaxHighlighter (parent) {

}

void MintHighlighter::highlightBlock(const QString &text) {

	for (const HighlightRule &rule : Rules) {

		QRegularExpressionMatchIterator matchIterator = rule.match(text);

		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			setFormat(match.capturedStart(), match.capturedLength(), rule.format());
		}
	}
}
