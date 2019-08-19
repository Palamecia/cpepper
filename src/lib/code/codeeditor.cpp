#include "codeeditor.h"
#include "linenumberarea.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QPainter>
#include <QtGui/QTextBlock>
#include <QtWidgets/QLayout>

/// \todo Use code model factory
#include "codemodel/mintcodemodel.h"

CodeEditor::CodeEditor(QWidget *parent) :
	QPlainTextEdit(parent),
	m_lineNumberArea(new LineNumberArea(this)),
	m_codeModel(new MintCodeModel(document())) {

	connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
	connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
	connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

	updateLineNumberAreaWidth(0);
	highlightCurrentLine();

	/// TEST
	setFont(QFont("Monospace"));
	setTabStopDistance(QFontMetricsF(font()).width(' ') * 4);
	///
}

int CodeEditor::lineNumberAreaWidth() {

	int digits = 1;
	int max = qMax(1, blockCount());

	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 18 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

	return qMax(space, 50);
}

void CodeEditor::updateLineNumberAreaWidth(int newBlockCount) {

	Q_UNUSED(newBlockCount)

	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy) {

	if (dy) {
		m_lineNumberArea->scroll(0, dy);
	}
	else {
		m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());
	}

	if (rect.contains(viewport()->rect())) {
		updateLineNumberAreaWidth(0);
	}
}

void CodeEditor::resizeEvent(QResizeEvent *event) {

	QPlainTextEdit::resizeEvent(event);

	QRect cr = contentsRect();
	m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine() {

	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		QColor lineColor = "#303132"; /// \todo color from code style colors

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {

	QPainter painter(m_lineNumberArea);
	painter.fillRect(event->rect(), "#555555");

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
	int bottom = top + static_cast<int>(blockBoundingRect(block).height());

	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(palette().windowText().color());
			painter.drawText(0, top, m_lineNumberArea->width() - 15, fontMetrics().height(), Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + static_cast<int>(blockBoundingRect(block).height());
		++blockNumber;
	}
}
