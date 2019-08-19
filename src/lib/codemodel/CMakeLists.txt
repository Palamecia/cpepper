project(codemodel)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(${PROJECT_NAME}_SRC
	abstractcodemodel.cpp
	mintcodemodel.cpp
)

set(${PROJECT_NAME}_MOC
	${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/mintcodemodel.h
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
	highlight
	Qt5::Core
)
