#ifndef PROJECTEXPLORERDOCKWIDGET_H
#define PROJECTEXPLORERDOCKWIDGET_H

#include <QtWidgets/QDockWidget>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QMap>
#include <QtCore/QDir>

namespace Ui {
class ProjectExplorerDockWidget;
}

class AbstractEditor;

class ProjectExplorerDockWidget : public QDockWidget {
	Q_OBJECT
public:
	explicit ProjectExplorerDockWidget(QWidget *parent = nullptr);
	~ProjectExplorerDockWidget();

	QList<AbstractEditor *> editors();

signals:
	void showEditor(AbstractEditor *editor);

public slots:
	void openProject(const QDir &project);
	void openDocument(const QFileInfo &document);
	void closeDocument(const QFileInfo &document);
	void closeAllDocuments();

private slots:
	void openItem(class QTreeWidgetItem *item);
	void openContextMenu(const QPoint &pos);

private:
	void parseProject(QTreeWidgetItem *parent, const QDir &dir);

	QScopedPointer<Ui::ProjectExplorerDockWidget> m_ui;
	QMap<QString, class DocumentItem *> m_documents;
	QFileSystemWatcher m_fileSystemWatcher;
	QTreeWidgetItem *m_projectsItem;
	QTreeWidgetItem *m_documentsItem;
};

#endif // PROJECTEXPLORERDOCKWIDGET_H
