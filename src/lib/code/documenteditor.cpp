#include "code/documenteditor.h"
#include "codeeditor.h"

DocumentEditor::DocumentEditor(const QFileInfo &document, QWidget *parent) :
	AbstractEditor(parent),
	m_document(document),
	m_codeEditor(new CodeEditor(this)) {

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(new QLabel(document.fileName(), this)); /// \todo add header
	layout->addWidget(m_codeEditor);
	setLayout(layout);

	QFile file(m_document.absoluteFilePath());

	if (file.open(QFile::Text | QFile::ReadOnly)) {
		m_codeEditor->setPlainText(file.readAll());
	}

	connect(m_codeEditor, &CodeEditor::modificationChanged, this, &DocumentEditor::modificationChanged);
}

QFileInfo DocumentEditor::document() const {
	return m_document;
}

bool DocumentEditor::saveAs(const QString &path) {

	QFile file(path);
	QTextStream stream(&file);

	if (file.open(QFile::Text | QFile::WriteOnly)) {
		stream << m_codeEditor->toPlainText();
		m_codeEditor->document()->setModified(false);
		return true;
	}

	return false;
}

bool DocumentEditor::save() {
	return saveAs(m_document.absoluteFilePath());
}
