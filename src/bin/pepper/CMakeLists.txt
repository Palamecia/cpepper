project(pepper)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(${PROJECT_NAME}_SRC
	main.cpp
	mainwindow.cpp
	projectexplorerdockwidget.cpp
	projecttreeitem.cpp
)

set(${PROJECT_NAME}_MOC
	mainwindow.h
	projectexplorerdockwidget.h
	projecttreeitem.h
)

set(${PROJECT_NAME}_UI
	ui/mainwindow.ui
	ui/projectexplorerdockwidget.ui
)

qt5_wrap_cpp(${PROJECT_NAME}_MOCING ${${PROJECT_NAME}_MOC})
qt5_wrap_ui(${PROJECT_NAME}_UICING ${${PROJECT_NAME}_UI})
qt5_add_resources(${PROJECT_NAME}_QRC ${PROJECT_DATA_DIR}/resources.qrc)

add_executable(
	${PROJECT_NAME}
	${${PROJECT_NAME}_SRC}
	${${PROJECT_NAME}_QRC}
	${${PROJECT_NAME}_MOCING}
	${${PROJECT_NAME}_UICING}
)

target_link_libraries(
	${PROJECT_NAME}
	Qt5::Widgets
	highlight
	codemodel
	code
)
