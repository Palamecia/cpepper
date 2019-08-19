#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore/QObject>
#include <QtCore/QDir>

class Project : public QObject {
	Q_OBJECT
public:
	Project(const QDir &directory);
	~Project() override;

	static Project *activeProject();
	static void setActiveProject(Project *project);

	QString getPath() const;

signals:
	void activeChanged(bool active);

private:
	QDir m_directory;
};

#endif // PROJECT_H
