project(code)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(${PROJECT_NAME}_SRC
	abstracteditor.cpp
	codeeditor.cpp
	documenteditor.cpp
	linenumberarea.cpp
	project.cpp
)

set(${PROJECT_NAME}_MOC
	${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/documenteditor.h
	${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/project.h
	codeeditor.h
	linenumberarea.h
)

# set(${PROJECT_NAME}_UI
#
# )

qt5_wrap_cpp(${PROJECT_NAME}_MOCING ${${PROJECT_NAME}_MOC})
# qt5_wrap_ui(${PROJECT_NAME}_UICING ${${PROJECT_NAME}_UI})

add_library(
	${PROJECT_NAME}
	${${PROJECT_NAME}_SRC}
	${${PROJECT_NAME}_MOCING}
	# ${${PROJECT_NAME}_UICING}
)

target_link_libraries(
	${PROJECT_NAME}
	codemodel
	Qt5::Widgets
)
