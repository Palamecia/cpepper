#include "highlight/codestylemanager.h"

CodeStyleManager::CodeStyleManager() {

}

CodeStyleManager &CodeStyleManager::instance() {
	static CodeStyleManager g_instance;
	return g_instance;
}

QTextCharFormat CodeStyleManager::format(CodeStyleFormat f) const {

	QTextCharFormat codeStyleFormat;

	/// \todo Use user defined color scheme

	switch (f) {
	case CodeStyleFormat::None:
		return QTextCharFormat();

	case CodeStyleFormat::Comment:
		codeStyleFormat.setForeground(Qt::gray);
		codeStyleFormat.setFontItalic(true);
		break;

	case CodeStyleFormat::KeyWord:
		codeStyleFormat.setForeground(QColor("#45c6d6"));
		codeStyleFormat.setFontItalic(true);
		break;

	case CodeStyleFormat::Number:
		codeStyleFormat.setForeground(QColor("#8a602c"));
		break;

	case CodeStyleFormat::String:
		codeStyleFormat.setForeground(QColor("#d69545"));
		break;
	}

	return codeStyleFormat;
}
