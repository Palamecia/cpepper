#ifndef PROJECTTREEITEM_H
#define PROJECTTREEITEM_H

#include <QtWidgets/QTreeWidgetItem>
#include <QtCore/QFileInfo>

class Project;
class DocumentEditor;

class ProjectTreeItem : public QObject, public QTreeWidgetItem {
public:
	ProjectTreeItem(const QString &label, QObject *parent = nullptr);

	virtual QMenu *contextMenu() = 0;
	virtual void open() = 0;
};

class ProjectRootItem : public ProjectTreeItem {
	Q_OBJECT
public:
	ProjectRootItem(const QDir &directory);
	~ProjectRootItem() override;

	QMenu *contextMenu() override;
	void open() override;

public slots:
	void setActive(bool active);

private:
	Project *m_project;
};

class ProjectDirectoryItem : public ProjectTreeItem {
public:
	ProjectDirectoryItem(const QDir &directory);

	QMenu *contextMenu() override;
	void open() override;
};

class ProjectFileItem : public ProjectTreeItem {
	Q_OBJECT
public:
	ProjectFileItem(const QFileInfo &file);

	QMenu *contextMenu() override;
	void open() override;

signals:
	void openDocument(const QFileInfo &document);

private:
	QFileInfo m_file;
};

class DocumentItem : public ProjectTreeItem {
	Q_OBJECT
public:
	DocumentItem(const QFileInfo &document);
	~DocumentItem() override;

	QMenu *contextMenu() override;
	void open() override;

	DocumentEditor *editor() const;

signals:
	void showEditor(DocumentEditor *editor);
	void closeDocument(const QFileInfo &document);

public slots:
	void save();
	void saveAs();

protected:
	bool eventFilter(QObject *object, QEvent *event) override;

private:
	void setActive(bool active);

	DocumentEditor *m_editor;
};

#endif // PROJECTTREEITEM_H
