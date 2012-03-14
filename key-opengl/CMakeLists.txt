project(key-opengl)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-opengl STATIC 
	lib_key_opengl.h
	GLRenderer.h
	GLRenderer.cpp
	SDLWindowInfo.h
	SDLWindowInfo.cpp
	GLOp.h
	sdl_gl_headers.h
	)

target_link_libraries(key-opengl 
	key-common
	key-window
	key-render
	${SDL_LIBRARY}
	${OPENGL_LIBRARY}
	)