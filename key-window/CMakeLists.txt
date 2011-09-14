project(key-window)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-window STATIC 
	lib_key_window.h
	Window.h
	Window.cpp
	SsWindow.hpp
	)

target_link_libraries(key-window 
	key-common
	${SDL_LIBRARY}
	)