#ifndef CODESTYLEMANAGER_H
#define CODESTYLEMANAGER_H

#include <QtGui/QTextCharFormat>

enum class CodeStyleFormat {
	None,
	Comment,
	KeyWord,
	Number,
	String,
};

class CodeStyleManager {
public:
	static CodeStyleManager &instance();

	QTextCharFormat format(CodeStyleFormat f) const;

private:
	CodeStyleManager();
	CodeStyleManager(const CodeStyleManager &other) = delete;
	CodeStyleManager &operator =(const CodeStyleManager &other) = delete;
};

#endif // CODESTYLEMANAGER_H
