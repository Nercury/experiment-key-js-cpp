project(key-opengl)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-opengl STATIC 
	lib_key_opengl.h
	GLRenderer.h
	GLRenderer.cpp
	GLWindow.h
	GLWindow.cpp
	)

target_link_libraries(key-opengl 
	key-common
	key-window
	${SDL_LIBRARY}
	${OPENGL_LIBRARY}
	)