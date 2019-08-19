#include "projectexplorerdockwidget.h"
#include "projecttreeitem.h"
#include "code/documenteditor.h"
#include "code/project.h"

#include "ui_projectexplorerdockwidget.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QMenu>

ProjectExplorerDockWidget::ProjectExplorerDockWidget(QWidget *parent) :
	QDockWidget(parent),
	m_ui(new Ui::ProjectExplorerDockWidget) {
	m_ui->setupUi(this);
	m_ui->treeWidget->expandAll();
	m_ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	/// \todo use custom header
	/// setTitleBarWidget(new ProjectExplorerTitleBar(this));

	connect(m_ui->treeWidget, &QTreeWidget::itemDoubleClicked, this, &ProjectExplorerDockWidget::openItem);
	connect(m_ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &ProjectExplorerDockWidget::openContextMenu);

	m_projectsItem = m_ui->treeWidget->topLevelItem(0);
	m_documentsItem = m_ui->treeWidget->topLevelItem(1);
}

ProjectExplorerDockWidget::~ProjectExplorerDockWidget() {

}

QList<AbstractEditor *> ProjectExplorerDockWidget::editors() {

	QList<AbstractEditor *> list;

	for (DocumentItem *item : m_documents) {
		list.append(item->editor());
	}

	return list;
}

void ProjectExplorerDockWidget::parseProject(QTreeWidgetItem *parent, const QDir &dir) {

	for (const QFileInfo &entry : dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot)) {
		if (entry.isDir()) {
			ProjectDirectoryItem *item = new ProjectDirectoryItem(entry.filePath());
			m_fileSystemWatcher.addPath(entry.absolutePath());
			parent->addChild(item);
			parseProject(item, entry.absoluteFilePath());
		}
		else if (entry.suffix() == "mn" || entry.suffix() == "txt") { /// \todo suffix filter based on editors factory
			ProjectFileItem *item = new ProjectFileItem(entry);
			connect(item, &ProjectFileItem::openDocument, this, &ProjectExplorerDockWidget::openDocument);
			parent->addChild(item);
		}
	}
}

void ProjectExplorerDockWidget::openProject(const QDir &project) {

	if (project.exists()) {
		ProjectRootItem *item = new ProjectRootItem(project);
		parseProject(item, project);
		if (m_projectsItem->childCount() == 0) {
			item->setActive(true);
		}
		m_projectsItem->addChild(item);
		m_ui->treeWidget->expandItem(item);
	}
}

void ProjectExplorerDockWidget::openDocument(const QFileInfo &document) {

	auto i = m_documents.find(document.absoluteFilePath());

	if (i != m_documents.end()) {
		i.value()->open();
	}
	else {
		DocumentItem *item = new DocumentItem(document);
		m_fileSystemWatcher.addPath(document.absoluteFilePath());
		m_documentsItem->addChild(item);
		m_documents.insert(document.absoluteFilePath(), item);
		connect(item, &DocumentItem::showEditor, this, &ProjectExplorerDockWidget::showEditor);
		connect(item, &DocumentItem::closeDocument, this, &ProjectExplorerDockWidget::closeDocument);
		item->open();
	}
}

void ProjectExplorerDockWidget::closeDocument(const QFileInfo &document) {

	auto i = m_documents.find(document.absoluteFilePath());

	if (i != m_documents.end()) {
		m_fileSystemWatcher.removePath(document.absoluteFilePath());
		m_documents.erase(i);
		delete i.value();
	}
}

void ProjectExplorerDockWidget::closeAllDocuments() {
	m_fileSystemWatcher.removePaths(m_documents.keys());
	qDeleteAll(m_documents);
}

void ProjectExplorerDockWidget::openItem(class QTreeWidgetItem *item) {

	if (ProjectTreeItem *projectItem = dynamic_cast<ProjectTreeItem *>(item)) {
		projectItem->open();
	}
}

void ProjectExplorerDockWidget::openContextMenu(const QPoint &pos) {

	if (ProjectTreeItem *projectItem = dynamic_cast<ProjectTreeItem *>(m_ui->treeWidget->itemAt(pos))) {
		if (QMenu *menu = projectItem->contextMenu()) {
			menu->exec(m_ui->treeWidget->mapToGlobal(pos));
			menu->deleteLater();
		}
	}
	else {
		QMenu menu;
		menu.addAction(tr("Close all documents"), this, &ProjectExplorerDockWidget::closeAllDocuments);
		menu.exec(m_ui->treeWidget->mapToGlobal(pos));
	}
}
