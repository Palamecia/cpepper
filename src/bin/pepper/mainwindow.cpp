#include "mainwindow.h"
#include "projectexplorerdockwidget.h"
#include "code/abstracteditor.h"
#include "code/project.h"

#include "ui_mainwindow.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFile>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_ui(new Ui::MainWindow),
	m_projectExplorer(new ProjectExplorerDockWidget) {
	m_ui->setupUi(this);

	m_projectExplorer->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::LeftDockWidgetArea, m_projectExplorer.data());
	connect(m_projectExplorer.data(), &ProjectExplorerDockWidget::showEditor, this, &MainWindow::setEditor);

	connect(m_ui->actionOpenProject, &QAction::triggered, this, &MainWindow::openProject);
	connect(m_ui->actionOpen, &QAction::triggered, this, &MainWindow::openDocument);
	connect(m_ui->actionSave, &QAction::triggered, this, &MainWindow::saveCurrentEditor);
	connect(m_ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveCurrentEditorAs);
	connect(m_ui->actionSaveAll, &QAction::triggered, this, &MainWindow::saveModifiedEditors);
	connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);

	connect(m_ui->actionFullscreen, &QAction::triggered, this, &MainWindow::setFullscreen);

	connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);

	///// TEST
	if (qApp->arguments().count() == 2) {
		m_projectExplorer->openProject(qApp->arguments().at(1));
	}
	/////
}

MainWindow::~MainWindow() {

}

void MainWindow::setEditor(AbstractEditor *editor) {

	if (QWidget *previous = takeCentralWidget()) {
		disconnect(previous, &QWidget::destroyed, this, &MainWindow::resetEditor);
	}

	if (editor) {

		setWindowTitle(QString("%1 - %2").arg(qAppName()).arg(editor->document().fileName()));
		setCentralWidget(editor);

		connect(editor, &QWidget::destroyed, this, &MainWindow::resetEditor);

		m_ui->actionSave->setEnabled(editor);
		m_ui->actionSaveAs->setEnabled(editor);
		m_ui->actionSaveAll->setEnabled(true);
	}
	else {
		resetEditor();
	}
}

void MainWindow::resetEditor() {

	setWindowTitle(qAppName());
	/// \todo custom widget
	setCentralWidget(new QWidget(this));

	m_ui->actionSave->setEnabled(false);
	m_ui->actionSaveAs->setEnabled(false);
	m_ui->actionSaveAll->setEnabled(true);
}

void MainWindow::openProject() {

	QString dir = QDir::homePath();

	if (Project *project = Project::activeProject()) {
		dir = project->getPath();
	}

	QString path = QFileDialog::getExistingDirectory(this, tr("Open project"), dir);

	if (!path.isEmpty()) {
		m_projectExplorer->openProject(path);
	}
}

void MainWindow::openDocument() {

	QString dir = QDir::homePath();

	if (Project *project = Project::activeProject()) {
		dir = project->getPath();
	}

	QString path = QFileDialog::getOpenFileName(this, tr("Open document"), dir, "*.mn");

	if (!path.isEmpty()) {
		m_projectExplorer->openDocument(path);
	}
}

void MainWindow::saveCurrentEditor() {

	if (AbstractEditor *editor = dynamic_cast<AbstractEditor *>(centralWidget())) {
		editor->save();
	}
}

void MainWindow::saveCurrentEditorAs() {

	if (AbstractEditor *editor = dynamic_cast<AbstractEditor *>(centralWidget())) {

		QString dir = editor->document().absoluteFilePath();
		QString path = QFileDialog::getSaveFileName(this, tr("Save document as"), dir, "*.mn");

		if (!path.isEmpty()) {
			editor->saveAs(path);
		}
	}
}

void MainWindow::saveModifiedEditors() {

	for (AbstractEditor *editor : m_projectExplorer->editors()) {
		editor->save();
	}
}

void MainWindow::setFullscreen(bool enabled) {

	if (enabled) {
		m_previousWindowState = windowState();
		showFullScreen();
	}
	else {
		setWindowState(m_previousWindowState);
	}
}

void MainWindow::showAboutDialog() {
	QMessageBox::about(this, tr("About %1").arg(qAppName()),
					   tr("<b>%1</b>").arg(qAppName()));
}
