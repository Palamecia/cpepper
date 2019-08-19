#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QtWidgets/QWidget>

class CodeEditor;

class LineNumberArea : public QWidget {
	Q_OBJECT
public:
	LineNumberArea(CodeEditor *editor);

	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	CodeEditor *m_codeEditor;
};

#endif // LINENUMBERAREA_H
