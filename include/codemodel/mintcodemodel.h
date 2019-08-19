#ifndef MINTCODEMODEL_H
#define MINTCODEMODEL_H

#include <QtCore/QScopedPointer>

#include "codemodel/abstractcodemodel.h"
#include "highlight/minthighlighter.h"

class MintCodeModel : public AbstractCodeModel {
public:
	MintCodeModel(QTextDocument *parent = nullptr);

	QSyntaxHighlighter *highlighter() const override;

private:
	QScopedPointer<MintHighlighter> m_highlighter;
};

#endif // MINTCODEMODEL_H
