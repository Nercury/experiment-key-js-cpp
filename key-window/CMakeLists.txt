project(key-window)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-window STATIC 
	lib_key_window.h
	Renderer.h
	Renderer.cpp
	Window.h
	Window.cpp
	MouseMotion.h
	MouseMotion.cpp
	KeyCode.h
	KeyCode.cpp
	ScanCode.h
	ScanCode.cpp
	KeyEvent.h
	KeyEvent.cpp
	DrawTree.h
	DrawTree.cpp
	DrawSequence.h
	DrawSequence.cpp
	Translate.h
	Translate.cpp
	)

target_link_libraries(key-window 
	key-common
	key-v8
	key-render
	)