#include "code/project.h"

static Project *g_activeProject = nullptr;

Project::Project(const QDir &directory) :
	m_directory(directory) {

}

Project::~Project() {
	if (g_activeProject == this) {
		setActiveProject(nullptr);
	}
}

Project *Project::activeProject() {
	return g_activeProject;
}

void Project::setActiveProject(Project *project) {

	if (g_activeProject != project) {

		if (g_activeProject) {
			emit g_activeProject->activeChanged(false);
		}

		if ((g_activeProject = project)) {
			emit g_activeProject->activeChanged(true);
		}
	}
}

QString Project::getPath() const {
	return m_directory.absolutePath();
}
