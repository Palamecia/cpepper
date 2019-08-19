#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include "code/abstracteditor.h"

#include <QtCore/QFileInfo>

class CodeEditor;

class DocumentEditor : public AbstractEditor {
	Q_OBJECT
public:
	explicit DocumentEditor(const QFileInfo &document, QWidget *parent = nullptr);

	QFileInfo document() const override;

	bool saveAs(const QString &path) override;
	bool save() override;

signals:
	void modificationChanged(bool);

private:
	QFileInfo m_document;
	CodeEditor *m_codeEditor;
};

#endif // DOCUMENTEDITOR_H
