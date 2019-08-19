#ifndef ABSTRACTEDITOR_H
#define ABSTRACTEDITOR_H

#include <QtWidgets/QtWidgets>

class AbstractEditor : public QWidget {
public:
	AbstractEditor(QWidget *parent = nullptr);

	virtual QFileInfo document() const = 0;

	virtual bool saveAs(const QString &path) = 0;
	virtual bool save() = 0;
};

#endif // ABSTRACTEDITOR_H
