#include "codemodel/mintcodemodel.h"

MintCodeModel::MintCodeModel(QTextDocument *parent) :
	m_highlighter(new MintHighlighter(parent)) {

}

QSyntaxHighlighter *MintCodeModel::highlighter() const {
	return m_highlighter.data();
}
