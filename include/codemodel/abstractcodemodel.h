#ifndef ABSTRACTCODEMODEL_H
#define ABSTRACTCODEMODEL_H

class QSyntaxHighlighter;

class AbstractCodeModel {
public:
	AbstractCodeModel();

	virtual QSyntaxHighlighter *highlighter() const = 0;
};

#endif // ABSTRACTCODEMODEL_H
