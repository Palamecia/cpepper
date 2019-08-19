#include "projecttreeitem.h"
#include "code/project.h"
#include "code/documenteditor.h"

#include <QtWidgets/QFileIconProvider>
#include <QtWidgets/QMenu>
#include <QtCore/QDir>

static QFileIconProvider g_iconProvider;

ProjectTreeItem::ProjectTreeItem(const QString &label, QObject *parent) :
	QObject(parent),
	QTreeWidgetItem({label}) {

}

ProjectRootItem::ProjectRootItem(const QDir &directory) :
	ProjectTreeItem (directory.dirName()),
	m_project(new Project(directory)) {
	connect(m_project, &Project::activeChanged, this, &ProjectRootItem::setActive);
}

ProjectRootItem::~ProjectRootItem() {
	delete m_project;
}

QMenu *ProjectRootItem::contextMenu() {

	QMenu *menu = new QMenu;

	menu->addAction(tr("Set as active project"), [this] { setActive(true); });
	menu->addSeparator();
	menu->addAction(tr("Close"), [this] { deleteLater(); });

	return menu;
}

void ProjectRootItem::open() {

}

void ProjectRootItem::setActive(bool active) {

	QFont f = font(0);
	f.setBold(active);
	setFont(0, f);

	Project::setActiveProject(m_project);
}

ProjectDirectoryItem::ProjectDirectoryItem(const QDir &directory) :
	ProjectTreeItem(directory.dirName()) {
	setIcon(0, g_iconProvider.icon(QFileIconProvider::Folder));
	setToolTip(0, directory.absolutePath());
}

QMenu *ProjectDirectoryItem::contextMenu() {
	return nullptr;
}

void ProjectDirectoryItem::open() {

}

ProjectFileItem::ProjectFileItem(const QFileInfo &file) :
	ProjectTreeItem(file.fileName()),
	m_file(file) {
	setIcon(0, g_iconProvider.icon(file));
	setToolTip(0, file.absoluteFilePath());
}

QMenu *ProjectFileItem::contextMenu() {
	return nullptr;
}

void ProjectFileItem::open() {
	emit openDocument(m_file);
}

DocumentItem::DocumentItem(const QFileInfo &document) :
	ProjectTreeItem(document.fileName()),
	m_editor(new DocumentEditor(document)) {
	setToolTip(0, document.absoluteFilePath());
	setFlags((flags() | Qt::ItemNeverHasChildren) & ~Qt::ItemIsSelectable);

	m_editor->installEventFilter(this);
	connect(m_editor, &DocumentEditor::modificationChanged, [this] (bool changed) {
		setText(0, m_editor->document().fileName() + (changed ? QChar('*') : QChar()));
	});
}

DocumentItem::~DocumentItem() {
	delete m_editor;
}

QMenu *DocumentItem::contextMenu() {

	QMenu *menu = new QMenu;

	menu->addAction(tr("Save"), this, &DocumentItem::save);
	menu->addAction(tr("Save as"), this, &DocumentItem::saveAs);
	menu->addSeparator();
	menu->addAction(tr("Close"), [this] { emit closeDocument(m_editor->document()); });

	return menu;
}

void DocumentItem::open() {
	emit showEditor(m_editor);
}

DocumentEditor *DocumentItem::editor() const {
	return m_editor;
}

void DocumentItem::save() {
	m_editor->save();
}

void DocumentItem::saveAs() {

	QString dir = m_editor->document().absoluteFilePath();
	QString path = QFileDialog::getSaveFileName(QApplication::activeWindow(), tr("Save document as"), dir, "*.mn");

	if (!path.isEmpty()) {
		m_editor->saveAs(path);
	}
}

bool DocumentItem::eventFilter(QObject *object, QEvent *event) {

	switch (event->type()) {
	case QEvent::Hide:
		setActive(false);
		break;

	case QEvent::Show:
		setActive(true);
		break;

	default:
		break;
	}

	return QObject::eventFilter(object, event);
}

void DocumentItem::setActive(bool active) {

	QFont f = font(0);
	f.setUnderline(active);
	setFont(0, f);
}
