#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QScopedPointer>

class ProjectExplorerDockWidget;
class AbstractEditor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void setEditor(AbstractEditor *editor);
	void resetEditor();
	void openProject();
	void openDocument();
	void saveCurrentEditor();
	void saveCurrentEditorAs();
	void saveModifiedEditors();

	void setFullscreen(bool enabled);

	void showAboutDialog();

private:
	QScopedPointer<Ui::MainWindow> m_ui;
	QScopedPointer<ProjectExplorerDockWidget> m_projectExplorer;
	Qt::WindowStates m_previousWindowState;
};

#endif // MAINWINDOW_H
